import socket

HOST = "172.20.10.2"  # The server's hostname or IP address
PORT = 80            # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.connect((HOST, PORT))
	s.settimeout(1) # timeout 1s

	while True:
		s.sendall(b'Hello, world')
		try:
			data = s.recv(1024)
			print('Received', repr(data))
		except KeyboardInterrupt:
			exit()
		except:
			pass
