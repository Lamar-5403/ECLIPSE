# COMMUNICATION PROTOCOL SPECIFICATION
**Framed Communication Protocol for Distributed Control Systems**

---
## 1.0 SCOPE
This document establishes the communication protocol specification for the ECLIPSE project utilizing heterogeneous microcontroller (MCU) and microprocessor (MPU) architectures. The protocol defines logical framing, message semantics, timing constraints, and validation rules for inter-processor communication within the ECLIPSE project.

### 1.1 Purpose
The purpose of this specification is to provide a standardized communication framework that ensures deterministic, reliable data exchange between processing nodes while maintaining real-time performance constraints and deterministic fault containment.

### 1.2 Applicable documents
The following documents form a part of this specification to the extent specified herein:

- ISO/IEC 9899 - C language standard
- ISO/IEC 14882 - C++ language standard
- RFC 1662 - PPP in HDLC-like Framing (analogous implementation)
- CCITT CRC-16 Specification (X.25 / CCITT-FALSE)
- Project internal documents:
    - 02_architecture.md
    - 04_security_threat_model.md
    - 05_test_plan.md

This specification assumes the system architecture defined in `02_architecture.md`. Language standards are referenced to constrain implementation behavior only and do not define protocol semantics.

---

## 2.0 PROTOCOL LAYER SPECIFICATION

### 2.1 Message Frame Structure

The protocol is transport-agnostic and may be conveyed over any reliable byte stream interface capable of preserving message order. All interprocessor messages conform to the following standardized frame format:

```text
+----------+----------+----------+----------+----------+
| Start    | Type     | Length   | Payload  | CRC      |
| (1 byte) | (1 byte) | (1 byte) | (N bytes)| (2 bytes)|
+----------+----------+----------+----------+----------+
```

**Start Byte (0xAA):** Frame synchronization marker for byte alignment detection

**Message Type Field (Summary):**
- MSG_ARM (0x01): Authorization request message
- MSG_DISARM (0x02): Authorization revocation message
- MSG_STATUS_REQUEST (0x03): System state query message
- MSG_STATUS_RESPONSE (0x04): System state response message
- MSG_HEARTBEAT (0x05): Liveness indication message

Detailed semantics, authority constraints, and state effects defined in Section 2.2.

**Length:** Specifies length in bytes of payload field

**Payload:** Message to be delivered, interpreted based on MSG_TYPE

**CRC (Cyclic Redundancy Check):** 16-bit CRC-16/CCITT-FALSE calculated over Start, Type, Length and Payload fields for transmission error detection, transmitted MSB first

### 2.2 Message Type Definitions (Normative)

The Arduino node is the sole authority for system state transitions. Command messages are advisory and may be rejected without response if preconditions are not met. No external node may directly force a state transition.

**MSG_ARM (0x01):**
- Emitter: Pi 5 only
- Receiver: Arduino only
- Preconditions: System state == SAFE
- Effect: Transitions system to ARMING state
- Failure behavior: Message shall be discarded if system state ≠ SAFE

**MSG_DISARM (0x02):**
- Emitter: Pi 5 only
- Receiver: Arduino only
- Preconditions: System state == ARMED
- Effect: Transitions system to SAFE state
- Failure behavior: Message shall be discarded if system state == SAFE

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
- Failure behavior: Responses shall be emitted only in direct response to a valid MSG_STATUS_REQUEST

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

### 3.2 Discard semantics

- No state mutation may occur prior to CRC validation.
- Frames failing CRC validation are discarded immediately.
- CRC failure does not generate protocol-visible errors.
- Error counters are local and diagnostic only.

---

## 4.0 TIMING AND PERFORMANCE REQUIREMENTS

### 4.1 Deterministic Processing Constraints

- Commands shall not block frame parsing.
- Frame processing shall complete within a bounded, non-blocking execution window appropriate to the execution environment (typically one main loop iteration).
- No command may cause unbounded delay of subsequent frames.

---

## 5.0 SECURITY CONSIDERATIONS

This protocol currently provides no cryptographic authentication or confidentiality guarantees. Security mechanisms, including message authentication and asymmetric key exchange, will be defined in `04_security_threat_model.md` and integrated in a future revision. This revision does not attempt to mitigate spoofing, replay, or eavesdropping threats. Message authenticity and origin validation are explicitly out of scope for this revision.

---

## 6.0 REVISION HISTORY

|Version |Date       |Description   |
|--------|-----------|--------------|
|0.1     |2026-01-16 |Initial Draft |

---

## 7.0 ACRONYMS AND DEFINITIONS

- CCITT: Consultative Committee for International Telephony and Telegraphy
- CRC: Cyclic Redundancy Check
- FSM: Finite State Machine
- MCU: Microcontroller unit
- MPU: Microprocessor unit
- MSB: Most Significant Bit

---

END OF DOCUMENT
