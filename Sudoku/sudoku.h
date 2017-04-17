#include <stdio.h>
#include <stdlib.h>

struct Cell{
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
void initialRunThrough(Cell *** &sudoku);
void findPossibleValues(Cell *** &sudoku, int i, int j);