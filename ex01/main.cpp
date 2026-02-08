#include <iostream>
#include <string>
#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    RPN rpn;
    int check = rpn.processInput(argv[1]);
    if (check != 0)
        return 1;
    return 0;
}