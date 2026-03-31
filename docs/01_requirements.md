# SYSTEM REQUIREMENTS SPECIFICATION

Document Version: 1.0.0  
Status: Released

---

## 1.0 PURPOSE

This document defines the verifiable functional and non-functional requirements of the system. These requirements describe the required behaviors of the system. Implementation procedures are defined normatively in downstream documents.

All requirements defined in this document are intended to be:

- Testable
- Unambiguous
- Traceable
- Implementation-independent

---

## 2.0 SCOPE

E.C.L.I.P.S.E. is a distributed research system designed to coordinate controlled cybersecurity reconnaissance operations across multiple heterogeneous computing nodes.

The system operates across a small network of two to three nodes consisting of an authoritative control node, an execution node, and an optional observation node. The authoritative controller operates on an embedded microcontroller platform, while the execution controller operates on a Linux-based system. Communication between nodes occurs through a custom framed protocol layered over the operating system's native byte transport mechanisms.

The system simulates controlled reconnaissance and attack orchestration against externally designated network targets within a supervised research environment. Execution of operational tasks occurs only after authorization by the authoritative controller.

The intended users of the system are researchers, students, and developers who deploy the system using the implementation artifacts provided in the associated project repository. 

This specification defines the system-level behavioral requirements governing authorization, execution control, communication integrity, and evidence generation. Detailed implementation procedures and protocol definitions are specified in downstream design documentation.

---

## 3.0 DEFINITIONS AND ACRONYMS

| Term | Definition |
|:---|:---|
| Node | Independent computing element within the system. |
| Authoritative Node | Node responsible for system state control. |
| Execution Node | Node responsible for operational task execution. |
| Observation Node | Node responsible for telemetry and evidence collection. |

---

## 4.0 APPLICABLE DOCUMENTS

The following documents form a part of this specification to the extent specified herein:

- `00_overview.md`
- `04_comm_protocol.md`
- `05_security_threat_model.md`

---

## 5.0 SYSTEM CONTEXT

This system is designed to perform reconnaissance on external networks with owner permission. Once the subnet of the network is obtained, the execution controller performs reconnaissance with authoritative node authorization and logs the results.

### 5.1 External Systems

| Entity | Description |
| :---- | :---- |
| Operator | Human controlling the system |
| Target Network | External environment where actions occur |
| Observation Infrastructure | Evidence collection infrastructure |

### 5.2 System Boundary

Inside the system are the authoritative controller, execution controller, the observation node, and the logic responsible for requesting, authorizing, executing, and logging operations.

Outside the system are the external target network, the human operator, and any potential adversaries.

---

## 6.0 OPERATIONAL CONCEPT

Upon system initialization, the authoritative controller enters the SAFE state.

The execution controller may submit a request to perform an authorized operation.

The authoritative controller evaluates the request against system policy and either authorizes or denies execution.

If authorized, the execution controller performs authorized reconnaissance operations against the designated external target network.

Execution artifacts and operational results are recorded in the system evidence log.

The system returns to an idle SAFE state following the completion of the operation.

---

## 7.0 SYSTEM OBJECTIVES

| Objective ID | Description |
|:--- | :--- |
| SYS-OBJ-001 | Ensure the system initializes into a safe and controlled operational state. |
| SYS-OBJ-002 | Maintain centralized authority over global system state. |
| SYS-OBJ-003 | Ensure that operational actions occur only after explicit authorization. |
| SYS-OBJ-004 | Maintain integrity and validity of inter-node communication. |
| SYS-OBJ-005 | Preserve verifiable evidence of operational activity. |
| SYS-OBJ-006 | Ensure the system remains operational despite loss or failure of non-authoritative nodes. |

---

## 8.0 SYSTEM REQUIREMENTS

### 8.1 Requirement Identification Scheme

Requirement IDs shall follow the format:

SYS-\<TYPE\>-###

Where:

- SYS identifies a system-level requirement
- \<TYPE\> identifies the requirement class
- \### is a zero-padded sequential identifier

Type definitions are as follows:

- FR   : Functional Requirement
- COM  : Communication Requirement
- SEC  : Security Requirement
- LOG  : Evidence and Logging Requirement
- REL  : Reliability Requirement
- PERF : Performance Requirement

### 8.2 Functional Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-FR-001 | The system shall initialize into a known SAFE state on boot. | Test |
| SYS-FR-002 | The authoritative controller shall maintain a single global system state. | Inspection |
| SYS-FR-003 | Only the authoritative controller shall modify the system state. | Test |
| SYS-FR-004 | The execution controller shall execute only commands authorized by the authoritative controller. | Test |
| SYS-FR-005 | The system shall verify message integrity using CRC before processing frames. | Test |

