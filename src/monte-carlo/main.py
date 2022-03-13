import datetime
import math
import random

from lib.functions import test_function_himmelblau as test_function

test_quantity = int(input('Test quantity='))
gene_quantity = int(input('Gene quantity(N%2=0)='))
population_quantity = int(input('how many iterations:'))
started = datetime.datetime.now()
solutions = []

for __ in range(test_quantity):
    solutions.append(max([test_function.f([random.randint(0, 1) for i in range(gene_quantity)]) for _ in
                          range(population_quantity)]))

e = math.sqrt(sum([abs(i - test_function.optimal([0] * gene_quantity)) ** 2 for i in solutions]) / len(solutions))
print(f'E={e}')
print(f'delta={(datetime.datetime.now() - started) / datetime.timedelta(milliseconds=1)} ms')
