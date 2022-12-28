#include "life_offline_interface.h"

life::LifeOfflineInterface::LifeOfflineInterface(const command_parser::CommandLineParser::ParsedCmdParameters &start_options) {
    game_handler_ = Game(start_options);
}

void life::LifeOfflineInterface::SimulateGameplay() {
    for (size_t i = 0; i < game_handler_.start_options().iterations(); ++i) {
        game_handler_.MakeMove();
    }
    Print();
}

namespace {
    void PrintGameRules(std::ostream &output, const life::Game &game_handler) {
        output << file_format::kBirthRulePrefix;
        for (auto i: game_handler.game_rules().birth())
            output << i;
        output << file_format::kRuleSeparator << file_format::kSurvivalRulePrefix;
        for (auto i: game_handler.game_rules().survival())
            output << i;
    }

    void PrintLiveCellsCoordinatesToFile(std::ofstream &output_file, const life::Game &game_handler) {
        std::pair<int, int> coordinate;
        for (int x = 0; x < game_handler.game_field().width(); ++x) {
            for (int y = 0; y < game_handler.game_field().width(); ++y) {
                coordinate = {x, y};
                if (game_handler.game_field()[coordinate].IsAlive())
                    output_file << '\n' << x << ' ' << y;
            }
        }
    }
}

void life::LifeOfflineInterface::Print() {
    std::ofstream output_file(game_handler_.start_options().out_filename());
    output_file.is_open() ?: throw std::invalid_argument("Unable to open output file.");
    output_file << file_format::kGameVersion << '\n';

    output_file << file_format::kNameOfUniverseIdentifier << ' '
                << game_handler_.game_field().universe_name() << '\n';

    output_file << file_format::kGameRulesIdentifier << ' ';
    PrintGameRules(output_file, game_handler_);

    PrintLiveCellsCoordinatesToFile(output_file, game_handler_);

    output_file.close();
}