### 8.3 Communication Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-COM-001 | The system shall frame all inter-node communication using the defined transport protocol. | Inspection |
| SYS-COM-002 | The decoder shall reject frames failing CRC verification. | Test |
| SYS-COM-003 | The system shall process frames only after detecting a valid frame start byte. | Test |

### 8.4 Security Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-SEC-001 | Only the authoritative controller shall authorize execution commands. | Test |
| SYS-SEC-002 | The system shall prevent non-authoritative nodes from modifying system state. | Test |
| SYS-SEC-003 | The system shall log all command authorization events. | Inspection |

### 8.5 Evidence and Logging Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-LOG-001 | The system shall generate an append-only execution log. | Inspection |
| SYS-LOG-002 | The system shall record all command execution attempts. | Test |
| SYS-LOG-003 | The system shall record execution timestamps for each operation. | Test |

### 8.6 Reliability Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-REL-001 | The system shall detect corrupted communication frames using CRC. | Test |
| SYS-REL-002 | The system shall continue operation if a non-authoritative node disconnects. | Test |

### 8.7 Performance Requirements

| Requirement ID | Description | Verification |
|:--- | :--- | :--- |
| SYS-PERF-001 | The system shall process incoming frames within 10 milliseconds. | Test |
| SYS-PERF-002 | The system shall process authorization requests within 200 milliseconds. | Test |

---

## 9.0 INTERFACE REQUIREMENTS

The following interfaces define logical communication relationships between system nodes.

### 9.1 Node Interfaces

| Interface | Description |
|:--- | :--- |
| Authority-Execution Interface | Command authorization and execution control |
| Execution-Observation Interface | Telemetry reporting and storage |
| Authority-Observation Interface | System state monitoring |

---

## 10.0 SYSTEM CONSTRAINTS

This section explicitly defines the constraints imposed on the system by design.

### 10.1 Hardware Platform Limitations

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-001 | The authoritative controller shall operate on an embedded microcontroller platform. | 

### 10.2 Operating System Dependencies

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-002 | The execution node shall operate on Linux-based systems. |

### 10.3 Transport Protocol Restrictions

| Constraint ID | Description |
| :--- | :--- |
| SYS-CON-003 | The transport protocol defined shall operate as a wrapper for the existing method of byte transport supplied by the operating system. |

---

## 11.0 VERIFICATION METHODS

This section defines how requirements are validated.

| Method | Description |
| :--- | :--- |
| Test | Verification through controlled execution of the system. |
| Inspection | Verification through examination of source code or documentation. |
| Analysis | Verification through logical reasoning or modeling. |
| Demonstration | Verification through operational demonstration of capability. |

---

## 12.0 REQUIREMENTS TRACEABILITY

Traceability between:

- System Objectives
- System Requirements
- Verification Tests

| Requirement | Objective | Verification |
|:--- | :--- | :--- |
| SYS-FR-001 | SYS-OBJ-001 | Test |
| SYS-FR-002 | SYS-OBJ-002 | Inspection |
| SYS-FR-003 | SYS-OBJ-002 | Test |
| SYS-FR-004 | SYS-OBJ-003 | Test |
| SYS-FR-005 | SYS-OBJ-004 | Test |
| SYS-COM-001 | SYS-OBJ-004 | Inspection |
| SYS-COM-002 | SYS-OBJ-004 | Test |
| SYS-COM-003 | SYS-OBJ-004 | Test |
| SYS-SEC-001 | SYS-OBJ-003 | Test |
| SYS-SEC-002 | SYS-OBJ-002 | Test |
| SYS-SEC-003 | SYS-OBJ-005 | Inspection |
| SYS-LOG-001 | SYS-OBJ-005 | Inspection |
| SYS-LOG-002 | SYS-OBJ-005 | Test |
| SYS-LOG-003 | SYS-OBJ-005 | Test |
| SYS-REL-001 | SYS-OBJ-004 | Test |
| SYS-REL-002 | SYS-OBJ-006 | Test |
| SYS-PERF-001 | SYS-OBJ-004 | Test |
| SYS-PERF-002 | SYS-OBJ-003 | Test |

--- 

## 13.0 DEFERRED REQUIREMENTS

This section defines requirements that are not implemented in the current design.

| Requirement ID | Description |
| :--- | :--- |
| SYS-SEC-010 | The system shall implement cryptographic authentication between nodes. |

---

END OF DOCUMENT
