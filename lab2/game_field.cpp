#include "game_field.h"

life::GameField::Cell::Cell() : value_(false) {
    //empty
}

life::GameField::Cell::Cell(bool value) {
    value_ = value;
}

life::GameField::Cell &life::GameField::operator[](std::pair<int, int> coordinate) {
    return field_[(coordinate.first % width_) * width_ + (coordinate.second % height_)];
}

life::GameField::GameField() : universe_name_(""), width_(0), height_(0), field_(nullptr) {
    //empty
}

life::GameField::GameField(std::string name_of_universe, size_t width, size_t height) :
        universe_name_(std::move(name_of_universe)), width_(width), height_(height) {
    field_ = new Cell[width * height];
}

life::GameField::~GameField() {
    delete[] field_;
}

void life::GameField::SetCoordinate(std::pair<int, int> coordinate) {
    this->operator[](coordinate) = Cell(true);
}
