# SYSTEM REQUIREMENTS SPECIFICATION

Document Version: 1.0.0  
Status: Released

---

## 1.0 PURPOSE

This document defines the verifiable functional and non-functional requirements of the system. These requirements describe the non-negotiable actions of the system. Implementation procedures are defined normatively in downstream documents.

All requirements defined in this document are intended to be:

- Testable
- Unamibuous
- Traceable
- Implementation-independent

---

## 2.0 SCOPE

Eclipse

Operates between raspbian os and arduino runtime environment

any user who download the and implements the items in the github repo

operates between two to three nodes

simulates recon and attack orchestration

---

## 3.0 DEFINITIONS AND ACRONYMS

Node: Independed computing element within the system

Authority Node: Node responsible for system state control

Execution Node: Node responsible for operational task execution

Observation Node: Node responsible for telemetry and evidence collection

---

## 4.0 APPLICABLE DOCUMENTS

The following documents form a part of this specification to the extent specified herein:

- `00_overview.md`
- `04_comm_protocol.md`
- `05_security_threat_model.md`

---

## 5.0 SYSTEM CONTEXT

This system is designed to perform reconaissance on external networks with owner permission. Once the subnet of the network is obtained, the execution controller performs reconaissance with authoritative node authorization and logs the results.

### 5.1 External Systems

| Entity | Description |
|--- | ---- |
| Operator | Human controlling the system |
| Target Network | External environment where actions occur |
| Observation Infrastructure | Evidence collection infrastructure |

### 5.2 System Boundary

Inside the system is are the authoritative and execution controllers, the observation node, and the logic that requests, authorizes, executes, and logs the results of an attack.

Outside the system is are the external network to be attacked, the human operators, and any potential adversaries.

---

## 6.0 OPERATIONAL CONCEPT

Upon boot, the system will enter a known SAFE state and initialize all subsystems, including system state. The execution controller will construct an outgoing frame requesting to run the reconnaissance attack. The arduino shall receive this frame agnostic of transport and verfiy attacks are within scope and cooldowns are not in effect before authorizing execution controller to perform the attack. Upon authorization, the execution controller will perform reconnaissance on the external target network, creating an append-only log file to report results. System execution halts after this sequence. The log report is not transmitted to the observation node in the current revsion.

---

## 7.0 SYSTEM REQUIREMENTS

### 7.1 Functional Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-FR-001 | init | Test |
| SYS-FR-002 | gss | Inspection |
| SYS-FR-003 | modify | Test |
| SYS-FR-004 | execute | Test |
| SYS-FR-005 | CRC | Test |

### 7.2 Communication Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-COM-001 | frame | Inspection |
| SYS-COM-002 | reject | Test |
| SYS-COM-003 | start | Test |

### 7.3 Security Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-SEC-001 | authorize | Test |
| SYS-SEC-002 | prevent | Test |
| SYS-SEC-003 | log | Inspection |

### 7.4 Evidence and Logging Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-LOG-001 | append-only | Inspection |
| SYS-LOG-002 | record | Test |
| SYS-LOG-003 | operation | Test |

### 7.5 Reliability Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-REL-001 | detect | Test |
| SYS-REL-002 | continue | Test |

### 7.6 Performance Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-PERF-001 | process | Test |
| SYS-PERF-002 | support | Test |

---

## 8.0 INTERFACE REQUIREMENTS

This section defines required interfaces between system components.

### 8.1 Node Interfaces

| Interface | Description |
|:--- | :--- |
| Authority-Execution Interface | Command authorization and execution control |
| Execution-Observation Interface | Telemetry reporting and storage |
| Authority-Observation Interface | System state monitoring |

---

## 9.0 SYSTEM CONSTRAINTS

This section explicitly defines the constraints imposed on the system by design.

### 9.1 Hardware Platform Limitations

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-001 | embedded microcontroller platform | 

### 9.2 Operating System Dependencies

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-002 | Linux-based systems |

### 9.3 Transport Protocol Restrictions

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-003 | Bytes |

---

## 10.0 VERIFICATION METHODS

This section defines how requirements are validated.

| Method | Description |
| :--- | :--- |
| Test | Verified through execution testing |
| Inspection | Verified through code or document review |
| Analysis | Verified through reasoning or modeling |
| Demonstration | Verified through operational demonstration |

---

## 11.0 REQUIREMENTS TRACEABILITY

Traceability between:

- System Objectives
- System Requirements
- Verification Tests

| Requirement | Objective | Verification |
|:--- | :--- | :--- |
| SYS-FR-001 | Safe initialization | Test |
| SYS-FR-004 | Controlled execution | Inspection |

--- 

## 12.0 FUTURE REQUIREMENTS

This section defines requirements that are not implemented in the current design.

| Requirement ID | Description |
| :--- | :--- |
| SYS-SEC-010 | The system shall implement cryptographic authentication between nodes. |

---

END OF DOCUMENT
