#include <iostream>

#include <thread>

//! assembler __attribute__ only for turning of compiler optimizations
void __attribute__((noinline)) use(int num)
{
    asm("");
}

const int loop_lim = 1000000;

int x;


void race() 
{
    for (size_t i = 0; i < loop_lim; ++i)
    {
        x+= 1; 
        use(x);
    }
    
    for (size_t i = 0; i < loop_lim; ++i)
    {
        x-= 1;
        use(x);
    }
}

int main()
{
    std::thread thr1{race};
    std::thread thr2{race};
    thr1.join();
    thr2.join();


    std::cout << "\n\nnow x is " << x;

    return 0;
}
