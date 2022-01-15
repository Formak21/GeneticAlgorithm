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
    con.settimeout(6)
    con.connect((Configuration['IP'], Configuration['PORT']))
    con.send('Connected.'.encode('utf-8'))
    Parameters = json.loads(con.recv(32768).decode('utf-8'))
    # size, leng, iters, m_reg, func
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
    