#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &)
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &)
{
    return *this;
}

ScalarConverter::~ScalarConverter() {}

bool is_char(const std::string &str)
{
    if (str.length() == 1)
        return true;
    return false;
}

size_t count_occurence(const std::string &str, const char c)
{
    size_t count;

    count = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == c)
            count++;
    }
    return count;
}

bool is_number(const std::string &str)
{
    if (str.find_first_not_of("0123456789+-.fe") != std::string::npos)
        return false;
    if (count_occurence(str, 'e') > 1)
        return false;
    else if ((str.find("e") != std::string::npos && (str.find("e+") == std::string::npos && str.find("e-") == std::string::npos)) || str[0] == 'e' || !isdigit(str[str.find("e") + 2]))
        return false;
    else if (str.find("e+") != std::string::npos && str.find(".")== std::string::npos)
        return false;// "2e+10 -> false"
    if (count_occurence(str, '+') > 2)
        return false;
    else if (count_occurence(str, '+') == 1 && str.find("+") != 0 && str[str.find("+") - 1] != 'e')
        return false;
    else if (count_occurence(str, '+') == 2 && (str[0] != '+' || str[str.find("+") - 1] != 'e'))
        return false;
    if (count_occurence(str, '-') > 2)
        return false;
    else if (count_occurence(str, '-') == 1 && str.find("-") != 0 && str[str.find("-") - 1] != 'e')
        return false;
    else if (count_occurence(str, '-') == 2 && (str[0] != '-' || str[str.find("-") - 1] != 'e'))
        return false;
    if (count_occurence(str, '.') > 1)
        return false;
    else if (count_occurence(str, '.') == 1 && (str[0] == '.' || !isdigit(str[str.find(".") + 1]) || str[str.find_first_of(".e")] == 'e'))
        return false;
    if (count_occurence(str, 'f') > 1 || (count_occurence(str, 'f') == 1 && str[str.size() - 1] != 'f'))
        return false;
    return true;
}

bool is_int(const std::string &str)
{
    return is_number(str);
}

bool is_float(const std::string &str)
{
    if (str == "nan" || str == "+inff" || str == "-inff")
        return true;
    if (is_number(str))
        return true;
    if (str.find(".") == std::string::npos)
        return false;
    return false;
}

bool is_double(const std::string &str)
{
    if (str == "nan" || str == "+inf" || str == "-inf")
        return true;
    if (is_number(str))
        return true;
    if (str.find(".") == std::string::npos || str.find("f") != std::string::npos)
        return false;
    return false;
}

bool is_nan_float(float f)
{
	return (f != f);
}

bool is_nan_double(double d)
{
	return (d != d);
}

bool is_inf_float(float f)
{
	return (f == std::numeric_limits<float>::infinity() || f == -std::numeric_limits<float>::infinity());
}

bool is_inf_double(double d)
{
	return (d == std::numeric_limits<double>::infinity() || d == -std::numeric_limits<double>::infinity());
}

std::string detect_types(const std::string &str)
{
    if (is_char(str))
        return "char";
    else if (is_int(str))
        return "int";
    else if (is_float(str))
        return "float";
    else if (is_double(str))
        return "double";
    return "impossible";
}

void convert_char(const char &c)
{
    if (isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

void convert_int(long &n)
{
    if (std::numeric_limits<char>::min() <= n && std::numeric_limits<char>::max() >= n)
    {
        if (isprint(static_cast<int>(n)))
            std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    if (std::numeric_limits<int>::min() <= n && std::numeric_limits<int>::max() >= n)
        std::cout << "int: " << static_cast<int>(n) << std::endl;
    else
        std::cout << "int: impossible" << std::endl;
    if (1000000 <= n || -1000000 >= n)
        std::cout << "float: " << static_cast<float>(n) << "f" << std::endl;
    else
        std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(n) << "f" << std::endl;
    if (1000000 <= n || -1000000 >= n)
        std::cout << "double: " << static_cast<double>(n) << std::endl;
    else
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(n) << std::endl;
}

void convert_float(float &f)
{
    if (std::numeric_limits<char>::min() <= f && std::numeric_limits<char>::max() >= f)
    {
        if (isprint(static_cast<int>(f)))
            std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    if (std::numeric_limits<int>::min() <= f && std::numeric_limits<int>::max() >= f)
        std::cout << "int: " << static_cast<int>(f) << std::endl;
    else
        std::cout << "int: impossible" << std::endl;
    if (1000000.0 <= f || -1000000.0 >= f || is_nan_float(f) || is_inf_float(f))
        std::cout << "float: " << static_cast<float>(f) << "f" << std::endl;
    else
        std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(f) << "f" << std::endl;
    if (1000000.0 <= f || -1000000.0 >= f || is_nan_float(f) || is_inf_float(f))
        std::cout << "double: " << static_cast<double>(f) << std::endl;
    else
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
}

void convert_double(double &d)
{
    if (std::numeric_limits<char>::min() <= d && std::numeric_limits<char>::max() >= d)
    {
        if (isprint(static_cast<int>(d)))
            std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    if (std::numeric_limits<int>::min() <= d && std::numeric_limits<int>::max() >= d)
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    else
        std::cout << "int: impossible" << std::endl;
    if (1000000.0 <= d || -1000000.0 >= d || is_nan_double(d) || is_inf_double(d))
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
    else
        std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
    if (1000000.0 <= d || -1000000.0 >= d || is_nan_double(d) || is_inf_double(d))
        std::cout << "double: " << d << std::endl;
    else
        std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void ScalarConverter::convert(const std::string &str)
{
    int i;
    std::string type;
    std::string types_table[] = {"char", "int", "float", "double"};
    type = detect_types(str);

    for (i = 0; i < 4; i++)
    {
        if (type == types_table[i])
            break;
    }
    switch (i)
    {
    case 0:
    {
        char c = static_cast<char>(str[0]);
        convert_char(c);
        break;
    }
    case 1:
    {
        long n = strtol(str.c_str(), NULL, 10);
        convert_int(n);
        break;
    }
    case 2:
    {
        float f;
        if (str == "nanf")
            f = std::numeric_limits<float>::quiet_NaN();
        else if (str == "+inff")
            f = std::numeric_limits<float>::infinity();
        else if (str == "-inff")
            f = -1 * std::numeric_limits<float>::infinity();
        else
            f = strtof(str.c_str(), NULL);
        convert_float(f);
        break;
    }
    case 3:
    {
        double d;
        if (str == "nan")
            d = std::numeric_limits<double>::quiet_NaN();
        else if (str == "+inf")
            d = std::numeric_limits<double>::infinity();
        else if (str == "-inf")
            d = -std::numeric_limits<double>::infinity();
        else
            d = strtod(str.c_str(), NULL);
        convert_double(d);
        break;
    }
    default:
        std::cout << "The type conversion is impossible" << std::endl;
    }
}
