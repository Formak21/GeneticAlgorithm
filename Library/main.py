import datetime


class GeneticMain:
    def __init__(self, GeneticAlgorithm, GeneticIndividual, EGraph, TestFunction, Params):
        self.GA = GeneticAlgorithm
        self.GI = GeneticIndividual
        self.GR = EGraph
        self.Func = TestFunction
        self.individuals_quantity = Params[0]  # int(input('how many individuals:'))
        self.gene_quantity = Params[1]  # int(input('how many genes in one individual:'))
        self.mutation_mode = Params[2]  # input('mutation mode(WEAK/NORMAL/STRONG/NULL):')
        self.population_quantity = Params[3]  # int(input('how many iterations:'))
        self.solutions = []
        self.es = []
        self.grs = []
        self.deltas = []
        self.times = 0

    def run(self, flag):
        ga = self.GA(self.individuals_quantity, self.gene_quantity, self.mutation_mode, self.GI, self.Func.f)
        population = 0
        ga_graph = self.GR(self.Func.optimal([0] * self.gene_quantity), ga, population)
        Started = datetime.datetime.now()

        while True:
            ga.quality_update()
            ga.update_best_solution()
            ga.selection()
            ga_graph.add_point()
            if population > self.population_quantity:
                # print('Done!')
                # print(f'Started:{Started.strftime("%d.%m.%y-%H:%M:%S")}')
                # print(f'Ended:{datetime.datetime.now().strftime("%d.%m.%y-%H:%M:%S")}')
                # print(f'Delta microseconds/1000:{(datetime.datetime.now() - Started).microseconds / 1000}')
                # print(f'E={ga_graph.return_e(population)}')
                # print()
                if flag:
                    ga_graph.open_graph()
                # if not bool(int(input('Continue? 0/1:'))):
                #    break
                # self.population_quantity += int(input(f'now {population} iterations left, how many more iterations:'))
                self.solutions.append(ga.best_solution)
                self.es.append(ga_graph.return_e(population))
                ga_graph.obj = None # garbage collector should destroy ga
                self.grs.append(ga_graph)
                self.deltas.append(datetime.datetime.now() - Started)
                break
            ga.crossover()
            ga.mutation()
            population += 1
        self.times += 1

    def return_e(self):
        return self.GR.get_e(self.es)

    def run_n_times(self, n):
        for _ in range(n):
            self.run(False)
