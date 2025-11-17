#pragma once

#include <chrono>

class Watchdog {

public:
    explicit Watchdog(uint64_t timeoutMs=1000);
    void kick();
    bool expired();
    void reset();
private:
    uint64_t timeoutMs_;
    std::chrono::steady_clock::time_point lastKick_;
};
