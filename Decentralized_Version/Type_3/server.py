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
import sys

from Test_Functions import TestFunction6 as TestFunction4

VERSION = "4.1.0RePy"

if __name__ == '__main__':
    listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listener.bind(('192.168.88.246', 25566))
    listener.listen(1)


    def connect_machine(n):
        print(f'Waiting for machine no{n}...')
        machine_t = listener.accept()
        print(f'Machine No{n} Successfully connected. ')
        return machine_t


    machines = int(input('how many machines:'))
    Connected_Machines = [connect_machine(i) for i in range(machines)]

    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    Started = datetime.datetime.now()
    solutions = [[]]

    for __ in range(12):
        for machine in Connected_Machines:
            data_for_send = json.dumps([individuals_quantity, gene_quantity, mutation_mode, population_quantity])
            machine[0].send(data_for_send.encode("utf-8"))
        for _ in range(population_quantity+2):
            individual_bank = []
            machine_bank = []
            for machine in Connected_Machines:
                data = machine[0].recv(65536).decode('utf-8')
                data = json.loads(data)
                if data[0] == 0:
                    continue
                else:
                    individual_bank.append(data)
                    machine_bank.append(machine)
            for machine in Connected_Machines:
                if machine in machine_bank:
                    data_for_send = json.dumps(individual_bank.pop(random.randint(0, len(individual_bank)-1)))
                    machine[0].send(data_for_send.encode("utf-8"))
                else:
                    machine[0].send('ok'.encode("utf-8"))
        for machine in Connected_Machines:
            data = float(machine[0].recv(65536).decode('utf-8'))
            solutions[-1].append(data)
        solutions[-1] = max(solutions[-1])
        solutions.append([])

    e = math.sqrt(sum([abs(i - TestFunction4.optimal([0]*gene_quantity))**2 for i in solutions[:-1]])/len(solutions))
    print(f'global delta={(datetime.datetime.now() - Started) / datetime.timedelta(milliseconds=1)} ms')
    print(f'e={e}')
