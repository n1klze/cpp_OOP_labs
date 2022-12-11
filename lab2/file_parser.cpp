#include "file_parser.h"

namespace {
    const char kRuleProhibitedValue = '9';
}

const std::string life::FileParser::kDefaultUniverseFilename = "default.life";
const life::FileParser::Format life::FileParser::kFileFormat{};

void life::FileParser::GetNameOfUniverse(const std::string &buffer) {
    if (std::isspace(buffer[kFileFormat.kNameOfUniverseIdentifier.size()])) {
        header_.name_of_universe = buffer.substr(kFileFormat.kNameOfUniverseIdentifier.size() + 1);
    } else {
        header_.name_of_universe = buffer.substr(kFileFormat.kNameOfUniverseIdentifier.size());
        std::cerr << "No space after " + kFileFormat.kNameOfUniverseIdentifier + ':' + buffer
                  << "\n";  //future: to log
    }
    if (!header_.name_flag) {
        header_.name_flag = true;
    } else {
        throw std::invalid_argument("Following definition of the universe name: " + buffer); //TODO: to custom exception
    }
}

void life::FileParser::GetBirthRuleValues(const std::string &buffer, size_t &i) {
    for (; i < buffer.length() && std::isdigit(buffer[i]); ++i) {
        if (buffer[i] == kRuleProhibitedValue)
            throw std::invalid_argument(
                    "Invalid value " + std::to_string(buffer[i]) + " in " + buffer); //TODO: to custom exception
        if (header_.rules_.birth.find(buffer[i] - '0') != header_.rules_.birth.end()) {
            std::cerr << "Rule" << buffer[i] << "defined twice in birth rules: " + buffer; //TODO: to log
        } else {
            header_.rules_.birth.insert(buffer[i] - '0');
        }
    }
}

void life::FileParser::GetSurvivalRuleValues(const std::string &buffer, size_t &i) {
    for (; i < buffer.length(); ++i) {
        if (!std::isdigit(buffer[i]))
            throw std::invalid_argument(
                    "Invalid value " + std::to_string(buffer[i]) + " in " + buffer); //TODO: to custom exception
        if (buffer[i] == kRuleProhibitedValue)
            throw std::invalid_argument(
                    "Invalid value " + std::to_string(buffer[i]) + " in " + buffer); //TODO: to custom exception
        if (header_.rules_.survival.find(buffer[i] - '0') != header_.rules_.survival.end()) {
            std::cerr << "Rule" << buffer[i] << "defined twice in survival rules: " + buffer; //TODO: to log
        } else {
            header_.rules_.survival.insert(buffer[i] - '0');
        }
    }
}

void life::FileParser::ParseGameRules(const std::string &buffer) {
    size_t i = 0;
    if (buffer.empty())
        throw std::invalid_argument(
                "The rules of the game are specified but not set: " + buffer); //TODO: to custom exception

    if (buffer.substr(i, kFileFormat.kBirthRulePrefix.size()) != kFileFormat.kBirthRulePrefix)
        throw std::invalid_argument(
                "Unknown parameter: " + std::to_string(buffer[i]) + " in " + buffer); //TODO: to custom exception

    i += kFileFormat.kBirthRulePrefix.size();

    GetBirthRuleValues(buffer, i);

    if (i == buffer.length())
        throw std::invalid_argument("Not enough rules set: " + buffer); //TODO: to custom exception

    if (buffer.substr(i, kFileFormat.kRuleSeparator.size()) != kFileFormat.kRuleSeparator)
        throw std::invalid_argument("Parts of the rules should be separated with " + kFileFormat.kRuleSeparator + ": " +
                                    buffer); //TODO: to custom exception

    i += kFileFormat.kRuleSeparator.size();

    if (buffer.substr(i, kFileFormat.kSurvivalRulePrefix.size()) != kFileFormat.kSurvivalRulePrefix)
        throw std::invalid_argument(
                "Unknown parameter: " + std::to_string(buffer[i]) + " in " + buffer); //TODO: to custom exception

    i += kFileFormat.kSurvivalRulePrefix.size();

    GetSurvivalRuleValues(buffer, i);
}

void life::FileParser::GetGameRules(const std::string &buffer) {
    if (std::isspace(buffer[kFileFormat.kGameRulesIdentifier.size()])) {
        ParseGameRules(buffer.substr(kFileFormat.kGameRulesIdentifier.size() + 1));
    } else {
        ParseGameRules(buffer.substr(kFileFormat.kGameRulesIdentifier.size()));
        std::cerr << "No space after " + kFileFormat.kGameRulesIdentifier + ':' + buffer
                  << "\n";  //TODO: to log
    }
    if (!header_.rule_flag) {
        header_.rule_flag = true;
    } else {
        throw std::invalid_argument("Following definition of the game rules: " + buffer); //TODO: to custom exception
    }
}

void life::FileParser::GetOption(const std::string &buffer) {
    if (buffer.substr(0, kFileFormat.kNameOfUniverseIdentifier.size()) ==
        kFileFormat.kNameOfUniverseIdentifier) {
        GetNameOfUniverse(buffer);
    } else if (buffer.substr(0, kFileFormat.kNameOfUniverseIdentifier.size()) ==
               kFileFormat.kGameRulesIdentifier) {
        GetGameRules(buffer);
    } else {
        throw std::invalid_argument("Unknown option " + buffer); //TODO: to custom exception
    }
}

life::GameField life::FileParser::ReadUniverseFromFile(const std::string &filename) {
    std::ifstream input_file(filename);
    input_file.is_open() ?: throw std::invalid_argument("Unable to open input file.");

    std::string buffer;

    std::getline(input_file, buffer);
    if (buffer != kFileFormat.kGameVersion) {
        input_file.close();
        throw std::invalid_argument("Unsupported version.");
    }

    while (std::getline(input_file, buffer)) {
        try {
            if (buffer[0] == kFileFormat.kOptionSymbol) {
                GetOption(buffer);
            } else if (std::isdigit(buffer[0])) {
                break;
            } else {
                throw std::invalid_argument("Unknown parameter " + buffer); //TODO: to custom exception
            }
        } catch (const std::exception &except) {
            input_file.close();
            throw except;
        }
    }

    if (!header_.name_flag) {
        std::cerr << "Name not set. Use filename as default." << "\n";  //TODO: to log
        header_.name_of_universe = filename;
    }

    //GetCoordinates

    input_file.close();
}
