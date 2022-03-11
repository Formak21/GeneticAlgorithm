import datetime
import socket
import json
import math

from lib import GeneticIndividual as Gi
from lib import GeneticAlgorithm as Ga

from lib.functions import test_function_6 as test_function

# Network
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


class NetworkGA(Ga.GeneticAlgorithm):
    def quality_update(self):
        self.exec_time['Started'] = datetime.datetime.now()
        global Connected_Machines
        queue = [i for i in range(self.SIZE)]
        wait = []
        machine_number = 0
        while len(queue) or len(wait):
            if Connected_Machines[machine_number]['Status'] == 1:
                self.individuals[Connected_Machines[machine_number]['Data']].quality = float(
                    Connected_Machines[machine_number]['Machine'][0].recv(65535).decode('utf-8'))
                wait.remove(Connected_Machines[machine_number]['Data'])
                Connected_Machines[machine_number]['Status'] = 0
                Connected_Machines[machine_number]['Data'] = -1
            if Connected_Machines[machine_number]['Status'] == 0 and len(queue):
                Connected_Machines[machine_number]['Status'] = 1
                wait.append(queue.pop(0))
                Connected_Machines[machine_number]['Data'] = wait[-1]
                data_for_send = json.dumps([int(i) for i in
                                            self.individuals[
                                                Connected_Machines[machine_number]['Data']].individual])
                Connected_Machines[machine_number]['Machine'][0].send(data_for_send.encode("utf-8"))
            machine_number = (machine_number + 1) % machines
        self.exec_time['Ended'] = datetime.datetime.now()


# Genetic Algorithm Parameters
test_quantity = int(input('Test quantity='))
individuals_quantity = int(input('Individuals quantity(N%2=0)='))
gene_quantity = int(input('Gene quantity(N%2=0)='))
mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
population_quantity = int(input('how many iterations:'))
started = datetime.datetime.now()
solutions = []

for __ in range(test_quantity):
    ga = NetworkGA(individuals_quantity, gene_quantity, mutation_mode, Gi.GeneticIndividual, test_function.f)

    population = 0
    while True:
        ga.quality_update()
        ga.update_best_solution()
        if population >= population_quantity:
            solutions.append(ga.best_solution.quality)
            break
        ga.selection()
        ga.crossover()
        ga.mutation()
        population += 1

e = math.sqrt(sum([abs(i - test_function.optimal([0] * gene_quantity)) ** 2 for i in solutions[:-1]]) / len(solutions))
print(f'delta={(datetime.datetime.now() - started) / datetime.timedelta(milliseconds=1)} ms')
print(f'e={e}')

for i in Connected_Machines:
    i['Machine'][0].send('exit'.encode('utf-8'))
