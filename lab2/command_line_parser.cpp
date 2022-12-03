#include "command_line_parser.h"

const std::string command_parser::CommandLineParser::kUsageMessage =
        "Usage: program [-h | --help] [filename1.life] [-i x | --input=x] [-o filename2.life | --output=filename2.life]\n"
        "-------------------------------------------------------------------------------------------------------------\n"
        "-h, --help\n"
        "\tPrint (on the standard output) usage message with a description of command-line options.\n"
        "filename1.life\n"
        "\tinput file with universe description in the Life 1.06 file format.\n"
        "-i x | --input=<x>\n"
        "\tSet the number of iterations to x.\n"
        "-o filename2.life, --output=filename2.life\n"
        "\tPlace output in file filename2.life, where the universe will be save after the game ends.";

void command_parser::CommandLineParser::GetCommandLineOptions(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string current_string = std::string(argv[i]);
        switch (current_string[0]) {
            case '-':
                switch (current_string[1]) {
                    case '-':   //case: --...
                        break;
                    case 'i':   //case -i...
                        if (current_string == "-i") {
                            try {
                                std::size_t pos{};
                                data_.iterations = std::stoi(argv[++i], &pos);
                                if (pos != std::string(argv[i]).size())
                                    throw std::invalid_argument("Number of iterations must be a numeric.");
                                if (data_.iterations < 0)
                                    throw std::invalid_argument("Number of iterations must be positive");
                            } catch (const std::invalid_argument &except) {
                                throw std::invalid_argument("Unrecognized value: " + std::string(argv[i]));
                            } catch (const std::out_of_range &except) {
                                throw std::out_of_range("Argument value is too big " + std::string(argv[i]));
                            }
                        } else {
                            throw std::invalid_argument("Unrecognized command line option: " + current_string);
                        }
                        break;
                    case 'o':   //case -o...
                        if (current_string == "-o") {
                            data_.out_filename = std::string(argv[++i]);
                        } else {
                            throw std::invalid_argument("Unrecognized command line option: " + current_string);
                        }
                        break;
                    case 'h':
                        if (current_string == "-h") {
                            std::cout << kUsageMessage << std::endl;
                        } else {
                            throw std::invalid_argument("Unrecognized command line option: " + current_string);
                        }
                        break;
                    default:
                        throw std::invalid_argument("Unrecognized command line option: " + current_string);
                }
                break;
            default:
                if (!data_.in_filename.empty()) {
                    throw std::invalid_argument("File not recognized.");
                } else {
                    data_.in_filename = current_string;
                }
                break;
        }
    }
}

