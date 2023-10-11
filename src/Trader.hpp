#ifndef TRADER_HPP_
#define TRADER_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <string>
#include <vector>

#include "MarketOrder.hpp"
#include "LimitOrder.hpp"
#include "OrderType.hpp"
#include "Order.hpp"

namespace TS {

    class System;
    
    class Trader {
    public:
        Trader(const std::string&, const std::string&, double);
        Trader(const Trader&) = delete;
        Trader(Trader&&) noexcept;
        ~Trader();
    public:
        Trader& operator=(Trader&&) noexcept;
    public:
        const std::string& getSurname() const;
        const std::string& getName() const;
        double getBalance() const;
        std::size_t getId() const;
        void setName(const std::string&);
        void setSurname(const std::string&);
        void addBalance(double);
        void reduceBalance(double);
        void addStock(const std::string&, int);
        void printStocks() const;
        int getStockCount(const std::string&) const;
        int getStocksCount() const;
        Order* trade();
    private:
        void loadOrders();
        void loadStocks();
    private:
        double m_balance;
        std::size_t m_id;
        std::string m_name;
        std::string m_surname;
        std::vector<Order*> m_orders;
        static inline int m_traderId = 1;
        std::vector<std::pair<std::string, int>> m_stocks;
    };

} //namespace TS

#endif //TRADER_HPP_