#ifndef LAB2_COMMAND_LINE_PARSER_H
#define LAB2_COMMAND_LINE_PARSER_H

#include <iostream>
#include <stdexcept>
#include <string>

namespace command_parser {
    class CommandLineParser {
    public:
        class ParsedCmdParameters {
        public:
            ParsedCmdParameters() : iterations_(0) {}

            int iterations() const { return iterations_; }

            const std::string &in_filename() const { return in_filename_; }

            const std::string &out_filename() const { return out_filename_; }

            void iterations(int number_of_iterations) { iterations_ = number_of_iterations; }

            void in_filename(const std::string &in_filename) { in_filename_ = in_filename; }

        private:
            friend class CommandLineParser;
            int iterations_;
            std::string in_filename_;
            std::string out_filename_;
        };

        void GetCommandLineOptions(int argc, char **argv);

        ParsedCmdParameters data() const { return data_; }

    private:
        void ParseShortCommand(char **, const std::string &, int &);

        void GetNumberOfIterations(char **, int &);

        void GetInputFilename(const std::string &);

        static const std::string kUsageMessage;
        ParsedCmdParameters data_;
    };
} //namespace command_parser

#endif //LAB2_COMMAND_LINE_PARSER_H
