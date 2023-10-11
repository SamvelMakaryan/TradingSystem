#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <cstddef>
#include <string>

namespace TS {

    class Stock {
    public:
        Stock(const std::string&, double, int);
        Stock(const Stock&);
        Stock(Stock&&) noexcept;
        ~Stock() = default;
    public:
        Stock& operator=(Stock&&) noexcept;
    public:
        const std::string& getName() const;
        double getPrice() const;
        int getCount() const;
        void setName(const std::string&);
        void increasePrice(double);
        void decreasePrice(double);
        void increaseCount(int);
        void decreaseCount(int);
    private:
        std::string m_name;
        double m_price;
        int m_count;
    };

} //namespace TS

#endif //STOCK_HPP_