//GENETICAL ALGORITHM
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <thread>
#include <time.h>

const std::string version = "1.1.0";

class Graph {
private:
	std::string filename;
	std::ofstream output;
public:
	Graph(std::string filename1) {
		filename1 += ".txt";
		filename = filename1;
		output.open(filename, std::ofstream::app);
		char timedate[128];
		_strtime_s(timedate, 128);
		output << "#G.A. " << version << " GRAPH STARTED Time: " << timedate << " Date: ";
		_strdate_s(timedate, 128);
		output << timedate << " " << filename << "#";
	}
	~Graph() {
		output.close();
	}
	void funcinit(std::string funcname) {
		output << "\n#" << funcname << "#\n";
	}
	void addData(int x, int y) {
		output << "(" << x << ", " << y << ")\n";

	}
};

Graph FitStatPerTick("FitStatPerTick");
Graph BestLinePerTick("BestLine");
//Generates a random matrix of LineSym * ColumnSym values, in a one-dimensional vector.
std::vector<bool> RandomMatrix(int lineSym, int ColumnSym) {
	std::vector<bool> temp;
	for (int i = 0; i < lineSym * ColumnSym; i++) {
		temp.push_back(rand() % 2 == 1 ? true : false);
	}
	return temp;
}
//Outputs a matrix written in a one-dimensional vector, requires the number of values ​​in a line (LineSym).
void PrintMatrix(std::vector<bool> matrix, int lineSym) {
	int SymbolCounter = 0;
	for (int i = 0; i < matrix.size(); i++) {
		if (SymbolCounter == lineSym) {
			std::cout << "\n";
			SymbolCounter = 0;
		}
		SymbolCounter++;
		matrix[i] == true ? std::cout << "1" : std::cout << "0";
	}
}
//Cuts out a line (LineNum) from a matrix written in a one-dimensional vector, requires the number of values ​​in one line (LineSym).
std::vector<bool> GetLineFromMatrix(std::vector<bool> matrix, int lineSym, int LineNum) {
	std::vector<bool> temp;
	int SymbolCounter = 0;
	int LineCounter = 1;
	for (int i = 0; i < matrix.size(); i++) {
		if (SymbolCounter == lineSym) {
			SymbolCounter = 0;
			LineCounter++;
		}
		if (LineCounter == LineNum) {
			temp.push_back(matrix[i]);
		}
		SymbolCounter++;
	}

	return temp;
}
//Random Mutation of line
std::vector<bool> MutationProc(std::vector<bool> temp, int Prob) {
	for (int i = 0; i < temp.size(); i++) {
		int RandPerc = rand() % 101;
		if (RandPerc <= Prob) {
			temp[i] == true ? temp[i] = false : temp[i] = true;
		}
	}
	return temp;

}
//Fit Status with best matrix-line(11111.. and etc.)
int FitStatus(std::vector<bool> Line) {
	int FitCounter=0;
	for (int i = 0; i < Line.size(); i++) {
		if (Line[i] == 1) {
			FitCounter++;
		}
	}
	return FitCounter;
}

//this function getting bestlines from FirstPop 
std::vector<bool> BestLineSearch(std::vector<bool> FirstPop, int LineSymb, std::vector<bool> BestLine1 = {}) {
	std::vector<int> FitStatuses;
	FitStatuses.push_back(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)));
	FitStatuses.push_back(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)));
	FitStatuses.push_back(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)));
	FitStatuses.push_back(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4)));
	FitStatuses.push_back(0);
	while (true) {
		for (int i = 1; i < 4; i++) {
			if (FitStatuses[i] > FitStatuses[FitStatuses[4]]) {
				FitStatuses[4] = i;
			}
			else if (FitStatuses[FitStatuses[4]] > FitStatuses[i]) {
				continue;
			}
			else {
				if (rand() % 2 == 1) { FitStatuses[4] = i; }

			}

		}
		if (!BestLine1.empty()) {
			if (BestLine1 != GetLineFromMatrix(FirstPop, LineSymb, FitStatuses[4] + 1)) {
				return GetLineFromMatrix(FirstPop, LineSymb, FitStatuses[4] + 1);
			}
			else {
				FitStatuses[FitStatuses[4]] = -1;
				FitStatuses[4] = 0;
			}
		}
		else {
			return GetLineFromMatrix(FirstPop, LineSymb, FitStatuses[4] + 1);
		}
	}

}
//IdealLine 1111111.. and etc, has a max FitStatus
std::vector<bool> IdealLine(int LineSym) {
	std::vector<bool> IdealLine1(LineSym, true);
	return IdealLine1;
}

