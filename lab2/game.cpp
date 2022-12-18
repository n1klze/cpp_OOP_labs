#include "game.h"

life::Game::Game(command_parser::CommandLineParser::Data command_line_parameters) : start_options_(
        std::move(command_line_parameters)) {
    FileParser file_parser;
    if (start_options_.in_filename.empty()) {
        game_field_ = file_parser.ReadUniverseFromFile();
    } else {
        game_field_ = file_parser.ReadUniverseFromFile(start_options_.in_filename);
    }
    game_rules_ = file_parser.header().rules_;
}

int life::Game::CountNumberOfNeighbours(const std::pair<int, int> &coordinate) {
    int number_of_neighbours = game_field()[std::make_pair(coordinate.first - 1, coordinate.second - 1)].value() +
                               game_field()[std::make_pair(coordinate.first - 1, coordinate.second)].value() +
                               game_field()[std::make_pair(coordinate.first - 1, coordinate.second + 1)].value() +
                               game_field()[std::make_pair(coordinate.first, coordinate.second - 1)].value() +
                               game_field()[std::make_pair(coordinate.first, coordinate.second + 1)].value() +
                               game_field()[std::make_pair(coordinate.first + 1, coordinate.second - 1)].value() +
                               game_field()[std::make_pair(coordinate.first + 1, coordinate.second)].value() +
                               game_field()[std::make_pair(coordinate.first + 1, coordinate.second + 1)].value();
    return number_of_neighbours;
}

void life::Game::MakeMove() {
    GameField new_field = GameField(game_field_.universe_name(), game_field_.width(), game_field_.height());

    std::pair<int, int> coordinate;
    for (int x = 0; x < game_field_.width(); ++x) {
        for (int y = 0; y < game_field_.height(); ++y) {
            coordinate = {x, y};
            int number_of_neighbours = this->CountNumberOfNeighbours(coordinate);
            if (game_field_[coordinate].IsAlive()) {
                if (game_rules_.survival().find(number_of_neighbours) != game_rules_.survival().end()) {
                    new_field[coordinate] = GameField::Cell(true);
                } else {
                    new_field[coordinate] = GameField::Cell(false);
                }
            } else {
                if (game_rules_.birth().find(number_of_neighbours) != game_rules_.birth().end()) {
                    new_field[coordinate] = GameField::Cell(true);
                } else {
                    new_field[coordinate] = GameField::Cell(false);
                }
            }
        }
    }

    game_field_ = new_field;
    ++number_of_iterations_;
}
