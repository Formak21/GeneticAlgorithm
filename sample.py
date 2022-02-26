#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime
import time
import sys
sys.path.append('lib')
import GeneticIndividual
import GeneticAlgorithm
import ModernGraph

VERSION = "4.0.2RePy_LDE"


class AlterGenIndiv(GeneticIndividual.GeneticIndividual):
    def quality_ind(self):
        time.sleep(1)  # И.Б.Д.
        return super().quality_ind()


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
        Test.selection()
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
        counter += 1
