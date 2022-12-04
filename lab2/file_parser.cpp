#include "file_parser.h"

const std::string file_parser::FileParser::kDefaultUniverseFilename = "default.life";

life::GameField file_parser::FileParser::ReadUniverseFromFile(std:: string filename) {
    std::ifstream input_file(filename);
    input_file.is_open() ? : throw std::invalid_argument("Unable to open input file.");


}