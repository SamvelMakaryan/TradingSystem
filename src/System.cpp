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
            std::exit(-1);
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
            std::exit(-1);
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
        auto start = std::chrono::high_resolution_clock::now();
        while (std::chrono::high_resolution_clock::now() - start < duration) {
           std::this_thread::sleep_for(1s);
           execute();
        }
        finish();
    }
    
    void System::execute() {
        for (auto& trader : m_traders) {
            Order* order = trader.trade(*this);
            if (order) {
                processOrder(trader, *order);
            }
        }
    }

    void System::processOrder(Trader& trader, Order& order) {
        order.execute(trader, *(std::find_if(m_stocks.begin(), m_stocks.end(), 
            [name = order.getStockName()](const auto& stock)
            {return name == stock.getName();})), m_orders);
    }

    void System::finish() const {
        std::fstream output("../history/transactions.txt", std::ios::app);
        if(!output.is_open()) {
            std::cerr << "Failed to store transactions history" << std::endl;
            output.close();
            std::exit(-1);
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
                std::cout << "no stocks" << std::endl;
            }
        }
    }

    void System::printTradersInfo() const {
        std::cout << "name\tsurname\tID\tbalance" << std::endl;
        for (const auto& trader : m_traders) {
            std::cout << trader.getName() << " " << trader.getSurname() << " " << trader.getId() << " " << trader.getBalance() << std::endl;   
        }
    }

} // namespace TS
