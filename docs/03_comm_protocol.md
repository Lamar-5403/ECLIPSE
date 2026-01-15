# COMMUNICATION PROTOCOL SPECIFICATION
**Distributed Embedded System Architecture**

---
## 1.0 SCOPE
This document establishes the communication protocol specification for the ECLIPSE project utilizing heterogenous microcontroller (MCU) and microprocessor (MPU) architectures. The protocol defines message structure, timing requirements, error handling, and interface specifications for inter-processor communication within mission-critical applications.

### 1.1 Purpose
The purpose of this specification is to provide a standardized communication framework that ensures deterministic, reliable data exchange between processing nodes while maintaining real-time performance constraints and fault tolerant requirements.

### 1.2 Applicable documents
The following documents form a part of this specification to the extent specified herein:

- MIL-STD-XXXX
- ISO XXXX
- IEC XXXX
- RTCA XXXX
- IEEE XXXX

---

## 2.0 SYSTEM ARCHITECTURE OVERVIEW

### 2.1 Network Topology
The embedded system employs a hierarchial multi-tier architecture consistingof: 

**Tier 1 - Transport Layer:**
High-performance microcontroller executing... with primary responsibilities including...

**Tier 2 - Frame Layer:**
where frames are encoded/decoded

**Tier 3 - Controller/Application Layer:**
Where frame payloads are interpreted based on message types.

### 2.2 Physical layer implementation
Communication between tiers utilizes multiple physical layer technologies selected based on bandwidth, latency, and reliability requirements:

- SPI (Serial Peripheral Interface): High speed data acquisition, up to 16 MHz clock
- I2C (inter-Integrated Circuit): Low speed peripheral configuration, 400 kHz fast mode
- Ethernet (100Base-TX): Tier 3 to external systems, 600 Mbps full-duplex
- UART (Universal Asynchronous Receiver-Transmitter): Debug and diagnostic interfaces, 115200 baud

---

## 3.0 PROTOCOL LAYER SPECIFICATION

### 3.1 Message Frame Structure

All inter-processor messages confrom to the following standardized frame format:

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
- MSG_ERROR (0x05): Error message generated from any layer in which an action was requested that could not be completed or a process terminated early without completing its intended objective
- MSG_HEARTBEAT (0x06): Status message automatically sent after a period of inactivity to confirm interdevice connection is still active and responsive

**Length:** Specifies length in bytes of payload field

**Payload:** Message to be delivered, interpreted based on MSG_TYPE

**CRC (Cyclic Redundancy Check:** 16-bit CRC-16/CCITT-FALSE calculated over Start, Type, Length and Payload fields for transmission error detection

---

## 4.0 TIMING AND PERFORMANCE REQUIREMENTS

### 4.1 Message Latency Specifications
Maximum end-to-end latency from message transmission to reception acknowledgement:

| Priority Level | Maximum Latency | Use Case |
| Critical | 1 ms | Safety-critical commands, emergency stops |
| High | 5 ms | Control loop updates, actuator commands |
| Medium | 20 ms | Telemetry streams, sensor data |
| Low | 100 ms | Diagnostics, configuration updates |

### 4.2 Throughput Requirements
Minimum sustained data rates per communication channel:

- SPI interfaces: 12.8 Mbps effective throughput (80% channel utilization)
- Ethernet link: 480 Mbps effective throughput (80% channel utilization)

### 4.3 Timeout and Retry Logic
**Command Timeout:** Commands not acknowledged within 3x the maximum latency threshold shall trigger a timeout condition.

**Retry Policy:**

- Critical priority: Retry up to 5 times with exponential backoff (1, 2, 4, 8, 16 ms)
- High Priority: Retry up to 3 times with 10 ms intervals
- Medium/Low Priority: Single retry after 50 ms

**Failure Handling:** After exhausting retry attempts, generate event message and excalate to control layer for fault recovery procedures.

---

## 5.0 ERROR DETECTION AND CORRECTION

### 5.1 CRC implementation
All messages include 16-bit CRC-16/CCITT-FALSE (polynomial 0x1021) calculated over Start, Type, Length and Payload fields. Receiving nodes shall:

1. Recalculate CRC upon frame reception
2. Compare calculated CRC against received CRC field
3. Discard frame and increment error counter if mismatch detected
4. Request retransmission for command messages if CRC fails.

### 5.2 Timeout Detection
Transmitting nodes implement watchdog timers for command acknowledgement. Timeout expiration triggers retry logic per section 4.3 and fault logging.

---

## 6.0 STATUS AND ERROR CODES

### 6.1 Success Codes

...


### 6.2 Error Codes

...

## 7.0 SECURITY CONSIDERATIONS

// HMAC-SHA256 auth code for cryptographically signed messages specified here. Asymmetrical encryption standards specified here.

---

## 8.0 INITIALIZATION AND CONFIGURATION

### Power-On Sequence
Upon power application, nodes execute the following initialization sequence:

1. hardware init
2. self test exec
3. network registration
4. config download
5. operational transition

### 8.2 Configuration Parameteres
...

### 8.3 Dynamic Reconfiguration
...

---

## 9.0 DIAGNOSTIC AND DEBUG INTERFACES

### 9.1 Statistics Collection
...

### 9.2 Trace Logging
...

### 9.3 Built-in Test (BIT)
...

---

## 10.0 COMPLIANCE AND VERIFICATION

### 10.1 Verification Methods
...

### 10.2 Acceptance Criteria
...

### 10.3 Documentation Requirements
...

---

## 11.0 REVISION HISTORY
...

---

## 12.0 ACRONYMS AND DEFINITIONS
...

---

END OF DOCUMENT