//Random Lines for comparing with algorithm
void RandomNumCheck(int LineSymb, int cycles = 0) {
	std::vector<bool> BackVec;
	if (cycles > 0) {
		for (long int i = 1; i <= cycles; i++) {
			for (int i = 0; i < LineSymb; i++) {
				rand() % 2 == 0 ? BackVec.push_back(true) : BackVec.push_back(false);
			}
			if (FitStatus(BackVec) == LineSymb) {
				std::cout << std::endl << "Cycles:" << i;
				return;
			}
			BackVec.clear();
		}
		std::cout << std::endl << "IdealLine not finded(" << cycles << ")";
	}
	else if (cycles == 0) {
		int i = 1;
		while (true) {
			for (long int i = 0; i < LineSymb; i++) {
				rand() % 2 == 0 ? BackVec.push_back(true) : BackVec.push_back(false);
			}
			if (FitStatus(BackVec) == LineSymb) {
				std::cout << std::endl << "Cycles:" << i;
				break;
			}
			BackVec.clear();
			i++;
			if (i > 2000000000) {
				std::cout << std::endl << "Not Finded. " << i;
			}
		}
	}
	else {
		std::cout << std::endl << "Error";
	}
}
//Genetical Algorithm
void GeneticalAlgorithm(int LineSymb, int MutationProb, int cycle, int cyclevariant) {
	int temp = cycle;
	int FindCounter = 0;
	cycle = 0;

	std::vector<bool> FirstPop = RandomMatrix(LineSymb, 4);
	std::vector<bool> BestLine1 = BestLineSearch(FirstPop, LineSymb);
	std::vector<bool> BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
	int BestFitStatus=0;
	while (true) {
		FitStatPerTick.addData(cycle, (FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))) / 4);
		if (cycle == temp ) {
			if (cyclevariant == 3 || cyclevariant == 1) {
				if (FindCounter == 0) {
					std::cout << std::endl << "IdealLines Not Finded. FC:" << FindCounter << " cl:" << cycle;
				}
				return;
			}
		}
		BestLine1.clear();
		BestLine2.clear();
		BestLine1 = BestLineSearch(FirstPop, LineSymb);
		BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
		std::vector<bool> temp1;
		for (int i = 0; i < (LineSymb / 2); i++) {
			temp1.push_back(BestLine1[i]);
		}
		for (int i = 0; i < (LineSymb / 2); i++) {
			BestLine1[i] = BestLine2[i];
		}
		for (int i = 0; i < (LineSymb / 2); i++) {
			BestLine2[i] = temp1[i];
		}
		rand() % 2 == 0 ? BestLine1 = MutationProc(BestLine1, MutationProb) : BestLine2 = MutationProc(BestLine2, MutationProb);
		if (FitStatus(BestLine1) > BestFitStatus) {
			BestLinePerTick.addData(cycle, FitStatus(BestLine1));
			BestFitStatus = FitStatus(BestLine1);
		}
		else {
			BestLinePerTick.addData(cycle, BestFitStatus);
		}
		if (BestLine1 == IdealLine(LineSymb) || BestLine2 == IdealLine(LineSymb)) {
			FindCounter++;
			std::cout << std::endl << "IdealLine Finded(" << cycle << ")";
			if (cyclevariant == -2 || cycle == 2100000000 ) {
				FitStatPerTick.addData(cycle, (FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)) + FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))) / 4);
				
				return;
			}
			if (cyclevariant == -1 || cyclevariant == 1) {
				
				continue;
			}
			if (cyclevariant== 0 || cyclevariant == 3) {
				BestLinePerTick.funcinit("\n#RESET#\n");
				BestFitStatus = 0;
				FirstPop.clear();
				FirstPop = RandomMatrix(LineSymb, 4);
				BestLine1.clear();
				BestLine2.clear();
				BestLine1 = BestLineSearch(FirstPop, LineSymb);
				BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
				continue;
			}

		}
		FirstPop.clear();
		FirstPop = RandomMatrix(LineSymb, 2);
		for (int i = 0; i < LineSymb; i++) {
			FirstPop.push_back(BestLine1[i]);
		}
		for (int i = 0; i < LineSymb; i++) {
			FirstPop.push_back(BestLine2[i]);
		}
		cycle++;
	}
}

