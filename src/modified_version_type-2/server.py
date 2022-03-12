import datetime
import socket
import json
import math

from lib.functions import test_function_shekelsfoxholes as test_function

# Network
listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listener.bind(('127.0.0.1', 25566))
listener.listen(1)


def connect_machine(n):
    print(f'Waiting for machine no{n}...')
    machine_t = listener.accept()
    print(f'Machine No{n} Successfully connected. ')
    return machine_t


machines = int(input('Machines quantity='))
Connected_Machines = [connect_machine(i) for i in range(machines)]

# Genetic Algorithm Parameters
test_quantity = int(input('Test quantity(recommend=machines quantity)='))
individuals_quantity = int(input('Individuals quantity(N%2=0)='))
gene_quantity = int(input('Gene quantity(N%2=0)='))
mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
population_quantity = int(input('how many iterations:'))
started = datetime.datetime.now()
solutions = [[]]

for __ in range(test_quantity):
    # Sending Parameters
    for machine in Connected_Machines:
        data = json.dumps([individuals_quantity, gene_quantity, mutation_mode, population_quantity])
        machine[0].send(data.encode("utf-8"))

    for machine in Connected_Machines:
        data = float(machine[0].recv(65536).decode('utf-8'))
        solutions[-1].append(data)
    solutions[-1] = max(solutions[-1])
    solutions.append([])

e = math.sqrt(sum([abs(i - test_function.optimal([0] * gene_quantity)) ** 2 for i in solutions[:-1]]) / len(solutions))
print(f'E={e}')
print(f'delta={(datetime.datetime.now() - started) / datetime.timedelta(milliseconds=1)} ms')

for i in Connected_Machines:
    i[0].send('exit'.encode('utf-8'))
