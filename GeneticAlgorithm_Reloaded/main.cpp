#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <utility>
#include <math.h>
#include <iomanip>
//Version
const std::string ver = "2.0.2A RELOADED";
std::vector< std::pair< int,int > > BestFS; // Lenght / fs
//This class is generating files with dot-coordinates for math-graph
class Graph {
private:
    //name of generated file
    std::string filename;
    //ofstream init
    std::ofstream opt;
public:
    //Constructor
    Graph(std::string temp) {
        //Filename
        filename = temp + ".txt";
        //Generating/Opening file with graph
        opt.open(filename, std::ofstream::app);
        //time and date var
        char timedate[128];
        _strtime_s(timedate, 128);
        //first line, it needed to check when, graph started, if file not empty
        opt << "\n#GA RELOADED " << ver << " GRAPH OPENED Time: " << timedate << " Date: ";
        _strdate_s(timedate, 128);
        opt << timedate << " " << filename << "#";
    }
    //Destructor
    ~Graph() {
        opt.close();
    }
    //Printing comments, in file
    void PrintText(std::string &text) {
        opt << "\n#" << text << "#";
        opt.flush();
    }
    //coordinates
    void addData(size_t &x, size_t &y) {
        opt << "\n(" << x << ", " << y << ")";
        opt.flush();

    }
};

//Initialization of two graph files
Graph AvgQualPerTick("AvgPerTick"); //Average quality, per every cycle, x-ticks, y-quality.
Graph BestQualPerTick("BestPerTick"); //Best quality, per every cycle, x-ticks, y-quality.
Graph BestQualAll("BestQualAll"); //Best quality, per all cycles, x-ticks, y-quality.
Graph LowQualPerTick("LowPerTick"); //Worst quality, per every cycle, x-ticks, y-quality.

//Individ Class
struct GenIndiv {
    std::vector<bool> Indv; //main vector of every indiv
    //Constructor
    GenIndiv(size_t LenTemp) {
        RandInd(LenTemp);
    }
    void RandInd(size_t LenTemp) {
        Indv.clear();
        for (size_t i = 0; i < LenTemp; i++) {
            Indv.push_back(rand() % 2 == 1 ? true : false);
        }
    }
    //This function returns individ quality
    size_t IndvQual() {
        size_t Temp = 0;
        for (size_t i = 0; i < Indv.size(); i++) {
            if (Indv[i] == true) {
                Temp++;
            }

        }
        return Temp;
    }
    //This Function can print the individ
    void PrintIndv() {
        for (size_t i = 0; i < Indv.size(); i++) {
            Indv[i] == true ? std::cout << "1" : std::cout << "0";
        }
    }
    //Mutation of individ
    void Mutation(size_t ProbTemp) {
        for (size_t i = 0; i < Indv.size(); i++) {
            size_t RandPerc = size_t((rand() % 101)) + 1;
            if (RandPerc <= ProbTemp) {
                Indv[i] == true ? Indv[i] = false : Indv[i] = true;
            }
        }
    }
};

