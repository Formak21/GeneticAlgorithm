#
#  GeneticAlgorithm.py
#  GeneticAlgorithm base class
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#

import numpy
import random

VERSION = "4.0.2RePy_LDE"


class GeneticAlgorithm:
    def __init__(self, size, leng, m_reg, IndividualClass, f):
        self.SIZE = size
        self.LENG = leng
        self.m_reg = m_reg
        self.individuals = []
        self.selected_its = []
        for _ in range(self.SIZE):
            self.individuals.append(IndividualClass(self.LENG))
            self.selected_its.append((int(), int()))
        self.individuals = numpy.array(self.individuals, dtype=IndividualClass)
        self.selected_its = numpy.array(self.selected_its, dtype=tuple)
        self.f = f

    def quality_update(self):  # VERY SLOW FUNCTION, PLS DON'T CALL IT IF IT NO NEEDED
        for i in range(self.SIZE):
            self.individuals[i].quality = self.f([int(i) for i in self.individuals[i].individual])

    def regen(self):
        for i in range(0, self.SIZE):
            self.individuals[i].gen_ind()

    def selection(self):
        for i in range(self.SIZE):
            random_its = (random.randint(0, self.SIZE - 1), random.randint(0, self.SIZE - 1))
            if self.individuals[random_its[0]] > self.individuals[random_its[1]]:
                self.selected_its[i][0] = random_its[0]
            elif self.individuals[random_its[0]] < self.individuals[random_its[1]]:
                self.selected_its[i][0] = random_its[1]
            elif self.individuals[random_its[0]] == self.individuals[random_its[1]]:
                self.selected_its[i][0] = random_its[random.randint(0, 1)]

        for i in range(self.SIZE):
            random_its = (random.randint(0, self.SIZE - 1), random.randint(0, self.SIZE - 1))
            if self.individuals[random_its[0]] > self.individuals[random_its[1]]:
                self.selected_its[i][1] = random_its[0]
            elif self.individuals[random_its[0]] < self.individuals[random_its[1]]:
                self.selected_its[i][1] = random_its[1]
            elif self.individuals[random_its[0]] == self.individuals[random_its[1]]:
                self.selected_its[i][1] = random_its[random.randint(0, 1)]

    def crossover(self):
        past_individuals = self.individuals.copy()
        for i in range(0, self.SIZE):
            past_individuals[i] = (
                    self.individuals[self.selected_its[i][0]] + self.individuals[self.selected_its[i][1]])
        self.individuals = past_individuals

    def mutation(self):
        for i in range(0, self.SIZE):
            self.individuals[i].mutation(self.m_reg)

    def qualities(self) -> list:
        quality = []
        for i in range(self.SIZE):
            quality.append(self.individuals[i].quality)
        return quality

    def max_quality(self):
        quality = None
        for i in range(self.SIZE):
            if quality is None or quality < self.individuals[i].quality:
                quality = self.individuals[i].quality
        return quality

    def min_quality(self):
        quality = None
        for i in range(self.SIZE):
            if quality is None or quality > self.individuals[i].quality:
                quality = self.individuals[i].quality
        return quality

    def __str__(self):
        return '\n'.join([str(self.individuals[i]) for i in range(self.SIZE)])
