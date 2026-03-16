# SYSTEM LIFECYCLE AND STATE

Document Version: 1.0.0  
Status: Released

---

## 1.0 PURPOSE AND SCOPE

This document defines all authoritative system state machines. This document establishes formal separation between lifecycle progression and control authority. All state semantics, transitions, invariants, and coupling rules are normatively specified within this document. This document serves as the sole source of truth for system state behavior.

---

## 2.0 STATE MODEL OVERVIEW

### 2.1 State Machine Inventory

The system contains exactly two authoritative finite state machines:

- **System Lifecycle State (SLS)**
- **Control Authority State (CAS)**

No additional state machines may grant execution authority or lifecycle progression.

## 2.2 Orthogonality Guarantee

- SLS and CAS are independent
- No implicit transitions are permitted
- Explicit coupling rules, if any, are declared in this document

---

## 3.0 SYSTEM LIFECYCLE STATE (SLS)

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
- Allowed actions include only subsystem initialization, transport initialization, and state initialization
- CAS must be initialized to SAFE before BOOTSTRAP completes
- Prohibits CAS from transitioning to any state other than SAFE, denying any execution request from non-authoritative nodes

**OPERATIONAL**
- SLS state indicating successful initialization of all subsystems
- Entered after all initialization functions return successfully
- Exited upon connectivity loss or fatal error
- Permits CAS to transition out of SAFE state and allows authoritative controller to grant permission to execute attack logic
- Forbidden actions: none

**DEGRADED**
- SLS state declaring system degradation due to loss of non-essential subsystem capability
- Entered upon the authoritative controller receiving DISCONNECTED or FAILED status from the transport layer.
- Exited upon system reboot, or recovery as authorized by authoritative controller
- System permitted to continue operation through available channels
- Protocol interaction with the failed transport channel is prohibited

**FAULT**
- SLS state declaring terminal or fatal error, irrecoverable by authoritative controller
- Entered upon attempted protocol interaction while the system is in an invalid state, including architecturally unreachable states
- Exited only upon total system reinitialization
- System is permitted and required to shut down
- System is forbidden from continuing any operation including authorization, execution, or observation

### 3.4 SLS Transition Rules

System reinitialization or reset forces SLS = BOOTSTRAP regardless of prior state. FAULT prohibits operational recovery without full system reinitialization.

#### 3.4.1 Valid transitions

- BOOTSTRAP → OPERATIONAL
- BOOTSTRAP → DEGRADED
- BOOTSTRAP → FAULT
- OPERATIONAL → DEGRADED
- OPERATIONAL → FAULT
- DEGRADED → OPERATIONAL (conditional upon recovery authorized by the authoritative controller)
- DEGRADED → FAULT

#### 3.4.2 Invalid transitions

- FAULT → OPERATIONAL
- FAULT → DEGRADED
- Any prior state → BOOTSTRAP (barring total system reset)

#### 3.4.3 Transition triggers

- Completion of subsystem initialization
- Loss of transport connectivity
- Recovery of degraded subsystem
- Detection of fatal system error
- Detection of invalid system state
- Explicit authoritative controller reset

#### 3.4.4 Transition Authority

- Only the authoritative controller may mutate SLS
- Transport layers and subsystems may signal faults but may not directly mutate SLS

### 3.5 SLS Invariants

- Properties that must always hold:
	- CAS transitions may be constrained by SLS state, but CAS does not mutate SLS
	- Only the authoritative controller may mutate authoritative state machines

- States that are irreversible:
	- SLS = FAULT due to fatal error

- Failure handling requirements:
	- Authoritative controller may attempt recovery to transition SLS from DEGRADED to OPERATIONAL
	- FAULT is a terminal state. Recovery requires system reset, which reinitializes SLS to BOOTSTRAP

---

## 4.0 CONTROL AUTHORITY STATE (CAS)

### 4.1 Purpose

- Govern authorization to execute actions
- Enforce safety dominance
- Serve as the sole gate for execution nodes

### 4.2 CAS State Enumeration

States:

- SAFE
- DISARMED
- ARMING
- ARMED
- LOCKOUT

### 4.3 CAS State Definitions

**SAFE**
- Initial known state entered upon system initialization or upon system reset following a FAULT condition
- Signals system unready to perform actions
- SAFE dominates all CAS states. When CAS = SAFE, execution authority must be denied regardless of any other system condition.
- Allowed actions include only subsystem initialization functions and transport initialization
- Strictly prohibits all system execution other than initialization

**DISARMED**
- CAS state declaring system operational ability to perform actions
- Entered upon successful initialization of subsystems, conditional upon SLS = OPERATIONAL
- Strictly prohibits execution controller from performing system actions

**ARMING**
- CAS state signaling transition validation
- Entered upon authoritative controller receiving request to arm system
- Signals that the authoritative controller is performing policy verification to accept or reject request to arm system
- Execution controller strictly prohibited from performing system actions

**ARMED**
- CAS state declaring system readiness and permission to perform authorized actions
- Entered upon completion of policy compliance verification
- Authorizes execution controller to perform requested actions against external target network
- Updates policy requirement compliance (sets cooldowns, etc)

**LOCKOUT**
- CAS state declaring terminal or fatal error, irrecoverable by authoritative controller
- System requires full system reset to return to SAFE state
- Strictly prohibits all system execution other than initialization

### 4.4 CAS Transition Rules