//Genetic Algorithm Main Class
struct GeneticAlgorithm {
    //main vector
    std::vector<GenIndiv> Population;
    std::vector<GenIndiv> NextPopulation;
    //IndivLenght - size of every individ, MutatProb - Mutation probual, BestQual - Best Quality Counter of population
    size_t IndivLenght, MutatProb, BestQualA = 0, Cycles=0;
    //Constructor
    GeneticAlgorithm(size_t &TempLenght, size_t &TempNum, size_t &TempProb) {
        IndivLenght = TempLenght;
        MutatProb = TempProb;
        //Filling Population vector
        for (size_t i = 0; i < TempNum; i++) {
            GenIndiv Temp(IndivLenght);
            Population.push_back(Temp);
        }
        BestFS.push_back({ IndivLenght, 0 });

    }
    //Selection
    void Selection() {
        //this cycle is finding 2 parrents from 4 random individs
        for (size_t x = 0; x < 2; x++) {
            size_t RandID[2] = { rand() % Population.size(),rand() % Population.size() };
            if (Population[RandID[0]].IndvQual() > Population[RandID[1]].IndvQual()) {
                NextPopulation.push_back(Population[RandID[0]]);
            }
            else if (Population[RandID[1]].IndvQual() > Population[RandID[0]].IndvQual()) {
                NextPopulation.push_back(Population[RandID[1]]);
            }
            else {
                rand() % 2 == 0 ? NextPopulation.push_back(Population[RandID[0]]) : NextPopulation.push_back(Population[RandID[0]]);
            }
        }
    }
    //Crossover
    void Crossover() {
        //writing in first parrent elements from second before random element, and in second first from random element, and deleting first/second(random)
        size_t r = rand() % IndivLenght;
        for (size_t x = 0; x < r; x++) {
            NextPopulation[NextPopulation.size()-2].Indv[x] = NextPopulation[NextPopulation.size()-1].Indv[x];
        }
        for (size_t x = r; x < IndivLenght; x++) {
            NextPopulation[NextPopulation.size()-1].Indv[x] = NextPopulation[NextPopulation.size() - 2].Indv[x];
        }
        if (rand() % 2 == 0) {
            NextPopulation.erase(NextPopulation.end()-1);
        }
        else {
            NextPopulation[NextPopulation.size() - 2] = NextPopulation[NextPopulation.size()-1];
            NextPopulation.erase(NextPopulation.end()-1);
        }
    }
    //Mutation, calls mutation func in every element
    void Mutation() {
        for (size_t i = 0; i < Population.size(); i++) {
            Population[i].Mutation(MutatProb);
        }
    }
    void AddData(short unsigned int param, size_t Cycle, std::string text="") {
        size_t tempp = 0;
        switch(param) {
        case 0:
            tempp = Population[0].IndvQual();
            for (size_t i = 1; i < Population.size(); i++) {
                if (tempp > Population[i].IndvQual()) {
                    tempp = Population[i].IndvQual();
                }
            }
            LowQualPerTick.addData(Cycle, tempp);
            break;
        case 1:
            tempp = 0;
            for (size_t i = 0; i < Population.size(); i++) {
                if (tempp < Population[i].IndvQual()) {
                    tempp = Population[i].IndvQual();
                }
            }

            BestQualPerTick.addData(Cycle,tempp);
            break;
        case 2:
            tempp = 0;
            for (size_t i = 0; i < Population.size(); i++) {
                if (tempp < Population[i].IndvQual()) {
                    tempp = Population[i].IndvQual();
                }
            }
            if (tempp > BestQualA) {
                BestQualA = tempp;
            }
            BestFS.back() = { IndivLenght, BestQualA };
            BestQualAll.addData(Cycle,BestQualA);
            break;
        case 3:
            tempp = 0;
            for (size_t i = 0; i < Population.size(); i++) {
                tempp += Population[i].IndvQual();
            }
            tempp/=Population.size();
            AvgQualPerTick.addData(Cycle, tempp);
            break;
        case 4:
            AvgQualPerTick.PrintText(text);
            BestQualPerTick.PrintText(text);
            BestQualAll.PrintText(text);
            LowQualPerTick.PrintText(text);
            break;
        }
    }
    void ResetInit(size_t TempNum) {
        AddData(4, 0, "RESET");
        BestQualA = 0;
        Cycles = 0;
        Population.clear();
        for (size_t i = 0; i < TempNum; i++) {
            GenIndiv Temp(IndivLenght);
            Population.push_back(Temp);
        }
    }
    void FullCycle(){
        for (size_t i = 0; i < Population.size(); i++) {
            Selection();
            Crossover();
        }
        Population.clear();
        Population = NextPopulation;
        NextPopulation.clear();
        Mutation();
        Cycles++;
        AddData(0, Cycles);
        AddData(1, Cycles);
        AddData(2, Cycles);
        AddData(3, Cycles);

    }
    void PrintMatrix() {
        for (size_t i = 0; i < Population.size(); i++) {
            Population[i].PrintIndv();
            std::cout << std::endl;
        }
    }
};
void GenAlgProc(size_t &IndivNum, size_t &IndivLenght, size_t &MutationProb, size_t &Cycles) {
    GeneticAlgorithm Temp(IndivLenght, IndivNum, MutationProb);
    Temp.AddData(4, 0, "GENETICAL ALGORITHM STANDART FUNCTION");
    std::cout << "\n";
    for (size_t i = 1; i <= Cycles; i++){
        std::cout << "Cycle:" << i;
        Temp.FullCycle();
        std::cout << "\r";
    }
    std::cout << "\nG.A. Stoped, returns to Main Menu..." << "\n\n\n";
}

int TranslatorDtoT(std::vector<bool> &temp, bool param=true){
    int answer=0;
    if (!param){
        std::reverse( temp.begin(), temp.end() );
    }
    for (size_t i = 0; i < temp.size(); i++){
            if (temp[i])
                answer=answer+(1<<int(temp.size()-i));
            else
                continue;
   }
   return answer;
}

int main() {
    system("color 02");
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
        std::cout << "Main Menu: \n* Input 0 to start GeneticAlgorithm  \n* Input 1 to Random(not done yet)  \n* Input 2 to find errors \n* Input 3 to exit";

        std::cout << "\n\n\nInput Number:";
        short unsigned int n;
        std::cin >> n;
        switch (n) {
        case 3:
            return 0;
            break;
        case 1:
            std::cout << "\nNot Done Yet :P\n";
            break;
        case 2:
        {
            double Forml = 0.0;
            for (size_t i = 0; i < BestFS.size(); i++) {
                Forml += double(std::abs(double(BestFS[i].second - BestFS[i].first))) / double(BestFS[i].second);
            }
            Forml /= double(BestFS.size());
            std::cout << std::fixed << std::setprecision(256) << Forml;
            break;
        }
        case 0:
            size_t TempNum, TempLenght, TempProb, TempCycles;
            std::cout << "\n\n* You must input number of lines, lenght of individ, MutationProb(0-100), Cycles(cycles>=0)\n\n\nInput Numbers:";
            std::cin >> TempNum >> TempLenght >> TempProb >> TempCycles;
            GenAlgProc(TempNum, TempLenght, TempProb, TempCycles);
            break;
        }
    }
}
