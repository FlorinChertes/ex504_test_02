#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace ::testing;

int foo()
{
    int *array = new int[100];
    delete array;

    return array[5];
}

TEST(ASunTest, UseMock)
{
    foo();
}