class GeneticIndiv {
public:
	std::vector<bool>indiv;
	int FitNum=0;
	int MutProb;
	GeneticIndiv(int LineSym, int Prob) {
		indiv = RandomMatrix(LineSym, 1);
		MutProb = Prob;
		FitNumber();
		Lenght();

	}
	int FitNumber() {
		FitNum=0;
		for (int i = 0; i < indiv.size(); i++) {
			if (indiv[i] == true) {
				FitNum++;
			}

		}
		return FitNum;
	}
	size_t Lenght() {
		//GUARD
		if (indiv.size() % 2 != 0) {
			if (rand() % 2 == 0) {
				indiv.push_back(false);
			}
			else {
				indiv.push_back(true);
			}
			FitNumber();
		}
		return indiv.size();
	}
	bool FitStatus(){
		FitNumber();
		if (indiv.size() == FitNum) {
			return true;
		}
		else
		{
			return false;
		}
	}
	void Mutation() {
		for (int i = 0; i < indiv.size(); i++) {
			int RandPerc = (rand() % 101) + 1;
			if (RandPerc <= MutProb) {
				indiv[i] == true ? indiv[i] = false : indiv[i] = true;
			}
		}
		FitNumber();
	}
	void indivUpdate(std::vector<bool>UpdateVec) {
		indiv.clear();
		indiv.reserve(UpdateVec.size());
		indiv = UpdateVec;
		Lenght();
		FitNumber();
	}
	std::vector<bool>indivHalf(std::vector<bool> Half = {}) {
		std::vector<bool> OldHalf;
		for (int i = Lenght()/2-1; i < Lenght(); i++ ){
			OldHalf.push_back(indiv[i]);
			if (Half.empty() == false) {
				indiv[i] = Half[i - (Lenght() / 2 - 1)];
			}
		}
		return OldHalf;
	}
};
class GeneticAlg {
public:
	std::vector<GeneticIndiv> Population;
	int IndivLenght;
	int IndivNum;
	int MutationProb;
	int cycles=1;
	GeneticAlg(int LineSymb, int indivNum, int MutatProb ) {
		IndivLenght = LineSymb;
		IndivNum = indivNum;
		MutationProb = MutatProb;
		Guard(true);
		for (int i = 0; i < IndivNum; i++) {
			GeneticIndiv Temp(IndivLenght, MutationProb);
			Population.push_back(Temp);

		}
		Guard();
	}
	void Guard(bool param = false) {
		if (param == false) {
			DataUpdate();
		}
		if (IndivLenght % 2 != 0) {
			IndivLenght++;
			if (param == false) {
				GeneticIndiv Temp(IndivLenght, MutationProb);
				Population.push_back(Temp);
			}
		}
		if (IndivNum % 2 != 0) {
			if (param == false) {
				for (int i = 0; i < IndivNum; i++) {
					Population[i].Lenght();
				}
			}
			IndivNum++;
		}
		if (param == false) {
			DataUpdate();
		}
	}
	void DataUpdate() {
		IndivNum = Population.size();
		for (int i = 0; i < IndivNum; i++) {
			if (IndivNum < Population[i].Lenght()) {
				IndivNum = Population[i].Lenght();
			}
		}
		for (int i = 0; i < IndivNum; i++) {
			if (Population[i].Lenght() != IndivLenght) {
				Population[i].indivUpdate(RandomMatrix(IndivLenght, 1));
				DataUpdate();
			}
		}
	}
	void addData(int type=0) {
		Guard();
		if (type == 0) {
			int centr;
			for (int i = 0; i < IndivNum; i++) {
				centr += Population[i].FitNumber();
			}
			//CHECK THIS LINE.
			centr = centr / IndivNum;

			FitStatPerTick.addData(cycles, centr);
		}
	
	}


};






