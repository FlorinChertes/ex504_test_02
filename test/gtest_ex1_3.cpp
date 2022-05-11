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


TEST(ActionTest, Invoke_1) {
	MockDOC_03 mock_doc;

	EXPECT_CALL(mock_doc, sum(::testing::_, ::testing::_))
		.WillOnce(::testing::Invoke(foo));

	std::cout << "sum_1: " << mock_doc.sum(3, 2) << std::endl;
}

TEST(ActionTest, Invoke_2) {
	MockDOC_03 mock_doc;

	EXPECT_CALL(mock_doc, sum(::testing::_, ::testing::_))
		.WillOnce(::testing::Invoke([](int x, int y) -> int
			{ return x - y; }
		));

	std::cout << "sum_2: " << mock_doc.sum(3, 2) << std::endl;
}


TEST(ClauselTest, With) {
	MockDOC_03 mock_doc;

	EXPECT_CALL(mock_doc, sum(::testing::_, ::testing::_))
		.With(::testing::Args<0,1>(::testing::Gt()))
	    .WillOnce(::testing::Invoke(foo));

	std::cout << "sum: " << mock_doc.sum(3, 2) << std::endl;
}

class MockDOC_04 {
public:
	MOCK_METHOD(void, func_1, ());
	MOCK_METHOD(void, func_2, ());
	MOCK_METHOD(void, func_3, ());
};


TEST(ClauselTest, After) {
	MockDOC_04 mock_doc;

	::testing::ExpectationSet es;

	es += EXPECT_CALL(mock_doc, func_1());
	es += EXPECT_CALL(mock_doc, func_2());

	EXPECT_CALL(mock_doc, func_3)
		.After(es);

	mock_doc.func_1();
	mock_doc.func_2();

	mock_doc.func_3();

	std::cout << "func_1: " <<
		"func_2: " <<
		"func_3: " << std::endl;
}

TEST(ClauselTest, Times) {
	MockDOC_04 mock_doc;

	EXPECT_CALL(mock_doc, func_1())
		.Times(1);
	EXPECT_CALL(mock_doc, func_2())
		.Times(1);
	EXPECT_CALL(mock_doc, func_3())
		.Times(2);


	mock_doc.func_1();
	mock_doc.func_2();

	mock_doc.func_3();
	mock_doc.func_3();

	std::cout << "func_1: " <<
		"func_2: " <<
		"func_3: " << std::endl;
}

TEST(ClauselTest, TimesAnyAtLeast) {
	MockDOC_04 mock_doc;

	EXPECT_CALL(mock_doc, func_1())
		.Times(::testing::AtLeast(1));
	EXPECT_CALL(mock_doc, func_2())
		.Times(::testing::AtMost(1));
	EXPECT_CALL(mock_doc, func_3())
		.Times(::testing::AnyNumber());

	mock_doc.func_1();
	mock_doc.func_2();

	mock_doc.func_3();
	mock_doc.func_3();

	std::cout << "func_1: " <<
		"func_2: " <<
		"func_3: " << std::endl;
}


class MockDOC_05 {
public:
	MockDOC_05() {
		EXPECT_CALL(*this, foo(::testing::_))
			.Times(::testing::AnyNumber())
			.WillRepeatedly(::testing::Return(0));
	}

	MOCK_METHOD(int, foo, (int));

};

TEST(ClauselTest, Generalize_1) {
	MockDOC_05 mock_doc;

	EXPECT_CALL(mock_doc, foo(1))
		.WillOnce(::testing::Return(1));

	std::cout << "foo: " << mock_doc.foo(1) << std::endl;
	std::cout << "foo: " << mock_doc.foo(100) << std::endl;

}


class MockDOC_06 {
public:
	MockDOC_06() {

		ON_CALL(*this, bar(::testing::_))
			.WillByDefault(::testing::Return(1));
	}

	MOCK_METHOD(int, bar, (int));
	MOCK_METHOD(int, foo, (int));
};

TEST(ClauselTest, Generalize_3) {
	MockDOC_06 mock_doc;

	EXPECT_CALL(mock_doc, foo(1))
		.WillOnce(::testing::Return(1));

	if (mock_doc.bar(1) == 1)
	{
		std::cout << "foo: " << mock_doc.foo(1) << std::endl;
	}
}
