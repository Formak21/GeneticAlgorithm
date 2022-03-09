#
#  ModernGraph.py
#  GeneticAlgorithm New Graph class
#
#  Created by Alexandr Formakovskiy ( Form49.d ).
#
import numpy

from Library import Graph
import plotly
import plotly.express as px
import pandas as pd
import time

VERSION = "4.1.0RePy"

'''
График минимумов 
График максимумов
График средних
График максимального максимума
График времени вычисления функции к популяции
'''


class ModernGraph:
    def __init__(self, obj, population=0):
        self.obj = obj
        self.population = population
        self.Graphs = {'min_quality': Graph.Graph('min_quality'),
                       'max_quality': Graph.Graph('max_quality'),
                       'max_max_quality': Graph.Graph('max_max_quality'),
                       'avg_quality': Graph.Graph('avg_quality'),
                       'time_quality': Graph.Graph('time_quality')}
        self.points = {'min_quality': [] + [0] * self.population,
                       'max_quality': [] + [0] * self.population,
                       'max_max_quality': [] + [0] * self.population,
                       'avg_quality': [] + [0] * self.population,
                       'time_quality': [] + [0] * self.population}

    def add_text(self, text):
        for key in self.Graphs.keys():
            self.Graphs[key].add_text(text)

    def add_point(self):
        for key in self.points.keys():
            self.points[key].append(0)

        self.points['min_quality'][self.population] = self.obj.min_quality()
        self.Graphs['min_quality'].add_point((self.population, self.points['min_quality'][self.population]))

        self.points['max_quality'][self.population] = self.obj.max_quality()
        self.Graphs['max_quality'].add_point((self.population, self.points['max_quality'][self.population]))
        self.points['max_max_quality'][self.population] = max(self.points['max_quality'])
        self.Graphs['max_max_quality'].add_point((self.population, self.points['max_max_quality'][self.population]))

        temp = self.obj.qualities()
        self.points['avg_quality'][self.population] = sum(temp) / len(temp)
        self.Graphs['avg_quality'].add_point((self.population, self.points['avg_quality'][self.population]))

        self.points['time_quality'][self.population] = (
                                                               self.obj.exec_time['Ended'] - self.obj.exec_time[
                                                           'Started']).microseconds / 1000
        self.Graphs['time_quality'].add_point((self.population, self.points['time_quality'][self.population]))

        self.population += 1

    def open_graph(self):
        fig = px.line(self.points,
                      y=pd.Index(['avg_quality', 'max_max_quality', 'max_quality', 'min_quality'], dtype=str))
        fig.show()
        time.sleep(2)
        fig = px.line(self.points, y=pd.Index(['time_quality'], dtype=str))
        fig.show()

    def save_graph(self):
        fig = px.line(self.points, y=pd.Index(self.points.keys(), dtype=str))
        fig.write_image("Graphs/LastGraph.png")
        plotly.offline.plot(fig, filename='Graphs/LastGraph.html')
        fig = px.line(self.points, y=pd.Index(['time_quality'], dtype=str))
        fig.write_image("Graphs/Last2Graph.png")
        plotly.offline.plot(fig, filename='Graphs/Last2Graph.html')