int main() {
	//VERY IMPORTANT LINE, IT IS NECESSARY FOR THE RAND() FUNCTION TO WORK CORRECTLY.
	srand(time(0));
	//For correct time work
	_tzset();
	//Menu
	/*Explanations of menu itemsand the like, have not yet been scribedand as well as
	the Answer-Lines(cout), either without a description or have grammatical errors, 
	this will be fixed in the next version.*/
	

	int MutationProb = 5;
	int LineSymb = 10;
	std::vector<bool> FirstPop = RandomMatrix(LineSymb, 4);
	std::vector<bool> BestLine1 = BestLineSearch(FirstPop, LineSymb);
	std::vector<bool> BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);

	while (true) {
		std::cout << "\nFormak21 2020 " << version << "\n" << "\n" << "\n"
			<< "Main Menu ->\n"
			<< "\n" << "\n"
			<< " 1 to Generate New First Population \n"
			<< " 2 To display First Population \n"
			<< " 3 to Get BestLines From current population \n"
			<< " 4 to BestLine Mutation\n"
			<< " 5 to include bestline in new First Population\n"
			<< " 6 to set line length \n"
			<< " 7 to set mutation prob\n"
			<< " 8 to auto\n"
			<< " 9 to random\n"
			<< " 10 to display BestLines\n"
			<< " 11 to exit\n"
			<< "\n" << "\n" << "\n" << "\n"	
			<< "\n" << "\n" << "\n" << "\n";
		int answer;
		std::cout << "Answer(ONLY 1-11):";
		std::cin >> answer;
		if (answer == 1) {
			FirstPop.clear();
			FirstPop = RandomMatrix(LineSymb, 4);
			std::cout << std::endl;
			std::cout << "First Population: \n";
			PrintMatrix(FirstPop, LineSymb);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 2) {
			std::cout << std::endl;
			std::cout << "First Population: \n";
			PrintMatrix(FirstPop, LineSymb);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 3) {
			BestLine1.clear();
			BestLine2.clear();
			BestLine1 = BestLineSearch(FirstPop, LineSymb);
			BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
			std::cout << std::endl;
			std::cout << "BestLines: \n";
			PrintMatrix(BestLine1, LineSymb);
			std::cout << std::endl;
			PrintMatrix(BestLine2, LineSymb);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 4) {
			std::vector<bool> temp1;
			for (int i = 0; i < (LineSymb / 2); i++) {
				temp1.push_back(BestLine1[i]);
			}
			for (int i = 0; i < (LineSymb / 2); i++) {
				BestLine1[i] = BestLine2[i];
			}
			for (int i = 0; i < (LineSymb / 2); i++) {
				BestLine2[i] = temp1[i];
			}
			rand() % 2 == 0 ? BestLine1 = MutationProc(BestLine1, MutationProb) : BestLine2 = MutationProc(BestLine2, MutationProb);

			std::cout << std::endl;
			std::cout << "BestLines Mutated: \n";
			PrintMatrix(BestLine1, LineSymb);
			std::cout << std::endl;
			PrintMatrix(BestLine2, LineSymb);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 5) {
			FirstPop.clear();
			FirstPop = RandomMatrix(LineSymb, 2);
			for (int i = 0; i < LineSymb; i++) {
				FirstPop.push_back(BestLine1[i]);
			}
			for (int i = 0; i < LineSymb; i++) {
				FirstPop.push_back(BestLine2[i]);
			}
			std::cout << std::endl;
			std::cout << "Population with bestlines: \n";
			PrintMatrix(FirstPop, LineSymb);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 6) {
			std::cout << std::endl << "Line lenght(BE CAREFUL, NOT INPUT ODD NUMBERS AND VERY BIG NUMBERS): ";
			std::cin >> LineSymb;
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 7) {
			std::cout << std::endl << "Mutation Prob(0-100): ";
			int temp2 = MutationProb;
			std::cin >> MutationProb;
			if (MutationProb > 100 && MutationProb < 0) {
				MutationProb = temp2;
				std::cout << "\nError\n";
			}
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if (answer == 8) {
			int cycle;
			std::cout << std::endl << "Cycles(0 for while true and reset, -1 for while true without reset, -2 while true for one idealline):";
			std::cin >> cycle;
			switch (cycle) {
				case -2:
					FitStatPerTick.funcinit("GeneticalAlgorithmType-2");
					BestLinePerTick.funcinit("GeneticalAlgorithmType-2");
					GeneticalAlgorithm(LineSymb, MutationProb, 0, -2);
					break;
				case -1:
					FitStatPerTick.funcinit("GeneticalAlgorithmType-1");
					BestLinePerTick.funcinit("GeneticalAlgorithmType-1");
					GeneticalAlgorithm(LineSymb, MutationProb, 0, -1);
					break;
				case 0:
					FitStatPerTick.funcinit("GeneticalAlgorithmType0");
					BestLinePerTick.funcinit("GeneticalAlgorithmType0");
					GeneticalAlgorithm(LineSymb, MutationProb, 0, 0);
					break;
				default:
					int modec;
					std::cout << std::endl << "with reset or without? 3/1" << std::endl;
					std::cin >> modec;
					FitStatPerTick.funcinit("GeneticalAlgorithmType1, " + modec);
					BestLinePerTick.funcinit("GeneticalAlgorithmType1, " + modec);
					GeneticalAlgorithm(LineSymb, MutationProb, cycle, modec);
					break;
			}
		}
		else if (answer == 9) {
			int temp;
			std::cout << std::endl << "Cycles(if u not want use cycles, type 0):";
			std::cin >> temp;
			RandomNumCheck(LineSymb, temp);
			std::cout << std::endl;
			system("pause");
			continue;
		}
		else if(answer == 10) {
		std::cout << std::endl << "BestLines:"<< std::endl;
		PrintMatrix(BestLine1, LineSymb);
		std::cout << std::endl;
		PrintMatrix(BestLine2, LineSymb);
		std::cout << std::endl;
		system("pause");
		continue;
		}
		else if(answer == 11) {
		return 0;
		}
		else { continue; }
	}
	return 0;
}