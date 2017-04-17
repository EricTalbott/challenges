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

	Cell *** sudoku;

	sudoku = (Cell***)malloc(sizeof(Cell**)*9);
	for(int i = 0; i < 9; i++){
		sudoku[i] = (Cell**)malloc(sizeof(Cell*)*9);
		for(int j = 0; j < 9; j++){
			sudoku[i][j] = (Cell*)malloc(sizeof(Cell));

			sudoku[i][j]->number = puzzle[i][j];
			
			sudoku[i][j]->row = i;
			sudoku[i][j]->col = j;

			if(i < 3){
				if(j < 3)
					sudoku[i][j]->box = 0;
				else if(j < 6)
					sudoku[i][j]->box = 3;
				else
					sudoku[i][j]->box = 6;
			}
			else if(i < 6){
				if(j < 3)
					sudoku[i][j]->box = 1;
				else if(j < 6)
					sudoku[i][j]->box = 4;
				else
					sudoku[i][j]->box = 7;
			}
			else{
				if(j < 3)
					sudoku[i][j]->box = 2;
				else if(j < 6)
					sudoku[i][j]->box = 5;
				else
					sudoku[i][j]->box = 8;
			}
			
			if(sudoku[i][j]->number != 0)
				sudoku[i][j]->isSet = true;
			else
				sudoku[i][j]->isSet = false;

		}
	}

	return sudoku;
}

void initialRunThrough(Cell *** &sudoku){

	int ** puzzle; 

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if(!sudoku[i][j]->isSet){
				findPossibleValues(sudoku, i, j);	
			}

		}
	}

	puzzle = (int**)malloc(sizeof(int*)*9);
	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*)malloc(sizeof(int)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = sudoku[i][j]->number;
		}
	}


	printf("\n\n");
	
	printPuzzle(puzzle);


}

void findPossibleValues(Cell *** &sudoku, int i, int j){
	int notPos[9] = {0};
	int size = 0;

	//check each column
	for(int c = 0; c < 9; c++){
		if(sudoku[i][c]->isSet){
			bool inList = false;

			//assure number isn't already in notPos list
			for(int k = 0; k < size; k++){
				if(sudoku[i][c]->number == notPos[k]){
					inList = true;
				}
			}
			if(!inList){
				notPos[size] = sudoku[i][c]->number;
				size++;
			}
		}
	}

	//check each row
	for(int r = 0; r < 9; r++){
		if(sudoku[r][j]->isSet){
			bool inList = false;

			//assure number isn't already in notPos list
			for(int k = 0; k < size; k++){
				if(sudoku[r][j]->number == notPos[k]){
					inList = true;
				}
			}
			if(!inList){
				notPos[size] = sudoku[r][j]->number;
				size++;
			}
		}
	}
	
	//check each box
	for(int r = 0; r < 9; r++){

		for(int c = 0; c < 9; c++){

			if(sudoku[r][c]->box == sudoku[i][j]->box){

				if(sudoku[r][c]->isSet){
					bool inList = false;
					
					//assure number isn't already in notPos list
					for(int k = 0; k < size; k++){

						if(sudoku[r][c]->number == notPos[k]){
							inList = true;
						}
					}

					if(!inList){
						notPos[size] = sudoku[r][c]->number;
						size++;
					}

				}
			}
		}
	}

	int array[9] = {0};
	int arrSize = 0;

	for(int value = 1; value < 10; value++){
		bool hasVal = false;
		for(int k = 0; k < size; k++){
			if(value == notPos[k])
				hasVal = true;
		}
			
		if(!hasVal){
			array[arrSize] = value;
			arrSize++;
		}	

	}


	sudoku[i][j]->count = arrSize;
	if(sudoku[i][j]->count <= 1){
		sudoku[i][j]->number = array[0];
		sudoku[i][j]->isSet = true;
		return;
	}

	
	sudoku[i][j]->possible = (int*)malloc(sizeof(int)*arrSize);

	for(int num = 0; num < arrSize; num++){
		
		sudoku[i][j]->possible[num] = array[num];
		
	}


}

































