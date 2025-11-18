# Flight Mode Manager

This project implements a simulated Flight Mode Manager (FM) for a small satellite/CubeSat. It demonstrates:

- A deterministic state machine:  
  `BOOT -> SAFE -> NOMINAL -> PAYLOAD -> DEGRADED -> SHUTDOWN`
- Watchdog monitoring and reset behavior
- Command handler for ground commands
- Fault detection logic (IMU/GPS/CPU/power)
- Telemetry packet formatter (binary-like)


## State Machine

```mermaid
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
```


# Clean previous builds

```
make clean

```
# Build the Flight Mode Manager

```
make all

```
# Run

```
./bin/flight_mode_manager

```

```
[MAIN] Interactive console. Type commands (NOMINAL/SAFE/DEGRADED/PAYLOAD/BOOT/SHUTDOWN/KICK). Type EXIT to stop.

```