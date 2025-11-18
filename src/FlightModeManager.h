#pragma once
#include "FaultDetector.h"
#include "CommandHandler.h"
#include "Watchdog.h"
#include "Telemetry.h"
#include <chrono>
#include <vector>
#include <string>

enum class FlightMode { BOOT=0, SAFE, NOMINAL, PAYLOAD, DEGRADED, SHUTDOWN };

class FlightModeManager {
public:
    FlightModeManager();
    void start(bool simulate = false);  
    void step();
    FlightMode getMode() const;
    void handleCommand(const std::string& cmd);

private:
    void transitionTo(FlightMode newMode);

    FlightMode mode_;
    bool simulate_;
    bool running_{false};
    std::chrono::steady_clock::time_point bootTime_;

    Watchdog wd_;
    FaultDetector fd_;
    CommandHandler ch_;
    Telemetry tx_;
};
