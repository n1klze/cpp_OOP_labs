#include "life_console_interface.h"

life::LifeConsoleInterface::LifeConsoleInterface(const command_parser::CommandLineParser::Data &start_options) {
    game_handler_ = Game(start_options);
}

void life::LifeConsoleInterface::SimulateGameplay() {
    for (size_t i = 0; i < game_handler_.start_options().iterations; ++i) {
        game_handler_.MakeMove();
    }
    Print();
}

namespace {
    void PrintGameRules(std::ostream &output, const life::Game &game_handler) {
        output << life::FileParser::kFileFormat.kBirthRulePrefix;
        for (auto i: game_handler.game_rules().birth())
            output << i;
        output << life::FileParser::kFileFormat.kRuleSeparator << life::FileParser::kFileFormat.kSurvivalRulePrefix;
        for (auto i: game_handler.game_rules().survival())
            output << i;
    }
}

void life::LifeConsoleInterface::Print() {
    std::cout << game_handler_.game_field().universe_name() << '\n';

    PrintGameRules(std::cout, game_handler_);

    std::cout << '\n' << game_handler_.number_of_iterations();

    std::pair<int, int> coordinate;
    for (int y = 0; y < game_handler_.game_field().height(); ++y) {
        for (int x = 0; x < game_handler_.game_field().width(); ++x) {
            coordinate = {x, y};
            if (x == 0)
                std::cout << '\n';
            std::cout << (game_handler_.game_field()[coordinate].value() ? '#' : ' ');
        }
    }
}
