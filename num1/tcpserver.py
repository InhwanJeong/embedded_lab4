import socket

HOST, PORT = "192.168.0.75", 8080
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(1)
conn, addr = sock.accept()

while True:
    data = conn.recv(1024)
    print("Received", data)
conn.close() 
