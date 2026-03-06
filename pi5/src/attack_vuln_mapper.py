from attack_vuln_database import VULN_DB
import re

def map_vuln(data):
    for host in data["hosts"]:
        for port in host["ports"]:

            if "vulnerabilities" not in port:
                port["vulnerabilities"] = []

            service = port.get("service", "")
            version = port.get("version", "")

            if service not in VULN_DB:
                continue

            if not version:
                continue

            for rule in VULN_DB[service]:
                if re.search(rule["version_pattern"], version):
                    port["vulnerabilities"].append(
                        {
                            "cve": rule["cve"],
                            "tactic": rule["tactic"],
                            "technique": rule["technique"],
                            "vector": rule["vector"] 
                        }
                    )
    return data