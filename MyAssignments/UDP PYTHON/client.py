import socket
import time
import sys

UDP_IP = "127.0.1.11"
UDP_PORT = 5005
buf = 1024
file_name = sys.argv[2]
text = sys.argv[1]

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(text, (UDP_IP, UDP_PORT))
sock.sendto(file_name, (UDP_IP, UDP_PORT))
print "Sending %s ..." % file_name
print "Sending %s ..." % text
f = open(file_name, "r")
data = f.read(buf)

while(data):
    if(sock.sendto(data, (UDP_IP, UDP_PORT))):
        data = f.read(buf)
        time.sleep(0.02)
sock.close()
f.close()
