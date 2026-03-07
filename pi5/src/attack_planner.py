from attack_registry import ATTACK_REGISTRY

CVE_ATTACK_MAP = {
    cve: name
    for name, attack in ATTACK_REGISTRY.items()
    for cve in attack.get("cves", [])
}

def plan_attack(data):

    tactics = set()
    techniques = set()

    for host in data["hosts"]:
        for port in host["ports"]:

            if "vulnerabilities" not in port:
                continue

            for vuln in port["vulnerabilities"]:

                cve = vuln["cve"]

                attack_name = CVE_ATTACK_MAP.get(cve)
                if not attack_name:
                    continue
                
                attack = ATTACK_REGISTRY[attack_name]

                if "attack_plan" not in port:
                    port["attack_plan"] = []

                port["attack_plan"].append({
                    "attack": attack_name,
                    "tactic": attack["tactic"],
                    "tactic_code": attack["tactic_code"],
                    "technique": attack["technique"],
                    "technique_code": attack["technique_code"],
                    "vector": attack["vector"]
                })

                tactics.add(attack["tactic_code"])
                techniques.add(attack["technique_code"])

    data["tactics"] = list(tactics)
    data["techniques"] = list(techniques)
    return data