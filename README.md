# Flight Mode Manager
This project implements a simulated Flight Mode Manager (FM) for a small
satellite/CubeSat. It demonstrates:
- A deterministic state machine:
`BOOT -> SAFE -> NOMINAL -> PAYLOAD -> DEGRADED -> SHUTDOWN`
- Watchdog monitoring and reset behavior
- Command handler for ground commands
- Fault detection logic (IMU/GPS/CPU/power)
- Telemetry packet formatter (binary-like)
- Unit tests and a "SIMRUN" simulation mode
## Build
Requirements:
- g++ (C++17), make
- Python 3 for the day-in-life script
Build:
```bash
make all
