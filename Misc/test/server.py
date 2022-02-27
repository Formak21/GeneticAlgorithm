import socket
import json
import random


def f(n):
    return [random.randint(0, 1) for _ in range(n)]


listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listener.bind(('127.0.0.1', 12333))
listener.listen(1)
connection = listener.accept()
data = f(10)
connection[0].send(json.dumps(data).encode("utf-8"))
print(f"Data sent:{data}")
print(f"Data received:{connection[0].recv(500).decode('utf-8')}")
