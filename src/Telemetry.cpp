#include "Telemetry.h"
#include "FlightModeManager.h" // for FlightMode definition
#include <cstdint>
#include <vector>

// Simple CRC16-CCITT for demo
static uint16_t crc16_ccitt(const std::vector<uint8_t>& data) {
    uint16_t crc = 0xFFFF;
    for (auto d : data) {
        crc ^= (uint16_t)d << 8;
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x8000) crc = (crc << 1) ^ 0x1021;
            else crc <<= 1;
        }
    }
    return crc;
}

std::vector<uint8_t> Telemetry::format(FlightMode mode, const FaultDetector& fd, uint8_t cpuLoad) {
    std::vector<uint8_t> pkt;
    // SYNC bytes
    pkt.push_back(0xAA);
    pkt.push_back(0x55);
    // Mode (1 byte)
    pkt.push_back(static_cast<uint8_t>(mode));
    // fault bitmask
    FaultStatus st = fd.status();
    uint8_t mask = 0;
    if (st.imuFault) mask |= 0x01;
    if (st.gpsFault) mask |= 0x02;
    if (st.thermalFault) mask |= 0x04;
    if (st.powerFault) mask |= 0x08;
    pkt.push_back(mask);
    // CPU load
    pkt.push_back(cpuLoad);
    // CRC16
    uint16_t crc = crc16_ccitt(pkt);
    pkt.push_back((crc >> 8) & 0xFF);
    pkt.push_back(crc & 0xFF);
    return pkt;
}
