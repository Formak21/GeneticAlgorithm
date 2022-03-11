import datetime
import math

from lib import GeneticIndividual as Gi
from lib import GeneticAlgorithm as Ga

from lib.functions import test_function_himmelblau as test_function

# Genetic Algorithm Parameters
test_quantity = int(input('Test quantity='))
individuals_quantity = int(input('Individuals quantity(N%2=0)='))
gene_quantity = int(input('Gene quantity(N%2=0)='))
mutation_mode = input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
population_quantity = int(input('how many iterations:'))
started = datetime.datetime.now()
solutions = []

for __ in range(test_quantity):
    ga = Ga.GeneticAlgorithm(individuals_quantity, gene_quantity, mutation_mode, Gi.GeneticIndividual, test_function.f)
    population = 0
    while True:
        ga.quality_update()
        ga.update_best_solution()
        if population >= population_quantity:
            solutions.append(ga.best_solution.quality)
            break
        ga.selection()
        ga.crossover()
        ga.mutation()
        population += 1

e = math.sqrt(sum([abs(i - test_function.optimal([0] * gene_quantity)) ** 2 for i in solutions[:-1]]) / len(solutions))
print(f'delta={(datetime.datetime.now() - started) / datetime.timedelta(milliseconds=1)} ms')
print(f'e={e}')
