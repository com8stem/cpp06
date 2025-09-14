#include "Base.hpp"

int main()
{
    Base* ptr = generate();

    identify(ptr);
    identify(*ptr);
    delete ptr;
}