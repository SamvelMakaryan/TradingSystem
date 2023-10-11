#include <iostream>
#include <thread>
#include <chrono>

#include "Emulation.hpp"
#include "System.hpp"
#include "Order.hpp"

int main() {
    constexpr int duration = 10;
    std::thread timerThread(timer, duration);
    TS::System& market = TS::System::getSystemInstance();
    market.open(duration);
    timerThread.join();
}