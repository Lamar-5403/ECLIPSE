import nmap

def scan_network(target):
    nm = nmap.PortScanner()

    nm.scan(target, arguments='-sn')
    
    hosts = nm.all_hosts()

    if not hosts:
        print("No hosts discovered")
        return
    
    for host in hosts:
        print(f"Host: {host}")
        print(f"State: {nm[host].state()}")

        for proto in nm[host].all_protocols():
            ports = nm[host][proto].keys()

            for port in ports: 
                state = nm[host][proto][port]['state']
                service = nm[host][proto][port]['name']

                print(f"Port {port}/{proto} - {state} - {service}")

if __name__ == "__main__":
    target_ip = "192.168.4.0/22"
    scan_network(target_ip)