import socket
import select

UDP_IP = "127.0.1.11"
IN_PORT = 5005
timeout = 3

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, IN_PORT))

#while True:
    #text, addr = sock.recvfrom(1024)
    #f text:
     #  print text

while True:
    
    text,addr = sock.recvfrom(1024)
    if text:
    	print text
    data, addr = sock.recvfrom(1024) 	
    if data:
        print "File name:", data
        file_name = data.strip()

    f = open(file_name, 'wb')

    while True:
        ready = select.select([sock], [], [], timeout)
        if ready[0]:
            data, addr = sock.recvfrom(1024)
            f.write(data)
        else:
            print "%s Finish!" % file_name
            f.close()
            break



