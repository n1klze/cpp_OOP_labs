#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <string>
#include <set>

namespace life {
    class GameField {
    public:
        struct GameRules {
            std::set<int> birth;
            std::set<int> survival;
        };

        GameField() = default;

        virtual ~GameField() = default;

    private:
        friend class FileParser;

        GameRules rules_;
        std::string universe_name_;
        size_t width_;
        size_t height_;
        bool *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
