#include <iostream>
#include "BigInt.h"
#include "googletest/googletest/include/gtest/gtest.h"

class BigIntTestConstructorsTest : public ::testing::Test {
public:
    std::string strings[4] = {"-0", "-01234567890123456789", "01234567890123456789", "AB"};
    int numbers[3] = {0, INT_MIN, INT_MAX};
};

TEST_F(BigIntTestConstructorsTest, constructors) {
    EXPECT_EQ(std::string(BigInt()), "0");
    EXPECT_EQ(std::string(BigInt(numbers[0])), "0");
    EXPECT_EQ(std::string(BigInt(strings[0])), "0");

    EXPECT_EQ(std::string(BigInt(numbers[1])), std::to_string(INT_MIN));
    EXPECT_EQ(std::string(BigInt(numbers[2])), std::to_string(INT_MAX));

    EXPECT_EQ(std::string(BigInt(strings[1])), "-1234567890123456789");
    EXPECT_EQ(std::string(BigInt(strings[2])), "1234567890123456789");

    BigInt biObj(strings[1]);
    EXPECT_EQ(std::string(biObj), std::string(BigInt(biObj)));

    EXPECT_THROW(BigInt incorrectArg(strings[3]), std::invalid_argument);
}

class BigIntTest : public ::testing::Test {
public:
    BigInt a, b, c;

    void setUp(const std::string& s1, const std::string& s2, const std::string& s3){
        a = BigInt(s1);
        b = BigInt(s2);
        c = BigInt(s3);
    }
};

TEST_F(BigIntTest, compareOperators) {
    setUp("-1234567890", "0", "123456789");
    EXPECT_TRUE(a == a);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a >= b);
    EXPECT_FALSE(a > b);
}

TEST_F(BigIntTest, unaryOperators) {
    setUp("-123456789", "0", "123456789");
    EXPECT_TRUE(-a == c);
    EXPECT_TRUE(-b == BigInt());
    EXPECT_TRUE(+a == a);

    EXPECT_TRUE(a > a++);
    EXPECT_TRUE(a == ++a);
    EXPECT_TRUE(a < a--);
    EXPECT_TRUE(a == --a);
}

TEST_F(BigIntTest, arithmeticOperators) {
    
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}