#include <fstream>
#include <iostream>

#include "csv_parser.h"
#include "tuple_printer.h"

int main() {
    auto t = std::make_tuple(100, 'a', "123as", 3.14);
    std::cout << t << std::endl;

    std::ifstream file("..\\test.csv");
    if (!file.is_open()) {
        std::cerr << "File error.";
        return EXIT_FAILURE;
    }
    parser::CSVParser<int, std::string> parser(file, 0);
    for (const auto &rs: parser)
        std::cout << rs << std::endl;

    return EXIT_SUCCESS;
}
