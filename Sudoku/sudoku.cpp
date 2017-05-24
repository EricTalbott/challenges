#include "sudoku.h"

int main()
{
	int **puzzle = createPuzzle();
	Cell *** allCells;
	printPuzzle(puzzle);
	allCells = setUpPuzzle(puzzle);
	initialRunThrough(allCells);
	puzzle = makePrintablePuzzle(allCells);
	printPuzzle(puzzle);
	nextRunThrough(allCells);
	puzzle = makePrintablePuzzle(allCells);
	printPuzzle(puzzle);

	return 0;
}