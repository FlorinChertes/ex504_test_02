#include "sut.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>


TEST(SutTest_ipc, do_not_UseMock)
{
    // Arange
    ServicePoint servicePoint;
    SUT_ipc<ServicePoint> sut_ipc(servicePoint);

    // Act
    int res = sut_ipc.foo();

    // Assert
    ASSERT_TRUE(res == 153);
}


class MockServicePoint
{
    using Handler = std::function<int(int)>;

public:

    MOCK_METHOD(int, makeCall, (std::string uri, int param, Handler handler));

    MOCK_METHOD(int, callOneReply, (std::string uri, int param, Handler handler));

    template<typename T>
    inline int callOneReply(std::string uri, int param, T object, int(T::* handler)(int))
    {
        return callOneReply(uri, param, std::bind(handler, object, std::placeholders::_1));
    }

};

TEST(SutTest_ipc, UseMock)
{
    // Arange
    MockServicePoint mock_servicePoint;
    SUT_ipc<MockServicePoint> mock_sut_ipc(mock_servicePoint);

    std::string uri{ };
    int param{ 0 };
    auto callback{ std::function<int(int)>{} };

    // Expect
    {
        ::testing::InSequence s;

        EXPECT_CALL(mock_servicePoint, callOneReply(::testing::_
            , ::testing::_
            , ::testing::_))
            .Times(::testing::AtLeast(1))
            .WillOnce(
                ::testing::DoAll(
                  ::testing::SaveArg<0>(&uri)
                , ::testing::SaveArg<1>(&param)
                , ::testing::SaveArg<2>(&callback)
                , ::testing::Return(154)
                ));
    }
    // Act
    int res = mock_sut_ipc.foo();

    // Assert
    ASSERT_TRUE(res == 154);

    ASSERT_TRUE(uri == "uri");
    ASSERT_TRUE(param == 153);
    ASSERT_TRUE(callback(155) == 155);
}
