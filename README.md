# E.C.L.I.P.S.E.
Embedded Cybersecurity Control and Evidence Integrity System

---

## Overview
ECLIPSE is a distributed embedded system designed to **simulate, control, and supervise cybersecurity attack operations** in a **tightly governed environment**. The system separates **authority, execution, and evidence preservation** across independent hardware platforms.

---

## System Components

### Raspberry Pi 5 - Attack Simulation Node

- Executes controlled cybersecurity attack simulations
- Generates operational logs and artifacts
- Operates only when explicitly authorized

### Raspberry Pi Zero WH - Evidence Protection Node

- Collects and stores attack logs
- Preserves evidence integrity
- Monitors Pi 5 health and behavior

### Arduino Uno R4 Wifi - System Authority Controller

- Maintains global system state
- Enforces authorization and safety rules
- Validates all inbound commands

---

## Security Model

- Explicit authorization only
- Deterministic state enforcement
- No implicit trust between nodes
- Physical separation of authority and execution
- Corruption detection via CRC framing

---

## Communication Model

All inter-device communication uses a framed protocol with:

- Fixed start byte
- Explicit length field
- CRC-16 validation
- Deterministic parsing via FSM

Invalid frames are discarded without side effects.
Detailed specifications are defined in `/docs/03_comm_protocol.md`.

  ---

  ## High-Level Architecture

  ```text
  Pi Zero (Evidence)
        ↑
        |
  Arduino (Authority)
        |
        ↓
  Pi 5 (Attack Execution)
```

---

## System States

The system operates under a finite set of global states enforced by the Arduino controller:

- SAFE
- ARMING
- ARMED
- DISARMED
- LOCKOUT

Attack execution is only permitted while the system is in the ARMED state.

---

## Repository Structure

```
arduino/
|-- include/    #Public headers
|-- src/        # Source files
|-- lib/        # External libraries
|-- tests/      # Unit and integration tests
|-- docs/       # Formal project documentation
|-- platform.ini
```

---

## Documentation

Formal documentation is located in the `/docs` directory:

-`00_overview.md`
-`01_requirements.md`
-`02_architecture.md`
-`03_comm_protocol.md`
-`04_security_threat_model.md`
-`05_test_plan.md`
-`06_bom.md`
-`07_deployment.md`

---

## Status

This project is under active development.
Interfaces, protocols, and system behavior are subject to change.
