#include "sut.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
    
class MockDOC : public DOC {
public:

    MOCK_METHOD(std::string, foo, (), (override));    
    MOCK_METHOD(int, bar, (), (override));
};   

TEST(SutTest, UseMock)
{
    // Arange
    MockDOC mock_doc;
    SUT sut(mock_doc);

    // Expect
    EXPECT_CALL(mock_doc, foo())
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return("from google 'foo' was called"));
    EXPECT_CALL(mock_doc, bar())
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

TEST(SutTest, do_not_UseMock)
{
    DOC doc;
    SUT sut(doc);

    bool res{ true };
    res = sut.foo(true, true);
    if (res == true)
    {
        res = sut.bar(true, true);
    }

    // Assert
    ASSERT_TRUE(res);
}
