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
			printf("------------------------------\n");
	}
	printf("\n");
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
			sudoku[i][j]->count = 0;
			sudoku[i][j]->possible = new int[9];
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
	bool newValueSet;

	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					findPossibleValues(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
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
	bool newValueSet;
	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					checkUniquePossibilities(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
						setCellValue(sudoku, i, j);
						initialRunThrough(sudoku);	
						newValueSet = true;
					}
				}
			}
		}		
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);
}

void thirdRunThrough(Cell *** &sudoku){
	bool newValueSet;
	do{ 
		newValueSet = false;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if(!sudoku[i][j]->isSet){
					twinValuePossible(sudoku, i, j);
						//If only one possibility, set the Cell
					if(sudoku[i][j]->count == 1){
						setCellValue(sudoku, i, j);
						nextRunThrough(sudoku);	
						newValueSet = true;
					}
				}
			}
		}		
		if(puzzleSolved(sudoku)) break;

	}while(newValueSet);

}





void twinValuePossible(Cell *** &sudoku, int row, int col){
	int id = sudoku[row][col]->ID;
	int cnt = sudoku[row][col]->count;
	int twinLocation = -1;
	int value1, value2;

	if(cnt == 2){
		value1 = sudoku[row][col]->possible[0];
		value2 = sudoku[row][col]->possible[1];

		//Check columns first
		for(int r = 0; r < 9; r++){
			if(!(sudoku[r][col]->isSet) && (sudoku[r][col]->count == cnt)
				 && (sudoku[r][col]->ID != id)){		
				if(value1 == sudoku[r][col]->possible[0] &&
					value2 == sudoku[r][col]->possible[1]){
						twinLocation = r;
						break;
				}
				
			}
		}
		for(int r = 0; r < 9; r++){
			if(r == twinLocation) continue;

			if(rowVectorContains(sudoku, r, col, value1)){
				removeImpossibleValue(sudoku, r, col, value1);
			}
			if(rowVectorContains(sudoku, r, col, value2)){
				removeImpossibleValue(sudoku, r, col, value2);
			}
		}
		twinLocation = -1;
		//Check rows
		for(int c = 0; c < 9; c++){
			if(!(sudoku[row][c]->isSet) && (sudoku[row][c]->count == cnt)
				 && (sudoku[row][c]->ID != id)){		
				if(value1 == sudoku[row][c]->possible[0] &&
					value2 == sudoku[row][c]->possible[1]){
						twinLocation = c;
						break;
				}
				
			}
		}
		for(int c = 0; c < 9; c++){
			if(c == twinLocation) continue;

			if(rowVectorContains(sudoku, row, c, value1)){
				removeImpossibleValue(sudoku, row, c, value1);
			}
			if(rowVectorContains(sudoku, row, c, value2)){
				removeImpossibleValue(sudoku, row, c, value2);
			}
		}

		int twinBoxLocation[2] = {-1, -1};
		int boxNum = sudoku[row][col]->box;
		bool innerbreak = false;
		
		for(int r = 0; r < 9; r++){
			if(innerbreak) break;   //There's a better way to do this for sure!!!
			for(int c = 0; c < 9; c++){
				if(!(sudoku[r][c]->isSet) && (sudoku[r][c]->count == cnt)
					 && (sudoku[r][c]->ID != id) && (sudoku[r][c]->box != boxNum)){
					if(value1 == sudoku[r][c]->possible[0] &&
					   value2 == sudoku[r][c]->possible[1]){
						twinBoxLocation[0] = r;
						twinBoxLocation[1] = c;
						innerbreak = true;
						break;
					}
				}
			}
		}

		for(int r = 0; r < 9; r++){
			for(int c = 0; c < 9; c++){
				if(r == twinBoxLocation[0] && c == twinBoxLocation[1]) continue;

				if(sudoku[r][c]->box == boxNum){
					if(rowVectorContains(sudoku, r, c, value1)){
						removeImpossibleValue(sudoku, r, c, value1);
					}
					if(rowVectorContains(sudoku, r, c, value2)){
						removeImpossibleValue(sudoku, r, c, value2);
					}
				}
			}
		}

	}

}






