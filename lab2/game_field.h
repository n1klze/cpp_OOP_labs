#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <string>

#include "game_rules.h"

namespace life {
    class GameField {
    public:
        GameField() = default;

        //GameField(std::string name_of_universe, GameRules rules, );

        virtual ~GameField() = default;

    private:
        friend class FileParser;

        std::string universe_name_;
        GameRules rules_;
        size_t width_;
        size_t height_;
        bool *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
