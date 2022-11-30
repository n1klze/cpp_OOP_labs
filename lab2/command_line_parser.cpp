#include "command_line_parser.h"

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
                                data_.iterations = std::stoi(std::string(argv[++i]), nullptr);
                            } catch (const std::invalid_argument &except) {
                                throw std::invalid_argument("Unrecognized value: " + std::string(argv[i]) + '\n');
                            } catch (const std::out_of_range &except) {
                                throw std::out_of_range("Warning: numeric overflow: " + std::string(argv[i]) + '\n');
                            }
                        } else {
                            throw std::invalid_argument("Unrecognized command line option: " + current_string + '\n');
                        }
                        break;
                    case 'o':   //case -o...
                        if (current_string == "-o") {
                            data_.out_filename = std::string(argv[++i]);
                        } else {
                            throw std::invalid_argument("Unrecognized command line option: " + current_string + '\n');
                        }
                        break;
                    default:
                        throw std::invalid_argument("Unrecognized command line option: " + current_string + '\n');
                }
                break;
            default:
                if (!data_.in_filename.empty()) {
                    throw std::invalid_argument("File not recognized.\n");
                } else {
                    data_.in_filename = current_string;
                }
                break;
        }
    }
}
