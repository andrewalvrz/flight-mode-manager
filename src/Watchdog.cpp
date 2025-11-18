#include "Watchdog.h"
#include <chrono>

Watchdog::Watchdog(uint64_t timeoutMs)
    : timeoutMs_(timeoutMs),
      lastKick_(std::chrono::steady_clock::now())
{}

void Watchdog::kick() {
    lastKick_ = std::chrono::steady_clock::now();
}

bool Watchdog::expired() {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto ms = duration_cast<milliseconds>(now - lastKick_).count();
    return (uint64_t)ms > timeoutMs_;
}

void Watchdog::reset() {
    lastKick_ = std::chrono::steady_clock::now();
}
