//GENETICAL ALGORITHM
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
//Generates a random matrix of LineSym * ColumnSym values, in a one-dimensional vector.
vector<bool> RandomMatrix(int lineSym, int ColumnSym) {
	vector<bool> temp;
	for (int i = 0; i < lineSym * ColumnSym; i++) {
		temp.push_back(rand() % 2 == 1 ? true : false);
	}
	return temp;
}
//Outputs a matrix written in a one-dimensional vector, requires the number of values ​​in a line (LineSym).
void PrintMatrix(vector<bool> matrix, int lineSym) {
	int SymbolCounter = 0;
	for (int i = 0; i < matrix.size(); i++) {
		if (SymbolCounter == lineSym) {
			cout << "\n";
			SymbolCounter = 0;
		}
		SymbolCounter++;
		matrix[i] == true ? cout << "1" : cout << "0";
	}
}
//Cuts out a line (LineNum) from a matrix written in a one-dimensional vector, requires the number of values ​​in one line (LineSym).
vector<bool> GetLineFromMatrix(vector<bool> matrix, int lineSym, int LineNum) {
	vector<bool> temp;
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
vector<bool> MutationProc(vector<bool> temp, int Prob) {
	for (int i = 0; i < temp.size(); i++) {
		int RandPerc = rand() % 101;
		if (RandPerc <= Prob) {
			temp[i] == true ? temp[i] = false : temp[i] = true;
		}
	}
	return temp;

}
//Fit Status with best matrix-line(11111.. and etc.)
int FitStatus(vector<bool> Line) {
	int FitCounter=0;
	for (int i = 0; i < Line.size(); i++) {
		if (Line[i] == 1) {
			FitCounter++;
		}
	}
	return FitCounter;
}
//old BestLineSearch
/*vector<bool> BestLineSearch(vector<bool> FirstPop, int LineSymb, vector<bool> BestLine1 = {}) {
	vector<bool> BestLine2;

	int BestLine2NotDefault = -1;
	int MaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)), FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4)))));
	int SecondMaxFitStatus = -1;

	if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1))) {
		SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)), FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))));
		BestLine1 = GetLineFromMatrix(FirstPop, LineSymb, 1);
		for (int i = 1; i <= 4; i++) {
			if (i == 1) {
				i++;
			}
			if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
				BestLine2 = GetLineFromMatrix(FirstPop, LineSymb, i);
			}
		}
	}

	if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2))) {
		if (SecondMaxFitStatus != -1) {
			BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, 2) : BestLine1;
		}
		else {
			BestLine1 = GetLineFromMatrix(FirstPop, LineSymb, 2);
		}

		SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)), FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))));

		for (int i = 1; i <= 4; i++) {
			if (i == 2) {
				i++;
			}
			if (BestLine2NotDefault == -1) {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = GetLineFromMatrix(FirstPop, LineSymb, i);
					BestLine2NotDefault = 0;
				}
			}
			else {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, i) : BestLine2;
				}
			}
		}
	}

	if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3))) {

		if (SecondMaxFitStatus != -1) {
			BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, 3) : BestLine1;
		}
		else {
			BestLine1 = GetLineFromMatrix(FirstPop, LineSymb, 3);
		}

		SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)), FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))));

		for (int i = 1; i <= 4; i++) {
			if (i == 3) {
				i++;
			}
			if (BestLine2NotDefault == -1) {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = GetLineFromMatrix(FirstPop, LineSymb, i);
					BestLine2NotDefault = 0;
				}
			}
			else {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, i) : BestLine2;
				}
			}
		}
	}

	if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 4))) {
		if (SecondMaxFitStatus != -1) {
			BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, 4) : BestLine1;
		}
		else {
			BestLine1 = GetLineFromMatrix(FirstPop, LineSymb, 4);
		}

		SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 1)), FitStatus(GetLineFromMatrix(FirstPop, LineSymb, 3))));

		for (int i = 1; i <= 4; i++) {
			if (i == 4) {
				break;
			}
			if (BestLine2NotDefault == -1) {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = GetLineFromMatrix(FirstPop, LineSymb, i);
					BestLine2NotDefault = 0;
				}
			}
			else {
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, LineSymb, i))) {
					BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, LineSymb, i) : BestLine2;
				}
			}
		}
	}
	if (BestLine1.empty() == true) {
		return BestLine1;
	}
	else {
		return BestLine2;
	}
}*/
//this function getting bestlines from FirstPop 
vector<bool> BestLineSearch(vector<bool> FirstPop, int LineSymb, vector<bool> BestLine1 = {}) {
	vector<int> FitStatuses;
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
vector<bool> IdealLine(int LineSym) {
	vector<bool> IdealLine1(LineSym, true);
	return IdealLine1;
}

//Random Lines for comparing with algorithm
void RandomNumCheck(int LineSymb, int cycles = 0) {
	vector<bool> BackVec;
	if (cycles > 0) {
		for (long int i = 1; i <= cycles; i++) {
			for (int i = 0; i < LineSymb; i++) {
				rand() % 2 == 0 ? BackVec.push_back(true) : BackVec.push_back(false);
			}
			if (FitStatus(BackVec) == LineSymb) {
				cout << endl << "Cycles:" << i;
				return;
			}
			BackVec.clear();
		}
		cout << endl << "IdealLine not finded(" << cycles << ")";
	}
	else if (cycles == 0) {
		int i = 1;
		while (true) {
			for (long int i = 0; i < LineSymb; i++) {
				rand() % 2 == 0 ? BackVec.push_back(true) : BackVec.push_back(false);
			}
			if (FitStatus(BackVec) == LineSymb) {
				cout << endl << "Cycles:" << i;
				break;
			}
			BackVec.clear();
			i++;
			if (i > 2000000000) {
				cout << endl << "Not Finded. " << i;
			}
		}
	}
	else {
		cout << endl << "Error";
	}
}
//Genetical Algorithm
void GeneticalAlgorithm(int LineSymb, int MutationProb, int cycle, int cyclevariant) {
	int temp = cycle;
	int FindCounter = 0;
	cycle = 0;
	vector<bool> FirstPop = RandomMatrix(LineSymb, 4);
	vector<bool> BestLine1 = BestLineSearch(FirstPop, LineSymb);
	vector<bool> BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
	
	while (true) {
		if (cycle == temp && cyclevariant ==1 ) {
			if (FindCounter == 0) {
				cout << endl << "IdealLines Not Finded. FC:" << FindCounter << " cl:" << cycle;
			}
			return;
		}
		BestLine1.clear();
		BestLine2.clear();
		BestLine1 = BestLineSearch(FirstPop, LineSymb);
		BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
		vector<bool> temp1;
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
		if (BestLine1 == IdealLine(LineSymb) || BestLine2 == IdealLine(LineSymb)) {
			FindCounter++;
			cout << endl << "IdealLine Finded(" << cycle << ") FC:" << FindCounter << " cl:" << cycle;
			if (cyclevariant == -2 || cycle == 2100000000 ) {
				return;
			}
			if (cyclevariant == -1 || cyclevariant == 1) {
				continue;
			}
			if (cyclevariant== 0) {
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

int main() {
	//VERY IMPORTANT LINE, IT IS NECESSARY FOR THE RAND() FUNCTION TO WORK CORRECTLY.
	srand(time(0));
	//Menu
	/*Explanations of menu itemsand the like, have not yet been scribedand as well as
	the Answer-Lines(cout), either without a description or have grammatical errors, 
	this will be fixed in the next version.*/
	int MutationProb = 5;
	int LineSymb = 10;
	vector<bool> FirstPop = RandomMatrix(LineSymb, 4);
	vector<bool> BestLine1 = BestLineSearch(FirstPop, LineSymb);
	vector<bool> BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);


	while (true) {
		cout << "\nFormak21 2019 v1.0.0(GAMMA)" << "\n" << "\n" << "\n"
			<< "Here we have some func ->\n"
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
		cout << "Answer(ONLY 1-11):";
		cin >> answer;
		if (answer == 1) {
			FirstPop.clear();
			FirstPop = RandomMatrix(LineSymb, 4);
			cout << endl;
			cout << "First Population: \n";
			PrintMatrix(FirstPop, LineSymb);
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 2) {
			cout << endl;
			cout << "First Population: \n";
			PrintMatrix(FirstPop, LineSymb);
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 3) {
			BestLine1.clear();
			BestLine2.clear();
			BestLine1 = BestLineSearch(FirstPop, LineSymb);
			BestLine2 = BestLineSearch(FirstPop, LineSymb, BestLine1);
			cout << endl;
			cout << "BestLines: \n";
			PrintMatrix(BestLine1, LineSymb);
			cout << endl;
			PrintMatrix(BestLine2, LineSymb);
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 4) {
			vector<bool> temp1;
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

			cout << endl;
			cout << "BestLines Mutated: \n";
			PrintMatrix(BestLine1, LineSymb);
			cout << endl;
			PrintMatrix(BestLine2, LineSymb);
			cout << endl;
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
			cout << endl;
			cout << "Population with bestlines: \n";
			PrintMatrix(FirstPop, LineSymb);
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 6) {
			cout << endl << "Line lenght(BE CAREFUL, NOT INPUT ODD NUMBERS AND VERY BIG NUMBERS): ";
			cin >> LineSymb;
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 7) {
			cout << endl << "Mutation Prob(0-100): ";
			int temp2 = MutationProb;
			cin >> MutationProb;
			if (MutationProb > 100 && MutationProb < 0) {
				MutationProb = temp2;
				cout << "\nError\n";
			}
			cout << endl;
			system("pause");
			continue;
		}
		else if (answer == 8) {
			int cycle;
			cout << endl << "Cycles(0 for while true and reset, -1 for while true without reset, -2 while true for one idealline):";
			cin >> cycle;
			switch (cycle) {
				case -2:
					GeneticalAlgorithm(LineSymb, MutationProb, 0, -2);
					break;
				case -1:
					GeneticalAlgorithm(LineSymb, MutationProb, 0, -1);
					break;
				case 0:
					GeneticalAlgorithm(LineSymb, MutationProb, 0, 0);
					break;
				default:
					GeneticalAlgorithm(LineSymb, MutationProb, cycle, 1);
					break;
			}
		}
		else if (answer == 9) {
			int temp;
			cout << endl << "Cycles(if u not want use cycles, type 0):";
			cin >> temp;
			RandomNumCheck(LineSymb, temp);
			cout << endl;
			system("pause");
			continue;
		}
		else if(answer == 10) {
		cout << endl << "BestLines:"<< endl;
		PrintMatrix(BestLine1, LineSymb);
		cout << endl;
		PrintMatrix(BestLine2, LineSymb);
		cout << endl;
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