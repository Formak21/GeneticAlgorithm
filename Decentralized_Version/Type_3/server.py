#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime
import socket
import json
import math
import random

from Library import GeneticIndividual as Gi
from Test_Functions import TestFunction4

VERSION = "4.1.0RePy"

if __name__ == '__main__':
    listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listener.bind(('192.168.88.246', 25566))
    listener.listen(1)


    def connect_machine(n):
        print(f'Waiting for machine no{n}...')
        machine = listener.accept()
        print(f'Machine No{n} Successfully connected. ')
        return machine


    machines = int(input('how many machines:'))
    Connected_Machines = [connect_machine(i) for i in range(machines)]

    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    Started = datetime.datetime.now()
    solutions = [[]]


    def best_solution_finder(x):
        return max(x, key=lambda y: y.quality)

    for machine in Connected_Machines:
        data_for_send = json.dumps([individuals_quantity, gene_quantity, mutation_mode, population_quantity])
        machine[0].send(data_for_send.encode("utf-8"))
    for _ in range(population_quantity):
        individual_bank = []
        machine_bank = []
        for machine in Connected_Machines:
            data = json.loads(machine[0].recv(65536).decode('utf-8'))
            if data[0] is int:
                continue
            else:
                individual_bank.append(data)
                machine_bank.append(machine)
        for machine in machine_bank:
            data_for_send = individual_bank.pop(random.randint(0, len(individual_bank)-1))
            machine[0].send(data_for_send.encode("utf-8"))
    for machine in Connected_Machines:
        data = json.loads(machine[0].recv(65536).decode('utf-8'))
        solutions[-1].append(Gi.GeneticIndividual(gene_quantity, data[0]))
        solutions[-1][-1].quality = data[1]
        solutions[-1] = best_solution_finder(solutions[-1])
        solutions.append([])

    e = math.sqrt(sum([abs(i.quality - TestFunction4.optimal(i.individual))**2 for i in solutions[:-1]])/len(solutions))
    print(f'global delta={(datetime.datetime.now() - Started) / datetime.timedelta(milliseconds=1)} ms')
    print(f'e={e}')
