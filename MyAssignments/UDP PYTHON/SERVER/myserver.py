import socket
import select

IP = "127.0.0.1"
PORT = 8003

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind((IP,PORT))

while True : 
	msg , addr = sock.recvfrom(1024)
	if msg: 
		print msg
	data , addrs = sock.recvfrom(1024)
	if data:
		print data
		filename = data.strip()
	f = open(filename,'wb')
	
	while True:
		filebuff,addr = sock.recvfrom(1024)
		f.write(filebuff)
		print("Done")
		f.close()
		break
	break;
sock.close()
