#include "frac.hh"

int main()
{
    Obj obj1{1, 2};

    std::cout << "\nResult:\n";
    std::cout << obj1.get_numer() << "/" << obj1.get_denom() << std::endl;
    return 0;
}