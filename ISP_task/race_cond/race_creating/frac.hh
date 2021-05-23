#ifndef FRAC__
#define FRAC__

#include <iostream>


class Obj final
{
    int numer_ = 0;
    int denom_ = 0;

    public:
    
    Obj(int numer, int denom) : numer_(numer), denom_(denom)
    {}

    int get_numer();

    int get_denom();
};


#endif /* FRAC__ */
