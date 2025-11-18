#include "FlightModeManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

// Constructor
FlightModeManager::FlightModeManager()
    : mode_(FlightMode::BOOT),
      running_(false),
      wd_(5000),  // 5-second watchdog
      fd_(),
      ch_(),
      tx_()
{
    std::cout << "[FM] Initialized in BOOT mode.\n";
}

// Start FSM loop
void FlightModeManager::start(bool simulate)
{
    running_ = true;
    simulate_ = simulate;
    std::cout << "[FM] Starting Flight Mode Manager...\n";

    while (running_) {
        step();

        // Slow loop down to ~5 Hz
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

// Single FSM step
void FlightModeManager::step()
{
    // Kick watchdog every step
    wd_.kick();

    // Sample faults
    fd_.sample();

    // Check faults
    if (fd_.hasCriticalFault()) {
        if (mode_ != FlightMode::SAFE) {
            std::cout << "[FM] Critical fault detected! Switching to SAFE mode.\n";
            transitionTo(FlightMode::SAFE);
        }
    } else if (fd_.hasFault() && mode_ != FlightMode::SAFE && mode_ != FlightMode::DEGRADED) {
        std::cout << "[FM] Non-critical fault detected. Entering DEGRADED mode.\n";
        transitionTo(FlightMode::DEGRADED);
    }

    // Process pending commands
    while (ch_.hasPending()) {
        std::string cmd = ch_.pop();
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

        if (cmd == "SAFE") transitionTo(FlightMode::SAFE);
        else if (cmd == "DEGRADED") transitionTo(FlightMode::DEGRADED);
        else if (cmd == "SHUTDOWN") transitionTo(FlightMode::SHUTDOWN);
        else if (cmd == "PAYLOAD") transitionTo(FlightMode::PAYLOAD);
        else if (cmd == "NOMINAL") transitionTo(FlightMode::NOMINAL);
        else if (cmd == "BOOT") transitionTo(FlightMode::BOOT);
        else if (cmd == "KICK") wd_.kick();
        else std::cout << "[FM] Unknown command: " << cmd << "\n";
    }

    // Watchdog expired? Only switch to SAFE if actually expired
    if (wd_.expired()) {
        if (mode_ != FlightMode::SAFE) {
            std::cout << "[FM] Watchdog expired! Switching to SAFE mode.\n";
            transitionTo(FlightMode::SAFE);
        }
    }

    // Mode-specific auto-transition demo
    if (mode_ == FlightMode::BOOT && !simulate_) {
        transitionTo(FlightMode::NOMINAL);
    }

    // Generate telemetry
    std::vector<uint8_t> packet = tx_.format(mode_, fd_, 50); // CPU load stub
    std::cout << "[TELEMETRY] Mode: " << static_cast<int>(mode_)
              << " | IMU:" << fd_.getIMU()
              << " GPS:" << fd_.getGPS()
              << " THERM:" << fd_.getThermal()
              << " PWR:" << fd_.getPower()
              << " | CPU:50%\n";
}
    
// Return current mode
FlightMode FlightModeManager::getMode() const
{
    return mode_;
}

// Deliver command from main
void FlightModeManager::handleCommand(const std::string& cmd)
{
    ch_.push(cmd);
}

// Transition FSM
void FlightModeManager::transitionTo(FlightMode newMode)
{
    if (newMode != mode_) {
        std::cout << "[FM] Transitioning from " << static_cast<int>(mode_)
                  << " to " << static_cast<int>(newMode) << "\n";
        mode_ = newMode;
    }
}
