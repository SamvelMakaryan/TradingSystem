cmake_minimum_required(VERSION 3.10)

project(TradingSystem)

set(SOURCES
    src/Commands.cpp
    src/LimitOrder.cpp
    src/MarketOrder.cpp
    src/Order.cpp
    src/Signals.cpp
    src/Stock.cpp
    src/Trader.cpp
    src/Visualizer.cpp
    src/main.cpp
    src/OrderBook.cpp
    src/System.cpp
)

set(HEADERS
    src/Commands.hpp
    src/LimitOrder.hpp
    src/MarketOrder.hpp
    src/Order.hpp
    src/Signals.hpp
    src/Stock.hpp
    src/Trader.hpp
    src/Visualizer.hpp
    src/OrderBook.hpp
    src/OrderType.hpp
    src/System.hpp
)

add_executable(TradingSystem ${SOURCES} ${HEADERS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