void findPossibleValues(Cell *** &sudoku, int row, int col){
	int notPos[9] = {-1};
	int notPosCnt = 0;
	int boxNum = sudoku[row][col]->box;

	//Check if value is contained in "visible" cell
	for(int val = 1; val <= 9; val++){
		if(columnContains(sudoku, val, col) || rowContains(sudoku, val, row) || boxContains(boxNum, val)){
			notPos[notPosCnt] = val;
			notPosCnt++;
		}
	}

	//If first time visiting cell, populate possible values
	//Else remove impossible values
	sudoku[row][col]->count = (9 - notPosCnt);
	int current = 0;

	int *finder;
	for(int i = 1; i <= 9; i++){
		finder = std::find(std::begin(notPos), std::end(notPos), i);
		if(finder == std::end(notPos)){
			sudoku[row][col]->possible[current]=i;
			current++;
		}
	}
}

void checkUniquePossibilities(Cell *** &sudoku, int row, int col){
	int boxNum, value, id;

	boxNum = sudoku[row][col]->box;
	id = sudoku[row][col]->ID;

  	for (int i = 0; i < sudoku[row][col]->count; i++){
    	value = sudoku[row][col]->possible[i];
    	if(!(visibleVectorContains(sudoku, boxNum, value, id, row, col))){
    		setPossibleValue(value, sudoku[row][col]->possible, sudoku[row][col]->count);
    	}
  	}
}

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
	bool rowContains = false,
		colContains = false,
		boxContains = false;

	for(int rw = 0; rw < 9; rw++){
		for (int col = 0; col < 9; col++){
			if((!(sudoku[rw][col]->isSet)) && (sudoku[rw][col]->ID != id)){	
				if(rw == row){		
					if(rowVectorContains(sudoku, rw, col, value)) rowContains = true;
				}		
				
				if(col == column){
					if(columnVectorContains(sudoku, rw, col, value)) colContains = true;
		  		}

		  		if(sudoku[rw][col]->box == boxNum ){
		  			if(boxVectorContains(sudoku, rw, col, value)) boxContains = true;
		  		}
			}
		}
	}
	return (rowContains && colContains && boxContains);
}


bool rowVectorContains(Cell *** sudoku, int rw, int col, int value){
	bool rowContains = false;
	for (int i = 0 ; i < sudoku[rw][col]->count; i++){
		if(value == sudoku[rw][col]->possible[i]){ 
		    rowContains = true;
		}
	}
	return rowContains;
}

bool columnVectorContains(Cell *** sudoku, int rw, int col, int value){
	bool colContains = false;

	for (int i = 0 ; i < sudoku[rw][col]->count; i++){
		if(value == sudoku[rw][col]->possible[i]) {
		    colContains = true;
		}
	}
	return colContains;
}

bool boxVectorContains(Cell *** sudoku, int rw, int col, int value){
	bool boxContains = false;
	for (int i = 0 ; i < sudoku[rw][col]->count; i++){
		if(value == sudoku[rw][col]->possible[i]){
		    boxContains = true;	
		}	
	}
	return boxContains;
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
	sudoku[row][col]->number = sudoku[row][col]->possible[0];
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

void setPossibleValue(int value, int* &poss, int &count){
	poss[0] = value;
	count = 1;
}

void printPossibilities(Cell *** sudoku){
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			std::cout <<"Row " << i <<", Col " << j <<",  " << ", Box " << sudoku[i][j]->box << ": ";
  			for (int k = 0; k < sudoku[i][j]->count; k++)
    		std::cout << ' ' << sudoku[i][j]->possible[k];
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



void removeImpossibleValue(Cell *** &sudoku, int row, int col, int value){
	int cnt = sudoku[row][col]->count;
	
	for(int i = 0; i < cnt; i++){
		if(sudoku[row][col]->possible[i] == value){
			for(int j = i; j < cnt; j++){
				sudoku[row][col]->possible[j] = sudoku[row][col]->possible[j+1];
			}
			--cnt;
		}
	}
	sudoku[row][col]->count = cnt;
}








