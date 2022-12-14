#include "file_parser.h"

namespace {
    const char kRuleProhibitedValue = '9';
}

const std::string life::FileParser::kDefaultUniverseFilename = "../examples/default.life";
const life::GameRules life::FileParser::kDefaultRules(GameRules::NotableLifeLikeRules::kDefaultLifeRules);

void life::FileParser::GetNameOfUniverse(const std::string &buffer) {
    if (std::isspace(buffer[file_format::kNameOfUniverseIdentifier.size()])) {
        header_.name_of_universe_ = buffer.substr(file_format::kNameOfUniverseIdentifier.size() + 1);
    } else {
        header_.name_of_universe_ = buffer.substr(file_format::kNameOfUniverseIdentifier.size());
        std::cerr << "No space after " + file_format::kNameOfUniverseIdentifier + ':' + buffer << "\n";
    }
    if (!header_.is_name_set_) {
        header_.is_name_set_ = true;
    } else {
        throw FileFormatException("Following definition of the universe name: " + buffer);
    }
}

void life::FileParser::GetBirthRuleValues(const std::string &buffer, size_t &i) {
    for (; i < buffer.length() && std::isdigit(buffer[i]); ++i) {
        if (buffer[i] == kRuleProhibitedValue)
            throw FileFormatException("Invalid value " + std::to_string(buffer[i]) + " in " + buffer);
        if (header_.rules_.birth_.find(buffer[i] - '0') != header_.rules_.birth_.end()) {
            std::cerr << "Rule " << buffer[i] << " defined twice in birth rules: " + buffer << '\n';
        } else {
            header_.rules_.birth_.insert(buffer[i] - '0');
        }
    }
    if (header_.rules_.birth_.empty()) {
        header_.rules_.birth_.insert(0);
        std::cerr << "Birth rules not set explicitly, use B0/S...." << '\n';
    }
}

void life::FileParser::GetSurvivalRuleValues(const std::string &buffer, size_t &i) {
    for (; i < buffer.length(); ++i) {
        if (!std::isdigit(buffer[i]))
            throw FileFormatException("Invalid value " + std::to_string(buffer[i]) + " in " + buffer);
        if (buffer[i] == kRuleProhibitedValue)
            throw FileFormatException("Invalid value " + std::to_string(buffer[i]) + " in " + buffer);
        if (header_.rules_.survival_.find(buffer[i] - '0') != header_.rules_.survival_.end()) {
            std::cerr << "Rule" << buffer[i] << "defined twice in survival rules: " + buffer << '\n';
        } else {
            header_.rules_.survival_.insert(buffer[i] - '0');
        }
    }
    if (header_.rules_.survival_.empty()) {
        header_.rules_.survival_.insert(0);
        std::cerr << "Survival rules not set explicitly, use B.../S0." << '\n';
    }
}

void life::FileParser::ParseGameRules(const std::string &buffer) {
    size_t i = 0;
    if (buffer.empty())
        throw FileFormatException("The rules of the game are specified but not set: " + buffer);

    if (buffer.substr(i, file_format::kBirthRulePrefix.size()) != file_format::kBirthRulePrefix)
        throw FileFormatException("Unknown parameter: " + std::to_string(buffer[i]) + " in " + buffer);

    i += file_format::kBirthRulePrefix.size();

    GetBirthRuleValues(buffer, i);

    if (i == buffer.length())
        throw FileFormatException("Not enough rules set: " + buffer);

    if (buffer.substr(i, file_format::kRuleSeparator.size()) != file_format::kRuleSeparator)
        throw FileFormatException(
                "Parts of the rules should be separated with " + file_format::kRuleSeparator + ": " + buffer);

    i += file_format::kRuleSeparator.size();

    if (buffer.substr(i, file_format::kSurvivalRulePrefix.size()) != file_format::kSurvivalRulePrefix)
        throw FileFormatException("Unknown parameter: " + std::to_string(buffer[i]) + " in " + buffer);

    i += file_format::kSurvivalRulePrefix.size();

    GetSurvivalRuleValues(buffer, i);
}

void life::FileParser::GetGameRules(const std::string &buffer) {
    if (std::isspace(buffer[file_format::kGameRulesIdentifier.size()])) {
        ParseGameRules(buffer.substr(file_format::kGameRulesIdentifier.size() + 1));
    } else {
        ParseGameRules(buffer.substr(file_format::kGameRulesIdentifier.size()));
        std::cerr << "No space after " + file_format::kGameRulesIdentifier + ':' + buffer << "\n";
    }
    if (!header_.is_rules_set_) {
        header_.is_rules_set_ = true;
    } else {
        throw FileFormatException("Following definition of the game rules: " + buffer);
    }
}

