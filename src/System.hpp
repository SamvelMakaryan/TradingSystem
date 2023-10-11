#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <algorithm>
#include <iostream>
#include <fstream>
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
    private:
        void execute();
        void start() const;
        void finish() const;
        void processOrder(Trader&, Order&);
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