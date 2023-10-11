#include "Stock.hpp"

namespace TS {
    
    Stock::Stock(const std::string& name, double price, int count) 
    :   m_name(name),
        m_price(price),
        m_count(count) {}

    Stock::Stock(const Stock& oth)
    :   m_name(oth.m_name),
        m_count(oth.m_count),
        m_price(oth.m_price) {}

    Stock::Stock(Stock&& oth) noexcept
    :   m_name(std::move(oth.m_name)),
        m_count(oth.m_count),
        m_price(oth.m_count) {}

    Stock& Stock::operator=(Stock&& lhs) noexcept {
        if (&lhs == this) {
            return *this;
        }
        m_name = std::move(lhs.m_name);
        m_count = lhs.m_count;
        m_price = lhs.m_price;
        return *this;
    }

    const std::string& Stock::getName() const {
        return m_name;
    }

    double Stock::getPrice() const {
        return m_price;
    }

    int Stock::getCount() const {
        return m_count;
    }

    void Stock::setName(const std::string& name) {
        m_name = name;
    }

    void Stock::increasePrice(double val) {
        m_price += val;
    }

    void Stock::decreasePrice(double val) {
        m_price -= val;
    }

    void Stock::increaseCount(int count) {
        m_count += count;
    }

    void Stock::decreaseCount(int count) {
        m_count -= count;
    }

} // namespace TS
