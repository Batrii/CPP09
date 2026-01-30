#include <iostream>
#include <string>
#include "BitcoinExchange.hpp"


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    BitcoinExchange bitcoinExchange;
    bitcoinExchange.processInputFile(inputFile);
    return 0;
}