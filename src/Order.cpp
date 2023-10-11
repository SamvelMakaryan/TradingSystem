#include "Order.hpp"

namespace TS {
    
    Order::Order(std::size_t traderId, int count, OrderType type, const std::string& stock_name)
    :   m_Id(m_transactionId++),
        m_traderId(traderId),
        m_type(type),
        m_stock_name(stock_name),
        m_count(count) {}
    
    int Order::getCount() const {
        return m_count;
    }

    std::size_t Order::getTraderId() const {
        return m_traderId;
    }

    std::size_t Order::getTransactionId() const {
        return m_transactionId;
    }

    OrderType Order::getType() const {
        return m_type;
    }

    const std::string& Order::getStockName() const {
        return m_stock_name;
    }

    double Order::getExpectedPrice() const {
        return std::numeric_limits<double>::infinity();
    }

    void Order::execute(Trader& trader, Stock& stock, OrderBook& orders) {
        if (m_type == OrderType::buy) {
            buy(trader, stock, orders);
        } else {
            sell(trader, stock, orders);
        }
    }

    void Order::serialize(const std::string& history) const {
        std::fstream output("../history/transactions.txt", std::ios::app);
        if (!output.is_open()) {
            std::cerr << "Failed to store transactions history" << std::endl;
        }
        output << history << std::endl;
        output.close();
    }

} // namespace TS
