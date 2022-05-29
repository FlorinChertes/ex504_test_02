#ifndef _DOC_H_
#define _DOC_H_

#include <functional>

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


class ServicePoint
{
    using Handler = std::function<int(int)>;

public:

    inline int makeCall(std::string uri, int param, Handler handler)
    {
        const int respone{ handler(param) };

        std::cout << "Uri is: " << uri
            << " make a call: " << respone << std::endl;

        return 153;
    }

    inline int callOneReply(std::string uri, int param, Handler handler)
    {
        return makeCall(uri, param, handler);
    }

    template<typename T>
    inline int callOneReply( std::string uri, int param, T object, int(T::* handler)(int) )
    {
        return callOneReply(uri, param, std::bind(handler, object, std::placeholders::_1));
    }
};


#endif
