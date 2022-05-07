#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace ::testing;

void foo()
{
    char* ptr = (char*) malloc(1);
    *ptr = 0;
}

void bar()
{
    char* ptr = (char*) calloc(1, sizeof(char));
    *ptr = 0;
}

void baz()
{
    char* ptr = new char();
    *ptr = 0;
}

TEST(ASunTest, MallocCallocNew)
{
    foo();
    bar();
    baz();
}
