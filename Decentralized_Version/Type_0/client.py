import socket
import json

from Test_Functions import TestFunction0
from Test_Functions import TestFunction1
from Test_Functions import TestFunction2
from Test_Functions import TestFunction3
from Test_Functions import TestFunction4
from Test_Functions import TestFunction5
from Test_Functions import TestFunction6


connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('127.0.0.1', 25566))
while True:
    data = connection.recv(65536).decode('utf-8')
    data = json.loads(data)
    data = TestFunction6.f(data)
    connection.send(f'{data}'.encode('utf-8'))
