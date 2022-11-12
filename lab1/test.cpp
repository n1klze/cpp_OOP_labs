#include <iostream>
#include "BigInt.h"
//#include "googletest/googletest/include/gtest/gtest.h"
#include "gtest/gtest.h"

class BigIntTestConstructorsTest : public ::testing::Test {
public:
    std::string string[4] = {"-0", "-01234567890123456789", "01234567890123456789", "AB"};
    int numbers[3] = {0, INT_MIN, INT_MAX};
};

TEST_F(BigIntTestConstructorsTest, emptyConstructorTest) {
    EXPECT_EQ(std::string(BigInt()), "0");
    EXPECT_EQ(std::string(BigInt(numbers[0])), "0");
    EXPECT_EQ(std::string(BigInt(string[0])), "0");
    EXPECT_TRUE(BigInt("\0") == BigInt());
}

TEST_F(BigIntTestConstructorsTest, fromStringConstructorTest) {
    EXPECT_EQ(std::string(BigInt(numbers[1])), std::to_string(INT_MIN));
    EXPECT_EQ(std::string(BigInt(numbers[2])), std::to_string(INT_MAX));

    EXPECT_EQ(std::string(BigInt(string[1])), "-1234567890123456789");
    EXPECT_EQ(std::string(BigInt(string[2])), "1234567890123456789");
}

TEST_F(BigIntTestConstructorsTest, fromStringConstructorExceptionTest) {
    EXPECT_THROW(BigInt incorrectArg(string[3]), std::invalid_argument);
    EXPECT_THROW(BigInt("+-123"), std::invalid_argument);
    EXPECT_THROW(BigInt("\n123"), std::invalid_argument);
}

TEST_F(BigIntTestConstructorsTest, fromBigIntConstructor) {
    BigInt biObj(string[1]);
    EXPECT_EQ(std::string(biObj), std::string(BigInt(biObj)));
}

class BigIntTest : public ::testing::Test {
public:
    BigInt a, b, c;

    void setUp(const std::string &s1, const std::string &s2, const std::string &s3) {
        a = BigInt(s1);
        b = BigInt(s2);
        c = BigInt(s3);
    }
};

TEST_F(BigIntTest, compareOperatorsTest) {
    setUp("-1234567890", "0", "123456789");
    EXPECT_TRUE(a == a);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a >= b);
    EXPECT_FALSE(a > b);
}

TEST_F(BigIntTest, unaryOperatorsTest) {
    setUp("-123456789", "0", "123456789");
    EXPECT_TRUE(-a == c);
    EXPECT_TRUE(-b == BigInt());
    EXPECT_TRUE(+a == a);

    EXPECT_TRUE(a > a++);
    EXPECT_TRUE(a == ++a);
    EXPECT_TRUE(a < a--);
    EXPECT_TRUE(a == --a);
}

TEST_F(BigIntTest, additionTest) {
    setUp("-12345678901234567890", "0", "12345678901234567890");
    EXPECT_TRUE(a + b == a);
    EXPECT_TRUE(b + c == c);
    EXPECT_TRUE(a + c == b);
    EXPECT_TRUE(a + a == -(c + c));
    EXPECT_TRUE(BigInt(-1) + 2 == BigInt(1));
}

TEST_F(BigIntTest, multiplyTest) {
    setUp("-12345678901234567890", "0", "12345678901234567890");
    EXPECT_TRUE(a * (-1) == c);
    EXPECT_TRUE(c * (-1) == a);
    EXPECT_TRUE(a * 2 == a + a);
    EXPECT_TRUE(c * 2 == c + c);
    EXPECT_TRUE(a * a == c * c);
    EXPECT_TRUE(a * c == c * a);
    EXPECT_TRUE(a * b == c * b);
    setUp("1234567890", "-1234567890", "1524157875019052100");
    EXPECT_TRUE(a * b == -c);
    EXPECT_TRUE(a * a == c);
}

