#include "BigInt.h"

const BigInt BigInt::ZERO("0");
const BigInt BigInt::ONE("1");

BigInt::BigInt() : number("0"), sign(false) {
    //empty
}

BigInt::BigInt(int number) : BigInt(std::to_string(number)) {
    //empty
}

BigInt::BigInt(const std::string &str) {
    switch (str[0]) {
        case '-':
            setNumber(str.substr(1));
            setSign(true);
            break;
        case '+':
            setNumber(str.substr(1));
            setSign(false);
            break;
        default:
            setNumber(str);
            setSign(false);
            break;
    }
}

BigInt::BigInt(const BigInt &other) : number(other.number), sign(other.sign) {
    //empty
}

BigInt::~BigInt() = default;

void BigInt::checkStringIsNumeric(const std::string &str) {
    size_t str_length = str.length();
    for (size_t i = 0; i < str_length; i++) {
        if (!std::isdigit(str[i]))
            throw std::invalid_argument("Number must contain only digits.");
    }
}

void BigInt::setNumber(const std::string &str, int radix) {
    if (radix == 10) {
        checkStringIsNumeric(str);
        number = str;
    } else {
        BigInt result(ZERO);
        BigInt power(ONE);
        BigInt biRadix(radix);
        size_t str_len = str.length();
        for (size_t i = 0; i < str_len; i++){
            char ch = str[i];
            result += power * BigInt(ch - '0');
            power *= biRadix;
        }
        number = result.number;
    }
    fixNegativeZero();
}

void BigInt::fixNegativeZero() {
    if (number == "0")
        sign = false;
}

void BigInt::setSign(bool s) {
    sign = s;
    fixNegativeZero();
}

BigInt &BigInt::operator=(const BigInt &b) {
    number = b.number;
    setSign(b.sign);
    return *this;
}

std::string BigInt::toBinString() const {
    BigInt copy(this->number);
    BigInt radix(2);
    std::string bin_str = "";
    do {
        bin_str += std::string(copy % radix);
        copy /= radix;
    } while (copy != ZERO);
    std::reverse(bin_str.begin(), bin_str.end());
    return bin_str;
}

BigInt &BigInt::operator++() {
    (*this) = (*this) + ONE;
    return (*this);
}

const BigInt BigInt::operator++(int) {
    BigInt before = (*this);
    (*this) = (*this) + ONE;
    return before;
}

BigInt &BigInt::operator--() {
    (*this) = (*this) - ONE;
    return (*this);
}

const BigInt BigInt::operator--(int) {
    BigInt before = (*this);
    (*this) = (*this) - ONE;
    return before;
}

BigInt &BigInt::operator+=(const BigInt &b) {
    (*this) = (*this) + b;
    return (*this);
}

BigInt &BigInt::operator-=(const BigInt &b) {
    (*this) = (*this) - b;
    return (*this);
}

BigInt &BigInt::operator*=(const BigInt &b) {
    (*this) = (*this) * b;
    return (*this);
}

BigInt &BigInt::operator/=(const BigInt &b) {
    (*this) = (*this) / b;
    return (*this);
}

BigInt &BigInt::operator^=(const BigInt &b) {
    (*this) = (*this) ^ b;
    return (*this);
}

BigInt &BigInt::operator%=(const BigInt &b) {
    (*this) = (*this) % b;
    return (*this);
}

BigInt &BigInt::operator&=(const BigInt &b) {
    (*this) = (*this) & b;
    return (*this);
}

BigInt &BigInt::operator|=(const BigInt &b) {
    (*this) = (*this) | b;
    return (*this);
}

BigInt BigInt::operator+() const {
    return BigInt(*this);
}

BigInt BigInt::operator-() const {
    BigInt tmp = BigInt(*this);
    tmp.setSign(!sign);
    return tmp;
}

bool BigInt::operator==(const BigInt &b) const {
    return (this->number == b.number && this->sign == b.sign);
}

bool BigInt::operator!=(const BigInt &b) const {
    return !(*this == b);
}

bool BigInt::operator<(const BigInt &b) const {
    bool sign_first = this->sign;
    bool sign_second = b.sign;
    if (sign_first && !sign_second) {
        return true;
    } else if (!sign_first && sign_second) {
        return false;
    } else if (!sign_first) {
        if (this->number.length() < b.number.length())
            return true;
        else if (this->number.length() > b.number.length())
            return false;
        else
            return this->number < b.number;
    } else {
        if (this->number.length() > b.number.length())
            return true;
        else if (this->number.length() < b.number.length())
            return false;
        else
            return this->number > b.number;
    }
}

