
#include "sut.h"
#include <iostream>
    
bool SUT::foo(bool param_1, bool param_2)
{
    if(param_1 && param_2)
    {
        std::cout << doc_.foo() << std::endl;
        return true;
    }
    
    return false;
}

bool SUT::bar(bool param_1, bool param_2)
{
    if(param_1 && param_2)
    {
        std::cout << doc_.bar() << std::endl;
        return true;
    }
    
    return false;
}

