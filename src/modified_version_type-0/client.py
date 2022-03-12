import socket
import json

from lib.functions import test_function_shekelsfoxholes as test_function

# Network
connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('127.0.0.1', 25566))

while True:
    data = connection.recv(65536).decode('utf-8')
    data = json.loads(data)
    data = test_function.f(data)
    connection.send(str(data).encode('utf-8'))
