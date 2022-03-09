from Library import ModernGraph
import math


class EModernGraph(ModernGraph.ModernGraph):
    def __init__(self, optimum, obj, population=0):
        super().__init__(obj)
        self.Graphs['e_quality'] = ModernGraph.Graph.Graph('e_quality')
        self.points['e_quality'] = [] + [0] * self.population
        self.optimum = optimum

    def add_point(self):
        super().add_point()
        self.population -= 1
        self.points['e_quality'][self.population] = abs(self.points['max_max_quality'][self.population] - self.optimum)
        self.Graphs['e_quality'].add_point((self.population, self.points['e_quality'][self.population]))
        self.population += 1

    def return_e(self, point):
        return self.points['e_quality'][point]

    @staticmethod
    def get_e(points):
        return math.sqrt(sum([i ** 2 for i in points]) / len(points))

    def open_graph(self):
        super().open_graph()
        ModernGraph.time.sleep(2)
        fig = ModernGraph.px.line(self.points, y=ModernGraph.pd.Index(['e_quality'], dtype=str))
        fig.show()

    def save_graph(self):
        super().save_graph()
        ModernGraph.time.sleep(2)
        fig = ModernGraph.px.line(self.points, y=ModernGraph.pd.Index(['e_quality'], dtype=str))
        fig.write_image("Graphs/Last3Graph.png")
        ModernGraph.plotly.offline.plot(fig, filename='Graphs/Last3Graph.html')
