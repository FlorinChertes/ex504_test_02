#include "sut.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>

class MockDOC_f {
public:
    MOCK_METHOD(std::string, foo, ());
    MOCK_METHOD(int, bar, ());
};

TEST(SutTest_f, UseMock)
{
    // Arange
    MockDOC_f mock_doc;
    SUT_f<MockDOC_f> mock_sut(mock_doc);

    // Expect
    EXPECT_CALL(mock_doc, foo())
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return("from google 'foo' was called"));
    EXPECT_CALL(mock_doc, bar())
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(154));

    // Act
    bool res{true};
    res = mock_sut.foo(true,true);
    if (res == true)
    {
        res = mock_sut.bar(true,true);
    }
    // Assert
    ASSERT_TRUE(res);
}

TEST(SutTest_f, do_not_UseMock)
{
    // Arange
    DOC_f doc;
    SUT_f<DOC_f> sut(doc);

    // Act
    bool res{ true };

    res = sut.foo(true, true);
    if (res == true)
    {
        res = sut.bar(true, true);
    }
    // Assert
    ASSERT_TRUE(res);
}


