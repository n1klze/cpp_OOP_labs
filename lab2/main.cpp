#include "command_line_parser.h"

int main(int argc, char **argv) {
    command_parser::CommandLineParser parser;

    try {
        parser.GetCommandLineOptions(argc, argv);
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
