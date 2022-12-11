#include "file_parser.h"

const std::string life::FileParser::kDefaultUniverseFilename = "default.life";
//const life::FileParser::Format life::FileParser::kFileFormat{};

void life::FileParser::GetNameOfUniverse(const std::string &buffer, life::GameField &field, bool &name_flag) {
    if (std::isspace(buffer[kFileFormat.kNameOfUniverseIdentifier.size()])) {
        field.universe_name_ = buffer.substr(kFileFormat.kNameOfUniverseIdentifier.size() + 1);
    } else {
        field.universe_name_ = buffer.substr(kFileFormat.kNameOfUniverseIdentifier.size());
        std::cerr << "No space after " + kFileFormat.kNameOfUniverseIdentifier + ':' + buffer
                  << "\n";  //future: to log
    }
    if (!name_flag) {
        name_flag = true;
    } else {
        std::cerr << "Following definition of the universe name: " + buffer
                  << "\n";  //future: to log
    }
}

void life::FileParser::ParseGameRules(const std::string &buffer, life::GameField &field) {

}

void life::FileParser::GetGameRules(const std::string &buffer, life::GameField &field, bool &rule_flag) {
    if (std::isspace(buffer[kFileFormat.kGameRulesIdentifier.size()])) {
        ParseGameRules(buffer.substr(kFileFormat.kGameRulesIdentifier.size() + 1), field);
    } else {
        ParseGameRules(buffer.substr(kFileFormat.kGameRulesIdentifier.size()), field);
        std::cerr << "No space after " + kFileFormat.kGameRulesIdentifier + ':' + buffer
                  << "\n";  //TODO: to log
    }
    if (!rule_flag) {
        rule_flag = true;
    } else {
        std::cerr << "Following definition of the universe name: " + buffer
                  << "\n";  //TODO: to log
    }
}

void life::FileParser::GetOption(const std::string &buffer, GameField &field, bool &name_flag, bool &rule_flag) {
    if (buffer.substr(0, kFileFormat.kNameOfUniverseIdentifier.size()) ==
        kFileFormat.kNameOfUniverseIdentifier) {
        GetNameOfUniverse(buffer, field, name_flag);
    }

    if (buffer.substr(0, kFileFormat.kNameOfUniverseIdentifier.size()) ==
        kFileFormat.kGameRulesIdentifier) {
        GetGameRules(buffer, field, rule_flag);
    }
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

    GameField field;

    while (std::getline(input_file, buffer)) {
        if (buffer[0] == kFileFormat.kOptionSymbol) {
            GetOption(buffer, field, name_flag, rule_flag);
        } else if (std::isdigit(buffer[0])) {
            //GetCoordinates
        } else {
            input_file.close();
            throw std::invalid_argument("Unknown parameter " + buffer);
        }
    }

    if (!name_flag) {
        std::cerr << "Name not set. Use filename as default." << "\n";  //TODO: to log
        field.universe_name_ =
    }

    input_file.close();
    return field;
}
