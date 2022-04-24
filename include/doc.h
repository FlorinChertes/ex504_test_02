#ifndef _DOC_H_
#define _DOC_H_

#include <string>

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

#endif
