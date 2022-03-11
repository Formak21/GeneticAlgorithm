import socket
import json
import sys

from lib.functions import test_function_himmelblau as test_function

# Network
connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('192.168.88.246', 25566))

while True:
    data = connection.recv(65536).decode('utf-8')
    if data == 'exit':
        sys.exit()
    data = json.loads(data)
    data = test_function.f(data)
    connection.send(str(data).encode('utf-8'))
