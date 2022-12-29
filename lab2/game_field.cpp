#include "game_field.h"

life::GameField::Cell::Cell() : value_(false) {
    //empty
}

life::GameField::Cell::Cell(bool value) {
    value_ = value;
}

life::GameField::Cell &life::GameField::operator[](const std::pair<int, int> &coordinate) {
    return field_[(((coordinate.first > 0) ? coordinate.first : width_ + coordinate.first) % width_) * width_ +
                  (((coordinate.second > 0) ? coordinate.second : height_ + coordinate.second) % height_)];
}

const life::GameField::Cell &life::GameField::operator[](const std::pair<int, int> &coordinate) const {
    return field_[(((coordinate.first > 0) ? coordinate.first : width_ + coordinate.first) % width_) * width_ +
                  (((coordinate.second > 0) ? coordinate.second : height_ + coordinate.second) % height_)];
}

life::GameField &life::GameField::operator=(const life::GameField &other) {
    if (std::addressof(other) == this)
        return *this;
    universe_name_ = other.universe_name_;
    width_ = other.width_;
    height_ = other.height_;
    field_ = new Cell[width_ * height_];
    for (size_t i = 0; i < width_ * height_; ++i)
        field_[i] = other.field_[i];
    return *this;
}

life::GameField::GameField() : width_(0), height_(0), field_(nullptr) {
    //empty
}

life::GameField::GameField(std::string name_of_universe, size_t width, size_t height) :
        universe_name_(std::move(name_of_universe)), width_(width), height_(height) {
    field_ = new Cell[width * height];
}

life::GameField::~GameField() {
    delete[] field_;
}

void life::GameField::SetCoordinate(std::pair<int, int> &coordinate) {
    (*this)[coordinate] = Cell(true);
}
