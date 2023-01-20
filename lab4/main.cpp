#include <iostream>

#include "tuple_printer.h"

int main() {
    auto t = std::make_tuple(100, 'a', "123as", 3.14);
    std::cout << t;
    return EXIT_SUCCESS;
}
