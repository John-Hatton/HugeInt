//
// Created by hattonjd on 5/3/2023.
//
#include <gtest/gtest.h>
#include "../source/HugeInt.cpp"

TEST(HugeInt_Test,Initialization_test)
{
    // Test initialization from unsigned long long value
    unsigned long long value = 1234567890;
    HugeInt actual(value);

    HugeInt expected("1234567890");



    EXPECT_EQ(expected, actual);
}

TEST(HugeInt_Test, Add_Two_Large_numbers)
{
    // Test initialization from unsigned long long value
    std::string value = "18446744073709551615";
    HugeInt actual(value);

    actual += actual;

    HugeInt expected("36893488147419103230");



    EXPECT_EQ(expected, actual);
}
