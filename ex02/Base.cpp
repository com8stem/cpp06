#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base()
{
}

Base *generate()
{
    srand(time(NULL));
    int r = rand() % 10;
    if (r >= 0 && r < 3)
        return new A();
    else if (r >= 3 && r < 6)
        return new B();
    else
        return new C();
}

void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "class is A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "class is B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "class is C" << std::endl;
    else
        std::cout << "can't identify" << std::endl;
}

void identify(Base &p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "class is A" << std::endl;
        return;
    }
    catch (std::exception &)
    {
    }
    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "class is B" << std::endl;
        return;
    }
    catch (std::exception &)
    {
    }
    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "class is C" << std::endl;
        return;
    }
    catch (std::exception &)
    {
        std::cout << "can't identify" << std::endl;
    }
}