import socket
import json
import sys

from lib import GeneticIndividual as Gi
from lib import GeneticAlgorithm as Ga

from lib.functions import test_function_himmelblau as test_function

# Network
connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('127.0.0.1', 25566))

while True:
    # Get parameters
    data = connection.recv(65536).decode('utf-8')
    data = json.loads(data)

    # Set up Genetic Algorithm
    ga = Ga.GeneticAlgorithm(data[0], data[1], data[2], Gi.GeneticIndividual, test_function.f)
    population = 0
    while True:
        ga.quality_update()
        ga.update_best_solution()
        if population >= data[3]:
            connection.send(str(ga.best_solution.quality).encode('utf-8'))
            break
        ga.selection()
        ga.crossover()
        ga.mutation()
        population += 1
