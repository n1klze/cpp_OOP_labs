#include "life_console_interface.h"

const life::LifeConsoleInterface::SupportiveCommands life::LifeConsoleInterface::kSupportiveCommands{};

life::LifeConsoleInterface::LifeConsoleInterface(const command_parser::CommandLineParser::Data &start_options) {
    game_handler_ = Game(start_options);
}

namespace {
    void PrintUsage() {
        std::cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n"
                     "║dump <filename> - save universe to file.                                      ║\n"
                     "╟──────────────────────────────────────────────────────────────────────────────╢\n"
                     "║tick <n=1> | t <n=1> - calculate n (by default 1) iterations and print result.║\n"
                     "╟──────────────────────────────────────────────────────────────────────────────╢\n"
                     "║exit - end game.                                                              ║\n"
                     "╟──────────────────────────────────────────────────────────────────────────────╢\n"
                     "║help - print usage message.                                                   ║\n"
                     "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    }

    void PrintGameRules(std::ostream &output, const life::Game &game_handler) {
        output << "\nGame rules: " << life::FileParser::kFileFormat.kBirthRulePrefix;
        for (auto i: game_handler.game_rules().birth())
            output << i;
        output << life::FileParser::kFileFormat.kRuleSeparator << life::FileParser::kFileFormat.kSurvivalRulePrefix;
        for (auto i: game_handler.game_rules().survival())
            output << i;
        output << '\n';
    }

    void PrintLiveCellsCoordinatesToFile(std::ofstream &output_file, const life::Game &game_handler) {
        std::pair<int, int> coordinate;
        for (int x = 0; x < game_handler.game_field().width(); ++x) {
            for (int y = 0; y < game_handler.game_field().width(); ++y) {
                coordinate = {x, y};
                if (game_handler.game_field()[coordinate].IsAlive())
                    output_file << '\n' << x << ' ' << y;
            }
        }
    }
}

void life::LifeConsoleInterface::Dump(const std::string &output_filename) {
    std::ofstream output_file(output_filename);
    output_file.is_open() ?: throw std::invalid_argument("Unable to open output file.");
    output_file << life::FileParser::kFileFormat.kGameVersion << '\n';

    output_file << life::FileParser::kFileFormat.kNameOfUniverseIdentifier << ' '
                << game_handler_.game_field().universe_name() << '\n';

    output_file << life::FileParser::kFileFormat.kGameRulesIdentifier << ' ';
    PrintGameRules(output_file, game_handler_);

    PrintLiveCellsCoordinatesToFile(output_file, game_handler_);

    output_file.close();
}

void life::LifeConsoleInterface::SimulateGameplay() {
    for (size_t i = 0; i < game_handler_.start_options().iterations; ++i) {
        game_handler_.MakeMove();
    }
    Print();

    while (true) {
        std::cout << '\n' << "Enter your command: ";
        std::string buffer;
        std::getline(std::cin, buffer);
        std::vector<std::string> args;
        std::string word;
        std::istringstream ss(buffer);
        while (ss >> word)
            args.push_back(word);
        if (args[0] == kSupportiveCommands.kDumpCommand) {
            if (args.size() == 1)
                std::cerr << "Output filename not set. Try again\n";
            if (args.size() > 2)
                std::cerr << "Too much arguments. Try again\n";
            try {
                Dump(args[1]);
            } catch (const std::exception &except) {
                std::cerr << except.what() << std::endl;
            }
        } else if (args[0] == kSupportiveCommands.kTickCommand || args[0] == kSupportiveCommands.kShortTickCommand) {
            int number_of_iterations = 1;
            if (args.size() > 1) {
                try {
                    number_of_iterations = std::stoi(args[1]);
                } catch (const std::exception &except) {
                    std::cerr << "Bad number of iterations. Try again." << std::endl;
                }
            }
            if (args.size() > 2)
                std::cerr << "Too much arguments. Try again\n";
            for (int i = 0; i < number_of_iterations; ++i)
                game_handler_.MakeMove();
            Print();
        } else if (args[0] == kSupportiveCommands.kExitCommand) {
            break;
        } else if (args[0] == kSupportiveCommands.kHelpCommand) {
            PrintUsage();
        } else {
            std::cout << "Unsupported command. Try again.";
        }
    }
}

void life::LifeConsoleInterface::Print() {
    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";
    std::cout << "\nName of universe: " << game_handler_.game_field().universe_name() << '\n';

    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";

    PrintGameRules(std::cout, game_handler_);

    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";

    std::cout << "\nNumber of iterations: " << game_handler_.number_of_iterations() << '\n';

    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";

    std::cout << "\n╔";
    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";
    std::cout << "╗\n║";
    std::pair<int, int> coordinate;
    for (int y = 0; y < game_handler_.game_field().height(); ++y) {
        for (int x = 0; x < game_handler_.game_field().width(); ++x) {
            coordinate = {x, y};
            if (x == 0 && y != 0)
                std::cout << "║\n║";
            std::cout << (game_handler_.game_field()[coordinate].value() ? '#' : ' ');
        }
    }
    std::cout << "║\n╚";
    for (size_t i = 0; i < game_handler_.game_field().width(); ++i)
        std::cout << "═";
    std::cout << "╝\n";
}
