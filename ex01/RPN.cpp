#include "RPN.hpp"

RPN::RPN() : elements()
{
}
RPN::RPN(const RPN& other) : elements(other.elements)
{
}
RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        elements = other.elements;
    }
    return *this;
}
RPN::~RPN()
{
}

int RPN::processInput(const std::string& input){
    size_t i = 0;
    while (i < input.length())
    {
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        if (std::isdigit(input[i]))
        {
            elements.push(input[i] - '0');
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            if (elements.size() < 2)
            {
                std::cerr << "Error: not enough operands for operator '" << input[i] << "'." << std::endl;
                return 1;
            }
            int b = elements.top(); elements.pop();
            int a = elements.top(); elements.pop();
            int result;
            switch (input[i])
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                    {
                        std::cerr << "Error: division by zero." << std::endl;
                        return 1;
                    }
                    result = a / b; break;
                default:
                    std::cerr << "Error: unknown operator '" << input[i] << "'." << std::endl;
                    return 1;
            }
            elements.push(result);
        }
        else
        {
            std::cerr << "Error: invalid character '" << input[i] << "' in input." << std::endl;
            return 1;
        }
        i++;
    }
    if (elements.size() != 1)
    {
        std::cerr << "Error: invalid RPN expression, expected exactly one result but got " << elements.size() << "." << std::endl;
    }
    std::cout << "Result: " << elements.top() << std::endl;
    return 0;
}