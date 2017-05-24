#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>


struct Cell{
	int number;
	bool isSet;
	int row;
	int col;
	int box;
	int ID;
	std::vector<int> possible;
};

typedef std::multimap<int, int> boxMap;
typedef boxMap::iterator mapIter;




int ** createPuzzle();
void printPuzzle(int ** puzzle);
Cell *** setUpPuzzle(int ** puzzle);
void initialRunThrough(Cell *** &sudoku);
void nextRunThrough(Cell *** &sudoku);
void findPossibleValues(Cell *** &sudoku, int i, int j);
////bool checkUniquePossibilitiesCols(Cell *** &sudoku, int i, int j);
void checkUniquePossibilities(Cell *** &sudoku, int i, int j);

int addToBox(int number, int i, int j);
void printBox();
void printPossibilities(Cell *** sudoku);
int** makePrintablePuzzle(Cell *** sudoku);

bool visibleVectorContains(Cell *** sudoku, int boxNum, int value, int id, int row, int column);
bool boxContains(int boxNumber, int value);
bool rowContains(Cell *** sudoku, int value, int row);
bool columnContains(Cell *** sudoku, int value, int column);
void removeImpossibleValue(int* notPos, std::vector<int> &poss);

bool puzzleSolved(Cell *** sudoku);


//Setters
void setCellValue(Cell *** &sudoku, int row, int col);
