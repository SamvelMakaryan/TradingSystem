#ifndef ORDERBOOK_HPP_
#define ORDERBOOK_HPP_

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cstddef>
#include <string>
#include <vector>
#include <cmath>

#include "Stock.hpp"
#include "Order.hpp"
#include "Trader.hpp"

namespace TS {

    // class Order;
    // class Trader;
    // class Stock;

    class OrderBook {
    public:
        OrderBook() = default;
        OrderBook(const OrderBook&) = delete;
        OrderBook(OrderBook&&) noexcept = delete;
        ~OrderBook() = default;
    public:
        int getOrdersCount() const;
        int getSellOrdersCount() const;
        int getBuyOrdersCount() const;
        std::vector<Order*>& getBuyOrders();
        std::vector<Order*>& getSellOrders();
        // Order* getOrderById(std::size_t) const;
        void addBuyOrder(Order&);
        void addSellOrder(Order&);
        void removeBuyOrder(Order&);
        void removeSellOrder(Order&);
        void findMatch(std::vector<Trader>&, std::vector<Stock>&);
    private:
        Trader& findTraderById(std::vector<Trader>&, std::size_t) const;
        void serialize(const std::string&) const;
    private:
        std::vector<Order*> m_buy_orders;
        std::vector<Order*> m_sell_orders;
    };

} //namespace TS

#endif //ORDERBOOK_HPP_