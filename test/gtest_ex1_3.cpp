#include "sut.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>


class MockDOC_03 {
public:
	MOCK_METHOD(int, sum, (int,int));

};

int foo(int a, int b)
{
	return a - b;

}

TEST(ActionTest, Invoke) {
	MockDOC_03 mock_doc;

	EXPECT_CALL(mock_doc, sum(::testing::_, ::testing::_))
		.WillOnce(::testing::Invoke(foo)
		);

	std::cout << "sum: " << mock_doc.sum(3, 2) << std::endl;
}
