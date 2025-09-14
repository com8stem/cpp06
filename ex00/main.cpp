#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
        ScalarConverter::convert(static_cast<std::string>(argv[1]));
    else
        std::cout << "usage: ./convert [number]" << std::endl;
}
