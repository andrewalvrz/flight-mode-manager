#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include "Watchdog.h"
#include "FaultDetector.h"
#include "CommandHandler.h"
#include "Telemetry.h"


enum class FlightMode {

    BOOT,
    SAFE,
    NOMINAL,
    PAYLOAD,
    DEGRADED,
    SHUTDOWN
};

class FligthModeManager{



public:

    FligthModeManager();

    void start (bool simulate = false);

    void step();
    FlightMode getMode() const;

    void handleCommand(const std:: string& cmd);

private:

    void transitionTo(FlightMode m);

    void evaluateFaults();

    FlightMode mode_;
    Watchdog wd_;
    FaultDetector fd_;
    CommandHandler ch_;
    Telemetry tx_;

    std::chrono::steady_clock::time_point bootTime_;
    bool simulate;


}





