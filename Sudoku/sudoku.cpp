#include "sudoku.h"

int main()
{
	int **puzzle = createPuzzle();
	Cell *** allCells;
	printPuzzle(puzzle);
	allCells = setUpPuzzle(puzzle);
	initialRunThrough(allCells);


	return 0;
}