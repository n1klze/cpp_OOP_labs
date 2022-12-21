#include "game_rules.h"

namespace {
    const std::set<int> kDefaultBirthRule{3};
    const std::set<int> kDefaultSurvivalRule{2, 3};
}

life::GameRules::GameRules(int identifier) noexcept {
    if (identifier == kDefaultLifeRules) {
        birth_ = kDefaultBirthRule;
        survival_ = kDefaultSurvivalRule;
    } else {
        birth_ = {};
        survival_ = {};
    }
}