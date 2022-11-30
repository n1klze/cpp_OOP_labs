#include <iostream>
#include "command_line_parser.h"

int main(int argc, char **argv) {
    command_parser::CommandLineParser parser;
    try {
        parser.GetCommandLineOptions(argc, argv);
    } catch (const std::exception &except) {
        std::cerr << except.what();
    }

    std::cout << parser.data().iterations << "\n"
              << parser.data().in_filename << "\n"
              << parser.data().out_filename << std::endl;
    return EXIT_SUCCESS;
}
