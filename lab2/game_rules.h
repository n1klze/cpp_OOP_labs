#ifndef LAB2_GAME_RULES_H
#define LAB2_GAME_RULES_H

#include <set>

namespace life {
    class GameRules {
    public:
        std::set<int> birth() { return birth_; }

        std::set<int> survival() { return survival_; }

    private:
        friend class FileParser;

        std::set<int> birth_;
        std::set<int> survival_;
    };
} //namespace life

#endif //LAB2_GAME_RULES_H
