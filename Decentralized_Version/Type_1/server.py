#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime
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


    class NetGeneticMain(main.GeneticMain):
        def run_n_times(self, n):
            queue = [i for i in range(n)]
            wait = []
            machine_number = 0
            while len(queue) or len(wait):
                if Connected_Machines[machine_number]['Status'] == 1:
                    data = Connected_Machines[machine_number]['Machine'][0].recv(65536).decode('utf-8')
                    data = json.loads(data)
                    Connected_Machines[machine_number]['Machine'][0].send('1'.encode("utf-8"))
                    self.solutions.append(self.GI(self.gene_quantity, data[0]))
                    self.solutions[-1].quality = data[1]
                    self.deltas.append(data[2])
                    self.es.append(data[3])
                    data = json.loads(Connected_Machines[machine_number]['Machine'][0].recv(524288).decode('utf-8'))
                    self.grs.append(
                        self.GR(self.Func.optimal([0] * self.gene_quantity), None, self.population_quantity, data))
                    wait.remove(Connected_Machines[machine_number]['Data'])
                    Connected_Machines[machine_number]['Status'] = 0
                    Connected_Machines[machine_number]['Data'] = -1
                if Connected_Machines[machine_number]['Status'] == 0 and len(queue):
                    Connected_Machines[machine_number]['Status'] = 1
                    wait.append(queue.pop(0))
                    Connected_Machines[machine_number]['Data'] = wait[-1]
                    data_for_send = json.dumps(
                        [self.individuals_quantity, self.gene_quantity, self.mutation_mode, self.population_quantity])
                    Connected_Machines[machine_number]['Machine'][0].send(data_for_send.encode("utf-8"))
                machine_number = (machine_number + 1) % machines
            self.times += n


    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    GM = NetGeneticMain(Ga.GeneticAlgorithm, Gi.GeneticIndividual, Mg.EModernGraph, TestFunction6,
                        [individuals_quantity, gene_quantity, mutation_mode, population_quantity])
    Started = datetime.datetime.now()
    GM.run_n_times(12)
    print(f'global delta ={(datetime.datetime.now() - Started)/ datetime.timedelta(milliseconds=1)} microseconds/1000')
    print(f'E={GM.return_e()}')

    print('Data:')
    for i in range(GM.times):
        print(f'{i} GeneticAlgorithm')
        print(f'Solution {GM.solutions[i]}')
        print(f'F={GM.solutions[i].quality}')
        print(f'Delta {GM.deltas[i]} millisec')
        print(f'E={GM.es[i]}')
        print('Rendering Graphs')
        GM.grs[i].open_graph()
        if not bool(int(input('Continue? 0/1:'))):
            break
