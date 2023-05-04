//
// Created by John on 5/3/2023.
//
#include <gtest/gtest.h>
#include <HugeInt.h>


// Run all tests here:
class MulDiv_Tests : public ::testing::Test {
protected:

    HugeInt value1;
    HugeInt value2;

    void SetUp() override {
        // setup code here
        value1 = HugeInt(426541);
        value2 = HugeInt(426541);

    }

    void TearDown() override {
        // teardown code here
        value1.resetDigits();
        value2.resetDigits();
    }
};

TEST_F(MulDiv_Tests, Multiply_Two_Numbers)
{
    // Test initialization from unsigned long long value
    value1.setValue(200);
    value2.setValue(200);
    value1 = value1 * value2;

    HugeInt expected(40000);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Multiply_To_TwoNumbers)
{
    // Test initialization from unsigned long long value
    value1.setValue(100000);
    value2.setValue(100000);
    value1 *= value2;

    HugeInt expected("10000000000");

    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Multiply_One_Pos__One_Neg)
{
    // Test initialization from unsigned long long value
    value1.setValue(100000);
    value2.setValue(-100000);
    value1 *= value2;

    HugeInt expected("-10000000000");

    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Numbers_1)
{
    // Test initialization from unsigned long long value
    value1.setValue(4);
    value2.setValue(2);
    value1 = value1 / value2;

    HugeInt expected(2);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Numbers_2)
{
    // Test initialization from unsigned long long value
    value1.setValue(6);
    value2.setValue(3);
    value1 = value1 / value2;

    HugeInt expected(2);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Numbers_3)
{
    // Test initialization from unsigned long long value
    value1.setValue(8);
    value2.setValue(2);
    value1 = value1 / value2;

    HugeInt expected(4);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Numbers_4)
{
    // Test initialization from unsigned long long value
    value1.setValue(9);
    value2.setValue(3);
    value1 = value1 / value2;

    HugeInt expected(3);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Numbers_5)
{
    // Test initialization from unsigned long long value
    value1.setValue(10);
    value2.setValue(5);
    value1 = value1 / value2;

    HugeInt expected(2);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_Two_Larger_Numbers)
{
    // Test initialization from unsigned long long value
    value1.setValue(5000);
    value2.setValue(200);
    value1 = value1 / value2;

    HugeInt expected(25);



    EXPECT_EQ(expected, value1);
}

TEST_F(MulDiv_Tests, Divide_To_TwoNumbers)
{
    // Test initialization from unsigned long long value
    value1.setValue(100000);
    value2.setValue(5);
    value1 =  value1 / value2;

    HugeInt expected(20000);

    EXPECT_EQ(expected, value1);
}
