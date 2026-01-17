# SYSTEM ARCHITECTURE

Document Version: 0.1
Status: Draft

---

## 1.0 ARCHITECTURAL OBJECTIVE

This architecture defines the structural composition of the system, the allocation of authority across nodes, and the permitted interaction paths between components.

The objective is to enforce centralized decision authority while allowing distributed execution, observation, and evidence collection across heterogeneous compute platforms.

This document constrains implementation choices without prescribing specific hardware, operating systems, or transport mechanisms beyond those already assumed in the system overview. This document defines architectural invariants that all implementations must preserve.

---

## 2.0 HIGH-LEVEL SYSTEM DECOMPOSITION

The system is composed of discrete nodes, each assigned a single primary responsibility class:

- **Authoritative Control**
- **Execution**
- **Observation**

Each node operates independently, communicates exclusively through framed messages, and enforces local safety constraints regardless of peer behavior.

No node may occupy more than one responsibility class for critical actions. Responsibility classes are mutually exclusive by architectural mandate and cannot be combined, overridden, or bypassed through configuration, deployment topology, or operational mode.

---

## 3.0 NODE CLASSES

### 3.1 Authoritative Controller

The authoritative controller is the sole entity permitted to mutate the global system state.

Responsibilities:

- Maintain the global finite state machine
- Validate and authorize state transitions
- Accept or reject requests from non-authoritative nodes
- Emit authoritative control messages

Constraints:

- Must boot into known SAFE state
- Must never delegate state authority
- Must preserve valid global state and authority semantics under partial system failure

There exists exactly one authoritative controller at any time.

### 3.2 Execution Nodes

Execution nodes perform actions only when explicitly authorized.

Responsibilities:

- Execute commands issued by the authoritative controller
- Enforce local safety and refusal policies
- Report execution status and outcomes

Constraints:

- May not initiate state transitions
- May refuse commands silently
- Must tolerate loss of control connectivity by entering a safe local condition
- Must not execute commands unless explicitly authorized by the authoritative controller

Execution capability does not imply trust.

### 3.3 Observation / Evidence Nodes

Observation nodes collect telemetry, logs, and artifacts.

Responsibilities:

- Passively observe system behavior
- Collect append-only evidence
- Report observations without influencing control flow

Constraints:

- Must never issue control commands
- Must never block or delay system execution
- Loss of observation must not alter system behavior

---

## 4.0 AUTHORITY AND TRUST BOUNDARIES

Authority is explicit, singular, and non-transferable. Authority is derived solely from architectural role, not message content.

- Only the authoritative controller may mutate global system state
- No trust is implied by message origin alone
- Each node independently validates inputs before acting
- Architectural trust does not imply cryptographic trust

Compromise of any non-authoritative node must not grant control authority.

---

## 5.0 INTER-NODE COMMUNICATION MODEL

All communication occurs via framed messages over an ordered byte stream. Ordering guarantees are assumed per `00_overview.md`.

Architectural constraints:

- No shared memory
- No shared clocks
- No implicit synchronization
- No side channels relied upon for correctness

Each node treats every incoming frame as potentially malformed, delayed, duplicated, or adversarial.

---

## 6.0 FAILURE ISOLATION MODEL

Failures are assumed to be partial, asymmetric, and silent.

Design assumptions:

- Nodes may reset or disappear without warning
- Non-authoritative node failure must not corrupt global state
- The authoritative controller must fail by transitioning to or remaining in the SAFE state
- Recovery is explicit, not automatic

Failing closed is preferred to degraded continuation or partial authority leakage.

---

## 7.0 DEPLOYMENT TOPOLOGY (LOGICAL)

The architecture assumes logical separation, not physical adjacency.

- Nodes may be co-located or physically distributed
- Transport selection does not alter authority semantics
- Latency affects responsiveness, not correctness

Topology must not introduce implicit authority escalation.

---

## 8.0 ARCHITECTURAL NON-GOALS

This architecture does not attempt to provide:

- Byzantine fault tolerance
- Distributed consensus
- Autonomous recovery
- Implicit redundancy
- Cryptographic identity enforcement (current revision)

These are consciously excluded to preserve determinism and auditability.

---

## 9.0 RELATIONSHIP TO OTHER DOCUMENTS

This architecture is constrained by:

- `00_overview.md` (assumptions and intent)

This architecture constrains:

- `03_comm_protocol.md`
- `04_security_threat_model.md`
- `05_test_plan.md`

Protocol details, message semantics, and security mechanisms must not violate the authority and trust boundaries defined here. Downstream documents may refine behavior but must not redefine authority, trust, or failure semantics established here.

---

END OF DOCUMENT
