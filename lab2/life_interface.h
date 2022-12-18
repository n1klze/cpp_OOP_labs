#ifndef LAB2_LIFE_INTERFACE_H
#define LAB2_LIFE_INTERFACE_H

#include <algorithm>

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

    protected:
        LifeInterface() = default;

        virtual void SimulateGameplay() = 0;

        Game game_handler_;
    };

    class LifeConsoleInterface : public LifeInterface {
    public:
        explicit LifeConsoleInterface(const command_parser::CommandLineParser::Data &);

        void Print() override;

    private:
        void SimulateGameplay() override;
    };

    class LifeOfflineInterface : public LifeInterface {
    public:
        explicit LifeOfflineInterface(const command_parser::CommandLineParser::Data &);

        void Print() override;

    private:
        void SimulateGameplay() override;
    };
} //namespace life

#endif //LAB2_LIFE_INTERFACE_H
