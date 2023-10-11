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