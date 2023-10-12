#include "Commands.hpp"

namespace cmd {
    
    void commandLine(TS::System& market) {
        std::string commands;
        std::cout << "Use commands to get information" << std::endl;
        std::cout << "Try 'help' to know about available commands." << std::endl;
        while (true) {
            std::getline(std::cin, commands);
            if (commands == "exit") {
                std::cout << "Closing Trading System\nAll changes are saved\n";
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

    void execute(const std::string& commands, TS::System& sys) {
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
                     "\tUsage:\n"
                     "\t\t(help)\n"
                     "\tdisplay     - display the followings\n"
                     "\t\t['stocks', 'traders info', 'traders stocks', 'transactions']\n"
                     "\tUsage:\n"
                     "\t\t(display stocks)\n"
                     "\t\t(display traders info)\n"
                     "\t\t(display traders stocks)\n"
                     "\t\t(display transactions)\n"
                     "\tadd         - add the followings\n"
                     "\t\t['trader', 'order', 'stock']\n"
                     "\tUsage:\n"
                     "\t\t(add trader 'Name' 'Surname' 'Balance')\n"
                     "\t\t(add order 'TraderID' 'Strategy' 'Type' 'Count' 'Stock Name' ['Price'])\n"
                     "\t\t(add stock 'Name' 'Price' 'Count')\n"
                     "\tremove      - remove the followings\n"
                     "\t\t['trader', 'stock']\n"
                     "\tUsage:\n"
                     "\t\t(remove trader id)"
                     "\t\t(remove stock name)"
                     "\tsearch      - search for the followings\n"
                     "\t\t['trader', 'stock']\n"
                     "\tUsage:\n"
                     "\t\t(search trader id)\n"
                     "\t\t(search stock name)\n"
                     "\texit        - to close the app\n"               
                     "\tUsage:\n"
                     "\t\t(exit) or (cntrl + C)";
    }

    void display(std::vector<std::string>& args, TS::System& sys) {
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

    void add(std::vector<std::string>& args, TS::System& sys) {
        if (args.empty()) {
            throw std::invalid_argument("Invalid argument of command add\n");
        }
        if (args[0] == "trader") {
            if (args.size() != 4) {
                throw std::invalid_argument("Invalid argument of command add trader\n");
            }
            std::string name = args[1];
            std::string surname = args[2];
            double balance;
            try {
                balance = std::stod(args[3]);
            } catch(...) {
                throw std::invalid_argument("Invalid argument of command add trader\nThird argument must be n");
            }
            if (has_symbols(name) || has_symbols(surname)) {
                throw std::invalid_argument("Invalid argument of command add trader\nName or Surname shouldn't consist of symbols\n");
            }
            sys.addTrader(name, surname, balance);
            return;
        } else if (args[0] == "stock") {
            if (args.size() != 4) {
                throw std::invalid_argument("Invalid argument of command add stock\n");
            }
            std::string name = args[1];
            double price;
            int count;
            try {
                price = std::stod(args[2]);
                count = std::stoi(args[3]);
            } catch(...) {
                throw std::invalid_argument("Invalid argument of command add stock\nValue of price should be double\nValue of count should be int");
            }
            if (has_symbols(name)) {
                throw std::invalid_argument("Invalid argument of command add trader\nName shouldn't consist of symbols\n");
            }
            sys.addStock(name, count, price);
            return;
        } else if (args[0] == "order") {
            if (args.size() != 7 && args.size() != 6) {
                throw std::invalid_argument("Invalid argument of command add order\n");
            }
            int id;
            int count;
            double price = std::numeric_limits<double>::infinity();
            std::string strategy = args[2];
            if (strategy != "limit" && strategy != "market") {
                throw std::invalid_argument("Invalid argumen of command add order\nStrategy can be ['market', 'limit']\n");
            }
            std::string type = args[3];
            if (type != "buy" && type != "sell") {
                throw std::invalid_argument("Invalid argumen of command add order\nType can be ['buy', 'sell']\n");
            }
            std::string stock_name = args[5];
            if (has_symbols(stock_name)) {
                throw std::invalid_argument("Invalid argument of command add order\nStock Name shouldn't consist of symbols\n");
            }
            try {
                id = std::stoi(args[1]);
                count = std::stoi(args[4]);
                if (args.size() == 7 ) {
                    if (args[2] == "limit") {
                        price = std::stod(args[6]);
                    } else {
                        throw 1;
                    }
                }
            } catch(...) {
                throw std::invalid_argument("Invalid argument of command add order\nValue price should be double\nValues ID and count should be int\n");
            }
            sys.addOrder(id, strategy, type, count, stock_name, price);
            return;
        } else {
            throw std::invalid_argument("Invalid argument of command add\n");
        }
    }

    void remove(std::vector<std::string>& args, TS::System& sys) {
        if (args.size() != 2) {
            throw std::invalid_argument("Invalid count of arguments of command remove\n");
        }
        if (args[0] == "trader") {
            int id;
            try {
                id = std::stoi(args[1]);
            } catch(...) {
                throw std::invalid_argument("Invalid argument of command remove trader\nValue id should be int\n");
            }
            sys.removeTraderById(id);
            return;
        } else if (args[0] == "stock") {
            sys.removeStockByName(args[1]);
            return;
        } else {
            throw std::invalid_argument("Invalid argument of command remove\n");
        }
    }
    
    void search(std::vector<std::string>& args, TS::System& sys) {
        if (args.size() != 2) {
            throw std::invalid_argument("Invalid count of arguments of command search\n");
        }
        if (args[0] == "trader") {
            int id;
            try {
                id = std::stoi(args[1]);
            } catch(...) {
                throw std::invalid_argument("Invalid argument of command search trader\nValue id should be int\n");
            }
            sys.printTraderById(id);
            return;
        } else if (args[0] == "stock") {
            sys.printStockByName(args[1]);
            return;
        } else {
            throw std::invalid_argument("Invalid arguments of command search\n");
        }
    }

    bool has_symbols(const std::string& s) {
        for (char c : s) {
            if (!std::isalnum(c)) {
                return true;
            }
        }
        return false;
    }

} // namespace cmd