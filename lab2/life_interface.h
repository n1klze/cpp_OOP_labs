#ifndef LAB2_LIFE_INTERFACE_H
#define LAB2_LIFE_INTERFACE_H

#include <algorithm>
#include <memory>

#include "command_line_parser.h"
#include "game.h"

namespace life {
    class LifeInterface {
    public:
        enum GameMode {
            kConsoleGameMode,
            kOfflineGameMode
        };

        virtual ~LifeInterface() = default;

        static void StartGame(int, char **);

        virtual void Print() = 0;
    };

    class LifeConsoleInterface : public LifeInterface {
    public:
        explicit LifeConsoleInterface(command_parser::CommandLineParser::Data);

        void Print() override;

    private:
        Game game_handler_;
    };

    class LifeOfflineInterface : public LifeInterface {
    public:
        explicit LifeOfflineInterface(command_parser::CommandLineParser::Data);

        void Print() override;

    private:
        Game game_handler_;
    };

    class Factory {
    public:
        std::unique_ptr<LifeInterface> CreateInterface(LifeInterface::GameMode, command_parser::CommandLineParser::Data);
    };
} //namespace life

#endif //LAB2_LIFE_INTERFACE_H
