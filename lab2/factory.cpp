#include "factory.h"

std::unique_ptr<life::LifeInterface> life::Factory::FactoryMethod(
        life::LifeInterface::GameMode mode, const command_parser::CommandLineParser::Data &start_options) {
    if (mode == LifeInterface::kConsoleGameMode) {
        return std::make_unique<LifeConsoleInterface>(start_options);
    } else if (mode == LifeInterface::kOfflineGameMode) {
        return std::make_unique<LifeOfflineInterface>(start_options);
    } else {
        throw std::invalid_argument("Unknown game mode.");
    }
}