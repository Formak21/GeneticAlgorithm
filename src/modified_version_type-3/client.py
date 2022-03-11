import random
import socket
import json
import sys

from lib import GeneticIndividual as Gi
from lib import GeneticAlgorithm as Ga

from lib.functions import test_function_himmelblau as test_function

# Network
connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connection.connect(('192.168.88.246', 25566))

while True:
    # Get parameters
    data = connection.recv(65536).decode('utf-8')
    if data == 'exit':
        sys.exit()
    data = json.loads(data)

    # Set up Genetic Algorithm
    ga = Ga.GeneticAlgorithm(data[0], data[1], data[2], Gi.GeneticIndividual, test_function.f)
    population = 0
    while True:
        ga.quality_update()
        ga.update_best_solution()

        # Modification
        if random.choice([True, False]):
            connection.send(
                json.dumps([[int(i) for i in ga.individuals[ga.best_per_population()].individual],
                            ga.individuals[ga.best_per_population()].quality]).encode('utf-8'))
            data_tmp = connection.recv(65536).decode('utf-8')
            data_tmp = json.loads(data_tmp)
            data_tmp[0] = Gi.GeneticIndividual(data[1], data_tmp[0])
            data_tmp[0].quality = data_tmp[1]
            ga.individuals[ga.best_per_population()] = data_tmp[0]
            ga.update_best_solution()
        else:
            connection.send(json.dumps([0, 0]).encode('utf-8'))
            connection.recv(500)
        # End of Modification

        if population >= data[3]:
            connection.send(str(ga.best_solution.quality).encode('utf-8'))
            break
        ga.selection()
        ga.crossover()
        ga.mutation()
        population += 1
