#ifndef _SUT_H_
#define _SUT_H_

#include "doc.h"
#include <iostream>

class SUT {
public:
    
    SUT(DOC& doc) : doc_(doc) {}
    
    bool foo(bool, bool);
    bool bar(bool, bool);

private:
    DOC& doc_;
};

#endif