TEST_F(BigIntTest, divisionTest) {
    setUp("-999999999", "0", "999999999");
    EXPECT_THROW(a / b, std::domain_error);
    EXPECT_TRUE(a / c == BigInt(-1));
    EXPECT_TRUE(a / a == BigInt(1));
    EXPECT_TRUE(c / BigInt(1000) == BigInt(999999));
    EXPECT_TRUE(BigInt(1000) / BigInt(10000) == b);
    EXPECT_TRUE(b / c == b);

    EXPECT_THROW(a % b, std::domain_error);
    EXPECT_TRUE(a % c == b);
    EXPECT_TRUE(a % a == b);
    EXPECT_TRUE(c % BigInt(1000) == BigInt(999));
    EXPECT_TRUE(c % ++c == b);
    EXPECT_TRUE(b / c == b);
}

TEST_F(BigIntTest, bitwiseNOTTest) {
    setUp("0", "1", "-1");
    EXPECT_TRUE(~a == -b);
    EXPECT_TRUE(~b == a);

    setUp("1024", "-1024", "0");
    EXPECT_TRUE(~a == b + 1);
    EXPECT_TRUE(~b == a - 1);
}

TEST_F(BigIntTest, bitwiseANDTest) {
    setUp("0", "1", "-1");
    EXPECT_TRUE((a & a) == a);
    EXPECT_TRUE((a & b) == a);
    EXPECT_TRUE((b & a) == a);
    EXPECT_TRUE((b & b) == b);

    EXPECT_TRUE((c & c) == c);
    EXPECT_TRUE((c & a) == a);
    EXPECT_TRUE((c & b) == b);

    setUp("1024", "-1024", "0");
    EXPECT_TRUE((a & (a - 1)) == c);
    EXPECT_TRUE((b & (b + 1)) == c);
}

TEST_F(BigIntTest, bitwiseORTest) {
    setUp("0", "1", "-1");
    EXPECT_TRUE((a | a) == a);
    EXPECT_TRUE((a | b) == b);
    EXPECT_TRUE((b | a) == b);
    EXPECT_TRUE((b | b) == b);

    EXPECT_TRUE((c | c) == c);
    EXPECT_TRUE((c | a) == c);
    EXPECT_TRUE((c | b) == c);

    setUp("1024", "-1024", "0");
    EXPECT_TRUE((a | b) == b);
}

TEST_F(BigIntTest, bitwiseXORTest) {
    setUp("0", "1", "-1");
    EXPECT_TRUE((a ^ a) == a);
    EXPECT_TRUE((a ^ b) == b);
    EXPECT_TRUE((b ^ a) == b);
    EXPECT_TRUE((b ^ b) == a);

    EXPECT_TRUE((c ^ c) == a);
    EXPECT_TRUE((c ^ a) == c);
    EXPECT_TRUE((c ^ b) == a);

    setUp("1024", "-1024", "0");
    EXPECT_TRUE((a ^ --a) == c);
    EXPECT_TRUE((b ^ ++b) == c);
}

TEST_F(BigIntTest, toIntConversionTest) {
    setUp(std::to_string(INT_MAX), std::to_string(INT_MIN), "0");
    EXPECT_EQ(int(a), INT_MAX);
    EXPECT_EQ(int(b), INT_MIN);
    EXPECT_EQ(int(c), 0);
}

TEST_F(BigIntTest, toStringConversionTest) {
    setUp(std::to_string(INT_MAX), std::to_string(INT_MIN), "0");
    EXPECT_EQ(std::string(a), std::to_string(INT_MAX));
    EXPECT_EQ(std::string(b), std::to_string(INT_MIN));
    EXPECT_EQ(std::string(c), std::to_string(0));
}

TEST_F(BigIntTest, getSizeMethodTest) {
    setUp(std::to_string(INT_MAX), std::to_string(INT_MIN), "0");
    EXPECT_EQ(a.size(), std::to_string(INT_MAX).size());
    EXPECT_EQ(b.size(), std::to_string(INT_MIN).size());
    EXPECT_EQ(c.size(), std::to_string(0).size());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
