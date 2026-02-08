#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

class BitcoinExchange
{
    private:
        std::map<std::string, double> exchangeRates;

        void loadExchangeRates(const std::string& filename);
        bool isValidDate(const std::string& date);
        int isValidValue(const std::string& valueStr, double& value);
    public:
        BitcoinExchange();
        BitcoinExchange(std::string filename);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void processInputFile(const std::string& inputFile);
};
#endif