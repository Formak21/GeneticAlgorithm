#
#  main.py
#  GeneticAlgorithm main
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import datetime

from Library import GeneticIndividual as Gi
from Library import GeneticAlgorithm as Ga
from Library import ModernGraph as Mg

from Test_Functions import TestFunction0
from Test_Functions import TestFunction1
from Test_Functions import TestFunction2
from Test_Functions import TestFunction3
from Test_Functions import TestFunction4
from Test_Functions import TestFunction5

VERSION = "4.1.0RePy"

if __name__ == '__main__':

    individuals_quantity = int(input('how many individuals:'))
    gene_quantity = int(input('how many genes in one individual:'))
    mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
    ga = Ga.GeneticAlgorithm(individuals_quantity, gene_quantity, mutation_mode, Gi.GeneticIndividual, TestFunction0.f)
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
