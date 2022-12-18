#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <memory>
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

            bool IsAlive() const { return value(); }

            bool value() const { return value_; }

        private:
            bool value_;
        };

        GameField();

        GameField(std::string, size_t, size_t);

        virtual ~GameField();

        Cell &operator[](const std::pair<int, int> &);

        const Cell &operator[](const std::pair<int, int> &) const;

        GameField &operator=(const GameField &);

        void SetCoordinate(std::pair<int, int> &);

        std::string universe_name() const { return universe_name_; }

        size_t width() const { return width_; }

        size_t height() const { return height_; }

    private:
        friend class FileParser;

        std::string universe_name_;
        size_t width_;
        size_t height_;
        Cell *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
