#ifndef LAB2_FILE_PARSER_H
#define LAB2_FILE_PARSER_H

#include <fstream>
#include <string>

#include "game_field.h"

namespace file_parser {
    class FileParser {
    public:
        struct Format {
            std::string kGameVersion              = "#Life 1.06";
            std::string kNameOfUniverseIdentifier = "#N";
            std::string kGameRulesIdentifier      = "#R";
            std::string kBirthRulePrefix          = "B";
            std::string kSurviveRulePrefix        = "S";
            std::string kRuleSeparator            = "/";
        };

        static const Format kFileFormat;

        static const std::string kDefaultUniverseFilename;

        FileParser() = default;

        virtual ~FileParser() = default;

        life::GameField ReadUniverseFromFile(std::string filename = kDefaultUniverseFilename);
    };
} //namespace file_parser

#endif //LAB2_FILE_PARSER_H
