import nmap

def enumerate_services(data):
    nm = nmap.PortScanner()

    for host in data["hosts"]:
        ip = host["ip"]

        port_list = [p["port"] for p in host["ports"]]

        if not port_list:
            continue

        port_string = ",".join(str(p) for p in port_list)

        nm.scan(ip, arguments=f"-sV -p {port_string}")

        if ip not in nm.all_hosts():
            continue

        for proto in nm[ip].all_protocols():
            for port in nm[ip][proto]:
                for p in host["ports"]:
                    if p["port"] == port:
                        service = nm[ip][proto][port].get("name", "unknown")
                        product = nm[ip][proto][port].get("product", "")
                        version = nm[ip][proto][port].get("version", "")
                        extrainfo = nm[ip][proto][port].get("extrainfo", "")

                        p["service"] = service
                        p["version"] = f"{product} {version} {extrainfo}".strip()
    return data