System reinitialization or reset forces CAS = SAFE regardless of prior state. LOCKOUT prohibits operational recovery without full system reinitialization.

#### 4.4.1 Valid Transitions

- SAFE → DISARMED
- SAFE → LOCKOUT
- DISARMED → ARMING
- DISARMED → LOCKOUT
- ARMING → ARMED
- ARMING → DISARMED 
- ARMING → LOCKOUT
- ARMED → DISARMED
- ARMED → LOCKOUT

#### 4.4.2 Invalid Transitions

- LOCKOUT → SAFE (barring total system reset)
- LOCKOUT → DISARMED
- LOCKOUT → ARMING
- LOCKOUT → ARMED

#### 4.4.3 Transition Triggers

- Completion of subsystem initialization
- System ARM request
- Validation of policy compliance
- Detection of fatal system error
- Detection of invalid system state
- Explicit authoritative controller reset

#### 4.4.4 Transition Authority

- Only the authoritative controller may mutate CAS
- Transport layers and subsystems may signal faults but may not directly mutate CAS

### 4.5 CAS Invariants

- Properties that must always hold:
	- CAS transitions may be constrained by SLS state, but CAS must not mutate SLS
	- Only the authoritative controller may mutate authoritative state machines

- When CAS = SAFE:
	- Execution authority must be denied
	- Execution controller must halt any active operation
	- Transport must reject action commands

- States that are irreversible:
	- CAS = LOCKOUT due to fatal error

- Failure handling requirements:
	- Authoritative controller prohibited from autonomous recovery from LOCKOUT state
	- Recovery from LOCKOUT requires system reset
	- System reset reinitializes CAS to SAFE

---

## 5.0 CAS ↔ SLS COUPLING CONSTRAINTS

### 5.1 Allowed Dependencies

CAS transitions are permitted only when SLS = OPERATIONAL or DEGRADED. CAS is prohibited from advancement when lifecycle is unsafe.

When SLS = BOOTSTRAP:
- CAS must remain SAFE.

When SLS = FAULT:
- CAS must remain SAFE or LOCKOUT until system reset.

### 5.2 Forbidden Dependencies

- Implicit transitions between SLS and CAS
- Automatic CAS escalation due solely to SLS changes
- Time-based CAS transitions
- Transport-layer state directly mutating CAS
- Execution node mutating lifecycle state

### 5.3 Failure Interaction Rules

If SLS transitions to FAULT:
- CAS must immediately transition to SAFE.

If CAS transitions to LOCKOUT:
- SLS must remain unchanged unless a system reset occurs.

If SLS transitions to DEGRADED:
- CAS state remains unchanged but execution may be restricted by policy.

If CAS transitions to SAFE:
- Execution authority must be immediately revoked.

CAS must never escalate SLS state.
CAS transitions may restrict execution authority but must not alter lifecycle phase.
--- 

## 6.0 AUTHORITY AND ENFORCEMENT

- The authoritative controller is the sole entity permitted to mutate SLS or CAS
- Subsystems may emit status signals but must not directly mutate state machines
- Execution node must treat CAS as read-only authority input
- Non-authoritative nodes may observe but never infer state
- State identity ambiguity results in denial
- Transport layers must not infer or derive authority state
- Any component observing inconsistent state information must deny execution
- All components must treat the authoritative controller as the single source of state truth
- Local caching of state must not be used to infer authority

---

## 7.0 RESET, REINITIALIZATION, AND TERMINAL CONDITIONS

### 7.1 Controlled Reset

System reset may occur under the following conditions:
	- Manual operator intervention
	- Authoritative controller issuing reset command
	- Detection of unrecoverable system error

System reset forces:
	- SLS = BOOTSTRAP
	- CAS = SAFE

All subsystems must be reinitialized following reset.

### 7.2 Irrecoverable States

The following states are terminal without system reset:
	- SLS = FAULT
	- CAS = LOCKOUT

Upon entry into a terminal state:
	- Execution must cease immediately
	- Transport communications must reject command messages
	- System must await system reset

---

## 8.0 FAILURE HANDLING AND STATE SAFETY

### 8.1 Partial Failure

When subsystem failure is detected but system integrity remains intact:
	- SLS must transition to DEGRADED
	- CAS state remains unchanged
	- Execution authority may be restricted by policy

### 8.2 Convergence Requirement

The system must converge to one of the following states:
	- OPERATIONAL + DISARMED
	- OPERATIONAL + ARMED
	- DEGRADED + DISARMED
	- DEGRADED + ARMED
	- FAULT + SAFE

If convergence cannot be achieved, the system must transition to FAULT. No other combinations may persist indefinitely.

### 8.3 Logging and Evidence

All state transitions must generate an audit record containing:
	- previous state
	- new state
	- transition trigger
	- timestamp

---

## 9.0 ARCHITECTURAL INVARIANTS

- CAS and SLS remain singular
- Safety dominates liveness
- State ambiguity results in denial
- Authority is never inferred from state alone
- Execution authority exists only when:
	- SLS = OPERATIONAL or DEGRADED
	- CAS = ARMED

---

## 10.0 RELATIONSHIP TO OTHER DOCUMENTS

This document is constrained by:
- `02_architecture.md`

This document constrains:
- `04_comm_protocol.md`
- `05_security_threat_model.md`
- `06_test_plan.md`

--- 

END OF DOCUMENT
