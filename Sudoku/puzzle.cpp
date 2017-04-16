#include "sudoku.h"

int ** createPuzzle(){
	int **puzzle;
	int array[9][9] = {
		{0, 9, 0, 5, 0, 0, 0, 7, 8},
		{0, 6, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 4, 9, 3, 0, 6},
		{7, 0, 9, 0, 0, 8, 0, 0, 5},
		{0, 4, 8, 0, 2, 0, 6, 1, 0},
		{5, 0, 0, 3, 0, 0, 4, 0, 9},
		{6, 0, 5, 2, 7, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 7, 4, 0},
		{2, 7, 0, 0, 0, 1, 0, 6, 0}
	};

	puzzle = (int**)malloc(sizeof(int*)*9);
	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*)malloc(sizeof(int)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = array[i][j];
		}
	}

	return puzzle;
}

void printPuzzle(int** puzzle){
	printf("------------------------------\n" );
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(puzzle[i][j] != 0)
				printf(" %d ", puzzle[i][j]);
			else
				printf(" _ ");
			if((j+1)%3 == 0)
				printf("|");
		}
		printf("\n");
		if((i+1) % 3 == 0)
			printf("------------------------------\n" );
	}
}

Cell *** setUpPuzzle(int ** puzzle){
	
	

}