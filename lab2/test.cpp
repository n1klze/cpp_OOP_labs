#include <iostream>

#include <gtest/gtest.h>

#include "life_interface.h"

class GameMechanicsTest : public ::testing::Test {
public:
    std::string test_input_filename = "../examples/test_glider.life";
    std::string test_output_filename = "../examples/check_test_glider.life";
    std::vector<std::pair<int, int>> live_cells_coordinates = {std::make_pair(0, 2), std::make_pair(1, 0),
                                                               std::make_pair(1, 2), std::make_pair(2, 1),
                                                               std::make_pair(2, 2)};
    std::vector<std::pair<int, int>> coordinates_after_iteration = {std::make_pair(0, 1), std::make_pair(1, 2),
                                                                    std::make_pair(1, 3), std::make_pair(2, 1),
                                                                    std::make_pair(2, 2)};
};

TEST_F(GameMechanicsTest, init_test) {
    command_parser::CommandLineParser::ParsedCmdParameters init_data;
    init_data.in_filename(test_input_filename);
    life::Game game_handler(init_data);
    for (auto i: live_cells_coordinates)
        EXPECT_TRUE(game_handler.game_field()[i].IsAlive());
}

TEST_F(GameMechanicsTest, gameplay_test) {
    command_parser::CommandLineParser::ParsedCmdParameters init_data;
    init_data.in_filename(test_input_filename);
    init_data.iterations(1);
    life::Game game_handler(init_data);
    game_handler.MakeMove();
    for (auto i: coordinates_after_iteration)
        EXPECT_TRUE(game_handler.game_field()[i].IsAlive());
}

TEST_F(GameMechanicsTest, output_test) {
    command_parser::CommandLineParser::ParsedCmdParameters init_data;
    init_data.in_filename(test_input_filename);
    init_data.iterations(100);
    life::Game game_handler(init_data);
    for (int i = 0; i < game_handler.start_options().iterations(); ++i)
        game_handler.MakeMove();

    life::FileParser file_parser;
    life::GameField check_field = file_parser.ReadUniverseFromFile(test_output_filename);
    for (int x = 0; x < game_handler.game_field().width(); ++x){
        for (int y = 0; y < game_handler.game_field().height(); ++y) {
            std::pair<int, int> current_coordinate = std::make_pair(x, y);
            EXPECT_EQ(check_field[current_coordinate].value(), game_handler.game_field()[current_coordinate].value());
        }
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}