#include "Trader.hpp"

namespace TS {
    
    Trader::Trader(const std::string& name, const std::string& surname, double balance) 
    :   m_name(name),
        m_surname(surname),
        m_id(m_traderId++),
        m_balance(balance) 
    {
        loadOrders();
        loadStocks();
    }

    void Trader::loadOrders() {
        std::fstream input(("../database/traders/orders/ID_" + std::to_string(m_id) + ".txt").c_str(), std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Can't open orders file for trader - ID_" << m_id << std::endl;
            input.close();
            std::exit(-1);
        }
        std::string order_name;
        std::string order_type_s;
        std::string order_strategy;
        OrderType order_type;
        int order_count;
        std::string line;
        while (std::getline(input, line)) {
            std::stringstream ss(line);
            ss >> order_strategy;    
            ss >> order_type_s;
            ss >> order_count;
            ss >> order_name;
            if (order_type_s == "buy") {
                order_type = OrderType::buy;
            } else {
                order_type = OrderType::sell;
            }
            if (order_strategy == "market") {
                m_orders.push_back(new MarketOrder(m_id, order_count, order_type, order_name));
            } else if (order_strategy == "limit") {
                double price;
                ss >> price;
                m_orders.push_back(new LimitOrder(m_id, order_count, order_type, order_name, price));
            }
        }
        input.close();
    }

    void Trader::loadStocks() {
        std::fstream input(("../database/traders/stocks/ID_" + std::to_string(m_id) + ".txt").c_str(), std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Can't open orders file" << std::endl;
            input.close();
            std::exit(-1);
        }
        std::string line;
        std::string stock_name;
        int count;
        while (std::getline(input, line)) {
            std::stringstream ss(line);
            ss >> stock_name;
            ss >> count;
            m_stocks.emplace_back(stock_name, count);
        }
        input.close();
    }

    Trader::Trader(Trader&& oth) noexcept
    :   m_id(oth.m_id),
        m_name(std::move(oth.m_name)),
        m_balance(oth.m_balance),
        m_orders(std::move(oth.m_orders)),
        m_surname(std::move(oth.m_surname)) {}

    Trader::~Trader() {
        for (auto order : m_orders) {
            delete order;
        }
    }

    Trader& Trader::operator=(Trader&& lhs) noexcept {
        if (&lhs == this) {
            return *this;
        }
        m_name = std::move(lhs.m_name);
        m_balance = lhs.m_balance;
        m_id = lhs.m_id;
        m_orders = std::move(lhs.m_orders);
        return *this;
    }

    const std::string& Trader::getName() const {
        return m_name;        
    }

    const std::string& Trader::getSurname() const {
        return m_surname;
    }

    void Trader::setName(const std::string& name) {
        m_name = name;
    }

    void Trader::setSurname(const std::string& surname) {
        m_surname = surname;
    }

    std::size_t Trader::getId() const {
        return m_id;
    }

    double Trader::getBalance() const {
        return m_balance;
    }

    void Trader::addBalance(double sum) {
        m_balance += sum;
    }

    void Trader::reduceBalance(double sum) {
        m_balance -= sum;
    }

    Order* Trader::trade(const System& sys) {
        if (m_orders.empty()) {
            return nullptr;
        }
        Order* order = m_orders.back(); 
        m_orders.pop_back();
        return order;
    }

    void Trader::addStock(const std::string& name, int count) {
        m_stocks.emplace_back(name, count);
    }

    void Trader::printStocks() const {
        for (const auto& stock : m_stocks) {
            std::cout << stock.first << ": " << stock.second << std::endl;
        }
    }

    int Trader::getStocksCount() const {
        return m_stocks.size();
    }

    int Trader::getStockCount(const std::string& stock) const {
        for (const auto& [name, count] : m_stocks) {
            if (stock == name) {
                return count;
            }
        }
        return 0;
    }


} // namespace TS