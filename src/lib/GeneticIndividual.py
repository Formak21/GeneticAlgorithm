#
#  GeneticIndividual.py
#  GeneticAlgorithm individual class
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#

import random
import numpy
import copy

VERSION = "4.1.0RePy"


class GeneticIndividual:
    def __init__(self, size, mass=None):
        self.SIZE = size
        self.quality = int()
        if mass is None:
            self.individual = numpy.array([False] * self.SIZE, dtype=bool)
            self.gen_ind()
        else:
            self.individual = numpy.array([bool(i) for i in mass], dtype=bool)

    def gen_ind(self):
        for i in range(0, self.SIZE):
            self.individual[i] = bool(random.randint(0, 1))

    def revrs_ind(self):
        self.individual = self.individual[-1::]

    def mutation(self, m_reg='WEAK'):
        if m_reg == 'WEAK':
            mt_prb = 1.0 / (3.0 * self.SIZE)
        elif m_reg == 'NORMAL':
            mt_prb = 1.0 / (1.0 * self.SIZE)
        elif m_reg == 'STRONG':
            mt_prb = 3.0 / (1.0 * self.SIZE)
        elif m_reg == 'NULL':
            mt_prb = 0.0
        else:
            raise ("m_reg error.")

        for i in range(0, self.SIZE):
            if (random.randint(0, 100) / 100) < mt_prb:
                self.individual[i] = not self.individual[i]

    def copy(self):
        return copy.deepcopy(self)

    def __lt__(self, other) -> bool:  # <
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        return self.quality < other.quality

    def __gt__(self, other) -> bool:  # >
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        return self.quality > other.quality

    def __le__(self, other) -> bool:  # <=
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        return self.quality <= other.quality

    def __ge__(self, other) -> bool:  # >=
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        return self.quality >= other.quality

    def __eq__(self, other) -> bool:  # ==
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        return self.quality == other.quality

    def __ne__(self, other) -> bool:  # != for checking equal individs (NOT QUAL LIKE OTHER COMPARISONS)
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL COMPARISON ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        if self.SIZE != other.SIZE:
            raise ("YOU CAN COMPARE ONLY GENINDIVS WITH EQUAL SIZES")
        for i in range(self.SIZE):
            if self.individual[i] != other.individual[i]:
                return True
        return False

    def __add__(self, other):  # +
        if type(other) != type(self):
            raise ("GENETICINDIVIDUAL ADDING ERROR, YOU CAN COMPARE ONLY GENINDIVS.")
        if self.SIZE != other.SIZE:
            raise ("YOU CAN ADD ONLY GENINDIVS WITH EQUAL SIZES")
        copyied_genindiv = self.copy()
        if self == other:
            return copyied_genindiv
        random_pos = random.randint(0, self.SIZE - 1)
        if random.randint(0, 1):
            for i in range(0, random_pos + 1):
                copyied_genindiv.individual[i] = other.individual[i]
        else:
            for i in range(random_pos, self.SIZE):
                copyied_genindiv.individual[i] = other.individual[i]
        return copyied_genindiv

    def __str__(self) -> str:
        return ''.join([str(int(i)) for i in self.individual])
