# SYSTEM OVERVIEW

Document Version: 1.0.0  
Status: Released

---

## 1.0 SYSTEM INTENT

This system is designed to coordinate multiple processing nodes under a centralized authority model. Its primary purpose is to enforce controlled execution of cybersecurity attacks, deterministic system state transitions, and verifiable outcomes across heterogeneous compute elements.

The architecture intentionally separates authority, execution capability, and observation into distinct nodes. Each node performs a specialized function and processes different classes of information, preventing any single node from simultaneously possessing full control authority and unrestricted execution capability.

This system explicitly prioritizes correctness, containment, and observability over throughput, automation, or autonomy. This document defines the conceptual assumptions under which all other documentation operates.

### 1.1 Operating Context

The system operates in a constrained, supervised environment. It is not intended for unsupervised deployment, autonomous decision-making, or safety-critical control without external validation.

All actions performed by the system are constrained to be intentional, test-driven, and subject to human operator review.

---

## 2.0 OPERATING ASSUMPTIONS

The system operates under the following assumptions:

1. The transport delivers bytes in the order transmitted.
2. Byte loss, duplication, or corruption is possible. Therefore, no guarantees are assumed regarding latency or delivery deadlines.
3. Transport framing is implemented by a custom protocol layered above the operating system's byte transport mechanism.
4. The decoder performs minimal validation and assumes all bytes received after a valid frame start byte belong to that frame until the frame is complete.
5. Frame integrity is verified using CRC verification. Any transport faults are expected to manifest as CRC mismatches as opposed to being prevented at the transport layer.
6. The authoritative node boots into a known SAFE state.
7. Non-authoritative nodes may reboot, reset, or disappear without notice.
8. Node behavior is independent. Nodes do not share memory or clocks, enforce their own local safety constraints independent of peer behavior, and are permitted to refuse commands without explanation.
9. All command execution is intentional and operator-initiated.
10. Internal nodes are not assumed to be mutually trustworthy.
11. Compromise of a non-authoritative node does not imply compromise of the authoritative node.
12. Evidence integrity is not cryptographically enforced in the current design.
13. A human operator is present during system use in a controlled test or research environment. 
14. Insider threats are out of scope for this implementation and physical access to hardware implies total system compromise with no mitigation in place.

---

## 3.0 CORE DESIGN PRINCIPLES

The system adheres to the following non-negotiable principles:

- Authority is centralized and explicit.
- Execution capability does not imply decision authority.
- State transitions are deterministic and externally observable.
- Failure modes favor containment over continuation.
- Evidence generation is prioritized over system availability.
- Memory footprint and execution overhead are minimized to support operation in constrained computing environments.

These principles inform all architectural and protocol-level decisions.

---

## 4.0 NODE ROLES AND TRUST MODEL

The system is composed of multiple nodes with intentionally asymmetric responsibilities.

Three primary roles are defined within the architecture:

**Authoritative Controller**

The authoritative controller is the sole arbiter of global system state. It grants permission for actions, authorizes requests, and enforces system safety constraints. No other node is permitted to mutate system state.

**Execution Controller**

The execution controller performs operational tasks authorized by the authoritative controller. This node is responsible for executing cybersecurity operations, interacting with external targets, and producing execution artifacts.

Although subordinate in terms of decision authority, the execution controller is architecturally significant and performs the majority of operational workload within the system.

**Observation Node**

The observation node passively collects telemetry and evidence from system operations. It does not authorize or execute actions and exists solely to provide independent observability of system behavior. This node is under active development and is not implemented in the current revision.

Trust is not transitive. Each node is evaluated independently, and compromise or loss of any non-authoritative node must not compromise the integrity of the authoritative controller.

---

## 5.0 SYSTEM STATE MODEL

The system maintains a singular global state that governs permissible actions.

Per assumption [6], the system is assumed to boot into a known SAFE state.

State transitions are: 

- Explicit
- Finite
- Enforced by the authoritative node

Non-authoritative nodes may request actions or query state, but they explicitly do not possess the ability to force transitions.

In the current implementation, the global state machine is enforced entirely within the authoritative controller process.

The internal mechanics of the state machine are defined in downstream specifications.

---

## 6.0 CONTROL AND DATA FLOW

Control flow and data flow are intentionally separated.

Control decisions originate from the authoritative node.

Authorized actions are executed by the designated execution controller. This controller interacts with external targets and generates operational artifacts.

The observation node independently monitors system activity and generates evidence records. Observation capability is intentionally isolated from both authorization and execution in order to preserve evidentiary independence.

Control messages are authoritative, while observational messages are informational and non-authoritative.

No node is permitted to both authorize and execute critical actions.

---

## 7.0 EVIDENCE AND INTEGRITY PHILOSOPHY

The system treats evidence as a first-class artifact.

Evidence collection is passive, append-only, and non-authoritative. The loss of evidence capability degrades observability but must not alter system behavior.

Evidence artifacts in the current revision primarily consist of append-only execution logs generated by system components.

Integrity guarantees are enforced structurally rather than cryptographically in the current design. Cryptographic enforcement is planned for inclusion in future revisions.

---

## 8.0 SYSTEM BOUNDARIES

**Physical:** The system assumes physical custody or controlled access to all nodes. Physical tampering, including hardware fault injection, is outside system responsibility.

**Transport:** The system implements a custom framed communication protocol layered on top of the operating system's byte transport mechanisms. Ordering guarantees are assumed from the underlying transport. Framing, validation, and CRC verification occur within the system's custom transport layer.

**Operator:** Human intent, correctness of test selection, and authorization to run attacks are external. The system does not validate operator legitimacy or intent.

**Target:** The system makes no claims about correctness, safety, or legality of actions performed against external targets. Targets are treated as opaque entities.

**Failure:** Simultaneous multi-node Byzantine behavior is outside scope. The design assumes at most one non-authoritative node fails at a time.

**Security:** Identity, authentication, and non-repudiation are explicitly excluded in the current revision. Any trust inferred between nodes is architectural, not cryptographic.

**Electrical:** Power integrity, voltage stability, and clock accuracy are assumed acceptable. Brownouts, clock drift, and signal degradation are not mitigated at the protocol or system level.

---

## 9.0 EXPLICIT NON-GOALS

This system does not attempt to provide:

- Cryptographic trust guarantees in the current design
- Autonomous decision-making
- Real-world safety assurances
- Network-level adversarial resilience
- Distributed consensus mechanisms

These exclusions are intentional and documented to prevent misinterpretation of system scope.

---

## 10.0 DOCUMENT RELATIONSHIPS

This overview establishes the conceptual foundation for all other system documentation.

Detailed protocol behavior, security analysis, node specifications, and testing methodology are defined in dedicated documents and are normatively subordinate to the assumptions stated here.

---

## 11.0 IMPLEMENTATION STATUS

Version 1.0.0 of the system implements the following components:

- Authoritative control node
- Execution controller capable of performing network reconnaissance and attack orchestration
- Custom framed communication protocol with CRC validation
- Evidence logging infrastructure

The following architectural components are defined but not fully implemented in Version 1.0.0:

- Independent observation node
- Cryptographic integrity verification
- Authenticated control channels
- Expanded attack capability modules
- Distributed telemetry aggregation

These capabilities are planned for future revisions of the system architecture.

---

END OF DOCUMENT
