//
//  Graph.h
//  GeneticAlgorithm Graph class
//
//  Created by Alexandr Formakovskiy ( Form49.d ).
//
#ifndef GRAPH_GENALG
#define GRAPH_GENALG

#ifndef VERSION
#define VERSION "3.X.X_LDE"
#endif // VERSION

#include <fstream>
#include <string>
#include <utility>

namespace GA{

    class Graph {
        private:
            std::ofstream opt;
        
        public:
            Graph(const std::string &filename);
            ~Graph();
            inline void add_text(const std::string &text);
            inline void add_point(const std::pair< long long, long long > &point);
        
    };

    Graph::Graph(const std::string &filename) {
        opt.open(filename + ".log", std::ofstream::app);
        opt << "#GA " << VERSION << " - GRAPH \'" << filename << "\' OPENED#" << std::endl;
    }

    Graph::~Graph() {
        opt.close();
    }

    inline void Graph::add_text(const std::string &text) {
        opt << "#" << text << "#" << std::endl;
    }

    inline void Graph::add_point(const std::pair< long long, long long > &point) {
        opt << point.first << ", " << point.second << std::endl;
    }

}


#endif // GRAPH_GENALG
