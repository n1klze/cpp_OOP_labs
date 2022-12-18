#ifndef LAB2_LIFE_CONSOLE_INTERFACE_H
#define LAB2_LIFE_CONSOLE_INTERFACE_H

#include "life_interface.h"

namespace life {
    class LifeConsoleInterface : public LifeInterface {
    public:
        explicit LifeConsoleInterface(const command_parser::CommandLineParser::Data &);

        void Print() override;

    private:
        void SimulateGameplay() override;
    };
} //namespace life

#endif //LAB2_LIFE_CONSOLE_INTERFACE_H
