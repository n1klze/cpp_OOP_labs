#ifndef LAB2_LIFE_CONSOLE_INTERFACE_H
#define LAB2_LIFE_CONSOLE_INTERFACE_H

#include <sstream>
#include <vector>

#include "life_interface.h"

namespace life {
    class LifeConsoleInterface : public LifeInterface {
    public:
        struct SupportiveCommands {
            const std::string kDumpCommand      = "dump";
            const std::string kTickCommand      = "tick";
            const std::string kShortTickCommand = "t";
            const std::string kExitCommand      = "exit";
            const std::string kHelpCommand      = "help";
        };

        explicit LifeConsoleInterface(const command_parser::CommandLineParser::Data &);

        void Print() override;

        static const SupportiveCommands kSupportiveCommands;

    private:
        void SimulateGameplay() override;

        void Dump(const std::string &);
    };
} //namespace life

#endif //LAB2_LIFE_CONSOLE_INTERFACE_H