bool BigInt::operator>(const BigInt &b) const {
    return b < *this;
}

bool BigInt::operator<=(const BigInt &b) const {
    return (*this < b) || (*this == b);
}

bool BigInt::operator>=(const BigInt &b) const {
    return (*this > b) || (*this == b);
}

BigInt::operator int() const {
    int sum = 0;
    int prevSum = 0;
    int number_len = number.length();
    for (int i = 0; i < number_len; i++) {
        prevSum = sum;
        sum = sum * 10 + number[i] - '0';
        if (sum < prevSum)
            throw std::overflow_error("Numeric overflow on conversion.");
    }
    return sum;
}

BigInt::operator std::string() const {
    std::string signedString = sign ? "-" : "";
    signedString += number;
    return signedString;
}

size_t BigInt::size() const {
    size_t size = sign ? 1 : 0;
    size += number.length();
    return size;
}

std::string BigInt::padLeft(const std::string &str, size_t length) {
    size_t str_length = str.length();
    if (str_length < length) {
        std::string str_copy = str;
        str_copy.insert(0, length - str_length, '0');
        return str_copy;
    } else {
        return str;
    }
}

std::string BigInt::add(const std::string &a, const std::string &b) {
    size_t digitsCount = (a.length() > b.length() ? a.length() : b.length());
    std::string sum = padLeft("", digitsCount);
    std::string a_copy = padLeft(a, digitsCount);
    std::string b_copy = padLeft(b, digitsCount);
    //add each digit pair
    int carry = 0;
    for (int i = a_copy.length() - 1; i >= 0; --i) {
        sum[i] = (carry + (a_copy[i] - '0') + (b_copy[i] - '0')) + '0';
        carry = 0;
        if (i != 0) {
            if (sum[i] > '9') {
                sum[i] -= 10;
                carry = 1;
            }
        } else {
            carry = 0;
        }
    }
    if (sum[0] > '9') {
        sum[0] -= 10;
        sum.insert(0, 1, '1');
    }
    return sum;
}

std::string BigInt::removeLeadingZeros(const std::string &str) {
    std::string result = str;
    while (result[0] == '0' && result.length() > 1)
        result.erase(0, 1);
    if (result.length() == 0)
        result = "0";
    return result;
}

std::string BigInt::subtract(const std::string &a, const std::string &b) {
    size_t digits = (a.length() > b.length() ? a.length() : b.length());
    std::string sub = padLeft("", digits);
    std::string a_copy = padLeft(a, digits);
    std::string b_copy = padLeft(b, digits);

    for (int i = a_copy.length() - 1; i >= 0; --i) {
        if (a_copy[i] < b_copy[i]) {
            a_copy[i] += 10;
            a_copy[i - 1]--;
        }
        sub[i] = ((a_copy[i] - '0') - (b_copy[i] - '0')) + '0';
    }
    sub = removeLeadingZeros(sub);
    return sub;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt sum;
    if (a.sign == b.sign) {
        sum.setNumber(BigInt::add(a.number, b.number));
        sum.setSign(a.sign);
    } else {
        if (BigInt(a.number) > BigInt(b.number)) {
            sum.setNumber(BigInt::subtract(a.number, b.number));
            sum.setSign(a.sign);
        } else {
            sum.setNumber(BigInt::subtract(b.number, a.number));
            sum.setSign(b.sign);
        }
    }
    if (sum.number == "0")
        sum.setSign(false);
    return sum;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    //a - b = a + (-b)
    BigInt b_copy = b;
    b_copy.setSign(!b.sign);
    return a + b_copy;
}

std::string BigInt::multiply(const std::string &a, const std::string &b) {
    std::string a_copy = a;
    std::string b_copy = b;

    if (a_copy.length() > b_copy.length())
        a_copy.swap(b_copy);

    std::string product = "0";
    for (int i = a_copy.length() - 1; i >= 0; --i) {
        std::string temp = b_copy;
        int currentDigit = a_copy[i] - '0';
        int carry = 0;
        for (int j = temp.length() - 1; j >= 0; --j) {
            temp[j] = ((temp[j] - '0') * currentDigit) + carry;
            if (temp[j] > 9) {
                carry = temp[j] / 10;
                temp[j] -= carry * 10;
            } else {
                carry = 0;
            }
            temp[j] += '0';     //back to char
        }

        if (carry > 0)
            temp.insert(0, 1, carry + '0');

        //as like multiply by 10, 100, 1000 ...
        temp.append(a_copy.length() - i - 1, '0');

        product = add(product, temp);               //O(n)
    }

    product = removeLeadingZeros(product);
    return product;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt product;
    product.number = BigInt::multiply(a.number, b.number);
    product.setSign(a.sign != b.sign);
    return product;
}

