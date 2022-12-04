#ifndef LAB2_GAME_FIELD_H
#define LAB2_GAME_FIELD_H

namespace life {
    class GameField {
    public:
        GameField();

        ~GameField();

        const std::string kUniverseName;
        const size_t kWidth;
        const size_t kHeight;

    private:
        bool *field_;
    };
} //namespace life

#endif //LAB2_GAME_FIELD_H
