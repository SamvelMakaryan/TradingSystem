#include "OrderBook.hpp"

namespace TS {

    int OrderBook::getOrdersCount() const {
        return m_buy_orders.size() + m_sell_orders.size();
    }

    int OrderBook::getBuyOrdersCount() const {
        return m_buy_orders.size();
    }

    int OrderBook::getSellOrdersCount() const {
        return m_sell_orders.size();
    }

    std::vector<Order*>& OrderBook::getBuyOrders() {
        return m_sell_orders;
    }   

    std::vector<Order*>& OrderBook::getSellOrders() {
        return m_buy_orders;
    }   

    // Order* OrderBook::getOrderById(std::size_t id) const {
    //     for (auto order : m_orders) {
    //         if (order->getTransactionId() == id) {
    //             return order;
    //         }
    //     }
    //     return nullptr;
    // }

    void OrderBook::addBuyOrder(Order& order) {
        m_buy_orders.push_back(&order);
    }

    void OrderBook::addSellOrder(Order& order) {
        m_sell_orders.push_back(&order);
    }

    void OrderBook::removeBuyOrder(Order& order) {
        for (int i = 0; i < m_buy_orders.size(); ++i) {
            if (order.getTransactionId() == m_buy_orders[i]->getTransactionId()) {
                m_buy_orders.erase(m_buy_orders.begin() + i);
                break;
            }
        }
    }

    void OrderBook::removeSellOrder(Order& order) {
        for (int i = 0; i < m_sell_orders.size(); ++i) {
            if (order.getTransactionId() == m_sell_orders[i]->getTransactionId()) {
                m_sell_orders.erase(m_sell_orders.begin() + i);
                break;
            }
        }
    }

    void OrderBook::findMatch(std::vector<Trader>& traders, std::vector<Stock>& stocks) {
        for (int i = 0; i < m_buy_orders.size(); ++i) {
            auto it = std::find_if(stocks.begin(), stocks.end(), [name = m_buy_orders[i]->getStockName()](const auto& stock)
                        {return name == stock.getName();});
            if (it != stocks.end() && !std::isinf(m_buy_orders[i]->getExpectedPrice()) && it->getPrice() <= m_buy_orders[i]->getExpectedPrice()) {
                try {
                    Trader& trader = findTraderById(traders, m_buy_orders[i]->getTraderId());
                    double sum = m_buy_orders[i]->getCount() * it->getPrice();
                    trader.reduceBalance(sum);
                    (*it).increasePrice(sum * 0.05);
                    (*it).decreaseCount(m_buy_orders[i]->getCount());
                    serialize("[limit] " + trader.getName() + " " + trader.getSurname() + " ID[" + std::to_string(trader.getId()) + "] buying " + it->getName()
                    + " transaction ID[" + std::to_string(m_buy_orders[i]->getTransactionId()) + "] confirmed\n");
                    delete m_buy_orders[i];
                    m_buy_orders.erase(m_buy_orders.begin() + i);
                    --i;
                } catch(std::exception& ex) {
                    ex.what();
                    std::exit(EXIT_FAILURE);
                }
            }
        }
        for (int i = 0; i < m_sell_orders.size(); ++i) {
            auto it = std::find_if(stocks.begin(), stocks.end(), [name = m_sell_orders[i]->getStockName()](const auto& stock)
                        {return name == stock.getName();});
            if (it != stocks.end() && !std::isinf(m_sell_orders[i]->getExpectedPrice()) && it->getPrice() >= m_sell_orders[i]->getExpectedPrice()) {
                try {
                    Trader& trader = findTraderById(traders, m_sell_orders[i]->getTraderId());
                    double sum = m_sell_orders[i]->getCount() * it->getPrice();
                    trader.addBalance(sum);
                    (*it).decreasePrice(sum * 0.05);
                    (*it).increaseCount(m_sell_orders[i]->getCount());
                    serialize("[limit] " + trader.getName() + " " + trader.getSurname() + " '" + std::to_string(trader.getId()) + "' selling " + it->getName()
                    + " '" + std::to_string(m_sell_orders[i]->getTransactionId()) + "' confirmed\n");
                    delete m_sell_orders[i];
                    m_sell_orders.erase(m_sell_orders.begin() + i);
                    --i;
                } catch(std::exception& ex) {
                    ex.what();
                    std::exit(EXIT_FAILURE);
                }
            }
        }
    }

    Trader& OrderBook::findTraderById(std::vector<Trader>& traders, std::size_t id) const {
        for (auto& trader : traders) {
            if (trader.getId() == id) {
                return trader;
            }
        }
        throw std::logic_error("No such trader");
    }

    void OrderBook::serialize(const std::string& history) const {
        std::fstream output("../history/transactions.txt", std::ios::out);
        if (!output.is_open()) {
            std::cerr << "Failed to store transactions history\n" << std::endl;
        }
        output << history << std::endl;
        output.close();
    }

} //namespace TS