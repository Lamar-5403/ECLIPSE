# SECURITY THREAT MODEL

Document Version: 1.0.0     
Status: Released

---

## 1.0 PURPOSE

This document defines the security threat model for the E.C.L.I.P.S.E. system.
It identifies potential threats, adversary capabilities, attack surfaces, and security controls required to preserve system integrity, authority separation, and evidence reliability.

---

## 2.0 SCOPE

This document applies to all components of the E.C.L.I.P.S.E. system, including:

- Authoritative Controller
- Attack Simulation Node
- Evidence Protection Node
- Inter-device communication channels
- System state control mechanisms
- Evidence storage mechanisms

The scope includes threats to:

- System integrity
- Command authority
- Evidence integrity
- Operational safety

The scope excludes threats external to the deployed system environment that do not interact with system components.

---

## 3.0 SYSTEM SECURITY OBJECTIVES

This section defines the primary security properties the system must preserve.

The primary objectives include:

- **Authority Integrity**
- **Execution Control**
- **Evidence Integrity**
- **Command Authenticity**
- **System State Safety**
- **Non-repudiation of system events**

### 3.1 Normative Definitions

- **Authority Integrity**: The system acknowledges only the authoritative controller as the sole authority and rejects commands, system states, and properties from any other entity.

- **Execution Control**: The system only authorizes and executes operations listed in the table of permitted tactics and techniques against only targets listed in the database of permitted targets.

- **Evidence Integrity**: The system preserves all artifacts of execution, including log files generated during attacks, without loss or corruption.

- **Command Authenticity**: The system accepts and processes frames only from known system nodes; however, only the authoritative controller is permitted to issue commands that alter system state or authorize execution.

- **System State Safety**: The system state is altered by no node other than the authoritative controller. The authoritative controller is the sole arbiter of the system state and all other system nodes treat the authoritative controller as the sole source of truth for current system state.

- **Non-repudiation of system events**: The system cannot deny the legitimacy of the authorization or execution of actions taken. All authorization messages and execution results are logged and stored in append-only files for traceability and accountability.

---

## 4.0 TRUST BOUNDARIES

This section defines the logical and physical boundaries where trust assumptions change.

These boundaries include:

- Authoritative Controller boundary
- Execution Node boundary
- Evidence Node boundary
- Inter-device communication channels
- Physical device boundaries

### 4.1 Normative Descriptions

- Authoritative Controller Boundary: Data originating from the authoritative controller shall be treated as authoritative only after successful protocol validation by receiving nodes.

- Execution Node Boundary: The execution node is untrusted with respect to authority. It must not be permitted to assert state or grant execution privileges.

- Evidence Node Boundary: The evidence node is trusted for storage but must not be permitted to influence execution or authority decisions.

- Communication Boundary: All inter-device communication is untrusted until validated through protocol framing and integrity checks.

- Physical Boundary: Physical access to any node is considered a potential compromise vector.

---

## 5.0 ADVERSARY MODEL

This section defines the assumed capabilities of potential adversaries.

### 5.1 Adversary Classes

- External network adversary
- Local network adversary
- Malicious operator
- Physical device attacker
- Compromised execution node

### 5.2 Adversary Capabilities

- Packet injection
- Packet replay
- Protocol fuzzing
- Unauthorized command attempts
- Physical device access
- Denial-of-service attempts

### 5.3 Adversary Limitations

- Inability to modify firmware on the authoritative controller
- Inability to bypass deterministic state enforcement
- Inability to bypass physical isolation without detection
- Inability to simultaneously compromise all system nodes without detection
- Integrity mechanisms (e.g., CRC) are assumed to provide error detection only and do not provide protection against intentional adversarial manipulation.

---

## 6.0 ASSETS REQUIRING PROTECTION

The following assets require protection:

- **System State Machines (SLS / CAS)**
	- Impact: Unauthorized state transitions may enable execution or disable safety controls.

- **Authorization Logic**
	- Impact: Compromise allows unauthorized execution.
 
- **Command Protocol Integrity**
	- Impact: Malformed or injected commands may alter system behavior.

- **Evidence Logs and Audit Trails (append-only)**
	- Impact: Loss or modification breaks traceability and non-repudiation.

- **Node Identity**
	- Impact: Impersonation may enable injection of unauthorized frames or influence system behavior.

- **Communication Channel Integrity**
	- Impact: Interception or manipulation may alter command flow.

---

## 7.0 ATTACK SURFACE ANALYSIS

The system exposes the following attack surfaces:

- **Serial Communication Interfaces**
	- Risk: Injection of malformed or unauthorized frames.

- **Network Interfaces**
	- Risk: Remote command injection or denial-of-service.

- **Protocol Parser**
	- Risk: Undefined behavior due to malformed input.

- **State Transition Requests**
	- Risk: Unauthorized escalation to ARMED state.

- **Evidence Storage Subsystem**
	- Risk: Deletion or modification of logs.

- **Power / Reset Interface**
	- Risk: Forced resets to disrupt operation.

- **Physical Access to Nodes**
	- Risk: Hardware tampering or data extraction.

All surfaces require strict validation and deterministic handling of input.

---

## 8.0 THREAT IDENTIFICATION

### 8.1 Command Injection
Unauthorized commands injected into communication channel.

### 8.2 Command Replay
Previously valid commands replayed to trigger unintended actions.

### 8.3 State Escalation
Unauthorized transition to ARMED or other privileged states.

### 8.4 Evidence Tampering
Modification or deletion of recorded system evidence.

### 8.5 Node Impersonation
A malicious device attempts to masquerade as a legitimate node.

### 8.6 Protocol Corruption
Malformed protocol frames designed to trigger undefined behavior.

