	



/*
	if(sudoku[row][col]->count == 0){
		for(int i = 0; i < 9; i++){
			if(!(value == notPos[value-1])){
				sudoku[row][col]->possible[sudoku[row][col]->count] = value;
				sudoku[row][col]->count++;
			}

		}
	}else
		for(int i = 0; i < 9; i++ ){
			if(notPos[i] != -1){
				removeImpossibleValue(notPos[i], sudoku[row][col]->possible, sudoku[row][col]->count);
			}
		}
*/



/*void removeImpossibleValue(int* notPos, int* &poss, int &count){
	for(int i = 1; i <= 9; i++){
		if(notPos[i] == i){
			for(int j = 0; j < count; j++){
				if(poss[j] == i){
					for(int k = j; k < count; k++){
						poss[k] = poss[k+1];
					}
					--count;
				}
			}
		}
	}
}*/
/*
void removeImpossibleValue(int value, int* &poss, int &count){
	for(int i = 0; i < count; i++){
		if(poss[i] == value){
			for(int j = i; j < count; j++){
				poss[j] = poss[j+1];
			}
			--count;
		}
	}
}
*/









// line 226: || sudoku[row][col]->box == boxNum






	for(int rw = 0; rw < 9; rw++){
		for (int col = 0; col < 9; col++){
			if((!(sudoku[rw][col]->isSet)) && (sudoku[rw][col]->ID != id)){
				if((rw == row)){
				
					possVector = sudoku[rw][col]->possible;
					for (it = possVector.begin() ; it != possVector.end(); it++){
		    			if(value == (*it)) return true;
		  			}
				}		

				if((col == column)){
					possVector = sudoku[rw][col]->possible;
					for (it = possVector.begin() ; it != possVector.end(); it++){
		    			if(value == (*it)) return true;
		  			}	
		  		}

		  		if(sudoku[rw][col]->box == boxNum ){
					possVector = sudoku[rw][col]->possible;
					for (it = possVector.begin() ; it != possVector.end(); it++){
		    			if(value == (*it)) return true;
		  			}	
		  		}
			}
		}
	}
	























	for (int rc = 0; rc < 9; rc++){


		if((rc == row) && !(sudoku[rc][column]->isSet) && (sudoku[rc][column]->ID != id)){
			possVector = sudoku[rc][column]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}
		}


		if((rc == column) && !(sudoku[row][rc]->isSet) && (sudoku[row][rc]->ID != id)){
			possVector = sudoku[row][rc]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}


		if( (sudoku[row][rc]->box == boxNum ) && !(sudoku[row][rc]->isSet) && (sudoku[row][rc]->ID != id)){
			possVector = sudoku[row][rc]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}


		if((sudoku[rc][column]->box == boxNum) && !(sudoku[rc][column]->isSet) && (sudoku[rc][column]->ID != id)){
			possVector = sudoku[rc][column]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}		

	}















	for (int rc = 0; rc < 9; rc++){


		if((!(sudoku[rc][column]->isSet)) && (sudoku[rc][column]->ID != id)){
			possVector = sudoku[rc][column]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}
		}


		if((!(sudoku[row][rc]->isSet)) && (sudoku[row][rc]->ID != id)){
			possVector = sudoku[row][rc]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}


		if( (sudoku[row][rc]->box == boxNum ) && !(sudoku[row][rc]->isSet) && (sudoku[row][rc]->ID != id)){
			possVector = sudoku[row][rc]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}


		if((sudoku[rc][column]->box == boxNum) && !(sudoku[rc][column]->isSet) && (sudoku[rc][column]->ID != id)){
			possVector = sudoku[rc][column]->possible;
			for (it = possVector.begin() ; it != possVector.end(); it++){
    			if(value == (*it)) return true;
  			}			
		}		

	}