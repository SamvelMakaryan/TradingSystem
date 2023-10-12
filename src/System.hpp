#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

#include "OrderBook.hpp"
#include "Trader.hpp"
#include "Stock.hpp"

namespace TS {

    class System {
    public:
        static System& getSystemInstance();
    public:
        void open(int);
        void printTradersStocks() const;
        void printTradersInfo() const;
        void printStocks() const;
        void printTransactions() const;
        void printTraderById(int) const;
        void printStockByName(const std::string&) const;
        void addStock(const std::string&, int, double);
        void addTrader(const std::string&, const std::string&, double);
        void addOrder(int, const std::string&, const std::string&, int, const std::string&, double);
        void removeTraderById(int);
        void removeStockByName(const std::string&);
    private:
        void execute(Trader&);
        void start() const;
        void finish() const;
        void loadTraders();
        void loadStocks();
        void storeStocks() const;
        void storeTraders() const;
    private:
        System() = default;
        ~System();
        System(const System&) = delete;
        System(System&&) noexcept = delete;
    private:
        std::vector<Stock> m_stocks;
        std::vector<Trader> m_traders;
        OrderBook m_orders;
    };

} //namespace TS

#endif //SYSTEM_HPP_    