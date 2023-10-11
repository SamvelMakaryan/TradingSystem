#ifndef ORDER_HPP_
#define ORDER_HPP_

#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
#include <limits>
#include <mutex>

#include "OrderType.hpp"
#include "Stock.hpp"

namespace TS {

    class Trader;
    class OrderBook;

    class Order {
    public:
        Order(std::size_t, int, OrderType, const std::string&);
        Order(const Order&) = delete;
        Order(Order&&) = delete;
        virtual ~Order() = default;
    public:
        void execute(Trader&, Stock&, OrderBook&);
        virtual void buy(Trader&, Stock&, OrderBook&) = 0;
        virtual void sell(Trader&, Stock&, OrderBook&) = 0;
        OrderType getType() const;
        int getCount() const;
        std::size_t getTraderId() const;
        std::size_t getTransactionId() const;
        const std::string& getStockName() const;
        double getExpectedPrice() const;
    protected:
        void serialize(const std::string&) const;
    protected:
        int m_count;
        OrderType m_type;
        std::size_t m_Id;
        std::mutex m_mutex;
        std::size_t m_traderId;
        std::string m_stock_name;
        static inline int m_transactionId = 1;
    };

} //namespace TS

#endif //ORDER_HPP_