# COMMUNICATION PROTOCOL SPECIFICATION
**Distributed Embedded System Architecture**

---
## 1.0 SCOPE
This document establishes the communication protocol specification for the ECLIPSE project utilizing heterogeneous microcontroller (MCU) and microprocessor (MPU) architectures. The protocol defines logical framing, message semantics, timing constraints, and validation rules for inter-processor communication within the ECLIPSE project.

### 1.1 Purpose
The purpose of this specification is to provide a standardized communication framework that ensures deterministic, reliable data exchange between processing nodes while maintaining real-time performance constraints and fault tolerant requirements.

### 1.2 Applicable documents
The following documents form a part of this specification to the extent specified herein:

- ISO/IEC 9899 - C language standard
- ISO/IEC 14882 - C++ language standard
- RFC 1662 - PPP in HDLC-like Framing (analogous implementation)
- CCITT CRC-16 Specification (X.25 / CCITT-FALSE)
- Project internal documents
	- 02_architecture.md
	- 04_security_threat_model.md
	- 05_test_plan.md

This specification assumes the system architecture defined in `02_comm_protocol.md`.

---

## 2.0 PROTOCOL LAYER SPECIFICATION

### 2.1 Message Frame Structure

The protocol is transport-agnostic and may be conveyed over any reliable byte stream interface capable of preserving message order. All inter-processor messages conform to the following standardized frame format:

```text
+----------+----------+----------+----------+----------+
| Start    | Type     | Length   | Payload  | CRC      |
| (1 byte) | (1 byte) | (1 byte) | (N bytes)| (2 bytes)|
+----------+----------+----------+----------+----------+
```

**Start Byte (0xAA):** Frame syncronization marker for byte alignment detection

**Message Types:**
- MSG_ARM (0x01): Request from attack layer for authorization to run prepared attacks
- MSG_DISARM (0x02): Confirmation of completion of generated attack requesting authorization layer to return to SAFE state
- MSG_STATUS_REQUEST (0x03): Request from attack layer for the status of the authorization layer
- MSG_STATUS_RESPONSE (0x04): Acknowledgement from authorization layer containing current system state
- MSG_HEARTBEAT (0x05): Status message automatically sent after a period of inactivity to confirm interdevice connection is still active and responsive

**Length:** Specifies length in bytes of payload field

**Payload:** Message to be delivered, interpreted based on MSG_TYPE

**CRC (Cyclic Redundancy Check):** 16-bit CRC-16/CCITT-FALSE calculated over Start, Type, Length and Payload fields for transmission error detection

### 2.2 Message Type Definitions

**MSG_ARM (0x01):**
- Emitter: Pi 5 only
- Receiver: Arduino only
- Preconditions: System state == SAFE
- Effect: Transitions system to ARMING state
- Failure behavior: Ignored if state != SAFE

**MSG_DISARM (0x02):**
- Emitter: Pi 5 only
- Receiver: Arduino only
- Preconditions: System state == ARMED
- Effect: Transitions system to SAFE state
- Failure behavior: Ignored if state == SAFE

**MSG_STATUS_REQUEST (0x03):**
- Emitter: Pi 5 only
- Receiver: Arduino only
- Preconditions: None
- Effect: Triggers response from Arduino containing current system state
- Failure behavior: None

**MSG_STATUS_RESPONSE (0x04):**
- Emitter: Arduino only
- Receiver: Pi 5 only
- Preconditions: None
- Effect: None
- Failure behavior: None

**MSG_HEARTBEAT (0x05):**
- Emitter: Pi 5, Pi 0, or Arduino
- Receiver: Pi 5, Pi 0, or Arduino
- Preconditions: None
- Effect: Resets inactivity countdown timer, re-establishing live connection
- Failure behavior: None

---

## 3.0 ERROR DETECTION AND CORRECTION

### 3.1 CRC implementation
All messages include 16-bit CRC-16/CCITT-FALSE (polynomial 0x1021) calculated over Start, Type, Length and Payload fields. Receiving nodes shall:

1. Recalculate CRC upon frame reception
2. Compare calculated CRC against received CRC field
3. Discard frame and increment error counter if mismatch detected
4. Request retransmission for command messages if CRC fails.

### 3.2 Discard semantics

- Frames failing CRC validation are discarded immediately.
- No state mutation may occur prior to CRC validation.
- CRC failure does not generate protocol-visible errors.
- Error counters are local and diagnostic only.

---

## 4.0 TIMING AND PERFORMANCE REQUIREMENTS

### 4.1 Qualitative Constraints

- Commands shall not block frame parsing.
- Frame processing shall complete within one main loop iteration.
- Retry behavior is bounded and deterministic.
- No command may cause unbounded delay of subsequent frames.

---

## 5.0 SECURITY CONSIDERATIONS

This protocol currently provides no cryptographic authentication or confidentiality guarantees. Security mechanisms, including message authentication and asymmetric key exchange, will be defined in `04_security_threat_model.md` and integrated in a future revision.

---

## 6.0 REVISION HISTORY

|Version |Date |Description|
 -------- ----- -----------
|0.1 |2026-01-15 |Initial Draft |

---

## 12.0 ACRONYMS AND DEFINITIONS

- CRC: Cyclic Redundancy Check
- FSM: Finite State Machine
- MCU: Microcontroller unit
- MPU: Microprocessor unit

---

END OF DOCUMENT
