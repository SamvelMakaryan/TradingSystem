#ifndef MARKETORDER_HPP_
#define MARKETORDER_HPP_

#include <string>

#include "Trader.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"

namespace TS {
    
    class MarketOrder : public Order {
    public:
        MarketOrder(std::size_t, int, OrderType, const std::string&);
    public:
        virtual void buy(Trader&, Stock&, OrderBook&) override;
        virtual void sell(Trader&, Stock&, OrderBook&) override;
    };

} // namespace TS

#endif //MARKETORDER_HPP_