#pragma once
#include <cstdint>

struct FaultStatus {
    bool imuFault = false;
    bool gpsFault = false;
    bool thermalFault = false;
    bool powerFault = false;
};

class FaultDetector {
public:
    FaultDetector();

    // Simulation-aware sampler
    void sample(bool simulate);

    // No-arg sampler
    void sample();

    bool hasFault() const;
    bool hasCriticalFault() const;
    FaultStatus status() const;

    // NEW: telemetry getters
    int getIMU() const { return imu_; }
    int getGPS() const { return gps_; }
    int getThermal() const { return thermal_; }
    int getPower() const { return power_; }

private:
    FaultStatus st_;
    uint64_t counter_;

    // NEW: simulated telemetry values
    int imu_ = 0;
    int gps_ = 0;
    int thermal_ = 0;
    int power_ = 0;
};
