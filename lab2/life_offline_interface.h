#ifndef LAB2_LIFE_OFFLINE_INTERFACE_H
#define LAB2_LIFE_OFFLINE_INTERFACE_H

#include "life_interface.h"

namespace life {
    class LifeOfflineInterface : public LifeInterface {
    public:
        explicit LifeOfflineInterface(const command_parser::CommandLineParser::ParsedCmdParameters &);

        void Print() override;

    private:
        void SimulateGameplay() override;
    };
} //namespace life

#endif //LAB2_LIFE_OFFLINE_INTERFACE_H
