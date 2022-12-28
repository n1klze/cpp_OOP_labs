#ifndef LAB2_FILE_PARSER_H
#define LAB2_FILE_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "file_format_exception.h"
#include "game_field.h"
#include "game.h"

namespace file_format {
    const char kOptionSymbol                    = '#';
    const std::string kGameVersion              = "#Life 1.06";
    const std::string kNameOfUniverseIdentifier = "#N";
    const std::string kGameRulesIdentifier      = "#R";
    const std::string kSizeOfFieldIdentifier    = "#S";
    const std::string kBirthRulePrefix          = "B";
    const std::string kSurvivalRulePrefix       = "S";
    const std::string kRuleSeparator            = "/";
}

namespace life {
    /*Use to parse universe to game field from file.
     * File header consists of:
     * #N <name of universe>. If not set use filename as default,
     * #R B{0-8}/S{0-8} game rules. If not set use life rules B3/S23 as default,
     * #S x y size of field. If not set use 32x32 as default.
     * After is only live cells coordinates.
     */
    class FileParser {
    public:
        class HeaderInfo {
        public:
            const GameRules &rules() const { return rules_; }

        private:
            friend class FileParser;

            std::string name_of_universe_;
            GameRules rules_;
            size_t width_ = 32;
            size_t height_ = 32;
            bool is_name_set_ = false;
            bool is_rules_set_ = false;
            bool is_size_set_ = false;
        };

        FileParser() = default;

        virtual ~FileParser() = default;

        life::GameField ReadUniverseFromFile(const std::string &filename = kDefaultUniverseFilename);

        const HeaderInfo &header() const { return header_; }

    private:
        void GetOption(const std::string &);

        void GetNameOfUniverse(const std::string &);

        void GetGameRules(const std::string &);

        void ParseGameRules(const std::string &);

        void GetBirthRuleValues(const std::string &, size_t &);

        void GetSurvivalRuleValues(const std::string &, size_t &);

        void GetSizeOfField(const std::string &);

        void GetWidthAndHeight(const std::string &);

        static void GetCoordinates(std::ifstream &, std::string &, GameField &);

        static const std::string kDefaultUniverseFilename;
        static const GameRules kDefaultRules;
        HeaderInfo header_;
    };
} //namespace life

#endif //LAB2_FILE_PARSER_H
