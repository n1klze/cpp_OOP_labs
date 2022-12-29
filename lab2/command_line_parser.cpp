#include "command_line_parser.h"

const std::string command_parser::CommandLineParser::kUsageMessage =
        "Usage: program [-h | --help] [filename1.life] [-i x | --input=x] [-o filename2.life | --output=filename2.life]\n"
        "--------------------------------------------------------------------------------------------------------------\n"
        "-h, --help\n"
        "\tPrint (on the standard output) usage message with a description of command-line options.\n"
        "filename1.life\n"
        "\tInput file with universe description in the Life 1.06 file format.\n"
        "\tIf filename1.life is not specified, the default is to take a filed from default.life.\n"
        "-i x, --input=<x>\n"
        "\tSet the number of iterations to x.\n"
        "-o filename2.life, --output=filename2.life\n"
        "\tPlace output in file filename2.life, where the universe will be save after the game ends.\n"
        "\tIf is not specified, the game opens in console mode.";

void command_parser::CommandLineParser::ParseShortCommand(char **argv, const std::string &current_string, int &i) {
    if (current_string == "-i") {
        GetNumberOfIterations(argv, i);
    } else if (current_string == "-o") {
        data_.out_filename_ = std::string(argv[++i]);
    } else if (current_string == "-h") {
        std::cout << kUsageMessage << std::endl;
    } else {
        throw std::invalid_argument("Unrecognized command line option: " + current_string);
    }
}

void command_parser::CommandLineParser::GetNumberOfIterations(char **argv, int &i) {
    try {
        std::size_t pos{};
        data_.iterations_ = std::stoi(argv[++i], &pos);
        if (pos != std::string(argv[i]).size())
            throw std::invalid_argument("Number of iterations must be a numeric.");
        if (data_.iterations_ < 0)
            throw std::invalid_argument("Number of iterations must be positive");
    } catch (const std::invalid_argument &except) {
        throw std::invalid_argument("Unrecognized value: " + std::string(argv[i]));
    } catch (const std::out_of_range &except) {
        throw std::out_of_range("Argument value is too big " + std::string(argv[i]));
    }
}

void command_parser::CommandLineParser::GetInputFilename(const std::string &current_string) {
    if (!data_.in_filename_.empty()) {
        throw std::invalid_argument("File not recognized.");
    } else {
        data_.in_filename_ = current_string;
    }
}

void command_parser::CommandLineParser::GetCommandLineOptions(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        std::string current_string = std::string(argv[i]);
        switch (current_string[0]) {
            case '-':
                ParseShortCommand(argv, current_string, i);
                break;
            default:
                GetInputFilename(current_string);
                break;
        }
    }
}
