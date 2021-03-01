//
//  GeneticIndividual.h
//  GeneticAlgorithm individual struct
//
//  Created by Alexandr Formakovskiy ( Form49.d ).
//
#ifndef GENETIC_INDIVIDUAL
#define GENETIC_INDIVIDUAL

#ifndef VERSION
#define VERSION "3.X.X_LDE"
#endif // VERSION

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

namespace GA{

    struct GeneticIndividual{
        private:
            std::vector<char> individual;
            const long long a, b, c;
            
        public:
            GeneticIndividual(const size_t size, const long long mk_a, const long long mk_b, const long long mk_c);
            const size_t size;
            void gen_ind();
            void reverse_ind();
            void mutation(const char m_reg);
            long long unsigned quality_ind() const;
            std::pair< long long, long long > x0y0() const; //debug

            bool operator< (const GeneticIndividual &r) const;
            bool operator> (const GeneticIndividual &r) const;
            bool operator<= (const GeneticIndividual &r) const;
            bool operator>= (const GeneticIndividual &r) const;
            bool operator== (const GeneticIndividual &r) const;
            bool operator!= (const GeneticIndividual &r) const;
            GeneticIndividual operator+ (GeneticIndividual r);
            GeneticIndividual &operator= (const GeneticIndividual &r);
            friend std::ostream& operator<< (std::ostream &out, const GeneticIndividual &r);

    };
    
    inline GeneticIndividual::GeneticIndividual(const size_t mk_ln, const long long mk_a, const long long mk_b, const long long mk_c) : individual(mk_ln, 0),
    a(mk_a), b(mk_b), c(mk_c), size(mk_ln){
        gen_ind();
    }

    void GeneticIndividual::gen_ind(){
        for (auto& i : individual){
            i = std::rand() % 2;
        }
    }

    inline void GeneticIndividual::reverse_ind(){
        std::reverse(individual.begin(), individual.end());
    }

    void GeneticIndividual::mutation(const char m_reg){
        double mt_prb;
        switch (m_reg){
            case 1:
                mt_prb = 1.0 / (3.0 * size);
                break;
            case 2:
                mt_prb = 1.0 / (1.0 * size);
                break;
            case 3:
                mt_prb = 3.0 / (1.0 * size);
                break;
            case 0:
                mt_prb=0;
                break;
        }
        
        for (auto& i : individual){
            if (((double)rand() / RAND_MAX) < mt_prb){
               i=!i;
            }
        }
    }

    long long unsigned GeneticIndividual::quality_ind() const{
        long long x=0, y=0;
        for (size_t i = 1; i < size/2; ++i){
            if (individual[i]){
                x+=std::pow(2, i-1);
            }
            
            if (individual[i+(size/2)]){
                y+=std::pow(2, i-1);
            }
        }

        if (individual[0]){
            x*=-1;
        }
        
        if (individual[size/2]){
            y*=-1;
        }

        if (y > 0 && x > std::numeric_limits< long long >::max() - y)
            throw std::range_error( "adding x and y causes overflow" );

        if (y < 0 && x < std::numeric_limits< long long >::min() - y)
            throw std::range_error( "adding x and y causes underflow" );

        return std::abs(c - ((a*x)+(b*y))) * 1LLU;
    }

    std::pair< long long, long long > GeneticIndividual::x0y0() const{
        long long x=0, y=0;
        for (size_t i = 1; i < size/2; ++i){
            if (individual[i]){
                x+=std::pow(2, i-1);
            }

            if (individual[i+(size/2)]){
                y+=std::pow(2, i-1);
            }
        }

        if (individual[0]){
            x*=-1;
        }

        if (individual[size/2]){
            y*=-1;
        }

        return std::make_pair(x, y);
    }

    inline bool GeneticIndividual::operator< (const GeneticIndividual &r) const{
        return quality_ind() < r.quality_ind();
    }

    inline bool GeneticIndividual::operator> (const GeneticIndividual &r) const{
        return quality_ind() > r.quality_ind();
    }

    inline bool GeneticIndividual::operator<= (const GeneticIndividual &r) const{
        return quality_ind() <= r.quality_ind();
    }

    inline bool GeneticIndividual::operator>= (const GeneticIndividual &r) const{
        return quality_ind() >= r.quality_ind();
    }

    inline bool GeneticIndividual::operator== (const GeneticIndividual &r) const{
        return individual == r.individual;
    }

    inline bool GeneticIndividual::operator!= (const GeneticIndividual &r) const{
        return individual != r.individual;
    }

    GeneticIndividual GeneticIndividual::operator+ (GeneticIndividual r){
        if (this->size != r.size){
            throw std::runtime_error("GenInd operator+ - incorrect size");
        }
        size_t random_pos = std::rand() % (this->size-1);
        
        if(std::rand() % 2){
            for(size_t i = random_pos; i < this->size; ++i){
                r.individual[i] = this->individual[i];
            }
        } else {
            for(size_t i = 0; i <= random_pos; ++i){
                r.individual[i] = this->individual[i];
            }
        }
        
        return r;
    }

    inline GeneticIndividual &GeneticIndividual::operator= (const GeneticIndividual &r){
        if (this->size != r.size){
            throw std::runtime_error("GenInd operator+ - incorrect size");
        }
        individual = r.individual;
        return *this;
    }

    std::ostream& operator<< (std::ostream &out, const GeneticIndividual &r){
        for (const auto& i : r.individual) {
            out << int(i);
        }
        return out;
    }

}

#endif // GENETIC_INDIVIDUAL
