VULN_DB = {
    "ssh": [
        {
            "version_pattern": r"OpenSSH\s3\.",
            "cve": "CVE-2004-2761",
            "tactic": "Initial Access",
            "technique": "T1190",
            "vector": "OpenSSH CRC32 buffer overflow",
        }
    ],

    "http": [
        {
            "version_pattern": r"Apache\shttpd\s2\.0",
            "cve": "CVE-2002-0392",
            "tactic": "Initial Access",
            "technique": "T1190",
            "vector": "Apache chunked encoding overflow",
        }
    ],

    "https": [
        {
            "version_pattern": r"OpenSSL|Apache|nginx",
            "cve": "CVE-2002-0656",
            "tactic": "Initial Access",
            "technique": "T1190",
            "vector": "Apache/SSL overflow",
        }
    ],

    "mysql": [
        {
            "version_pattern": r"MySQL",
            "cve": "CVE-2000-0981",
            "tactic": "Credential Access",
            "technique": "T1110",
            "vector": "weak authentication brute force",
        }
    ],

    "rpcbind": [
        {
            "version_pattern": r"2",
            "cve": "CVE-1999-0001",
            "tactic": "Discovery",
            "technique": "T1046",
            "vector": "RPC service enumeration",
        }
    ],

    "ipp": [
        {
            "version_pattern": r"CUPS\s1\.1",
            "cve": "CVE-2004-0888",
            "tactic": "Initial Access",
            "technique": "T1190",
            "vector": "CUPS buffer overflow",
        }
    ]
}