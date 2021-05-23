#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>



int main()
{

    std::ofstream frac_cc;
    frac_cc.open("frac.cc");

    std::string other_string
    {R"(
#include "frac.hh"

int Obj::get_numer() { return numer_; }
int Obj::get_denom() { return denom_; }

    )"};

    frac_cc << other_string;
    frac_cc.close();

    return 0;

    /*
    std::ofstream other_file{"some_obj.cc"};

    std::string other_string
    {R"(
        #include "some_obj.hh"

        int Obj::get_numer() { return numer_; }
        int Obj::get_denom() { return denom_; }

    )"};

    other_file << other_string;
    other_file.close();

    return 0;*/
}