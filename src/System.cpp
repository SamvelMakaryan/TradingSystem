#include "System.hpp"

namespace TS {
    
    System& System::getSystemInstance() {
        static System instance;
        return instance;
    }

    System::~System() {
        storeStocks();
        storeTraders();        
    }

    void System::storeStocks() const {
        std::fstream output("../database/stocks.txt", std::ios::out);
        if (!output.is_open()) {
            std::cerr << "Can't store stocks info" << std::endl;
        }
        for (const auto& stock : m_stocks) {
            output << stock.getName() << '/' << stock.getPrice() << '/' << stock.getCount() << '\n';
        }
        output.close();
    }

    void System::storeTraders() const {
        std::fstream output("../database/traders/info.txt", std::ios::out);
        if (!output.is_open()) {
            std::cerr << "Can't store traders info" << std::endl;
        }
        for (const auto& trader : m_traders) {
            output << trader.getName() << '/' << trader.getSurname() << '/' << trader.getBalance() << '\n';
        }
        output.close();
    }

    void System::start() const {
        std::fstream output("../history/transactions.txt", std::ios::out);
        if(!output.is_open()) {
            std::cerr << "Failed to store transactions history" << std::endl;
        }
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);
        output << "Stock Market opened : " << std::ctime(&current_time) << std::endl; 
        output.close();
    }

    void System::loadTraders() {
        std::fstream input("../database/traders/info.txt", std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Unable to get traders list." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::string trader;
        std::string name;
        std::string surname;
        double balance;
        while (std::getline(input, trader)) {
            std::stringstream ss(trader);
            std::getline(ss, name, '/');
            std::getline(ss, surname, '/');
            ss >> balance;
            m_traders.emplace_back(name, surname, balance);
        }
        input.close();
    }

    void System::loadStocks() {
        std::fstream input("../database/stocks.txt", std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Unable to get traders list." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::string name;
        double price;
        int count;
        std::string line;
        std::string num;
        while (std::getline(input, line)) {
            std::stringstream ss(line);
            std::getline(ss, name, '/');
            std::getline(ss, num, '/');
            price = std::stod(num);
            ss >> count;
            m_stocks.emplace_back(name, price, count);
        }
        input.close();
    }

    void System::open(int seconds) {
        using namespace std::chrono_literals;
        loadStocks();
        loadTraders();
        start();
        std::chrono::seconds duration(seconds);
        std::vector<std::thread> traderThreads;
        for (auto& trader : m_traders) {
            traderThreads.emplace_back([this, &trader, &duration]() {
                std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
                while (std::chrono::high_resolution_clock::now() - start < duration) {
                    std::this_thread::sleep_for(2s);
                    execute(trader);
                    this->m_orders.findMatch(this->m_traders, this->m_stocks);
                }
            });
        }
        for (auto& thread : traderThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        finish();
    }    

    void System::execute(Trader& trader) {
        Order* order = trader.trade();
        if (order) {
            order->execute(trader, *(std::find_if(m_stocks.begin(), m_stocks.end(),
                [name = order->getStockName()](const auto& stock)
                { return name == stock.getName(); })), m_orders);
        }
    }

    void System::finish() const {
        std::fstream output("../history/transactions.txt", std::ios::app);
        if(!output.is_open()) {
            std::cerr << "Failed to store transactions history" << std::endl;
            output.close();
            std::exit(EXIT_FAILURE);
        }
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);
        output << "Stock Market closed : " << std::ctime(&current_time) << std::endl;
        output.close();
    }

    void System::printTradersStocks() const {
        for (const auto& trader : m_traders) {
            std::cout << trader.getName() << " " << trader.getSurname() << std::endl;
            if (trader.getStocksCount() != 0) {
                trader.printStocks();
            } else {
                std::cout << "\tno stocks" << std::endl;
            }
        }
    }

    void System::printTradersInfo() const {
        std::cout << std::left << std::setw(15) << "Name"
                               << std::setw(15) << "Surname"
                               << std::setw(10) << "ID"
                               << std::setw(15) << "Balance" << std::endl;
        std::cout << std::endl;
        for (const auto& trader : m_traders) {
            std::cout << std::left << std::setw(15) << trader.getName() 
                      << std::setw(15) << trader.getSurname() 
                      << std::setw(10) << trader.getId() 
                      << std::setw(0) << trader.getBalance()
                      << '$' << std::endl;   
        }
    }

    void System::printStocks() const {
        std::cout << std::left << std::setw(15) << "Name"
                               << std::setw(15) << "Count"
                               << std::setw(15) << "Price" << std::endl;
        std::cout << std::endl;
        for (const auto& stock : m_stocks) {
            std::cout << std::left << std::setw(15) << stock.getName() 
                                   << std::setw(15) << stock.getCount() 
                                   << std::setw(0) << stock.getPrice() 
                                   << '$' << std::endl;
        }
    }

    void System::printTransactions() const {
        std::fstream tr("../history/transactions.txt", std::ios::in);
        if (!tr.is_open()) {
            std::cerr << "Can't open transactions history" << std::endl;
        }
        std::string line;
        std::string red = "\033[1;31m";
        std::string green = "\033[1;32m";
        std::string gray = "\033[1;90m";
        while (std::getline(tr, line)) {
            line += "\033[0m";
            if (line.rfind("confirmed") != std::string::npos) {
                line = green + line;
            } else if (line.rfind("rejected") != std::string::npos) {
                line = red + line;
            } else {
                line = gray + line;
            }
            std::cout << line << std::endl;
        }
        tr.close();
    }

} // namespace TS
