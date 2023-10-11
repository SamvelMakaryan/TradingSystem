#include "MarketOrder.hpp"

namespace TS {
    
    MarketOrder::MarketOrder(std::size_t traderID, int count, OrderType type, const std::string& stock)
    :   Order(traderID, count, type, stock) {}

    void MarketOrder::buy(Trader& trader, Stock& stock, OrderBook& orders) {
        double sum = stock.getPrice() * m_count;
        std::string history;
        history += "[market] " + trader.getName() + " " + trader.getSurname() + " '" + std::to_string(m_traderId) + "' buying "
        + m_stock_name + " '" + std::to_string(m_transactionId) + "' ";
        if (trader.getBalance() < sum ) {
            history += "rejected (low balance)\n";
            serialize(history);
            return;
        }
        if (m_count > stock.getCount()) {
            history += "rejected (no available stocks)\n";
            serialize(history);
            return;
        }
        trader.reduceBalance(sum);
        trader.addStock(m_stock_name, m_count);
        stock.decreaseCount(m_count);
        stock.increasePrice(stock.getPrice() * 0.05);
        history += "confirmed\n";
        serialize(history); 
    }

    void MarketOrder::sell(Trader& trader, Stock& stock, OrderBook& orders) {
        double sum = stock.getPrice() * m_count;
        trader.addBalance(sum);
        stock.increaseCount(m_count);
        stock.decreasePrice(stock.getPrice() * 0.05);
        std::string history;
        history += "[market] " + trader.getName() + " " + trader.getSurname() + " '" + std::to_string(m_traderId) + "' selling "
        + m_stock_name + " '" + std::to_string(m_transactionId) + "'"; 
        if (trader.getStockCount(m_stock_name) < m_count) {
            history += " rejected (unavalible recource)\n";
            serialize(history);
            return;
        }
        history += " confirmed\n"; 
        serialize(history);
    }

} // namespace TS
