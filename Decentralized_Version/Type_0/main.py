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
from Library import ModernGraph as Mg

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


    individuals_quantity = int(input('how many individuals:'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    ga = NetworkGA(individuals_quantity, gene_quantity, mutation_mode, Gi.GeneticIndividual)
    population = 0
    ga_graph = Mg.ModernGraph(ga, population)
    population_quantity = int(input('how many iterations:'))
    Started = datetime.datetime.now()

    while True:
        ga.quality_update()
        ga.update_best_solution()
        ga.selection()
        ga_graph.add_point()
        if population >= population_quantity:
            print('Done!')
            print(f'Started:{Started.strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Ended:{datetime.datetime.now().strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Delta seconds:{(datetime.datetime.now() - Started).seconds}')
            print()
            ga_graph.open_graph()
            if not bool(int(input('Continue? 0/1:'))):
                break
            population_quantity += int(input(f'now {population} iterations left, how many more iterations:'))
        ga.crossover()
        ga.mutation()
        population += 1
