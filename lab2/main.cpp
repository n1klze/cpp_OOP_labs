#include "command_line_parser.h"
#include "file_parser.h"

int main(int argc, char **argv) {
    command_parser::CommandLineParser parser;
    life::FileParser file_parser;
    try {
        parser.GetCommandLineOptions(argc, argv);
        file_parser.ReadUniverseFromFile();
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
