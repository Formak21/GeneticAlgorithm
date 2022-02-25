#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime
import socket
import json
import GeneticIndividual
import GeneticAlgorithm
import ModernGraph

VERSION = "4.0.2RePy_LDE"


listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listener.bind(('127.0.0.1', 12333))
listener.listen(1)
connection = listener.accept()


class AlterGenIndiv(GeneticIndividual.GeneticIndividual):
    def quality_ind(self):
        connection[0].send(json.dumps([int(i) for i in self.individual]).encode("utf-8"))
        return int(connection[0].recv(500).decode('utf-8'))


if __name__ == '__main__':
    size = int(input('how many individuals:'))
    leng = int(input('how many genes in one individual:'))
    m_reg = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    Test = GeneticAlgorithm.GeneticAlgorithm(size, leng, m_reg, AlterGenIndiv)
    counter = 0
    TestGraph = ModernGraph.ModernGraph(Test, counter)
    iters = int(input('how many iterations:'))
    Started = datetime.datetime.now()
    while True:
        TestGraph.add_point()
        # print(f"\rCycle:{counter}", end='')
        # print(f"Max:{Test.max_quality()}")
        # print(f"Max:{Test.min_quality()}")
        # print(f"Population:\n[{Test}]\n")
        if counter == iters:
            print('Done!')
            print(f'Started:{Started.strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Ended:{datetime.datetime.now().strftime("%d.%m.%y-%H:%M:%S")}')
            print(f'Delta seconds:{(datetime.datetime.now()-Started).seconds}')
            print()
            TestGraph.open_graph()
            if not bool(int(input('Continue? 0/1:'))):
                break
            iters += int(input(f'now {counter} iterations left, how many more iterations:'))
        Test.crossover()
        Test.mutation()
        Test.selection()
        counter += 1
