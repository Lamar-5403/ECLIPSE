ATTACK_REGISTRY = {
    "host_discovery": {
        "tactic": "TA0043",             # Reconnaissance
        "tactic_code": 0x43,
        "technique": "T1595",           # Active scanning
        "technique_code": 0x01,
        "vector": "icmp_ping_sweep"
    },

    "port_scan": {
        "tactic": "TA0043",
        "tactic_code": 0x43,
        "technique": "T1595",
        "technique_code": 0x01,
        "vector": "tcp_syn_scan"
    },

    "service_detection": {
        "tactic": "TA0043",
        "tactic_code": 0x07,
        "technique": "T1595",
        "technique_code": 0x01,
        "vector": "version_probe"
    },

    "ssh_bruteforce": {
        "tactic": "TA",
        "tactic_code": 0,
        "technique": "T1",
        "technique_code": 0,
        "vector": ""
    },

    "http_exploit": {
        "tactic": "TA",
        "tactic_code": 0,
        "technique": "T1",
        "technique_code": 0,
        "vector": ""
    },

    "smb_lateral_move": {
        "tactic": "TA",
        "tactic_code": 0,
        "technique": "T1",
        "technique_code": 0,
        "vector": ""
    }
}