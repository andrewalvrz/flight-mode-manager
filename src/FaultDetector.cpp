#include "FaultDetector.h"
#include <cstdlib>

// Constructor
FaultDetector::FaultDetector()
    : st_(), counter_(0), imu_(0), gps_(0), thermal_(0), power_(0)
{}

// Sample faults. 'simulate' tunes how often faults occur.
void FaultDetector::sample(bool simulate) {
    ++counter_;

    // Baseline probabilities (live mode = very rare, simulate mode = occasional)
    int imu_prob   = simulate ? 3000 : 200000;   // 1 in N chance per cycle
    int gps_prob   = simulate ? 5000 : 400000;
    int thermal_period = simulate ? 20000 : 1000000; // periodic thermal event
    int power_prob = simulate ? 25000 : 1000000; // critical power event rare

    // Randomized faults
    st_.imuFault = ((std::rand() % imu_prob) == 0);
    st_.gpsFault = ((std::rand() % gps_prob) == 0);
    st_.thermalFault = (counter_ % thermal_period) == 0;
    st_.powerFault = ((std::rand() % power_prob) == 0);

    // NEW: update simulated telemetry values
    if (simulate) {
        imu_ = std::rand() % 101;      // 0–100%
        gps_ = std::rand() % 101;
        thermal_ = std::rand() % 101;
        power_ = std::rand() % 101;
    } else {
        // live mode can just increment slowly or stay constant for demo
        imu_ = (imu_ + 1) % 101;
        gps_ = (gps_ + 1) % 101;
        thermal_ = (thermal_ + 1) % 101;
        power_ = (power_ + 1) % 101;
    }
}

// Old API compatibility wrapper (if someone calls sample() without args)
void FaultDetector::sample() {
    sample(false);
}

bool FaultDetector::hasFault() const {
    return st_.imuFault || st_.gpsFault || st_.thermalFault || st_.powerFault;
}

bool FaultDetector::hasCriticalFault() const {
    // For demo: power fault is considered critical
    return st_.powerFault;
}

FaultStatus FaultDetector::status() const {
    return st_;
}
