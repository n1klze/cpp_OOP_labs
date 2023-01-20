#include "life_gui_interface.h"

void life_gui::LifeGuiInterface::Tick() {
    game_handler_.MakeMove();
}

namespace {
    void PrintGameRules(std::ostream &output, const life::Game &game_handler) {
        output << "\nGame rules: " << file_format::kBirthRulePrefix;
        for (auto i: game_handler.game_rules().birth())
            output << i;
        output << file_format::kRuleSeparator << file_format::kSurvivalRulePrefix;
        for (auto i: game_handler.game_rules().survival())
            output << i;
        output << '\n';
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

void life_gui::LifeGuiInterface::Dump(const std::string &output_filename) {
    std::ofstream output_file(output_filename);
    output_file.is_open() ?: throw std::invalid_argument("Unable to open output file.");
    output_file << file_format::kGameVersion << '\n';

    output_file << file_format::kNameOfUniverseIdentifier << ' '
                << game_handler_.game_field().universe_name() << '\n';

    output_file << file_format::kGameRulesIdentifier << ' ';
    PrintGameRules(output_file, game_handler_);

    PrintLiveCellsCoordinatesToFile(output_file, game_handler_);

    output_file.close();
}