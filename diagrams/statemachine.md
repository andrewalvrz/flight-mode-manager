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