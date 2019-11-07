﻿//GENETICAL ALGORITHM
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
//Generates a random matrix of LineSym * ColumnSym values, in a one-dimensional vector.
std::vector<bool> RandomMatrix(int lineSym, int ColumnSym) {
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
vector<bool> MutationProc(vector<bool> temp) {
	int BreakMoment = rand() % 2;
	while (true) {
		if (BreakMoment == 1) {
			break;
	}
	int RandomElement = rand() % (temp.size()-1);
	temp[RandomElement] = rand() % 2 == 1 ? true : false;
	BreakMoment = rand() % 2;
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

int main() {
	//VERY IMPORTANT LINE, IT IS NECESSARY FOR THE RAND() FUNCTION TO WORK CORRECTLY.
	srand(time(0));
	

	//TestCode, no needed, delete if u want.
	//vector<bool> test;
	//int LineSym, ColumnSym, LineNum;
	//cin >> LineSym >> ColumnSym;
	//test = RandomMatrix(LineSym, ColumnSym);
	//PrintMatrix(test, LineSym);
	//cout << "\n";
	//cin >> LineNum;
	//PrintMatrix(MutationProc(GetLineFromMatrix(test, LineSym, LineNum)), LineSym);
	//End of TestCode

	//GeneticalAlgorithm
	vector<bool> FirstPop;
	FirstPop = RandomMatrix(6, 4);

	while (true) {
		vector<bool> BestLine1;
		vector<bool> BestLine2;
		int BestLine2NotDefault = -1;
		int MaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, 6, 1)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 3)), FitStatus(GetLineFromMatrix(FirstPop, 6, 4)))));
		int SecondMaxFitStatus = -1;

		if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, 1))) {
			SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, 6, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 3)), FitStatus(GetLineFromMatrix(FirstPop, 6, 4))));
			BestLine1 = GetLineFromMatrix(FirstPop, 6, 1);
			for (int i = 1; i <= 4; i++) {
				if (i == 1) {
					i++;
				}
				if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
					BestLine2 = GetLineFromMatrix(FirstPop, 6, i);
				}
			}
		}

		if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, 2))) {
			if (SecondMaxFitStatus != -1) {
				BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, 2) : BestLine1;
			}
			else {
				BestLine1 = GetLineFromMatrix(FirstPop, 6, 2);
			}

			SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, 6, 3)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 1)), FitStatus(GetLineFromMatrix(FirstPop, 6, 4))));

			for (int i = 1; i <= 4; i++) {
				if (i == 2) {
					i++;
				}
				if (BestLine2NotDefault == -1) {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = GetLineFromMatrix(FirstPop, 6, i);
						BestLine2NotDefault = 0;
					}
				}
				else {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, i) : BestLine2;
					}
				}
			}
		}

		if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, 3))) {

			if (SecondMaxFitStatus != -1) {
				BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, 3) : BestLine1;
			}
			else {
				BestLine1 = GetLineFromMatrix(FirstPop, 6, 3);
			}

			SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, 6, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 1)), FitStatus(GetLineFromMatrix(FirstPop, 6, 4))));

			for (int i = 1; i <= 4; i++) {
				if (i == 3) {
					i++;
				}
				if (BestLine2NotDefault == -1) {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = GetLineFromMatrix(FirstPop, 6, i);
						BestLine2NotDefault = 0;
					}
				}
				else {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, i) : BestLine2;
					}
				}
			}
		}

		if (MaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, 4))) {
			if (SecondMaxFitStatus != -1) {
				BestLine1 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, 4) : BestLine1;
			}
			else {
				BestLine1 = GetLineFromMatrix(FirstPop, 6, 4);
			}

			SecondMaxFitStatus = max(FitStatus(GetLineFromMatrix(FirstPop, 6, 2)), max(FitStatus(GetLineFromMatrix(FirstPop, 6, 1)), FitStatus(GetLineFromMatrix(FirstPop, 6, 3))));

			for (int i = 1; i <= 4; i++) {
				if (i == 4) {
					break;
				}
				if (BestLine2NotDefault == -1) {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = GetLineFromMatrix(FirstPop, 6, i);
						BestLine2NotDefault = 0;
					}
				}
				else {
					if (SecondMaxFitStatus == FitStatus(GetLineFromMatrix(FirstPop, 6, i))) {
						BestLine2 = rand() % 2 == 0 ? GetLineFromMatrix(FirstPop, 6, i) : BestLine2;
					}
				}
			}
		}
		vector<bool> temp1;
		for (int i = 0; i < 3; i++) {
			temp1.push_back(BestLine1[i]);
		}
		for (int i = 0; i < 3; i++) {
			BestLine1[i] = BestLine2[i];
		}
		for (int i = 0; i < 3; i++) {
			BestLine2[i] = temp1[i];
		}
		rand() % 2 == 0 ? BestLine1 = MutationProc(BestLine1) : BestLine2 = MutationProc(BestLine2);
		int TrueCounter1 = 0;
		int TrueCounter2 = 0;
		for (int i = 0; i < 6; i++) {
			if (BestLine1[i] = true) {
				TrueCounter1++;
			}
			if (BestLine2[i] = true) {
				TrueCounter2++;
			}
		}
		if (TrueCounter1 == 6 || TrueCounter2 == 6) {
			PrintMatrix(BestLine1, 6);
			cout << "\n";
			PrintMatrix(BestLine2, 6);
			cout << "\n";
			system("pause");
		}
		TrueCounter1 = 0;
		TrueCounter2 = 0;
		FirstPop.clear();
		FirstPop = RandomMatrix(6, 2);
		for (int i = 0; i < 6; i++) {
			FirstPop.push_back(BestLine1[i]);
		}
		for (int i = 0; i < 6; i++) {
			FirstPop.push_back(BestLine2[i]);
		}
		
	}
	system("pause");
	return 0;
}