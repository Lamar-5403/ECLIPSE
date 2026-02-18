# SYSTEM LIFECYCLE AND STATE

Document Version: 0.1
Status: Draft

---

## 1.0 PURPOSE AND SCOPE

This document defines all authoritative system state machines. This document establishes formal separation between lifecycle progression and control authority. All state semantics, transtions, invariants, and coupling rules are normatively specified within this document. This document serves as the sole source of truth for system state behavior.

---

## 2.0 STATE MODEL OVERVIEW

### 2.1 State Machine Inventory

The system contains exactly two authoritative finite state machines:

- **System Lifecycle State (SLS)**
- **Control Authority State (CAS)**

No additional state machines may grant execution authority or lifecycle progression.

## 2.2 Orthogonality Guarantee

- SLS and CAS are independent
- No implicity transitions are permitted
- Explicit coupling rules, if any, are declared in this document

---

## 3.0 SYTSTEM LIFECYCLE STATE (SLS)

### 3.1 Purpose

This state machine defines system phase and readiness. The state machine governs initialization, operation, shutdown, and terminal conditions, and controls when CAS transitions are permitted.

### 3.2 SLS State Enumeration

Lifecycle states:
- BOOTSTRAP
- OPERATIONAL
- DEGRADED
- FAULT

### 3.3 SLS State Definitions

**BOOTSTRAP**
- Initial known state where system initialization occurs
- Entered upon boot
- Exited upon completion of all subsystem initialization
- Allowed actions include only subsystem initialization functions, including transport_serial_init(), transport_wifi_init(), and system_state_init(), and transitioning of CAS to SAFE state
- Prohibits CAS from transitioning to any state other than SAFE, denying any execution request from non-authoritative nodes

**OPERATIONAL**
- SLS state indicating successful initialization of all subsystems
- Entered after all initialization functions return successfully
- Exited upon connectivity loss or fatal error
- Permits CAS to transition out of SAFE state and allows authoritative controller to grant permission to execute attack logic
- Forbidden actions: none

**DEGRADED**
- SLS state declaring system degradation upon wireless connectivity loss where system may still operate under serial connection only
- Entered upon authoritative controller receiving DISCONNECTED or FAILED status from transport layer.
- Exited upon system reboot, or recovery as authorized by system controller
- System permitted to continue operation through available channels
- System forbidden from protocol interaction with degraded subsystem(s)

**FAULT**
- SLS state declaring terminal or fatal error, irrecoverable by system controller
- Entered upon attempted protocol interaction while system is in invalid state, including architecturally unreachable states
- Exited only upon total system reinitialization
- System is permitted and required to shutdown
- System is forbidden from continuing any operation inlcuding authorization, execution, or observation

### 3.4 SLS Transition Rules

- Valid transitions:
 - BOOTSTRAP -> OPERATIONAL
 - BOOTSTRAP -> DEGRADED
 - BOOTSTRAP -> FAULT
 - OPERATIONAL -> BOOTSTRAP (conditional upon total system reinitialization)
 - OPERATIONAL -> DEGRADED
 - OPERATIONAL -> FAULT
 - DEGRADED -> BOOTSTRAP (conditional upon total system reinitialization)
 - DEGRADED -> OPERATIONAL (conditional upon system-controller-initiated recovery)
 - DEGRADED -> FAULT
 - FAULT -> BOOTSTRAP (conditional upon total system reinitialization)

- Invalid transitions:
 - FAULT -> OPERATIONAL
 - FAULT -> DEGRADED

- Transition triggers:
 - Loss of connectivity
 - Recovery of connectivity
 - Fatal error including invalid system state reached

- Authority required for transition:
 - System controller mutates CAS state based on current SLS state

### 3.5 SLS Invariants

- Properties that must always hold:
 - CAS state is subordinate to SLS state
 - Only the authoritative controller may mutate authoritative state machines

- States that are irreversible:
 - SLS = FAULT due to fatal error

- Failure handling requirements:
 - System controller may attempt recovery to transition SLS from DEGRADED to OPERATIONAL
 - System controller must transition from FAULT to BOOTSTRAP and reinitialize system to return to OPERATIONAL

---

## 4.0 CONTROL AUTHORITY STATE (CAS)

### 4.1 Purpose

- Govern authorization to execute actions
- Enforce safety dominance
- Serve as the sole gate for execution nodes

### 4.2 CAS State Enumeration

(List of authority states)

- SAFE
- ARMING
- ARMED
- DISARMED
- LOCKOUT

### 4.3 CAS State Definitions

For each state:
- Meaning
- Authorization semantics
- Required guarantees
- Prohibited behavior

### 4.4 CAS Transition Rules

- Valid transitions
- Invalid transitions
- Preconditions
- Required evidence or signals

### 4.5 CAS Invariants

- Safety guarantees
- Failure behavior
- Default-deny conditions

---

## 5.0 CAS ↔ SLS COUPLING CONSTRAINTS

### 5.1 Allowed Dependencies

- SLS states that permit CAS transitions
- SLS states that prohibit CAS transitions

### 5.2 Forbidden Dependencies

- Implicit transitions
- Automatic propagation
- Time-based escalation

### 5.3 Failure Interaction Rules

- Effect of SLS failure on CAS
- Effect of CAS failure on SLS

--- 

## 6.0 AUTHORITY AND ENFORCEMENT

- Only the authoritative controller may mutate CAS or SLS
- Non-authoritative nodes may observe but never infer state
- State identity ambiguity results in denial

---

## 7.0 RESET, REINITIALIZATION, AND TERMINAL CONDITIONS

### 7.1 Controlled Reset

- Conditions permitting reset
- Required authority
- State impact

### 7.2 Irrecoverable States

- Definition of terminal states
- Required actions upon entry
- Prohibition of recovery

---

## 8.0 FAILURE HANDLING AND STATE SAFETY

- State behavior under partial failure
- Required convergence behavior
- Evidence and logging requirements

---

## 9.0 ARCHITECTURAL INVARIANTS

- CAS and SLS remain singular
- Safety dominates liveness
- State ambiguity results in denial
- Authority is never inferred from state alone

---

## 10.0 RELATIONSHIP TO OTHER DOCUMENTS

This document is constrained by:
- `02_architecture.md`

This document constrains:
- `03_comm_protocol.md`
- `04_security_threat_model.md`
- `05_test_plan.md`

--- 

END OF DOCUMENT
