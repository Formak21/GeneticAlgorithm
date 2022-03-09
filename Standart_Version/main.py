#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime

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
    individuals_quantity = int(input('how many individuals(N%2=0):'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    population_quantity = int(input('how many iterations:'))
    GM = main.GeneticMain(Ga.GeneticAlgorithm, Gi.GeneticIndividual, Mg.EModernGraph, TestFunction6,
                          [individuals_quantity, gene_quantity, mutation_mode, population_quantity])
    Started = datetime.datetime.now()
    GM.run_n_times(12)
    print(f'global delta ={(datetime.datetime.now() - Started).microseconds / 1000} microseconds/1000')
    print(f'E={GM.return_e()}')

    print('Data:')
    for i in range(GM.times):
        print(f'{i} GeneticAlgorithm')
        print(f'Solution {GM.solutions[i]}')
        print(f'F={GM.solutions[i].quality}')
        print(f'Delta {GM.deltas[i]} microseconds/1000')
        print(f'E={GM.es[i]}')
        print('Rendering Graphs')
        GM.grs[i].open_graph()
        if not bool(int(input('Continue? 0/1:'))):
            break