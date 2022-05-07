
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <stack>

class Product
{
public:

    int data_;
    Product(int data) : data_(data) {}
};

bool cp_Product(Product lhs, Product rhs)
{
    return lhs.data_ == rhs.data_;
}

TEST(ProductTest, ProductEQ)
{
    Product p_1{ 1 };
    Product p_2{ 1 };
    ASSERT_PRED2(cp_Product, p_1, p_2);
}

class StackTest : public ::testing::Test
{
protected:
    std::stack<int> s;
    void SetUp() override {
        s.push(1);
        s.push(2);
        s.push(3);
    }
    void TearDown() override {}
};

TEST_F(StackTest, Size)
{
    int count = s.size();
    for (int i = 0; i < count; ++i)
    {
        s.push(i);
    }
    EXPECT_EQ(count * 2, s.size());
}

TEST_F(StackTest, Empty)
{
    int count = s.size();
    for (int i = 0; i < count; ++i)
    {
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}


class StackTestP : public ::testing::TestWithParam<int*>
{
protected:
    std::stack<int> s;
    void SetUp() override {
        int* params = GetParam();

        s.push(params[0]);
        s.push(params[1]);
        s.push(params[2]);

        std::cout << "params: " << params[0] <<
            ", " << params[1] <<
            ", " << params[2] << std::endl;

    }
    void TearDown() override {}
};

static int d1[]{ 1,2,3 };
static int d2[]{ -1,-2,-3 };
static int d3[]{ 4,5,6 };
static std::vector<int*> data{d1,d2,d3};


INSTANTIATE_TEST_SUITE_P(StackTestData, StackTestP, ::testing::ValuesIn(data));

TEST_P(StackTestP, Size)
{
    int count = s.size();
    for (int i = 0; i < count; ++i)
    {
        s.push(i);
    }
    EXPECT_EQ(count * 2, s.size());
}

TEST_P(StackTestP, Empty)
{
    int count = s.size();
    for (int i = 0; i < count; ++i)
    {
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

