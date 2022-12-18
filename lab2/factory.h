#ifndef LAB2_FACTORY_H
#define LAB2_FACTORY_H

#include <memory>

#include "life_interface.h"

namespace life {
    class Factory {
    public:
        std::unique_ptr<LifeInterface> FactoryMethod(LifeInterface::GameMode,
                                                     const command_parser::CommandLineParser::Data &);
    };
}

#endif //LAB2_FACTORY_H
