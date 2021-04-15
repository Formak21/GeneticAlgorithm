//
//  main.cpp
//  GeneticAlgorithm
//
//  Created by Alexandr Formakovskiy ( Form49.d ).
//
#define VERSION "3.0.4_LDE"
#include <iostream>
#include <string>
#include <utility>
#include <ctime>
#include "Graph.h"
#include "GeneticAlgorithm.h"

long long gcd (long long a, long long b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}


int main(){
    std::srand(std::time(nullptr));
    long long x0, y0;
    int a, b, c;
    size_t mk_sz=40, mk_ln=22, mk=1;
    std::cout<<"ax+by=c\nEnter:a b c (max:"<<(INT_MAX/3)-10<<") MK_MATRIX_WIDTH MK_MATRIX_HEIGHT\nrules:n%2==0; m%2==0; 5 < w < 127; 5 < h\n";
    std::cin>>a>>b>>c>>mk_ln>>mk_sz;
    while (true) {
        if (c % gcd(a, b) == 0){
            break;
        } else {
            if (gcd(a,b) - (c % gcd(a, b)) > gcd(a,b)/2){
                c-=c % gcd(a, b);
            } else {
                c+= gcd(a, b) - (c % gcd(a, b));
            }
            std::cout << "c can't be divided by gcd(a, b), c was recorrected to " << c <<".\n";
        }
    }


    GA::Graph min_qualities("min_qualities");
    GA::Graph max_qualities("max_qualities");
    char mk_rg=1;
    std::vector<GA::GeneticAlgorithm> GeneticAlgorithms(mk, GA::GeneticAlgorithm(mk_sz, mk_ln, mk_rg, a, b, c));

    for(auto &i : GeneticAlgorithms){
        long long unsigned population=0;
        min_qualities.add_text("New Algorithm");
        max_qualities.add_text("New Algorithm");
        min_qualities.add_point(std::make_pair(population, i.min_quality()));
        max_qualities.add_point(std::make_pair(population, i.max_quality()));
        while(i.min_quality() > 0){//debug (mk_pp)
            i.selection();
            i.crossover();
            i.mutation();
            population++;
            min_qualities.add_point(std::make_pair(population, i.min_quality()));
            max_qualities.add_point(std::make_pair(population, i.max_quality()));
        }

        x0 = i.x0y0().first;//debug
        y0 = i.x0y0().second;//debug
    }
    std::cout<<"Done!\n";
    if ((x0*a) + (y0*b) == c){
    std::cout<<"x0="<<x0<<" y0="<<y0<<'\n';
    long long g = gcd(a, b);
    long long k;
    std::cout<<"x="<<x0<<"+ k*"<<b/g<<" K in Z. \n"<<"y="<<y0<<"+ k*"<<a/g<<" K in Z. \nENTER SAMPLE K:";
    std::cin>>k;
    std::cout<<"x="<<x0+(k*(b/g))<<'\n';
    std::cout<<"y="<<y0+(k*(a/g))<<'\n';
    }
    return 0;
}