std::pair<BigInt, BigInt> BigInt::divide(const BigInt &numerator, const BigInt &denominator) {
    if (denominator == ZERO) {
        throw std::domain_error("Division by zero.");
    } else if (denominator < ZERO) {
        std::pair<BigInt, BigInt> result = divide(numerator, -denominator);
        result.first = -result.first;
        return result;
    } else if (numerator < ZERO) {
        std::pair<BigInt, BigInt> result = divide(-numerator, denominator);
        if (result.second == ZERO) {
            result.first = -result.first;
        } else {
            result.first = -result.first - 1;
            result.second = denominator - result.second;
        }
        return result;
    }

    BigInt quotient = BigInt(ZERO);
    BigInt remainder = BigInt(numerator);
    while (remainder >= denominator) {
        quotient++;
        remainder -= denominator;
    }
    std::pair<BigInt, BigInt> result = {quotient, remainder};
    return result;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
    std::pair<BigInt, BigInt> result = BigInt::divide(a, b);
    return result.first;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
    std::pair<BigInt, BigInt> result = BigInt::divide(a, b);
    return result.second;
}

BigInt BigInt::operator~() const {
    std::string binStr = this->toBinString();
    size_t strLen = binStr.length();

    for (size_t i = 0; i < strLen; i++)
        binStr[i] = (binStr[i] == '1') ? '0' : '1';
    binStr = removeLeadingZeros(binStr);
    BigInt result = BigInt();
    result.setNumber(binStr, 2);
    result.setSign(!this->sign);
    return result;
}

BigInt operator^(const BigInt &a, const BigInt &b) {
    std::string firstBinStr = a.toBinString();
    std::string secondBinStr = b.toBinString();
    size_t maxLen = std::max(firstBinStr.length(), secondBinStr.length());
    firstBinStr = BigInt::padLeft(firstBinStr, maxLen);
    secondBinStr = BigInt::padLeft(secondBinStr, maxLen);

    for (size_t i = 0; i < maxLen; i++)
        firstBinStr [i] = ((firstBinStr[i] == '1') ^ (secondBinStr[i] == '1')) ? '1' : '0';
    firstBinStr = BigInt::removeLeadingZeros(firstBinStr);

    BigInt result = BigInt();
    result.setNumber(firstBinStr, 2);
    result.setSign(a.sign ^ b.sign);
    return result;
}

BigInt operator&(const BigInt &a, const BigInt &b){
    std::string firstBinStr = a.toBinString();
    std::string secondBinStr = b.toBinString();
    size_t maxLen = std::max(firstBinStr.length(), secondBinStr.length());
    firstBinStr = BigInt::padLeft(firstBinStr, maxLen);
    secondBinStr = BigInt::padLeft(secondBinStr, maxLen);

    for (size_t i = 0; i < maxLen; i ++)
        firstBinStr [i] = ((firstBinStr[i] == '1') && (secondBinStr[i] == '1')) ? '1' : '0';
    firstBinStr = BigInt::removeLeadingZeros(firstBinStr);

    BigInt result = BigInt();
    result.setNumber(firstBinStr, 2);
    result.setSign(a.sign && b.sign);
    return result;
}

BigInt operator|(const BigInt &a, const BigInt &b) {
    std::string firstBinStr = a.toBinString();
    std::string secondBinStr = b.toBinString();
    size_t maxLen = std::max(firstBinStr.length(), secondBinStr.length());
    firstBinStr = BigInt::padLeft(firstBinStr, maxLen);
    secondBinStr = BigInt::padLeft(secondBinStr, maxLen);

    for (size_t i = 0; i < maxLen; i ++)
        firstBinStr [i] = ((firstBinStr[i] == '1') || (secondBinStr[i] == '1')) ? '1' : '0';
    firstBinStr = BigInt::removeLeadingZeros(firstBinStr);

    BigInt result = BigInt();
    result.setNumber(firstBinStr, 2);
    result.setSign(a.sign || b.sign);
    return result;
}

std::ostream &operator<<(std::ostream &o, const BigInt &i) {
    return o << std::string(i);
}
