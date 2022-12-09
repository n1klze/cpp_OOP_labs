#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

#include <string>

namespace life {
    class GameField {
    public:
        GameField();

        virtual ~GameField();

    private:
        friend class FileParser;

        std::string kUniverseName;
        size_t kWidth;
        size_t kHeight;
        bool *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
