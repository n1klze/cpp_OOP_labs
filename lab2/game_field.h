#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <string>

#include "game_rules.h"

namespace life {
    class GameField {
    public:
        class Cell {
        public:
            Cell();

            explicit Cell(bool);

            Cell &operator=(const Cell &) = default;

            bool value() { return value_; }

        private:
            bool value_;
        };

        GameField();

        GameField(std::string, size_t, size_t);

        virtual ~GameField();

        Cell &operator[](std::pair<int, int>);

        void SetCoordinate(std::pair<int, int>);

    private:
        friend class FileParser;

        std::string universe_name_;
        size_t width_;
        size_t height_;
        Cell *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
