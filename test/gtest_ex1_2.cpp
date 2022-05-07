#include "sut.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>

template<typename T>
class MockDOC : public DOC_t<T> {
public:

    MOCK_METHOD(std::string, foo, (T param), (override));    
    MOCK_METHOD(int, bar, (T param), (override));
};   

TEST(SutTest_t, UseMock)
{
    // Arange
    MockDOC<int> mock_doc;
    SUT_t sut(mock_doc);

    // Expect
    EXPECT_CALL(mock_doc, foo(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return("from google 'foo' was called"));
    EXPECT_CALL(mock_doc, bar(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(154));

    // Act
    bool res{true};
    res = sut.foo(true,true);
    if (res == true)
    {
        res = sut.bar(true,true);
    }

    // Assert
    ASSERT_TRUE(res);
}

TEST(SutTest_t, do_not_UseMock)
{
    DOC_t<int> doc;
    SUT_t sut(doc);

    bool res{ true };
    res = sut.foo(true, true);
    if (res == true)
    {
        res = sut.bar(true, true);
    }

    // Assert
    ASSERT_TRUE(res);
}
