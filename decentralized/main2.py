#
#  main2.py
#  GeneticAlgorithm main2
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime
import socket
import json
import sys

sys.path.append('../lib')
import GeneticIndividual
import GeneticAlgorithm
import ModernGraph

VERSION = "4.0.3RePy_NET"

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


    class NetworkGI(GeneticIndividual.GeneticIndividual):
        def __init__(self, sz):
            super().__init__(sz)
            self.quality = None

        def quality_ind(self):
            return self.quality


    class NetworkGA(GeneticAlgorithm.GeneticAlgorithm):
        def quality_update(self):  # VERY SLOW FUNCTION, PLS DON'T CALL IT IF IT NO NEEDED
            global Connected_Machines
            queue = [i for i in range(self.SIZE)]
            wait = []
            machine_number = 0
            while len(queue) or len(wait):
                if Connected_Machines[machine_number]['Status'] == 1:
                    self.individuals[Connected_Machines[machine_number]['Data']].quality = int(
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


    size = int(input('how many individuals:'))
    leng = int(input('how many genes in one individual:'))
    m_reg = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    Ga = NetworkGA(size, leng, m_reg, NetworkGI)
    counter = 0
    GaGraph = ModernGraph.ModernGraph(Ga, counter)
    iters = int(input('how many iterations:'))
    Started = datetime.datetime.now()
    while True:
        Ga.quality_update()
        Ga.selection()
        GaGraph.add_point()
        # print(f"\rCycle:{counter}", end='')
        # print(f"Max:{Test.max_quality()}")
        # print(f"Max:{Test.min_quality()}")
        # print(f"Population:\n[{Test}]\n")
        if counter == iters:
            print('Done!')
            print(f'Started:{Started.strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Ended:{datetime.datetime.now().strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Delta seconds:{(datetime.datetime.now() - Started).seconds}')
            print()
            GaGraph.open_graph()
            print(Ga)
            if not bool(int(input('Continue? 0/1:'))):
                break
            iters += int(input(f'now {counter} iterations left, how many more iterations:'))
        Ga.crossover()
        Ga.mutation()
        counter += 1
