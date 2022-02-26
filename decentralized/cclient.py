import socket
import json


def f(n) -> int:
    return sum(n)


connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('192.168.88.246', 25566))
while True:
    data = connection.recv(32768).decode('utf-8')
    print(data)
    data = json.loads(data)
    data = f(data)
    connection.send(f'{data}'.encode('utf-8'))
    print(f'Data sent:{data}')