#include "Commands.hpp"

namespace cmd {
    
    void commandLine(const TS::System& market) {
        std::string commands;
        std::cout << "Use commands to get information" << std::endl;
        std::cout << "Try 'help' to know about available commands." << std::endl;
        while (true) {
            std::getline(std::cin, commands);
            if (commands == "exit") {
                std::exit(EXIT_SUCCESS);
            }
            try {
                std::cout << std::endl;
                cmd::execute(commands, market);
                std::cout << std::endl;
            } catch (std::exception& ex) {
                std::cout << "\n\033[1;31m" << ex.what() << "\033[0m" << std::endl;
                std::cout << "Try 'help' for more information." << std::endl;
            }
        }
    }

    void execute(const std::string& commands, const TS::System& sys) {
        std::stringstream ss(commands);
        std::vector<std::string> args;
        std::string command;
        std::string arg;
        ss >> command;
        while (ss >> arg) {
            args.push_back(arg);
        }
        if (command == "help") {
            if (!args.empty()) {
                throw std::invalid_argument("help command doesn't gets arguments\n");
            }
            help();
        } else if (command == "display") {
            display(args, sys);
        } else if (command == "add") {
            add(args, sys);
        } else if (command == "remove") {
            remove(args, sys);
        } else if (command == "search") {
            search(args, sys);
        } else {
            throw std::invalid_argument("Invalid command\n");
        }
    }

    void help() {
        std::cout << "\tCommands    [arguments]\n"
                     "\thelp        - to see this\n"
                     "\tdisplay     - display the followings\n"
                     "\t\t['stocks', 'traders info', 'traders stocks', 'transactions']\n"
                     "\tadd         - add the followings\n"
                     "\t\t['traders', 'orders', 'stocks']\n"
                     "\tremove      - remove the followings\n"
                     "\t\t['traders', 'orders', 'stocks']\n"
                     "\tsearch      - search for the followings\n"
                     "\t\t['trader', 'stock']\n"
                     "\texit        - to close the app\n";               
    }

    void display(std::vector<std::string>& args, const TS::System& sys) {
        if (args.size() < 3 && !args.empty()) {
            if (args[0] == "stocks" || args[0] == "transactions") {
                if (args.size() > 1) {
                    throw std::invalid_argument("Invalid argument of command display " + args[0] + '\n');
                }
                if (args[0] == "stocks") {
                    sys.printStocks();
                } else {
                    sys.printTransactions();
                }
                return;
            } else if (args[0] == "traders") {
                if (args.size() != 2 || (args[1] != "info" && args[1] != "stocks")) {
                    throw std::invalid_argument("Invalid arguments of command display traders\n");
                }
                if (args[1] == "info") {
                    sys.printTradersInfo();
                } else {
                    sys.printTradersStocks();
                }
                return;
            } 
        }
        throw std::invalid_argument("Invalid arguments of command display\n");
    }

    void add(std::vector<std::string>& args, const TS::System& sys) {}

    void remove(std::vector<std::string>& args, const TS::System& sys) {}
    
    void search(std::vector<std::string>& args, const TS::System& sys) {}

} // namespace cmd