//
//  GeneticAlgorithm.h
//  GeneticAlgorithm base class
//
//  Created by Alexandr Formakovskiy ( Form49.d ).
//
#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#ifndef VERSION
#define VERSION "3.X.X_LDE"
#endif // VERSION

#include "GeneticIndividual.h"

namespace GA{

    class GeneticAlgorithm{
        private:
            std::vector<GeneticIndividual> individuals;
            std::vector< std::pair< size_t, size_t > > selected_its;
            const char m_regulator;
        public:
            const size_t size;
            GeneticAlgorithm(const size_t mk_sz, const size_t mk_ln, const char mk_rg, const long long mk_a, const long long mk_b, const long long mk_c);
            void selection();
            void crossover();
            void mutation();
            void regen();
            std::vector<long long unsigned> qualities() const;
            long long unsigned max_quality() const;
            long long unsigned min_quality() const;
            std::pair< long long, long long > x0y0() const;
            friend std::ostream& operator<< (std::ostream &out, GeneticAlgorithm &r);

    };

    GeneticAlgorithm::GeneticAlgorithm(const size_t mk_sz, const size_t mk_ln, const char mk_rg, const long long mk_a, const long long mk_b, const long long mk_c) :
        individuals(mk_sz, GeneticIndividual(mk_ln, mk_a, mk_b, mk_c)), selected_its(mk_sz), m_regulator(mk_rg), size(mk_sz){regen(); selection();}

    void GeneticAlgorithm::selection(){
        for (size_t i = 0; i < size; ++i){
            std::pair< size_t, size_t > random_its(std::rand() % size, std::rand() % size);
            if (individuals[random_its.first] > individuals[random_its.second]){
                selected_its[i].first = random_its.second;

            } else if (individuals[random_its.first] < individuals[random_its.second]){
                selected_its[i].first = random_its.first;

            } else if (individuals[random_its.first] == individuals[random_its.second]){
                if (rand() % 2){
                    selected_its[i].first = random_its.first;

                } else{
                    selected_its[i].first = random_its.second;

                }

            }

        }

        for (size_t i = 0; i < size; ++i){
            std::pair< size_t, size_t > random_its(std::rand() % size, std::rand() % size);
            if (individuals[random_its.first] > individuals[random_its.second]){
                selected_its[i].second = random_its.second;

            } else if (individuals[random_its.first] < individuals[random_its.second]){
                selected_its[i].second = random_its.first;

            } else if (individuals[random_its.first] == individuals[random_its.second]){
                if (rand() % 2){
                    selected_its[i].second = random_its.first;

                } else{
                    selected_its[i].second = random_its.second;

                }

            }

        }
    }

    void GeneticAlgorithm::crossover(){
        std::vector<GeneticIndividual> past_individuals = individuals;
        for (size_t i = 0; i < size; ++i){
           past_individuals[i] = (individuals[selected_its[i].first] + individuals[selected_its[i].second]);
        }
        std::swap(individuals, past_individuals);
    }

    void GeneticAlgorithm::mutation(){
        for (auto &i : individuals){
            i.mutation(m_regulator);
        }

    }

    void GeneticAlgorithm::regen(){
        for (auto &i : individuals){
            i.gen_ind();
        }

    }

    std::vector<long long unsigned> GeneticAlgorithm::qualities() const{
        std::vector<long long unsigned> quality(size, 0);
        for (size_t i = 0; i < size; ++i){
            quality[i] = individuals[i].quality_ind();
        }

        return quality;
    }

    long long unsigned GeneticAlgorithm::max_quality() const{
        long long unsigned quality = 0, tmp;
        for (const auto &i : individuals){
            tmp = i.quality_ind(); //itteration economy :)
            if (quality < tmp){
                quality = tmp;
            }
        }

        return quality;
    }

    long long unsigned GeneticAlgorithm::min_quality() const{
        long long unsigned quality = INT64_MAX, tmp;
        for (const auto &i : individuals){
            tmp = i.quality_ind(); //itteration economy :)
            if (quality > tmp){
                quality = tmp;
            }
        }

        return quality;
    }

    std::pair< long long, long long > GeneticAlgorithm::x0y0() const{
        size_t it=0;
        for (size_t i = 0; i < size; ++i){
            if (individuals[i].quality_ind() == 0){
                it = i;
            }
        }
        return individuals[it].x0y0();
    }

    std::ostream& operator<< (std::ostream &out, GeneticAlgorithm &r){
        for (const auto& i : r.individuals){
            out << i << '\n';
        }

        return out;
    }

}

#endif // GENETIC_ALGORITHM
