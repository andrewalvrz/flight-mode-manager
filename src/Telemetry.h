#pragma once

#include <vector>
#include <cstdint>
#include "FaultDetector.h"
#include "FlightModeManager.h"
class Telemetry {
public:
    std::vector<uint8_t> format(FlightMode mode, const FaultDetector& fd,
uint8_t cpuLoad);
};