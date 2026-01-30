#include "BitcoinExchange.hpp"

// BitcoinExchange::BitcoinExchange()

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
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open exchange rates file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find('date') != std::string::npos)
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

