import socket
import sys
import time

IP = "127.0.0.1"
PORT = 8003
msg = sys.argv[1]
filename = sys.argv[2]

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(msg, (IP, PORT))
sock.sendto(filename,(IP,PORT))
f = open(filename,"r")
data = f.read(1024)

while (data):
	if(sock.sendto(data,(IP,PORT))):
		data = f.read(1024);
		time.sleep(0.02)
	
sock.close()
f.close()
