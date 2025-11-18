#pragma once

#include <vector>
#include <cstdint>
#include "FaultDetector.h"


enum class FlightMode;



class Telemetry {
public:
    std::vector<uint8_t> format(FlightMode mode, const FaultDetector& fd,
uint8_t cpuLoad);
};