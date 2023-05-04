//
// Created by John on 5/3/2023.
//
#include <gtest/gtest.h>
#include <HugeInt.h>


// Run all tests here:
class AddSub_Tests : public ::testing::Test {
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

TEST_F(AddSub_Tests, Add_Two_Numbers)
{
    // Test initialization from unsigned long long value
    value1.setValue("100000");
    value2.setValue("100000");
    value1 = value1 + value2;

    HugeInt expected("200000");



    EXPECT_EQ(expected, value1);
}

TEST_F(AddSub_Tests, Add_To_TwoNumbers)
{
    // Test initialization from unsigned long long value
    value1.setValue("100000");
    value2.setValue("100000");
    value1 += value2;

    HugeInt expected("200000");

    EXPECT_EQ(expected, value1);
}

TEST_F(AddSub_Tests, Add_One_Pos__One_Neg_numbers)
{
    // Test initialization from unsigned long long value
    std::string num1 = "100000";
    std::string num2 = "-100000";



    value1.setValue(num1);
    value2.setValue(num2);

    HugeInt actual = value1 + value2;

    HugeInt expected(0);



    EXPECT_EQ(expected, actual);
}

TEST_F(AddSub_Tests, Add_To_One_Pos__One_Neg_str_numbers)
{
    // Test initialization from unsigned long long value
    std::string num1 = "100000";
    std::string num2 = "-100000";



    value1.setValue(num1);
    value2.setValue(num2);

    value1 += value2;

    HugeInt expected(0);



    EXPECT_EQ(expected, value1);
}

TEST_F(AddSub_Tests, Add_To_One_Pos__One_Neg_numbers)
{
    // Test initialization from unsigned long long value


    value1.setValue(100000);
    value2.setValue(-100000);

    value1 += value2;

    HugeInt expected(0);



    EXPECT_EQ(expected, value1);
}

TEST_F(AddSub_Tests, Subtract_Two_Numbers_numbers)
{
    // Test initialization from unsigned long long value
    value1.setValue("100000");
    value2.setValue("100000");
    value1 -= value2;

    HugeInt expected(0);



    EXPECT_EQ(expected, value1);
}

TEST_F(AddSub_Tests, Subtract_One_Pos__One_Neg_numbers)
{
    // Test initialization from unsigned long long value
    std::string num1 = "100000";
    std::string num2 = "-100000";



    value1.setValue(num1);
    value2.setValue(num2);

    HugeInt actual = value1 - value2;

    HugeInt expected(200000);



    EXPECT_EQ(expected, actual);
}