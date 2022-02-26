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


if __name__ == '__main__':
    def f(n) -> int:
        time.sleep(1)  # И.Б.Д.
        return sum(n)

    class DefaultGI(GeneticIndividual.GeneticIndividual):
        def __init__(self, sz):
            super().__init__(sz)
            self.quality = None

        def quality_ind(self):
            return self.quality


    class DefaultGA(GeneticAlgorithm.GeneticAlgorithm):
        def quality_update(self):  # VERY SLOW FUNCTION, PLS DON'T CALL IT IF IT NO NEEDED
            for i in range(self.SIZE):
                self.individuals[i].quality = f([int(i) for i in self.individuals[i].individual])


    size = int(input('how many individuals:'))
    leng = int(input('how many genes in one individual:'))
    m_reg = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    Ga = DefaultGA(size, leng, m_reg, DefaultGI)
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
            if not bool(int(input('Continue? 0/1:'))):
                break
            iters += int(input(f'now {counter} iterations left, how many more iterations:'))
        Ga.crossover()
        Ga.mutation()
        counter += 1