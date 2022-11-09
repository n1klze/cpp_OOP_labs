#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <string>
#include <stdexcept>
#include <algorithm>

class BigInt {
private:
    std::string number;    // string representation of this big integer in base=10
    bool sign;             //true is negative

    void setNumber(const std::string &str, int radix = 10);

    void checkStringIsNumeric(const std::string &str);

    void setSign(bool s);

    void fixNegativeZero();

    static std::string add(const std::string &, const std::string &);

    static std::string padLeft(const std::string &, size_t);

    static std::string subtract(const std::string &, const std::string &);

    static std::string removeLeadingZeros(const std::string &);

    static std::string multiply(const std::string &, const std::string &);

    static std::pair<BigInt, BigInt> divide(const BigInt &, const BigInt &);

    std::string toBinString() const;

    static const BigInt ZERO;
    static const BigInt ONE;

public:
    BigInt();

    BigInt(int);

    BigInt(const std::string &);

    BigInt(const BigInt &);

    ~BigInt();

    BigInt &operator=(const BigInt &);

    BigInt operator~() const;

    BigInt &operator++();

    const BigInt operator++(int);

    BigInt &operator--();

    const BigInt operator--(int);

    BigInt &operator+=(const BigInt &);

    BigInt &operator*=(const BigInt &);

    BigInt &operator-=(const BigInt &);

    BigInt &operator/=(const BigInt &);

    BigInt &operator^=(const BigInt &);

    BigInt &operator%=(const BigInt &);

    BigInt &operator&=(const BigInt &);

    BigInt &operator|=(const BigInt &);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt &) const;

    bool operator!=(const BigInt &) const;

    bool operator<(const BigInt &) const;

    bool operator>(const BigInt &) const;

    bool operator<=(const BigInt &) const;

    bool operator>=(const BigInt &) const;

    explicit operator int() const;

    explicit operator std::string() const;

    size_t size() const;  // size in bytes

    friend BigInt operator+(const BigInt &, const BigInt &);

    friend BigInt operator-(const BigInt &, const BigInt &);

    friend BigInt operator*(const BigInt &, const BigInt &);

    friend BigInt operator/(const BigInt &, const BigInt &);

    friend BigInt operator^(const BigInt &, const BigInt &);

    friend BigInt operator%(const BigInt &, const BigInt &);

    friend BigInt operator&(const BigInt &, const BigInt &);

    friend BigInt operator|(const BigInt &, const BigInt &);

    friend std::ostream &operator<<(std::ostream &o, const BigInt &i);
};

#endif //LAB1_BIGINT_H
