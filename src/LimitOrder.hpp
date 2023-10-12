#ifndef LIMITORDER_HPP_
#define LIMITORDER_HPP_

#include <string>
#include <vector>

#include "Order.hpp"
#include "Trader.hpp"
#include "OrderBook.hpp"

namespace TS {
    
    class LimitOrder : public Order {
    public:
        LimitOrder(std::size_t, int, OrderType, const std::string&, double);
    public:
        virtual void buy(Trader&, Stock&, OrderBook&) override;
        virtual void sell(Trader&, Stock&, OrderBook&) override;
        double getExpectedPrice() const override;
    private:
        double m_expected_price;
    };

} // namespace TS

#endif //LIMITORDER_HPP_