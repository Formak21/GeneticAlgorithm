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

from Library import GeneticIndividual as Gi
from Test_Functions import TestFunction6

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
    Connected_Machines = [{'Machine': connect_machine(i), 'Status': 0, 'Data': -1} for i in range(machines)]

    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    Started = datetime.datetime.now()
    solutions = [[] * 12]


    def best_solution_finder(x):
        return max(x, key=lambda y: y.quality)


    for k in range(12):
        queue = [i for i in range(machines)]
        wait = []
        machine_number = 0
        while len(queue) or len(wait):
            if Connected_Machines[machine_number]['Status'] == 1:
                data = json.loads(Connected_Machines[machine_number]['Machine'][0].recv(65536).decode('utf-8'))
                solutions[k].append(Gi.GeneticIndividual(gene_quantity, data[0]))
                solutions[k][-1].quality = data[1]
                wait.remove(Connected_Machines[machine_number]['Data'])
                Connected_Machines[machine_number]['Status'] = 0
                Connected_Machines[machine_number]['Data'] = -1
            if Connected_Machines[machine_number]['Status'] == 0 and len(queue):
                Connected_Machines[machine_number]['Status'] = 1
                wait.append(queue.pop(0))
                Connected_Machines[machine_number]['Data'] = wait[-1]
                data_for_send = json.dumps(
                    [individuals_quantity, gene_quantity, mutation_mode, population_quantity])
                Connected_Machines[machine_number]['Machine'][0].send(data_for_send.encode("utf-8"))
            machine_number = (machine_number + 1) % machines
        solutions[k] = best_solution_finder(solutions[k])
    e = math.sqrt(sum([abs(i.quality - TestFunction6.optimal(i.individual))**2 for i in solutions])/len(solutions))
    print(f'global delta={(datetime.datetime.now() - Started) / datetime.timedelta(milliseconds=1)} ms')
    print(f'e={e}')
