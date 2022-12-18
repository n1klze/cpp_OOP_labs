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

        /*const Game &game_handler() const { return game_handler_; }

        void set_game_handler(const Game &data) { game_handler_ = data; }*/

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

    class Factory {
    public:
        std::unique_ptr<LifeInterface> CreateInterface(LifeInterface::GameMode,
                                                       const command_parser::CommandLineParser::Data &);
    };
} //namespace life

#endif //LAB2_LIFE_INTERFACE_H
