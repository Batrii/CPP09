#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadExchangeRates("data.csv");
}

BitcoinExchange::BitcoinExchange(std::string filename)
{
    loadExchangeRates(filename);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    exchangeRates = other.exchangeRates;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        exchangeRates = other.exchangeRates;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange()
{
}


static std::string trim(std::string &str)
{
    size_t i = 0;
    size_t j = str.length() - 1;
    while (i < str.length() && std::isspace(str[i]))
        i++;
    while (j > i && std::isspace(str[j]))
        j--;
    return str.substr(i, j - i + 1);
}
void BitcoinExchange::loadExchangeRates(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open exchange rates file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("date") != std::string::npos)
            continue;
        std::string trimmedLine = trim(line);
        size_t commaPos = trimmedLine.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = trimmedLine.substr(0, commaPos);
            std::stringstream doubleValue;
            doubleValue << trimmedLine.substr(commaPos + 1);
            double rate;
            doubleValue >> rate;
            exchangeRates[date] = rate;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear))
            return false;
    }
    return true;
}

int BitcoinExchange::isValidValue(const std::string& valueStr, double& value)
{
    std::stringstream ss(valueStr);
    ss >> value;
    if (ss.fail() || !ss.eof())
        return 0;
    if (value < 0)
    {
        std::cerr << "Error: not a positive number. " << std::endl;
        return 0;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number. " << std::endl;
        return 0;
    }

    return 1;
}

void BitcoinExchange::processInputFile(const std::string& inputFile)
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open input file: " << inputFile << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("date") != std::string::npos)
            continue;
        std::string trimmedLine = trim(line);
        size_t pipePos = trimmedLine.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (pipePos != std::string::npos)
        {
            std::string dateStr = trimmedLine.substr(0, pipePos);
            std::string date = trim(dateStr);
            std::string valPart = trimmedLine.substr(pipePos + 1);
            std::string valueStr = trim(valPart);
            double value;
            if (!isValidDate(date))
            {
                std::cerr << "Error: Invalid date => " << date << std::endl;
                continue;
            }
            if (isValidValue(valueStr, value) == 0)
                continue;
            std::map<std::string, double>::iterator it = exchangeRates.lower_bound(date);
            if (it == exchangeRates.end() || it->first != date)
            {
                if (it != exchangeRates.begin())
                    --it;
                else
                {
                    std::cerr << "Error: No exchange rate available for date => " << date << std::endl;
                    continue;
                }
            }
            double rate = it->second;
            double result = value * rate;
            std::cout << date << " => " << value << " = " << result << std::endl;
        }
    }
    file.close();
}