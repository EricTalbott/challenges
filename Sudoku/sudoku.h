#include <stdio.h>
#include <stdlib.h>

typedef struct Cell{
	int number;
	bool isSet;
	int row;
	int col;
	int box;
	int *possible;
};


int ** createPuzzle();
void printPuzzle(int** puzzle);
Cell *** setUpPuzzle(int ** puzzle);