void life::FileParser::GetWidthAndHeight(const std::string &buffer) {
    std::istringstream ss(buffer);
    ss >> header_.width_;
    ss >> header_.height_;
    if (!ss.eof()) throw FileFormatException("Too many numbers of resolution parameters: " + buffer);
}

void life::FileParser::GetSizeOfField(const std::string &buffer) {
    if (std::isspace(buffer[file_format::kSizeOfFieldIdentifier.size()])) {
        GetWidthAndHeight(buffer.substr(file_format::kNameOfUniverseIdentifier.size() + 1));
    } else {
        GetWidthAndHeight(buffer.substr(file_format::kNameOfUniverseIdentifier.size()));
        std::cerr << "No space after " + file_format::kSizeOfFieldIdentifier + ':' + buffer << "\n";
    }
    if (!header_.is_size_set_) {
        header_.is_size_set_ = true;
    } else {
        throw FileFormatException("Following definition of the size of field: " + buffer);
    }
}

void life::FileParser::GetOption(const std::string &buffer) {
    if (buffer.substr(0, file_format::kNameOfUniverseIdentifier.size()) ==
        file_format::kNameOfUniverseIdentifier) {
        GetNameOfUniverse(buffer);
    } else if (buffer.substr(0, file_format::kNameOfUniverseIdentifier.size()) ==
               file_format::kGameRulesIdentifier) {
        GetGameRules(buffer);
    } else if (buffer.substr(0, file_format::kSizeOfFieldIdentifier.size()) ==
               file_format::kSizeOfFieldIdentifier) {
        GetSizeOfField(buffer);
    } else {
        throw FileFormatException("Unknown option " + buffer);
    }
}

void life::FileParser::GetCoordinates(std::ifstream &input_file, std::string &buffer, GameField &game_field) {
    if (!std::isdigit(buffer[0]))
        throw FileFormatException("Coordinates not set.");
    std::pair<int, int> current_coordinate;
    do {
        std::istringstream ss(buffer);
        std::string number;
        size_t number_of_args = 1;
        while (ss >> number) {
            if (number_of_args > 2)
                throw FileFormatException("To much numbers of coordinate " + buffer);
            std::size_t pos{};
            try {
                (number_of_args == 1) ? current_coordinate.first = std::stoi(number, &pos)
                                      : current_coordinate.second = std::stoi(number, &pos);
            } catch (const std::invalid_argument &except) {
                throw FileFormatException("Coordinate must be a numeric." + buffer);
            } catch (const std::out_of_range &except) {
                throw FileFormatException("Coordinate " + number + " is too big: " + buffer);
            }
            if (pos != number.size())
                throw FileFormatException("Coordinate must be a numeric." + buffer);
            ++number_of_args;
        }
        if (game_field[current_coordinate].value()) {
            std::cerr << "Coordinate set twice: " << buffer << '\n';
        } else {
            game_field.SetCoordinate(current_coordinate);
        }
    } while (std::getline(input_file, buffer));
}

life::GameField life::FileParser::ReadUniverseFromFile(const std::string &filename) {
    std::ifstream input_file(filename);
    input_file.is_open() ?: throw std::invalid_argument("Unable to open input file.");

    std::string buffer;

    std::getline(input_file, buffer);
    if (buffer != file_format::kGameVersion) {
        input_file.close();
        throw FileFormatException("Unsupported version: " + buffer);
    }

    while (std::getline(input_file, buffer)) {
        try {
            if (buffer[0] == file_format::kOptionSymbol) {
                GetOption(buffer);
            } else if (std::isdigit(buffer[0])) {
                break;
            } else {
                throw FileFormatException("Unknown parameter " + buffer);
            }
        } catch (const std::exception &except) {
            input_file.close();
            std::rethrow_exception(std::current_exception());
        }
    }

    if (!header_.is_name_set_) {
        std::cerr << "Name not set. Use filename as default." << "\n";
        header_.name_of_universe_ = filename;
    }
    if (!header_.is_rules_set_) {
        std::cerr << "Game rules not set. Use B3/S23 rule as default." << "\n";
        header_.rules_ = kDefaultRules;
    }

    GameField game_field(header_.name_of_universe_, header_.width_, header_.height_);

    try {
        GetCoordinates(input_file, buffer, game_field);
    } catch (const std::exception &except) {
        input_file.close();
        std::rethrow_exception(std::current_exception());
    }

    input_file.close();
    return game_field;
}
