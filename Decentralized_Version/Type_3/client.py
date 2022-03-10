import random
import socket
import json

from Library import GeneticIndividual as Gi
from Library import GeneticAlgorithm as Ga

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
    ga = Ga.GeneticAlgorithm(data[0], data[1], data[2], Gi.GeneticIndividual, TestFunction4.f)
    population = 0
    while True:
        ga.quality_update()
        ga.update_best_solution()
        if random.choice([True, False]):
            connection.send(
                json.dumps([[int(i) for i in ga.individuals[ga.best_per_population()].individual],
                            ga.individuals[ga.best_per_population()].quality]).encode('utf-8'))
            data_tmp = json.loads(connection.recv(65536).decode('utf-8'))
            data_tmp[0] = Gi.GeneticIndividual(data[1], data_tmp[0])
            data_tmp[0].quality = data_tmp[1]
            ga.individuals[ga.best_per_population()] = data_tmp[0]
            ga.update_best_solution()
        else:
            connection.send(json.dumps([0, 0]).encode('utf-8'))
        if population > data[3]:
            connection.send(str(ga.best_solution.quality).encode('utf-8'))
            break
        ga.selection()
        ga.crossover()
        ga.mutation()
        population += 1
