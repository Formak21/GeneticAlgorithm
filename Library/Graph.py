#
#  Graph.py
#  GeneticAlgorithm Graph class
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#

import datetime

VERSION = "4.1.0RePy"


class Graph:
    def __init__(self, filename):
        self.filename = 'Graphs/' + filename + ".log"
        self.add_text(
            f"GA {VERSION} - GRAPH '{filename}' OPENED, {datetime.datetime.now().strftime('%d.%m.%y-%H:%M:%S')}")

    def add_text(self, text):
        with open(self.filename, mode='a', encoding='utf-8') as f:
            f.write(f"\n#{text}#")

    def add_point(self, point):
        with open(self.filename, mode='a', encoding='utf-8') as f:
            f.write(f"\n{point[0]}, {point[1]}")
