//
//  main.cpp
//  GeneticAlgorithm
//
//  Created by Alexandr Formakovskiy ( Form49.d ).
//
#define VERSION "3.0.0_LDE"
#include <iostream>
#include <string>
#include <utility>
#include "Graph.h"
#include "GeneticAlgorithm.h"


int main(){
    std::srand(time(nullptr));
    GA::Graph min_qualities("min_qualities");
    GA::Graph max_qualities("max_qualities");
    size_t mk_sz=40, mk_ln=22, mk=20, pop=200;
    char mk_rg=1;
    std::vector<GA::GeneticAlgorithm> GeneticAlgorithms(mk, GA::GeneticAlgorithm(mk_sz, mk_ln, mk_rg));

    for(auto &i : GeneticAlgorithms){
        long long unsigned population=0;
        min_qualities.add_text("New Algorithm");
        max_qualities.add_text("New Algorithm");
        min_qualities.add_point(std::make_pair(population, i.min_quality()));
        max_qualities.add_point(std::make_pair(population, i.max_quality()));
        while(population < pop){
            i.selection();
            i.crossover();
            i.mutation();
            population++;
            min_qualities.add_point(std::make_pair(population, i.min_quality()));
            max_qualities.add_point(std::make_pair(population, i.max_quality()));
        }
    }
    std::cout<<"Done!";
    return 0;
}
