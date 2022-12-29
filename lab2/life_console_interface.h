#ifndef LAB2_LIFE_CONSOLE_INTERFACE_H
#define LAB2_LIFE_CONSOLE_INTERFACE_H

#include <sstream>
#include <vector>

#include "life_interface.h"

namespace supportive_commands {
    const std::string kDumpCommand      = "dump";
    const std::string kTickCommand      = "tick";
    const std::string kShortTickCommand = "t";
    const std::string kExitCommand      = "exit";
    const std::string kHelpCommand      = "help";
}

namespace life {
    class LifeConsoleInterface : public LifeInterface {
    public:
        explicit LifeConsoleInterface(const command_parser::CommandLineParser::ParsedCmdParameters &);

        void Print() override;

    private:
        void SimulateGameplay() override;

        void Dump(const std::string &);
    };
} //namespace life

#endif //LAB2_LIFE_CONSOLE_INTERFACE_H
