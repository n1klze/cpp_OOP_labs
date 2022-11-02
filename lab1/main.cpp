#include <iostream>
#include "BigInt.h"

int main() {
    try {
        BigInt a = BigInt("100000000000000000");
        BigInt b = BigInt(INT_MAX);
        std::cout << a / b;
    } catch (const std::exception &error) {
        std::cout << error.what() << std::endl;
    }
    return 0;
}
