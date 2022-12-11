#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <string>
#include <set>

namespace life {
    class GameField {
    public:
        /*struct GameRules {
            std::set<int> birth;
            std::set<int> survival;
        };
*/
        GameField() = default;

        //GameField(std::string name_of_universe, GameRules rules, );

        virtual ~GameField() = default;

    private:
        struct GameRules {
            std::set<int> birth;
            std::set<int> survival;
        };

        friend class FileParser;

        std::string universe_name_;
        GameRules rules_;
        size_t width_;
        size_t height_;
        bool *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
