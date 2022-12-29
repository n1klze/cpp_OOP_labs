#include "life_interface.h"

int main(int argc, char **argv) {
    try {
        life::LifeInterface::StartGame(argc, argv);
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
