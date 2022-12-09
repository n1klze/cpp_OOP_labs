#include "file_parser.h"

const std::string life::FileParser::kDefaultUniverseFilename = "default.life";

void life::GetOption(std::ifstream &input_file, std::string &buffer, GameField &field) {

}

life::GameField life::FileParser::ReadUniverseFromFile(const std::string &filename) {
    std::ifstream input_file(filename);
    input_file.is_open() ?: throw std::invalid_argument("Unable to open input file.");

    bool name_flag = false;
    bool rule_flag = false;

    std::string buffer;

    std::getline(input_file, buffer);
    if (buffer != kFileFormat.kGameVersion) {
        input_file.close();
        throw std::invalid_argument("Unsupported version.");
    }

    std::getline(input_file, buffer);
    if (buffer[0] == kFileFormat.kOptionSymbol) {
        if (buffer.substr(0, kFileFormat.kNameOfUniverseIdentifier.size()) == kFileFormat.kNameOfUniverseIdentifier) {
            
        }
    }
}
