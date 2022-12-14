#ifndef LAB2_GAME_H
#define LAB2_GAME_H

#include <utility>

#include "command_line_parser.h"
#include "file_parser.h"

namespace life {
    class Game {
    public:
        Game() = default;

        Game(command_parser::CommandLineParser::Data);

        ~Game() = default;

        void MakeMove();

        command_parser::CommandLineParser::Data start_options() const { return start_options_; }

        const GameRules &game_rules() const { return game_rules_; }

        const GameField &game_field() const { return game_field_; }

    private:
        command_parser::CommandLineParser::Data start_options_;
        GameRules game_rules_;
        GameField game_field_;
    };
} //namespace life

#endif //LAB2_GAME_H
