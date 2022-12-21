#ifndef LAB2_FILE_PARSER_H
#define LAB2_FILE_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "file_format_exception.h"
#include "game_field.h"
#include "game.h"


namespace life {
    /*Use to parse universe to game field from file.
     * File header consists of:
     * #N <name of universe>. If not set use filename as default,
     * #R B{0-8}/S{0-8} game rules. If not set use life rules B3/S23 as default,
     * #S x y size of field. If not set use 100x100 as default.
     * After is only live cells coordinates.
     */
    class FileParser {
    public:
        struct Format {
            const char kOptionSymbol                    = '#';
            const std::string kGameVersion              = "#Life 1.06";
            const std::string kNameOfUniverseIdentifier = "#N";
            const std::string kGameRulesIdentifier      = "#R";
            const std::string kBirthRulePrefix          = "B";
            const std::string kSurvivalRulePrefix       = "S";
            const std::string kRuleSeparator            = "/";
        };

        struct HeaderInfo {
            std::string name_of_universe;
            GameRules rules_;
            size_t width = 30;
            size_t height = 30;
            bool is_name_set = false;
            bool is_rules_set = false;
        };

        FileParser() = default;

        virtual ~FileParser() = default;

        static const Format kFileFormat;

        life::GameField ReadUniverseFromFile(const std::string &filename = kDefaultUniverseFilename);

        const HeaderInfo &header() const { return header_; }

    private:
        void GetOption(const std::string &);

        void GetNameOfUniverse(const std::string &);

        void GetGameRules(const std::string &);

        void ParseGameRules(const std::string &);

        void GetBirthRuleValues(const std::string &, size_t &);

        void GetSurvivalRuleValues(const std::string &, size_t &);

        static void GetCoordinates(std::ifstream &, std::string &, GameField &);

        static const std::string kDefaultUniverseFilename;
        static const GameRules kDefaultRules;
        HeaderInfo header_;
    };
} //namespace life

#endif //LAB2_FILE_PARSER_H
