#include "sudoku.h"


boxMap box;

int ** createPuzzle(){
	int **puzzle;
	int array[9][9] = {
		{8, 0, 0, 0, 0, 5, 0, 0, 0},
		{0, 7, 0, 0, 1, 0, 0, 0, 9},
		{0, 0, 1, 3, 0, 0, 5, 0, 0},
		{4, 0, 0, 5, 0, 8, 0, 0, 7},
		{6, 0, 0, 0, 2, 0, 0, 0, 8},
		{5, 0, 0, 4, 0, 1, 0, 0, 3},
		{0, 0, 8, 0, 0, 4, 6, 0, 0},
		{2, 0, 0, 0, 7, 0, 0, 8, 0},
		{0, 0, 0, 8, 0, 0, 0, 0, 5}
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
	int id = 0;
	sudoku = (Cell***)malloc(sizeof(Cell**)*9);
	for(int i = 0; i < 9; i++){
		sudoku[i] = (Cell**)malloc(sizeof(Cell*)*9);
		for(int j = 0; j < 9; j++){
			sudoku[i][j] = (Cell*)malloc(sizeof(Cell));

			sudoku[i][j]->number = puzzle[i][j];
			
			sudoku[i][j]->row = i;
			sudoku[i][j]->col = j;
			sudoku[i][j]->ID = id;
			id++;

			sudoku[i][j]->box = addToBox(puzzle[i][j], i, j);
		
			
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
	bool newValueSet;

	do{ 

		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					findPossibleValues(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->possible.size() == 1){
						setCellValue(sudoku, i, j);	
						newValueSet = true;
					}
				}
			}
		}

		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);

}


void nextRunThrough(Cell *** &sudoku){

	int ** puzzle; 
	bool newValueSet;

	do{ 
		newValueSet = false;

		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					checkUniquePossibilities(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->possible.size() == 1){
						setCellValue(sudoku, i, j);	
						newValueSet = true;
					}
				}
			}
		}

		if(newValueSet){
			initialRunThrough(sudoku);
		}
		if(puzzleSolved(sudoku)) break;


	}while(newValueSet);

}


void findPossibleValues(Cell *** &sudoku, int row, int col){
	int notPos[9] = {-1};
	int boxNum = sudoku[row][col]->box;

	//Check if value is contained in "visible" cell
	for(int val = 1; val <= 9; val++){
		if(columnContains(sudoku, val, col) || rowContains(sudoku, val, row) || boxContains(boxNum, val)){
			notPos[val-1] = val;
		}
	}

	//If first time visiting cell, populate possible values
	//Else remove impossible values
	if(sudoku[row][col]->possible.size() == 0){
		for(int value = 1; value <= 9; value++){
			if(!(value == notPos[value-1]))
				sudoku[row][col]->possible.push_back(value);
		}
	}else
		removeImpossibleValue(notPos, sudoku[row][col]->possible);
	
}

void checkUniquePossibilities(Cell *** &sudoku, int row, int col){
	int boxNum, value, id;
	std::vector<int>::iterator it;
	std::vector<int> possVector;

	boxNum = sudoku[row][col]->box;
	possVector = sudoku[row][col]->possible;
	id = sudoku[row][col]->ID;

  	for (it = possVector.begin() ; it != possVector.end(); ++it){
    	value = (*it);
    	if(!(visibleVectorContains(sudoku, boxNum, value, id, row, col))){
    		sudoku[row][col]->possible.clear();
    		sudoku[row][col]->possible.push_back(value);
    	}
  	}
}

/*
void checkUniquePossibilitiesRows(Cell *** &sudoku, int i, int j){

	bool isUnique = false;
	int arrSize = 0;

	for(int c = 0; c < 9; c++){
		if(!sudoku[i][c]->isSet && c != j){
			arrSize += sudoku[i][c]->count;
		}
	}

	int array[arrSize];
	int index = 0;

	for(int c = 0; c < 9; c++){
		if(!sudoku[i][c]->isSet && c != j){
			for(int x = 0; x < sudoku[i][c]->count; x++){
				array[index] = sudoku[i][c]->possible[x];
				index++;
			}
		}
	}

	index = 0;
	for(int x = 0; x < arrSize; x++){
		
		if(sudoku[i][j]->possible[index] == array[x]){
			index++;
			if(index == sudoku[i][j]->count){
				//return false;
			}
			x = -1;
			continue;
		}

		sudoku[i][j]->number = sudoku[i][j]->possible[index];
		sudoku[i][j]->isSet = true;
		newValueSet = true;
		
	}
}*/





