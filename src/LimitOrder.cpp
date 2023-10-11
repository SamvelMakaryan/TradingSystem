#include "LimitOrder.hpp"


namespace TS {
    
    LimitOrder::LimitOrder(std::size_t traderID, int count, OrderType type, const std::string& stock, double price)
    :   Order(traderID, count, type, stock),
        m_expected_price(price) {}

    void LimitOrder::buy(Trader& trader, Stock& stock, OrderBook& orders) {
        double sum = m_expected_price * m_count;
        std::string history;
        history += "[limit] " + trader.getName() + " " + trader.getSurname() + " ID[" + std::to_string(m_traderId) + "] buying "
        + m_stock_name + " transaction ID[" + std::to_string(m_Id) + "] ";
        if (trader.getBalance() < sum) {
            history += "rejected (low balance)\n";
            serialize(history);
            return;
        }
        if (stock.getCount() < m_count) {
            history += "rejected (no available stocks)\n";
            serialize(history);
            return;
        }
        if (stock.getPrice() <= m_expected_price) {
            m_mutex.lock();
            trader.reduceBalance(sum);
            stock.decreaseCount(m_count);
            stock.increasePrice(stock.getPrice() * 0.05);
            m_mutex.unlock();
            history += "confirmed\n";
        } else {
            history += "waiting\n";
            orders.addBuyOrder(*this);
        }
        serialize(history);
    }

    void LimitOrder::sell(Trader& trader, Stock& stock, OrderBook& orders) {
        double sum = m_expected_price * m_count;
        std::string history;
        history += "[limit] " + trader.getName() + " " + trader.getSurname() + " ID[" + std::to_string(m_traderId) + "] selling "
        + m_stock_name + " transactoin ID[" + std::to_string(m_Id) + "] ";
        if (stock.getPrice() >= m_expected_price) {
            m_mutex.lock();
            trader.addBalance(sum);
            stock.increaseCount(m_count);
            stock.decreaseCount(stock.getPrice() * 0.05);
            m_mutex.unlock();
            history += "confirmed\n";
        } else if (trader.getStockCount(m_stock_name) < m_count) {
            history += "rejected (no available resources)\n";
        } else {
            history += "waiting\n";
            orders.addSellOrder(*this);
        }
        serialize(history);
    }

    double LimitOrder::getExpectedPrice() const {
        return m_expected_price;
    }

} // namespace TS
