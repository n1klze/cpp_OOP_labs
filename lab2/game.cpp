#include "game.h"

life::Game::Game(command_parser::CommandLineParser::Data command_line_parameters) : start_options_(std::move(command_line_parameters)) {
    FileParser file_parser;
    if (start_options_.in_filename.empty()) {
        game_field_ = file_parser.ReadUniverseFromFile();
    } else {
        game_field_ = file_parser.ReadUniverseFromFile(start_options_.in_filename);
    }
    game_rules_ = file_parser.header().rules_;
}

void life::Game::MakeMove() {

}
