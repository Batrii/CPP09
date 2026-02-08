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
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = line.substr(0, commaPos);
            std::stringstream doubleValue;
            doubleValue << line.substr(commaPos + 1);
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
    // int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
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
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (pipePos != std::string::npos)
        {
            std::string date = line.substr(0, pipePos - 1);
            std::string valueStr = line.substr(pipePos + 2);
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