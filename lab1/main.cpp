#include <iostream>
#include "BigInt.h"

int main() {
    try {
        BigInt a(5);
        BigInt b(1);
        std::cout << a + b;
    } catch (const std::exception &error) {
        std::cout << error.what() << std::endl;
    }
    return 0;
}