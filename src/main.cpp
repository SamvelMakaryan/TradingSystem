#include <exception>
#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <random>

#include "Visualizer.hpp"
#include "Commands.hpp"
#include "Signals.hpp"
#include "System.hpp"

int main() {
    std::signal(SIGINT, sig::cntrlC);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(15, 40);
    int duration = dis(gen);
    std::thread timerThread(vis::timer, duration);
    TS::System& market = TS::System::getSystemInstance();
    market.open(duration);
    if (timerThread.joinable()) {
        timerThread.join();
    }
    cmd::commandLine(market);
}