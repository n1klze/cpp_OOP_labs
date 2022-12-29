#include "life_interface.h"

#include "factory.h"

void life::LifeInterface::StartGame(int argc, char **argv) {
    command_parser::CommandLineParser command_parser;
    command_parser.GetCommandLineOptions(argc, argv);

    Factory factory;
    std::unique_ptr<LifeInterface> interface;

    if (command_parser.data().out_filename().empty()) {
        interface = factory.FactoryMethod(kConsoleGameMode, command_parser.data());
    } else {
        interface = factory.FactoryMethod(kOfflineGameMode, command_parser.data());
    }

    interface->SimulateGameplay();
}

