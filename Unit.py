import time

import GeneticIndividual
import GeneticAlgorithm
import ModernGraph
import socket
import json


def json_import():
    with open('UnitConfig.json', 'r', encoding='utf-8') as _f:
        return json.load(_f)


def json_export(var):
    open('UnitConfig.json', 'w', encoding='utf-8').close()
    with open('UnitConfig.json', 'w', encoding='utf-8') as _f:
        json.dump(var, _f, ensure_ascii=False)


if __name__ == '__main__':
    Configuration = json_import()
    con = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    temp = 1
    while temp:
        try:
            con.connect((Configuration['IP'], int(Configuration['PORT'])))
            temp -= 1
        except:
            time.sleep(5)
            temp += 1
    con.send('Connected.'.encode('utf-8'))
    Parameters = None
    while Parameters is None:
        try:
            Parameters = json.loads(con.recv(32768).decode('utf-8'))
        except:
            time.sleep(5)
    # size, leng, iters, m_reg, func
    open('func.py', 'w', encoding='utf-8').close()
    with open('func.py', 'w', encoding='utf-8') as f:
        f.write(Parameters['func'])


    class CustomGeneticIndividual(GeneticIndividual.GeneticIndividual):
        def quality_ind(self):
            from func import func
            return func(self)


    GenAlg = GeneticAlgorithm.GeneticAlgorithm(Parameters['size'], Parameters['leng'], Parameters['m_reg'],
                                               CustomGeneticIndividual)
    counter = 0
    GenAlgGraph = ModernGraph.ModernGraph(GenAlg, counter)

    temp = None
    while temp != 'START':
        try:
            temp = con.recv(256).decode('utf-8')
        except:
            time.sleep(5)

    while counter != Parameters['iter']:
        GenAlgGraph.add_point()
        GenAlg.crossover()
        GenAlg.mutation()
        GenAlg.selection()
        counter += 1

    GenAlgGraph.save_graph()