int** makePrintablePuzzle(Cell *** sudoku){
	int ** puzzle = (int**)malloc(sizeof(int*)*9);
	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*)malloc(sizeof(int)*9);
		for(int j = 0; j < 9; j++){
			puzzle[i][j] = sudoku[i][j]->number;
		}
	}
	return puzzle;
}

int addToBox(int number, int i, int j){
	if(i < 3){
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(0,number));
			return 0;
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(1,number));
			return 1;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(2,number));
			return 2;
		}
	}else if(i < 6){
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(3,number));
			return 3;	
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(4,number));
			return 4;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(5,number));
			return 5;
		}
	}else{
		if(j < 3){
			if(number != 0)
				box.insert(std::pair<int, int>(6,number));
			return 6;
		}else if(j < 6){
			if(number != 0)
				box.insert(std::pair<int, int>(7,number));
			return 7;
		}else{
			if(number != 0)
				box.insert(std::pair<int, int>(8,number));
			return 8;
		}
	}	
}

//Return True if a given value is contained in a given "box". Returns false if not.
bool visibleVectorContains(Cell *** sudoku, int boxNum, int value, int id, int row, int column){
	std::vector<int>::iterator it;
	std::vector<int> possVector;

	for(int rw = 0; rw < 9; rw++){
		for (int col = 0; col < 9; col++){
			if( (rw == row || column == col || sudoku[row][col]->box == boxNum) && 
			   !(sudoku[row][col]->isSet) && (sudoku[row][col]->ID != id)){

				possVector = sudoku[rw][col]->possible;
				for (it = possVector.begin() ; it != possVector.end(); ++it){
    				if(value == (*it)) return true;
  				}
			}
		}
	}
	return false;
}

bool boxContains(int boxNumber, int value){
	mapIter it;

	std::pair<mapIter, mapIter> keyRange = box.equal_range(boxNumber);
	for(it = keyRange.first; it != keyRange.second; it++){
		if(value == (*it).second) return true;
	}

	return false;

}

//Return True if a given value is contained in a given row. Returns false if not.
bool rowContains(Cell *** sudoku, int value, int row){

	int checkVal;
	for(int c = 0; c < 9; c++){
		if(sudoku[row][c]->isSet){
			checkVal = sudoku[row][c]->number;
			if(checkVal == value) return true;
		}
	}
	return false;	

}

//Return True if a given value is contained in a given column. Returns false if not.
bool columnContains(Cell *** sudoku, int value, int column){

	int checkVal;
	for(int r = 0; r < 9; r++){
		if(sudoku[r][column]->isSet){
			checkVal = sudoku[r][column]->number;
			if(checkVal == value) return true;
		}
	}
	return false;	
}

void setCellValue(Cell *** &sudoku, int row, int col){
	sudoku[row][col]->number = sudoku[row][col]->possible.front();
	sudoku[row][col]->box = addToBox(sudoku[row][col]->number, row, col);
	sudoku[row][col]->isSet = true;
}

bool puzzleSolved(Cell *** sudoku){
	int solved = 0;
	for(int r = 0; r < 9; r++){
		for (int c = 0; c < 9; c++){
			if(sudoku[r][c]->isSet){
				solved++;
			}

		}
	}
	if(solved == 81) return true;
	
	return false;
}

void removeImpossibleValue(int* notPos, std::vector<int> &poss){
	std::vector<int>::iterator position;
	
	for(int i = 0; i < 9; i++){
		position = std::find(poss.begin(), poss.end(), notPos[i]);
		if (position != poss.end()){ 
   			poss.erase(position);
   		}
	}
}

void printPossibilities(Cell *** sudoku){
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			std::cout <<"Row " << i <<", Col " << j <<",  " << ", Box " << sudoku[i][j]->box << ": ";
  			for (std::vector<int>::iterator it = sudoku[i][j]->possible.begin() ; it != sudoku[i][j]->possible.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		}
}

void printBox(){

	mapIter m_it, s_it;

	for(m_it = box.begin(); m_it != box.end(); m_it = s_it){
		int key = (*m_it).first;

		std::cout << "Box " << key << ": ";

		std::pair<mapIter, mapIter> keyRange = box.equal_range(key);
		for(s_it = keyRange.first; s_it != keyRange.second; s_it++)
			std::cout << (*s_it).second << "  ";

		std::cout << std::endl;
	}
}










