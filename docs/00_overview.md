# SYSTEM OVERVIEW

Document Version: 0.1
Status: Draft

---

## 1.0 SYSTEM INTENT

This system is designed to coordinate multiple processing nodes under a centralized authority model. Its primary purpose is to enforce controlled execution of cybersecurity attacks, deterministic system state transitions, and verifiable outcomes across heterogeneous compute elements.

This system explicitly prioritizes correctness, containment, and observability over throughput or autonomy. This document defines the conceptual assumptions under which all other documentation operates.

### 1.1 Operating Context

The system operates in a constrained, supervised environment. It is not intended for unsupervised deployment, autonomous decision-making, or safety-critical control without external validation.

All actions performed by the system are constrained to be intentional, test-driven, and subject to review.

---

## 2.0 OPERATING ASSUMPTIONS

The system operates under the following assumptions:

1. The transport delivers bytes in the order transmitted.
2. Byte loss, duplication, or corruption is possible, therefore no guarantees are assumed regarding latency or delivery deadlines.
3. The authoritative node boots into a known SAFE state.
4. Non-authoritative nodes may reboot, reset, or disappear without notice.
5. Node behavior is independent. Nodes do not share memory or clocks, enforce their own local safety constraints independent of peer behavior, and are permitted to refuse commands without explanation.
6. All command execution is intentional and operator-initiated.
7. Internal nodes are not assumed to be mutually trustworthy.
8. Compromise of a non-authoritative node does not imply compromise of the authoritative node.
9. Evidence integrity is not cryptographically enforced in the current design.
10. A human operator is present during system use in a controlled test or research environment. Insider threats are out of scope for this implementation and physical access to hardware implies total system compromise with no mitigation in place.

---

## 3.0 CORE DESIGN PRINCIPLES

The system adheres to the following non-negotiable principles:

- Authority is centralized and explicit.
- Execution capability does not imply decision authority.
- State transitions are deterministic and externally observable.
- Failure modes favor containment over continuation.
- Evidence generation is prioritized over system availability.

These principles inform all architectural and protocol-level decisions.

---

## 4.0 NODE ROLES AND TRUST MODEL

The system is composed of multiple nodes with intentionally asymmetric responsibilities.

A single node serves as the authoritative controller and sole arbiter of system state. Other nodes operate in subordinate or observational roles and may not directly mutate global state.

Trust is not transitive. Each node is evaluated independently, and loss of any non-authoritative node must not compromise system integrity.

---

## 5.0 SYSTEM STATE MODEL

The system maintains a singular global state that governs permissible actions.

Per assumption [3], the system is assumed to boot into a known SAFE state.

State transitions are: 

- Explicit
- Finite
- Enforced by the authoritative node

Non-authoritative nodes may request actions or query state, but they explicitly do not possess the ability to force transitions.

The internal mechanics of the state machine are defined in downstream specifications.

---

## 6.0 CONTROL AND DATA FLOW

Control flow and data flow are intentionally separated.

Control decisions originate from the authoritative node.
Execution occurs on designated execution nodes.
Observation and evidence collection occur independently of control.
Control messages are authoritative, while observational messages are non-authoritative.

No node is permitted to both authorize and execute critical actions.

---

## 7.0 EVIDENCE AND INTEGRITY PHILOSOPHY

The system treats evidence as a first-class artifact.

Evidence collection is passive, append-only, and non-authoritative. The loss of evidence capability degrades observability but must not alter system behavior.

Integrity guarantees are enforced structurally rather than cryptographically in the current design. Cryptographic enforcement planned for addition in future revisions.

---

## 8.0 SYSTEM BOUNDARIES

**Physical:** The system assumes physical custody or controlled access to all nodes. Physical tampering, including hardware fault injection, are outside system responsibility.

**Transport:** The system boundary ends at ordered byte delivery. Framing, retries, and validation begin only after bytes are received. Higher layers assume correct ordering per assumption [1].

**Operator:** Human intent, correctness of test selection, and authorization to run attacks are external. The system does not validate operator legitimacy or intent.

**Target:** The system makes no claims about correctness, safety, or legality of actions performed against external targets. Targets are treated as opaque entities.

**Failure:** Simultaneous multi-node Byzantine behavior is outside scope. The design assumes at most one non-authoritative node fails at a time.

**Security:** Identity, authentication, and non-repudiation are explicitly excluded in the current revision. Any trust inferred between nodes is architectural, not cryptographic.

**Electrical:** Power integrity, voltage stability, and clock accuracy are assumed acceptable. Brownouts, clock drift, and signal degradation are not mitigated at the protocol or system level.

---

## 9.0 EXPLICIT NON-GOALS

This system does not attempt to provide:

- Cryptographic trust guarantees (in the current design)
- Autonomous decision-making
- Real-world safety assurances
- Network-level adversarial resilience

These exclusions are intentional and documented to prevent misinterpretation of system scope.

---

## 10.0 DOCUMENT RELATIONSHIPS

This overview establishes the conceptual foundation for all other system documentation.

Detailed protocol behavior, security analysis, and testing methodology are defined in dedicated documents and are normatively subordinate to the assumptions stated here.

---

END OF DOCUMENT
