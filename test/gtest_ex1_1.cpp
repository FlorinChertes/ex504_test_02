
#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

