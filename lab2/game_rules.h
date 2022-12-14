#ifndef LAB2_GAME_RULES_H
#define LAB2_GAME_RULES_H

#include <set>

namespace life {
    class GameRules {
    public:
        enum NotableLifeLikeRules {
            kDefaultLifeRules
        };

        GameRules() = default;

        explicit GameRules(int) noexcept;

        GameRules(const GameRules &) = default;

        ~GameRules() = default;

        GameRules &operator=(const GameRules &) = default;

        const std::set<int> &birth() const { return birth_; }

        const std::set<int> &survival() const { return survival_; }

    private:
        friend class FileParser;

        std::set<int> birth_;
        std::set<int> survival_;
    };
} //namespace life

#endif //LAB2_GAME_RULES_H
