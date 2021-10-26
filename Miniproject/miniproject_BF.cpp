#include "mini_def.h"




bool CheckRow(Cell (&_grid)[9][9], int row,int column,int candidate){

    for(int i = 0; i<9; i++){
        if(_grid[row][i].solved_value == candidate){
            return false;
        }
    }
    return true;
}

bool CheckColumn(Cell (&_grid)[9][9], int row,int column,int candidate){

    for(int i = 0; i<9; i++){
        if(_grid[i][column].solved_value == candidate){
            return false;
        }
    }
    return true;
}

bool CheckBox(Cell (&_grid)[9][9], int first_box_row,int first_box_column,int candidate){

    for(int i = first_box_row; i<first_box_row+3; i++){
        for(int j = first_box_column; j<first_box_column+3; j++){
            if(_grid[i][j].solved_value == candidate){
                return false;
            }
        }
    }
    return true;
}

bool NumberCheck(Cell (&_grid)[9][9], size_t _row,size_t _column,size_t candidate){
    // Is this a possible number to use in this spot?
    // Check if unused in row, column box.

//    int first_box_row = row - row % 3;
//    int first_box_column = column - column % 3;
// UGLY INIT OF BOX VALUES...CHANGE LATER

    int first_box_row = 0;
    int first_box_column = 0;

    if (_row < 3 )
    {
        first_box_row = 0;
    } else if ( (2 < _row ) && (_row < 6) )
    {
        first_box_row = 3;
    } else if ( (5 < _row ) && (_row < 9) ) 
    {
        first_box_row = 6;
    } else std::cout << "Row is out of bounds." << std::endl;

    if (_column < 3 )
    {
        first_box_column = 0;
    } else if ( (2 < _column ) && (_column < 6) )
    {
        first_box_column = 3;
    } else if ( (5 < _column ) && (_column < 9) ) 
    {
        first_box_column = 6;
    } else std::cout << "Column is out of bounds." << std::endl;

    if(CheckRow(_grid, _row,_column,candidate) && CheckColumn(_grid,_row,_column,candidate) && CheckBox(_grid, first_box_row, first_box_column, candidate)){
        return true;
    }
    return false;
}

std::pair<int,int> GetEmptyCell(Cell (&_grid)[9][9] ){

    for(int row = 0; row < 9; row++){
        for(int column = 0; column < 9; column++){

            if(_grid [row] [column].solved_value == 0){

//                std::cout << "GetEmptyCell(): " << row << "," << column << std::endl;                
                return std::make_pair(row, column);

            }
        }
    }
//    std::cout << "GetEmptyCell(): 9,9" << std::endl;                
    return std::make_pair(9,9);
}

// Solves sudoku brute force method.
// This is an ineffective version but it works. Now focus is on good version...
bool SolveSudokuBF(Cell (&_grid)[9][9]){ 

    size_t row,column;
    
    // Get coordintates of first empty cell.
    std::pair<int,int> row_and_column = GetEmptyCell(_grid);

    if(row_and_column.first == 9 && row_and_column.second == 9 ){
        // The table is filled in.
        std::cout << "The table is filled in." << std::endl;
        return true;
    }else{
        
        row = row_and_column.first;
        column = row_and_column.second;

        // Test for possible number
        for(int candidate=1; candidate<=9; candidate++){

            if(NumberCheck(_grid, row, column, candidate)){
                // The proposed number seems ok,
                // Place it in the position.
                // then call recursively and test next empty cell.

                _grid [row] [column].solved_value = candidate;

//                std::cout << "Assigning value: " << candidate << " to " << row << "," << column << std::endl;


                if(SolveSudokuBF(_grid)){
                    return true;
                }

                // The proposed number did not work, try next.
                _grid [row] [column].solved_value = 0;  // Why, är det inte redan noll???
            }
        }
    }
//    PrintGrid(_grid);
    return false;   

}
