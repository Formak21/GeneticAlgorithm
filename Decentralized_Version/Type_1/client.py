import socket
import json

from Library import GeneticIndividual as Gi
from Library import GeneticAlgorithm as Ga
from Library import EModernGraph as Mg
from Library import main

from Test_Functions import TestFunction0
from Test_Functions import TestFunction1
from Test_Functions import TestFunction2
from Test_Functions import TestFunction3
from Test_Functions import TestFunction4
from Test_Functions import TestFunction5
from Test_Functions import TestFunction6

connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('192.168.88.246', 25566))
while True:
    data = connection.recv(65536).decode('utf-8')
    data = json.loads(data)
    GM = main.GeneticMain(Ga.GeneticAlgorithm, Gi.GeneticIndividual, Mg.EModernGraph, TestFunction6, data)
    GM.run(False)
    Data1 = [[int(i) for i in GM.solutions[0].individual], GM.solutions[0].quality,
             GM.deltas[0].microseconds / 1000, GM.es[0]]
    Data2 = GM.grs[0].points
    connection.send(json.dumps(Data1).encode('utf-8'))
    connection.recv(512)
    connection.send(json.dumps(Data2).encode('utf-8'))
