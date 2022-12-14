#include "life_interface.h"

#include <memory>

std::unique_ptr<life::LifeInterface> life::Factory::CreateInterface(life::LifeInterface::GameMode mode,
                                                                    command_parser::CommandLineParser::Data start_options) {
    if (mode == LifeInterface::kConsoleGameMode) {
        return std::make_unique<LifeConsoleInterface>(std::move(start_options));
    } else if (mode == LifeInterface::kOfflineGameMode) {
        return std::make_unique<LifeOfflineInterface>(std::move(start_options));
    } else {
        throw std::invalid_argument("Unknown game mode.");
    }
}

life::LifeConsoleInterface::LifeConsoleInterface(command_parser::CommandLineParser::Data start_options) :
        game_handler_(Game(std::move(start_options))) {
    //empty
}

life::LifeOfflineInterface::LifeOfflineInterface(command_parser::CommandLineParser::Data start_options) :
        game_handler_(Game(std::move(start_options))) {
    //empty
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

    interface->Print();
}

void life::LifeConsoleInterface::Print() {
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

    for (auto i : game_handler_.game_rules().birth())
        output_file << i;
    output_file << life::FileParser::kFileFormat.kRuleSeparator << life::FileParser::kFileFormat.kSurvivalRulePrefix;
    for (auto i: game_handler_.game_rules().survival())
        output_file << i;

    std::pair<int, int> coordinate;
    for (int y = 0; y < game_handler_.game_field().height(); ++y) {
        for (int x = 0; x < game_handler_.game_field().width(); ++x) {
            coordinate = {x, y};
            if (x == 0)
                std::cout << '\n';
            std::cout << (game_handler_.game_field()[coordinate].value() ? '#' : ' ');
        }
    }

    for (int x = 0; x < game_handler_.game_field().width(); ++x) {
        for (int y = 0; y < game_handler_.game_field().width(); ++y) {
            coordinate = {x, y};
            if (game_handler_.game_field()[coordinate].value())
                output_file << '\n' << x << ' ' << y;
        }
    }

    output_file.close();
}
