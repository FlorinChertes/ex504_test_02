#ifndef _DOC_H_
#define _DOC_H_

#include <string>
#include <iostream>

//-----------------------------------------------------------------------------
class DOC {
public:
    
    virtual std::string foo()
    {
        return "Hello world!";
    }
    
    virtual int bar()
    {
        return 153;
    }
};

//-----------------------------------------------------------------------------
template<typename T>
class DOC_t {
public:

    virtual std::string foo(T param)
    {
        std::cout << param << std::endl;
        return "Hello world!";
    }

    virtual int bar(T param)
    {
        std::cout << param << std::endl;
        return 153;
    }
};

//-----------------------------------------------------------------------------

class DOC_f {
public:

    std::string foo()
    {
        std::cout << "Hello world!" << std::endl;
        return "Hello world!";
    }

    int bar()
    {
        std::cout << 153 << std::endl;
        return 153;
    }
};


#endif
