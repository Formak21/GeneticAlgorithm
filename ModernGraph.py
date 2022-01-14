#
#  ModernGraph.py
#  GeneticAlgorithm New Graph class
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#

import Graph
import plotly.express as px
import pandas as pd


VERSION = "4.X.XRePy_LDE"

'''
График минимумов 
График максимумов
График средних
График максимального максимума
'''


class ModernGraph:
    def __init__(self, obj, population=0):
        self.obj = obj
        self.population = population
        self.Graphs = {'min_quality': Graph.Graph('min_quality'),
                       'max_quality': Graph.Graph('max_quality'),
                       'max_max_quality': Graph.Graph('max_max_quality'),
                       'avg_quality': Graph.Graph('avg_quality')}
        self.points = {'min_quality': [0] * (self.population + 1),
                       'max_quality': [0] * (self.population + 1),
                       'max_max_quality': [0] * (self.population + 1),
                       'avg_quality': [0] * (self.population + 1)}

    def add_text(self, text):
        for key in self.Graphs.keys():
            self.Graphs[key].add_text(text)

    def add_point(self):
        self.points['min_quality'][self.population] = self.obj.min_quality()
        self.Graphs['min_quality'].add_point((self.population, self.points['min_quality'][self.population]))

        self.points['max_quality'][self.population] = self.obj.max_quality()
        self.Graphs['max_quality'].add_point((self.population, self.points['max_quality'][self.population]))
        self.points['max_max_quality'][self.population] = max(self.points['max_quality'])
        self.Graphs['max_max_quality'].add_point((self.population, self.points['max_max_quality'][self.population]))

        temp = self.obj.qualities()
        self.points['avg_quality'][self.population] = sum(temp) // len(temp)
        self.Graphs['avg_quality'].add_point((self.population, self.points['avg_quality'][self.population]))

        self.population += 1
        for key in self.points.keys():
            self.points[key].append(0)

    def save_graph(self, type_of_graph):
        pass

    def open_graph(self):
        fig = px.line(self.points, y=pd.Index(self.points.keys(), dtype=str))
        fig = px.line(x=list(range(0, self.population+1)), y=self.points['min_quality'])
        fig.show()
