#ifndef LAB2_LIFE_GUI_INTERFACE_H
#define LAB2_LIFE_GUI_INTERFACE_H

#include "../life_interface.h"

namespace life_gui {
    void startGame(const std::string &input_filename);

    class LifeGuiInterface{
    public:
        LifeGuiInterface() = default;

        void Dump(const std::string&);

        void Tick();



    private:
        life::Game game_handler_;
    };
}

#endif //LAB2_LIFE_GUI_INTERFACE_H
