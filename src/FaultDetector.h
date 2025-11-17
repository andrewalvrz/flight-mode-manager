#pragma once


#include <atomic>
struct FaultStatus {
    bool imuFault = false;

    bool gpsFault = false;
    bool thermalFault = false;
    bool powerFault = false;
};


class FaultDetector {
public:
    FaultDetector();
    void sample();
    bool hasFault() const;
    bool hasCriticalFault() const;
    FaultStatus status() const;
private:
    FaultStatus st_;
    int counter_;
};