### 8.7 Denial of Service
Attempts to exhaust resources or disrupt system communication.

---

## 9.0 THREAT IMPACT ANALYSIS

### 9.1 Command Injection

- **Affected Assets**:
	- Command protocol integrity
	- Authorization logic
	- System state machines (SLS / CAS)

- **Potential Impact**:
	- Unauthorized execution of commands
	- Bypass of authority enforcement
	- Transition to ARMED without authorization

- **Severity**: Critical

### 9.2 Command Replay

- **Affected Assets**:
	- Command protocol integrity
	- Authorization logic

- **Potential Impact**:
	- Re-execution of previously valid commands
	- Violation of execution intent and timing constraints

- **Severity**: High

### 9.3 State Escalation

- **Affected Assets**:
        - System state machines (SLS / CAS)
        - Authorization logic

- **Potential Impact**:
        - Unauthorized transition to ARMED state
        - Loss of execution control guarantees

- **Severity**: Critical

### 9.4 Evidence Tampering

- **Affected Assets**:
        - Evidence Logs and Audit Trails

- **Potential Impact**:
        - Loss of forensic integrity
        - Inability to verify system behavior
	- Violation of non-repudiation guarantees

- **Severity**: Critical

### 9.5 Node Impersonation

- **Affected Assets**:
        - Node identity
        - Command authenticity
	- Authorization logic

- **Potential Impact**:
        - Acceptance of malicious or unauthorized frames
        - Potential indirect influence on system behavior

- **Severity**: Critical

### 9.6 Protocol Corruption

- **Affected Assets**:
        - Protocol parser
        - Communication channel integrity

- **Potential Impact**:
        - Undefined system behavior
        - Potential crashes or unintended state transitions

- **Severity**: High

### 9.7 Denial of Service

- **Affected Assets**:
        - Communication channels
        - Execution availability
	- System responsiveness

- **Potential Impact**:
        - Loss of system availability
        - Delayed or blocked command processing
	- Potential forced transitions to DEGRADED or FAULT

- **Severity**: High

---

## 10.0 SECURITY CONTROLS

This system employs the following controls:

- Deterministic finite state machines (SLS / CAS)
- Explicit command authorization through the authoritative controller
- Strict protocol framing with length validation
- CRC-based integrity checking
- Physical separation of authority, execution, and evidence nodes
- Append-only evidence logging
- Fail-safe transitions to SAFE or FAULT states upon anomaly detection

All controls are implemented as defined in the architecture and communication protocol specifications.

---

## 11.0 RESIDUAL RISK

### 11.1 Physical Device Compromise

- **Description**:
	- Adversary gains physical access to one or more system nodes.

- **Reason Risk Remains**:
	- Physical access cannot be fully prevented through software or protocol controls.

- **Operational Mitigation**:
	- Controlled deployment environment
	- Restricted physical access
	- Device monitoring and inspection procedures

### 11.2 Denial of Service via Resource Exhaustion

- **Description**:
	- Adversary floods communication channels or overwhelms processing capacity.

- **Reason Risk Remains**:
        - Resource constraints on embedded systems limit ability to fully absorb or filter high-volume traffic.

- **Operational Mitigation**:
        - Input rate limiting
        - Watchdog timers
        - Automatic transition to safe states upon overload

### 11.3 Partial Communication Failure

- **Description**:
        - Loss or degradation of communication between nodes.

- **Reason Risk Remains**:
        - Communication channels are inherently unreliable and subject to interference or disruption.

- **Operational Mitigation**:
        - Transition to DEGRADED state
        - Restriction of execution authority
        - Recovery procedures defined in lifecycle management

### 11.4 Compromised Execution Node

- **Description**:
        - Execution node behaves maliciously or deviates from expected behavior.

- **Reason Risk Remains**:
        - Execution node performs active operations and is exposed to external interaction.

- **Operational Mitigation**:
        - Strict authority separation
        - No execution authority granted without CAS = ARMED
        - Independent evidence logging for verification

### 11.5 Command Replay Risk

- **Description**:
	- Valid command frames are captured and replayed within acceptable protocol format.

- **Reason Risk Remains**:
	- Protocol does not define cryptographic freshness guarantees (e.g., nonces or sequence enforcement beyond basic validation) in the current revision.

- **Operational Mitigation**:
	- Temporal constraints on command validity
	- State-dependent command acceptance
	- Monitoring for anomalous repetition patterns

### 11.6 Node Impersonation Risk

- **Description**:
	- Malicious device presents itself as a legitimate node within communication channels.

- **Reason Risk Remains**:
	- Absence of strong cryptographic identity verification between nodes in the current revision.

- **Operational Mitigation**:
	- Physical network isolation
	- Controlled device provisioning
	- Monitoring of unexpected communication sources

---

## 12.0 SECURITY ASSUMPTIONS

The security model assumes:

- Integrity of authoritative controller firmware
- Trusted physical deployment environment
- Correct implementation of protocol validation across all nodes
- No malicious modification of evidence node storage mechanisms
- Operator adherence to defined operational procedures

---

## 13.0 SECURITY VALIDATION

Security controls are validated through:

- Protocol fuzz testing
- Fault injection testing
- State transition validation
- Adversarial command testing
- Integrity verification of evidence storage

All validation procedures are defined in the system test plan.

---

## 14.0 RELATIONSHIP TO OTHER DOCUMENTS

This document is constrained by:

- `01_requirements.md`
- `02_architecture.md`
- `03_lifecycle_and_state.md`

This document constrains:

- `04_comm_protocol.md`
- `06_test_plan.md`

---

END OF DOCUMENT
