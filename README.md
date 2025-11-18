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

## STATE MACHINE


stateDiagram-v2
 [*] --> BOOT
 BOOT --> SAFE: boot_timeout
 SAFE --> NOMINAL: health_ok & cmd_enter_nominal
 NOMINAL --> PAYLOAD: cmd_enter_payload
 NOMINAL --> DEGRADED: fault_detected
 PAYLOAD --> NOMINAL: cmd_enter_nominal
 DEGRADED --> SAFE: recover
 * --> SHUTDOWN: critical_fault
 SHUTDOWN --> [*]


## Build
Requirements:
- g++ (C++17), make
- Python 3 for the day-in-life script
Build:
```bash
make all

