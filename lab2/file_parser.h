#ifndef LAB2_FILE_PARSER_H
#define LAB2_FILE_PARSER_H

#include <fstream>

#include "game_field.h"

namespace life {
    class FileParser {
    public:
        struct Format {
            const char kOptionSymbol                    = '#';
            const std::string kGameVersion              = "#Life 1.06";
            const std::string kNameOfUniverseIdentifier = "#N";
            const std::string kGameRulesIdentifier      = "#R";
            const char kBirthRulePrefix                 = 'B';
            const char kSurviveRulePrefix               = 'S';
            const char kRuleSeparator                   = '/';
        };

        FileParser() = default;

        virtual ~FileParser() = default;

        life::GameField ReadUniverseFromFile(const std::string& filename = kDefaultUniverseFilename);

    private:
        friend void GetOption(std::ifstream &input_file, std::string &buffer, GameField &field);
        static const Format kFileFormat;
        static const std::string kDefaultUniverseFilename;
    };
} //namespace life

#endif //LAB2_FILE_PARSER_H
