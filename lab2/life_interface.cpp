#include "life_interface.h"

#include <memory>

std::unique_ptr<life::LifeInterface> life::Factory::CreateInterface(
        life::LifeInterface::GameMode mode, const command_parser::CommandLineParser::Data &start_options) {
    if (mode == LifeInterface::kConsoleGameMode) {
        return std::make_unique<LifeConsoleInterface>(start_options);
    } else if (mode == LifeInterface::kOfflineGameMode) {
        return std::make_unique<LifeOfflineInterface>(start_options);
    } else {
        throw std::invalid_argument("Unknown game mode.");
    }
}

life::LifeConsoleInterface::LifeConsoleInterface(const command_parser::CommandLineParser::Data &start_options) {
    game_handler_ = Game(start_options);
}

life::LifeOfflineInterface::LifeOfflineInterface(const command_parser::CommandLineParser::Data &start_options) {
    game_handler_ = Game(start_options);
}

void life::LifeInterface::StartGame(int argc, char **argv) {
    command_parser::CommandLineParser command_parser;
    command_parser.GetCommandLineOptions(argc, argv);

    Factory factory;
    std::unique_ptr<LifeInterface> interface;

    if (command_parser.data().out_filename.empty()) {
        interface = factory.CreateInterface(kConsoleGameMode, command_parser.data());
    } else {
        interface = factory.CreateInterface(kOfflineGameMode, command_parser.data());
    }

    interface->SimulateGameplay();
}

void life::LifeConsoleInterface::SimulateGameplay() {
    for (size_t i = 0; i < game_handler_.start_options().iterations; ++i) {
        game_handler_.MakeMove();
    }
    Print();
}

void life::LifeOfflineInterface::SimulateGameplay() {
    for (size_t i = 0; i < game_handler_.start_options().iterations; ++i) {
        game_handler_.MakeMove();
    }
    Print();
}

namespace {
    void PrintGameRules(std::ostream &output, const life::Game &game_handler) {
        for (auto i: game_handler.game_rules().birth())
            output << i;
        output << life::FileParser::kFileFormat.kRuleSeparator << life::FileParser::kFileFormat.kSurvivalRulePrefix;
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

void life::LifeOfflineInterface::Print() {
    std::ofstream output_file(game_handler_.start_options().out_filename);
    output_file.is_open() ?: throw std::invalid_argument("Unable to open output file.");
    output_file << life::FileParser::kFileFormat.kGameVersion << '\n';

    output_file << life::FileParser::kFileFormat.kNameOfUniverseIdentifier << ' '
                << game_handler_.game_field().universe_name() << '\n';

    output_file << life::FileParser::kFileFormat.kGameRulesIdentifier << ' '
                << life::FileParser::kFileFormat.kBirthRulePrefix;
    PrintGameRules(output_file, game_handler_);

    std::pair<int, int> coordinate;
    for (int y = 0; y < game_handler_.game_field().height(); ++y) {
        for (int x = 0; x < game_handler_.game_field().width(); ++x) {
            coordinate = {x, y};
            if (x == 0)
                std::cout << '\n';
            std::cout << (game_handler_.game_field()[coordinate].value()/* ? '#' : ' '*/);
        }
    }

    PrintLiveCellsCoordinatesToFile(output_file, game_handler_);

    output_file.close();
}
