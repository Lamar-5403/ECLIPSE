# BILL OF MATERIALS

Document Version: 1.0.0  
Status: Released

---

## 1.0 PURPOSE

This document defines the Bill of Materials (BOM) for the E.C.L.I.P.S.E. system. The BOM establishes the authoritative list of hardware components required to construct, deploy, and operate the system as specified in the architecture documentation.

This document ensures the traceability of physical components used within the system and provides a reference for procurement, replication, and lifecycle management.

---

## 2.0 SCOPE

This document applies to all hardware components required to construct the E.C.L.I.P.S.E. system in its baseline configuration.

The scope includes:

- Primary compute platforms
- Storage media
- Required interface cabling
- Starter kit components required for system operation

The scope excludes:

- Development workstations
- External monitors or keyboards
- Network infrastructure
- Laboratory equipment used for development or testing

Only components that are part of the deployed system configuration are included.

---

## 3.0 BOM STRUCTURE

The BOM is organized into the following sections:

**Top-Level Assembly**

The complete E.C.L.I.P.S.E. system configuration required for operation.

**Subassemblies**

Logical hardware groupings corresponding to system components defined in the architecture:

- Authority Controller
- Attack Simulation Node
- Evidence Protection Node

Each subassembly lists the hardware required for that subsystem.

**Procurement and Traceability**

Defines the minimum requirements for tracking component origin, part identity, and procurement information.

---

## 4.0 TOP-LEVEL ASSEMBLY TABLE

| Item | Assembly Name | Quantity | Description |
| :--- | :--- | :--- | :--- |
| 1 | Authority Controller Assembly | 1 | Arduino-based system authority controller |
| 2 | Attack Simulation Node Assembly | 1 | Raspberry Pi 5 attack execution platform |
| 3 | Evidence Protection Node Assembly | 1 | Raspberry Pi Zero WH evidence collection platform |

---

## 5.0 SUBASSEMBLIES

### 5.1 Authority Controller Assembly 

| Item | Component | Manufacturer | Model | Quantity | Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | Microcontroller Board | Arduino | UNO R4 WiFi | 1 | Official Arduino board with integrated WiFi as system authority controller |
| 2 | Starter Kit (Procurement Source) | GeeekPi | UNO R4 WiFi Starter Kit | 1 | Procurement bundle used to obtain board |
| 3 | Prototyping Components | GeeekPi | Breadboard / jumper wires / passive components | As needed | Provided by kit but not strictly required for system replication |

Approximate procurement source: Amazon.com  
Approximate procurement cost: **$53 USD (kit total)**  

### 5.2 Attack Simulation Node Assembly

| Item | Component | Manufacturer | Model | Quantity | Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | Single Board Computer | Raspberry Pi | Raspberry Pi 5 | 1 | Primary attack simulation platform |
| 2 | System Storage | Samsung | microSD Card (256GB) | 1 | System storage medium |
| 3 | Power Supply | CanaKit | Pi 5 Power Supply | 1 | Included in starter kit |
| 4 | Enclosure | CanaKit | Pi 5 Case w/ Cooling Fan | 1 | Included in starter kit |

Procurement source: CanaKit Raspberry Pi Starter Kit  
Approximate procurement cost: **$200 USD**  

### 5.3 Evidence Protection Node Assembly

| Item | Component | Manufacturer | Model | Quantity | Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | Single Board Computer | Raspberry Pi | Raspberry Pi Zero WH | 1 | Evidence collection and monitoring platform |
| 2 | System Storage | Samsung | microSD Card (128GB) | 1 | System storage medium |
| 3 | Display Cable | Generic | Mini HDMI to HDMI Cable | 1 | Used for development and system configuration |

Procurement sources:

- Raspberry Pi Zero WH: Amazon  
- microSD Card: Best Buy  
- HDMI Cable: Best Buy  

Approximate procurement costs:

- Raspberry Pi Zero WH: **$25 USD**  
- microSD Card: **$20-30 USD**  
- HDMI Cable: **~$2 USD**  


---

## 6.0 PROCUREMENT AND TRACEABILITY REQUIREMENTS

All hardware used in the E.C.L.I.P.S.E. system shall be traceable to its procurement source.

At minimum, the following information should be recorded when available:

- Manufacturer
- Model name or part number
- Supplier or procurement source
- Purchase date
- Purchase cost
- Warranty information
- Serial numbers (if applicable)

For components procured prior to project initiation where detailed procurement records are unavailable, approximate cost estimates and vendor identification may be recorded.

Future system builds should maintain full procurement traceability.

---

## 7.0 ESTIMATED SYSTEM COST

Estimated total procurement cost for baseline system configuration:

| Component Group | Estimated Cost |
| :--- | :--- |
| Authority Controller Assembly | ~$53 |
| Attack Simulation Node Assembly | ~$200 |
| Evidence Protection Node Assembly | ~$50-60 |

Estimated total system cost:

**~$300 USD**

---

## 8.0 ATTACHMENTS

The following supporting documentation may be attached or referenced:

- Manufacturer datasheets
- Product specification sheets
- Supplier purchase receipts
- Warranty documentation

When available, attachments should be stored alongside this document within the `/docs` repository directory.

---

END OF DOCUMENT
