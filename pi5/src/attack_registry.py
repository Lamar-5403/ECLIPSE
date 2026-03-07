ATTACK_REGISTRY = {
    "host_discovery": {
        "tactic": "TA0043",             # Reconnaissance
        "tactic_code": 0x43,
        "technique": "T1595",           # Active scanning
        "technique_code": 0x01,
        "vector": "icmp_ping_sweep",
        "cves": []
    },

    "port_scan": {
        "tactic": "TA0043",
        "tactic_code": 0x43,
        "technique": "T1595",
        "technique_code": 0x01,
        "vector": "tcp_syn_scan",
        "cves": []
    },

    "service_detection": {
        "tactic": "TA0043",
        "tactic_code": 0x43,
        "technique": "T1595",
        "technique_code": 0x01,
        "vector": "version_probe",
        "cves": []
    },

    "ssh_bruteforce": {
        "tactic": "TA0006",
        "tactic_code": 0x06,
        "technique": "T1110",
        "technique_code": 0x04,
        "vector": "ssh_password_bruteforce",
        "cves": ["CVE-2004-2761"]
    },

    "apache_chunked_overflow": {
        "tactic": "TA0001",
        "tactic_code": 0x01,
        "technique": "T1190",
        "technique_code": 0x03,
        "vector": "apache_chunked_encoding_overflow",
        "cves": ["CVE-2002-0392"]
    },

    "ssl_overflow": {
        "tactic": "TA0001",
        "tactic_code": 0x01,
        "technique": "T1190",
        "technique_code": 0x03,
        "vector": "apache_ssl_overflow",
        "cves": ["CVE-2002-0656"]
    },

    "mysql_bruteforce": {
        "tactic": "TA0006",
        "tactic_code": 0x06,
        "technique": "T1110",
        "technique_code": 0x04,
        "vector": "mysql_password_bruteforce",
        "cves": ["CVE-2000-0981"]
    },

    "cups_exploit": {
        "tactic": "TA0001",
        "tactic_code": 0x01,
        "technique": "T1190",
        "technique_code": 0x03,
        "vector": "cups_buffer_overflow",
        "cves": ["CVE-2004-0888"]
    },

    "rpc_enum": {
        "tactic": "TA0007",
        "tactic_code": 0x07,
        "technique": "T1046",
        "technique_code": 0x06,
        "vector": "rpc_service_enum",
        "cves": ["CVE-1999-0001"]
    }
}