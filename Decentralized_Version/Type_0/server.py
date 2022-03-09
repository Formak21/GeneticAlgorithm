#
#  main.py
#  GeneticAlgorithm main2
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

VERSION = "4.1.0RePy_NET"

if __name__ == '__main__':

    listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listener.bind(('127.0.0.1', 25566))
    listener.listen(1)


    def connect_machine(n):
        print(f'Waiting for machine no{n}...')
        machine = listener.accept()
        print(f'Machine No{n} Successfully connected. ')
        return machine


    machines = int(input('how many machines:'))
    Connected_Machines = [{'Machine': connect_machine(i), 'Status': 0, 'Data': -1} for i in range(machines)]


    class NetworkGA(Ga.GeneticAlgorithm):
        def __init__(self, size, leng, m_reg, IndividualClass):
            super(NetworkGA, self).__init__(size, leng, m_reg, IndividualClass, None)

        def quality_update(self):  # VERY SLOW FUNCTION, PLS DON'T CALL IT IF IT NO NEEDED
            self.exec_time['Started'] = datetime.datetime.now()
            global Connected_Machines
            queue = [i for i in range(self.SIZE)]
            wait = []
            machine_number = 0
            while len(queue) or len(wait):
                if Connected_Machines[machine_number]['Status'] == 1:
                    self.individuals[Connected_Machines[machine_number]['Data']].quality = float(
                        Connected_Machines[machine_number]['Machine'][0].recv(32768).decode('utf-8'))
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


    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    GM = main.GeneticMain(NetworkGA, Gi.GeneticIndividual, Mg.EModernGraph, TestFunction0,
                          [individuals_quantity, gene_quantity, mutation_mode, population_quantity])
    GM.run_n_times(10)
    print(f'E={GM.return_e()}')

    print('Data:')
    for i in range(GM.times):
        print(f'{i} GeneticAlgorithm')
        print(f'Solution {GM.solutions[i]}')
        print(f'F {GM.solutions[i].quality}')
        print(f'Delta {GM.deltas[i].microseconds / 1000} microseconds/1000')
        print(f'E={GM.es[i]}')
        print('Rendering Graphs')
        GM.grs[i].open_graph()
        if not bool(int(input('Continue? 0/1:'))):
            break
