import nmap

def scan_ports(data):
    nm = nmap.PortScanner()

    for host in data["hosts"]:
        ip = host["ip"]

        nm.scan(ip, arguments='-sS -p- --open -T4')

        if ip not in nm.all_hosts():
            print(f"Host {ip} did not respond to port scan")
            continue

        for proto in nm[ip].all_protocols():
            ports = nm[ip][proto].keys()

            for port in ports:
                host["ports"].append({
                    "port": port,
                    "protocol": proto,
                    "state": nm[ip][proto][port]["state"]
                })
    return data

# if __name__ == "__main__":
#     results = scan_ports()
#     print(results)