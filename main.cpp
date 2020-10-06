//
//  main.cpp
//  GeneticAlgorithm
//
//  Created by Alexandr Formakovskiy ( Formak21 ).
//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <utility>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <vector>
const std::string ver = "2.0.5 beta 5";
class Graph {
private:
    std::string filename;
    std::ofstream opt;
public:
    Graph(const std::string temp) {
        const std::string filename = temp + ".txt";
        opt.open(filename, std::ofstream::app);
        int randnum = rand() % 32520;
        int n = 1;
        opt << "\n#GA RELOADED " << ver << " GRAPH OPENED RandNum: " << randnum << " No: " << n << " " << filename << "#";
    }
    ~Graph() {
        opt.close();
    }
    void prnt_txt(std::string &text) {
        opt << "\n#" << text << "#";
        opt.flush();
    }
    void add_data(size_t x, size_t y) {
        opt << "\n(" << x << ", " << y << ")";
        opt.flush();
    }
};
Graph avg_qual_per_tick("AvgPerTick"); //Average quality, per every cycle, x-ticks, y-quality.
Graph best_qual_per_tick("BestPerTick"); //Best quality, per every cycle, x-ticks, y-quality.
Graph allbest_qual_per_tick("BestQualAll"); //Best quality, per all cycles, x-ticks, y-quality.
Graph worst_qual_per_tick("LowPerTick"); //Worst quality, per every cycle, x-ticks, y-quality.
enum MutationRegulator { WEAK, AVERAGE, STRONG, NULLM };
struct GeneticIndv{
private:
    std::vector<bool> indv;
public:
    GeneticIndv(size_t len_tmp) {
        rand_ind(len_tmp);
    }
    void ind_rvrs(){
        std::reverse(indv.begin(), indv.end());
    }
    size_t size(){
        return indv.size();
    }
    void rand_ind(size_t len_tmp) {
        indv.clear();
        for (size_t i = 0; i < len_tmp; i++) {
            indv.push_back(bool(rand() % 2));
        }
    }
    size_t ind_qual() {
        size_t tmp = 0;
        for (size_t i = 0; i < size(); i++) {
            if (indv[i]) {
                tmp++;
            }

        }
        return tmp;
    }
    void mutation(MutationRegulator m_r = WEAK) {
        for (size_t i = 0; i < size(); i++) {
            double mt_prb;
            switch (m_r){
                case WEAK:
                    mt_prb = 1.0 / (3.0 * size());
                    break;
                case AVERAGE:
                    mt_prb = 1.0 / (1.0 * size());
                    break;
                case STRONG:
                    mt_prb = 3.0 / (1.0 * size());
                    break;
                case NULLM:
                    mt_prb=0;
            }
            if (((double)rand() / RAND_MAX) < mt_prb) {
               indv[i]=!indv[i];
            }
        }
    }
    friend std::ostream& operator<< (std::ostream &out, const GeneticIndv &prtindiv);
    friend bool operator< (GeneticIndv &l, GeneticIndv &r);
    friend bool operator> (GeneticIndv &l, GeneticIndv &r);
    friend bool operator<= (GeneticIndv &l, GeneticIndv &r);
    friend bool operator>= (GeneticIndv &l, GeneticIndv &r);
    friend bool operator== (const GeneticIndv &l, const GeneticIndv &r);
    friend bool operator!= (const GeneticIndv &l, const GeneticIndv &r);
    friend GeneticIndv operator+ (GeneticIndv l, GeneticIndv &r);
};
std::ostream& operator<< (std::ostream &out, const GeneticIndv &prtindiv){
    for (size_t i = 0; i < prtindiv.indv.size(); i++) {
        out << prtindiv.indv[i];
    }
    return out;
}
bool operator< (GeneticIndv &l, GeneticIndv &r){
    return l.ind_qual() < r.ind_qual();
}
bool operator> (GeneticIndv &l, GeneticIndv &r){
    return l.ind_qual() > r.ind_qual();
}
bool operator<= (GeneticIndv &l, GeneticIndv &r){
    return l.ind_qual() <= r.ind_qual();
}
bool operator>= (GeneticIndv &l, GeneticIndv &r){
    return l.ind_qual() >= r.ind_qual();
}
bool operator== (const GeneticIndv &l, const GeneticIndv &r){
    return l.indv == r.indv;
}
bool operator!= (const GeneticIndv &l, const GeneticIndv &r){
    return l.indv != r.indv;
}
GeneticIndv operator+ (GeneticIndv l, GeneticIndv &r){
    if (l.size() != r.size()){
        std::cout << "\n\n\n!Error in GenIndiv +operator - l size != r size!\n" <<
        "returning left value\n\n\n";
        return l;
    }
    size_t random_pos = rand() % (l.size()-1);
    if(rand() % 2){
        for(size_t i = random_pos; i < l.size(); i++ ){
            l.indv[i] = r.indv[i];
        }
    } else {
        for(size_t i = 0; i <= random_pos; i++ ){
            l.indv[i] = r.indv[i];
        }
    }
    return l;
}
struct GeneticAlgorithm{
private:
    size_t indv_len;
    MutationRegulator mtt_reg;
    std::pair< std::vector<GeneticIndv>, std::vector<GeneticIndv> > popul;
public:
    size_t best_qual_all = 0;
    GeneticAlgorithm(size_t indv_len, size_t ga_size, MutationRegulator mtt_reg=WEAK){
        if (ga_size % 2 == 1){
            ga_size++;
            std::cout<<"\n\n\n!Error size of population % 2 == 1, corrected to size+1!\n\n\n";
        }
        if (indv_len % 2 == 1){
            indv_len++;
            std::cout<<"\n\n\n!Error size of indiv % 2 == 1, corrected to size+1!\n\n\n";
        }
        this->indv_len = indv_len;
        this->mtt_reg = mtt_reg;
        for(size_t i = 0; size() <= ga_size; i++){
            GeneticIndv tmp(indv_len);
            popul.first.push_back(tmp);
        }
    }
    size_t size(bool f_or_s = 1){
        if (f_or_s)
            return popul.first.size();
        else
            return popul.second.size();
    }
    void slctn(){
        for(size_t i = 0; i < size() * 2; i++){
            std::pair< size_t, size_t > rndid = {rand() % (size()-1), rand() % (size()-1)};
            if (popul.first[rndid.first] > popul.first[rndid.second]){
                popul.second.push_back(popul.first[rndid.first]);
            } else if (popul.first[rndid.first] < popul.first[rndid.second]){
                popul.second.push_back(popul.first[rndid.second]);
            } else {
                if(rand() % 2){
                    popul.second.push_back(popul.first[rndid.first]);
                } else{
                    popul.second.push_back(popul.first[rndid.second]);
                }
            }
        }
        popul.first.clear();
    }
    void crsgv(){
        for(size_t i = 0; i < size(0)-1; i+=2){
            popul.first.push_back(popul.second[i] + popul.second[i+1]);
        }
        popul.second.clear();
    }
    void mtt(){
        for(size_t i = 0; i < size(); i++){
            popul.first[i].mutation(mtt_reg);
        }
    }
    void rst(){
        best_qual_all = 0;
        size_t ga_size;
        if (popul.second.empty()){
            ga_size = size();
        } else {
            ga_size = size(0) / 2;
        }
        popul.first.clear();
        popul.second.clear();
        for(size_t i = 0; size() <= ga_size; i++){
            GeneticIndv tmp(indv_len);
            popul.first.push_back(tmp);
        }
    }
    size_t popul_qual(){
        if (popul.first.empty()){
            std::cout << "\n\n\n!Error popul_qual func working only when popul.first not empty, returning zero!\n\n\n";
            return 0;
        }
        size_t qual=0;
        for(size_t i = 0; i < size(); i++){
            qual+=popul.first[i].ind_qual();
        }
        return qual;
    }
    size_t best_qual(){
        if (popul.first.empty()){
            std::cout << "\n\n\n!Error popul_qual func working only when popul.first not empty, returning zero!\n\n\n";
            return 0;
        }
        size_t tmp = 0;
        for(size_t i = 0; i < size(); i++){
            if (popul.first[i].ind_qual() > tmp){
                tmp = popul.first[i].ind_qual();
            }
        }
        if (best_qual_all < tmp){ best_qual_all = tmp;}
        return tmp;
    }
    size_t avg_qual(){
        if (popul.first.empty()){
            std::cout << "\n\n\n!Error popul_qual func working only when popul.first not empty, returning zero!\n\n\n";
            return 0;
        }
        size_t tmp = 0;
        for(size_t i = 0; i < size(); i++){
            tmp+=popul.first[i].ind_qual();
        }
        tmp/=size();
        return tmp;
    }
    size_t worst_qual(){
        if (popul.first.empty()){
            std::cout << "\n\n\n!Error popul_qual func working only when popul.first not empty, returning zero!\n\n\n";
            return 0;
        }
        size_t tmp = best_qual();
        for(size_t i = 0; i < size(); i++){
            if (popul.first[i].ind_qual() < tmp){
                tmp = popul.first[i].ind_qual();
            }
        }
        return tmp;
    }
    size_t ideal_popul_qual(){
        size_t ga_size;
        if (popul.second.empty()){
            ga_size = size();
        } else {
            ga_size = size(0) / 2;
        }
        return ga_size * indv_len;
    }
    friend std::ostream& operator<< (std::ostream &out, GeneticAlgorithm &prtalg);
};
std::ostream& operator<< (std::ostream &out, GeneticAlgorithm &prtalg){
    for (size_t i = 0; i < prtalg.size(); i++) {
        out << prtalg.popul.first[i] << std::endl;
    }
    return out;
}
int main(){
    srand(time(nullptr));

    size_t ga_num=100, ga_size=100, indv_len=100, popul_num = 200;
    MutationRegulator m_r=WEAK;
    while (true) {
        std::cout
            << "\n\n\n\n\n\n"
            << " $$$$$$\\                             $$\\    $$\\          $$$$$$\\ $$\\                           $$\\  $$\\    $$\\                    " << std::endl
            << "$$  __$$\\                            $$ |   \\__|        $$  __$$\\$$ |                          \\__| $$ |   $$ |                   " << std::endl
            << "$$ /  \\__|$$$$$$\\ $$$$$$$\\  $$$$$$\\$$$$$$\\  $$\\ $$$$$$$\\$$ /  $$ $$ |$$$$$$\\  $$$$$$\\  $$$$$$\\ $$\\$$$$$$\\  $$$$$$$\\ $$$$$$\\$$$$\\  " << std::endl
            << "$$ |$$$$\\$$  __$$\\$$  __$$\\$$  __$$\\_$$  _| $$ $$  _____$$$$$$$$ $$ $$  __$$\\$$  __$$\\$$  __$$\\$$ \\_$$  _| $$  __$$\\$$  _$$  _$$\\ " << std::endl
            << "$$ |\\_$$ $$$$$$$$ $$ |  $$ $$$$$$$$ |$$ |   $$ $$ /     $$  __$$ $$ $$ /  $$ $$ /  $$ $$ |  \\__$$ | $$ |   $$ |  $$ $$ / $$ / $$ |" << std::endl
            << "$$ |  $$ $$   ____$$ |  $$ $$   ____|$$ |$$\\$$ $$ |     $$ |  $$ $$ $$ |  $$ $$ |  $$ $$ |     $$ | $$ |$$\\$$ |  $$ $$ | $$ | $$ |" << std::endl
            << "\\$$$$$$  \\$$$$$$$\\$$ |  $$ \\$$$$$$$\\ \\$$$$  $$ \\$$$$$$$\\$$ |  $$ $$ \\$$$$$$$ \\$$$$$$  $$ |     $$ | \\$$$$  $$ |  $$ $$ | $$ | $$ |" << std::endl
            << " \\______/ \\_______\\__|  \\__|\\_______| \\____/\\__|\\_______\\__|  \\__\\__|\\____$$ |\\______/\\__|     \\__|  \\____/\\__|  \\__\\__| \\__| \\__|" << std::endl
            << "                                                                    $$\\   $$ |                                                    " << std::endl
            << "                                                                    \\$$$$$$  |                                                    " << std::endl
            << "                                                                     \\______/                           Formak21(c) version:" << ver << std::endl
            << "\n \n \n";
        std::cout << "Main Menu: \n* Input 0 to start GeneticAlgorithm   \n* Input 1 to exit";

        std::cout << "\n\n\nInput Number:";
        short unsigned int n;
        std::cin >> n;
        switch (n) {
        case 1:
        {
            return 0;
        }
        case 0:
            {
                std::cout << "\n\n* You must input Num of GeneticAlgorithms, Num of individs per GeneticAlgorithm, Num of lenght one indiv, populations per one geneticalgorithm, Mutation Regulator(NULLM/WEAK/AVERAGE/STRONG)(0/1/2/3).\n\n\nInput Numbers:";
                int m_r_t;
                std::cin >> ga_num >> ga_size >> indv_len >> popul_num >> m_r_t;
                switch (m_r_t){
                    case 0:
                        m_r = NULLM;
                        break;
                    case 1:
                        m_r = WEAK;
                        break;
                    case 2:
                        m_r = AVERAGE;
                        break;
                    case 3:
                        m_r = STRONG;
                        break;
                }
    std::vector< std::pair< int,int > > BestFS;
    std::vector<GeneticAlgorithm> GeneticAlgorithms;
    for(size_t i = 0; i < ga_num; i++){
        GeneticAlgorithm tmp(indv_len,ga_size,m_r);
        GeneticAlgorithms.push_back(tmp);
    }
    for(size_t i = 0; i < GeneticAlgorithms.size(); i++){
        size_t cycle=0;
        std::string tmpp = "NextAlgorithm";
        avg_qual_per_tick.prnt_txt(tmpp);
        best_qual_per_tick.prnt_txt(tmpp);
        worst_qual_per_tick.prnt_txt(tmpp);
        allbest_qual_per_tick.prnt_txt(tmpp);
        avg_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].avg_qual());
        best_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].best_qual());
        worst_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].worst_qual());
        allbest_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].best_qual_all);
        while(cycle < popul_num){
            GeneticAlgorithms[i].slctn();
            GeneticAlgorithms[i].crsgv();
            GeneticAlgorithms[i].mtt();
            cycle++;
            avg_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].avg_qual());
            best_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].best_qual());
            worst_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].worst_qual());
            allbest_qual_per_tick.add_data(cycle, GeneticAlgorithms[i].best_qual_all);
        }
        BestFS.push_back({indv_len, GeneticAlgorithms[i].best_qual_all});
    }
    double Forml = 0.0;
    for (size_t i = 0; i < BestFS.size(); i++) {
        Forml += double(std::abs(double(BestFS[i].second - BestFS[i].first))) / double(BestFS[i].second);
    }
    Forml /= double(BestFS.size());
    std::cout << "E=" << std::fixed << std::setprecision(128) << Forml;
                break;
            }
        }
    }
}
