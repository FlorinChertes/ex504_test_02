#ifndef _SUT_H_
#define _SUT_H_

#include "doc.h"

#include <iostream>

//-----------------------------------------------------------------------------
class SUT {
public:
    
    SUT(DOC& doc) : doc_(doc) {}
    
    bool foo(bool, bool);
    bool bar(bool, bool);

private:
    DOC& doc_;
};

//-----------------------------------------------------------------------------
class SUT_t {
public:

    SUT_t(DOC_t<int>& doc) : doc_(doc) {}

    bool foo(bool, bool);
    bool bar(bool, bool);

private:
    DOC_t<int>& doc_;
};

//-----------------------------------------------------------------------------
template<typename T>
class SUT_f {
public:

    SUT_f(T& doc) : doc_(doc) {}

    bool foo(bool param_1, bool param_2)
    {
        if (param_1 && param_2)
        {
            std::cout << doc_.foo() << std::endl;
            return true;
        }

        return false;
    }

    bool bar(bool param_1, bool param_2)
    {
        if (param_1 && param_2)
        {
            std::cout << doc_.bar() << std::endl;
            return true;
        }

        return false;
    }

private:
    T& doc_;
};


#endif

