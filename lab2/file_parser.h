#ifndef LAB2_FILE_PARSER_H
#define LAB2_FILE_PARSER_H

#include <fstream>
#include <iostream>

#include "game_field.h"

namespace life {
    /*Use to parse universe to game field from file.
     * File header consists of:
     * #N <name of universe>. If not set use filename as default,
     * #R B{0-8}/S{0-8} game rules. If not set use default life rules B3/S23 as default,
     * #S x y size of field. If not set use 100x100 as default.
     * After is only live cells coordinates.
     */
    class FileParser {
    public:
        struct Format {
            const char kOptionSymbol = '#';
            const std::string kGameVersion = "#Life 1.06";
            const std::string kNameOfUniverseIdentifier = "#N";
            const std::string kGameRulesIdentifier = "#R";
            const char kBirthRulePrefix = 'B';
            const char kSurviveRulePrefix = 'S';
            const char kRuleSeparator = '/';
        };

        struct HeaderData {
            std::string name_of_universe;
            std::set<int> birth;
            std::set<int> survival;
            size_t width = 100;
            size_t height = 100;
        };

        FileParser() = default;

        virtual ~FileParser() = default;

        life::GameField ReadUniverseFromFile(const std::string &filename = kDefaultUniverseFilename);

    private:
        static void GetOption(const std::string &, GameField &, bool &, bool &);

        static void GetNameOfUniverse(const std::string &, GameField &, bool &);

        static void GetGameRules(const std::string &, GameField &, bool &);

        static void ParseGameRules(const std::string &, GameField &);

        static const Format kFileFormat;
        static const std::string kDefaultUniverseFilename;
        HeaderData header_;
    };
} //namespace life

#endif //LAB2_FILE_PARSER_H
