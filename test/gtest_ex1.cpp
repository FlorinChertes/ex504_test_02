#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sut.h"

using namespace std;
using namespace ::testing;
    
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
        .Times(AtLeast(1))
        .WillRepeatedly(Return("from google 'foo' was called"));
    EXPECT_CALL(mock_doc, bar())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(154));

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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
