#include <stdio.h>
#include <stdlib.h>

typedef struct Cell{
	int number;
	bool isSet;
	int row;
	int col;
	int box;
	int *possible;
	int count;
};


int ** createPuzzle();
void printPuzzle(int ** puzzle);
Cell *** setUpPuzzle(int ** puzzle);
Cell *** initialRunThrough(Cell *** sudoku);
int * findPossibleValues(Cell *** sudoku, int i, int j);