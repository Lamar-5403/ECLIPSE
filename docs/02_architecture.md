# SYSTEM ARCHITECTURE

Document Version: 0.2
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

Each node MUST:
- Operate independently
- Communicates exclusively through framed messages
- Enforce local safety constraints regardless of peer behavior

No node may occupy more than one responsibility class for critical actions. Responsibility classes must be mutually exclusive by architectural mandate and must not be combined, overridden, or bypassed through configuration, deployment topology, or operational mode.

---

## 3.0 NODE CLASSES

### 3.1 Authoritative Controller

The authoritative controller is the sole entity permitted to mutate authoritative system state machines.

Responsibilities:

- Maintain the global finite state machine
- Validate and authorize state transitions
- Accept or reject requests from non-authoritative nodes
- Emit authoritative control messages

Constraints:

- Must boot with `CAS = SAFE`
- Must never delegate state authority
- Must preserve valid global state and authority semantics under partial system failure

There must exist exactly one authoritative controller at any time. Split-brain authority is architecturally forbidden. In the presence of multiple apparent controllers, all nodes MUST default to non-operational SAFE behavior.

### 3.1.1 Authoritative State Machines

The authoritative controller maintains exactly two independent finite state machines:

- **Control Authority State (CAS)** - governs execution authorization
- **System Lifecycle State (SLS)** - governs system phase and readiness

CAS and SLS are orthogonal, authoritative, and singular. No other state machines are permitted to confer execution authority or lifecycle progression.

The semantics, transitions, and coupling constraints of CAS and SLS are normatively defined in `03_lifecycle_and_state.md`.

### 3.2 Execution Nodes

Execution nodes must perform actions only when explicitly authorized.

Responsibilities:

- Execute commands issued by the authoritative controller
- Enforce local safety and refusal policies
- Report execution status and outcomes

Constraints:

- May not initiate state transitions
- May refuse commands silently
- Must tolerate loss of control connectivity by entering a safe local condition
- Must not execute commands unless explicitly authorized by the authoritative controller

Execution capability must not imply trust.

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

Authority must be explicit, singular, and non-transferable. Authority must be derived solely from architectural role, not message content.

- Only the authoritative controller may mutate global system state
- No trust is implied by message origin alone
- Each node independently validates inputs before acting
- Architectural trust must not imply cryptographic trust

Compromise of any non-authoritative node must not grant control authority.

### 4.1 Prohibited Authority Escalation Paths

The following must not occur.

- No message, sequence of messages, or message timing pattern may confer authority
- Authority must not be requested, delegated, voted, or inferred
- Authority must not be regained through reboot, reconnection, or timeout
- Authority must not be transferred during runtime under any condition

### 4.2 Trust Posture

- All nodes must operate under a zero-trust assumption
- Correct behavior of peers must never be assumed
- Malformed, delayed, replayed, or adversarial inputs must be architecturally expected
- Trust decisions must remain local and conservative
- Operational correctness of a peer must not modify architectural trust posture

### 4.3 Authority Origination

- Authority exists only by architectural designation at system instantiation
- Authority cannot be created, discovered, or inferred at runtime
- Any ambiguity in authority identity results in denial of all state mutation

---

## 5.0 INTER-NODE COMMUNICATION MODEL

All communication occurs via framed messages over an ordered byte stream. Ordering guarantees must be provided as specified in `00_overview.md`.

Architectural constraints:

- No shared memory
- No shared clocks
- No implicit synchronization
- No side channels relied upon for correctness

Each node treats every incoming frame as potentially malformed, delayed, duplicated, or adversarial. Successful message delivery, ordering, or validation must not imply authorization or legitimacy.

---

## 6.0 FAILURE ISOLATION MODEL

Failures must be treated as partial, asymmetric, and silent.

Design assumptions:

- Nodes may reset or disappear without warning
- Non-authoritative node failure must not corrupt global state
- The authoritative controller must fail by transitioning to or remaining CAS = SAFE
- Recovery is explicit, not automatic

Failing closed must take precedence over degraded continuation or partial authority leakage.

### 6.1 Failure Classes

Failure categories:

- **Communication failure**
 - Loss of frame bytes
 - Corruption of frame bytes
 - Duplication of frame bytes

- **Node failure**
 - Node reset
 - Node hang
 - Node crash

- **Protocol failure**
 - Malformed or invalid frame transmission
 - Protocol interaction attempted while the system is in an invalid state

- **Behavioral failure**
 - Out of sequence actions
 - Unauthorized actions

Each category must be handled independently. No failure class may escalate authority. All failure classes must converge to SAFE state at the authoritative controller. Unauthorized actions must be denied and recorded as evidence events.

### 6.2 Recovery Authority

- Only the authoritative controller may initiate recovery
- Non-authoritative nodes may signal fault but must never self-recover into an operational role
- Recovery must be treated as a state transition, not a transport event
- Restoration of connectivity must not trigger recovery

### 6.3 Irrecoverable Failure

- Certain failure states permanently prohibit return to operational modes without full system reinitialization
- The architecture does not guarantee recovery from arbitrary state corruption

---

## 7.0 DEPLOYMENT TOPOLOGY (LOGICAL)

The architecture requires logical separation, not physical adjacency.

- Nodes may be co-located or physically distributed
- Transport selection must not alter authority semantics
- Latency affects responsiveness, not correctness

Topology must not introduce implicit authority escalation.

---

## 8.0 ARCHITECTURAL INVARIANTS

Invariant truths that must always hold:

- Authority is singular and static
- Safety dominates liveness
- Absence of authorization results in denial
- Failure never increases capability
- Observation is never control
- Authority is never implicit
- CAS and SLS are independent and must not implicityly transition one another

---

## 9.0 ARCHITECTURAL NON-GOALS

This architecture does not attempt to provide:

- Byzantine fault tolerance
- Distributed consensus
- Autonomous recovery
- Implicit redundancy
- Cryptographic identity enforcement (current revision)
- High availability via controller replication

These are consciously excluded to preserve determinism and auditability.

---

## 10.0 RELATIONSHIP TO OTHER DOCUMENTS

This architecture is constrained by:

- `00_overview.md` (assumptions and intent)

This architecture constrains:

- `03_lifecycle_and_system.md`
- `04_comm_protocol.md`
- `05_security_threat_model.md`
- `06_test_plan.md`

Protocol details, message semantics, and security mechanisms must not violate the authority and trust boundaries defined here. Downstream documents may refine behavior but must not redefine authority, trust, or failure semantics established here. This document declares the existence and authority scope of CAS and SLS. All state semantics, transitions, and invariants are defined exclusively in `03_lifecycle_and_state.md`.

---

END OF DOCUMENT
