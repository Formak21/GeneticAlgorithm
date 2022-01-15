#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#

import GeneticIndividual
import GeneticAlgorithm
import ModernGraph

VERSION = "4.0.2RePy_LDE"


class AlterGenIndiv(GeneticIndividual.GeneticIndividual):
    def quality_ind(self):
        qual = 0
        for i in range(self.SIZE // 2):
            if self.individual[i]:
                qual += 1
        for i in range(self.SIZE // 2, self.SIZE):
            if not self.individual[i]:
                qual += 1
        return qual


if __name__ == '__main__':
    size = int(input('how many individuals:'))
    leng = int(input('how many genes in one individual:'))
    m_reg = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    Test = GeneticAlgorithm.GeneticAlgorithm(size, leng, m_reg, GeneticIndividual.GeneticIndividual)
    counter = 0
    TestGraph = ModernGraph.ModernGraph(Test, counter)
    while True:
        TestGraph.add_point()
        # print(f"\rCycle:{counter}", end='')
        # print(f"Max:{Test.max_quality()}")
        # print(f"Max:{Test.min_quality()}")
        # print(f"Population:\n[{Test}]\n")
        if Test.max_quality() == leng:
            break
        Test.crossover()
        Test.mutation()
        Test.selection()
        counter += 1

    print('Done!')
    TestGraph.open_graph()
