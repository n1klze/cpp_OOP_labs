#ifndef LAB2_COMMAND_LINE_PARSER_H
#define LAB2_COMMAND_LINE_PARSER_H

#include <iostream>
#include <stdexcept>
#include <string>

namespace command_parser {
    class CommandLineParser {
    public:
        struct Data {
            int iterations;
            std::string in_filename;
            std::string out_filename;
        };

        void GetCommandLineOptions(int argc, char **argv);

        Data data() const { return data_; }

    private:
        static const std::string kUsageMessage;
        Data data_;
    };
} //namespace command_parser

#endif //LAB2_COMMAND_LINE_PARSER_H
