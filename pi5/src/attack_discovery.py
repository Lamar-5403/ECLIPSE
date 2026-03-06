import nmap

def discover_hosts(target):
    nm = nmap.PortScanner()

    nm.scan(target, arguments='-sn')
    
    hosts = nm.all_hosts()

    data = { "hosts": [] }

    if not hosts:
        return data
    
    for host in hosts:
        if nm[host].state() == "up":
            data["hosts"].append({ "ip": host, "ports": [] })

    return data

if __name__ == "__main__":
    target_ip = "192.168.56.0/24"
    results = discover_hosts(target_ip)
    print(results)