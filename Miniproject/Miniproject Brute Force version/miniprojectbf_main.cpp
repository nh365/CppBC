#include "minibf_def.h"
// Start with the simple things.
// Define data structure.
// Strucure the program...high level...
// Import file and parse data.
// Print the imported data.
// Learn how to use header files.
// 
// Start to solve.
//
// IMPROVEMENTE / PRACTICE IDEAS:
// Send possible value to try out using pointer to structure!? <- Kommer inte att fungera, funktionen är rekursiv...
// Add check for incorrect data in input file...
// 



//SE_t *sudoku_table_ptr = new SE_t [9][9];
SE_t sudoku_table[9][9];


void ImportDataFromFile(){

    std::ifstream indata ("inputfile.txt");

    if(indata.is_open()){
        
        int row = 0, column = 0;
        
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                indata >> sudoku_table [row] [column].value;
//            std::cout << "Added cell value:" << sudoku_table [row] [column].value << std::endl;
            }
        }
    
        indata.close();

    } else {
        std::cout << "Cannot open data file!" << std::endl;
    }

    return;


// PREVIOUS SOLUTION!!! WITH DATACHECK!
/* 

    while (indata.good()) {

        std::cout << imported_value;

        // Check if data is correct.
        // Insert only numbers.
        // Exit if not number, space or EOL.
        if( 47 < imported_value && imported_value < 58){
            // Enter rows
            sudoku_table [row] [column].value = imported_value;
 //           std::cout << "Added cell value:" << sudoku_table [row][column].value << std::endl;

            // If zero, then it is not filled in.
            if(imported_value != 48){ 
                sudoku_table [row] [column].verified = true;
            } else sudoku_table [row] [column].verified = false;

            column++;
        }else if(imported_value == 10){
            // Line feed
            row++;
        }else if(imported_value == 32){
            // Space, throw away
        }else{
            std::cout << std::endl;
            std::cout << "Invalid input" << std::endl;
            indata.close();
            return;
        }
        // Get the next value
        imported_value = indata.get();
    }
    std::cout << std::endl;
  */   
}


void PrintCompletedData(){

    int row = 0, column = 0;

    std::cout << "----------------------------" << std::endl;

    // Print the first row
    for(row = 0; row < 9; row++){
        for(column = 0; column < 9; column++)
        {
            std::cout << sudoku_table [row] [column].value << " ";
//            std::cout << "," << sudoku_table [row] [column].verified;
//            std::cout << " ";
        }
        std::cout << std::endl;
    }
}


std::pair<int,int> GetEmptyCell(){

    for(int row = 0; row < 9; row++){
        for(int column = 0; column < 9; column++){

            if(sudoku_table [row] [column].value == 0){
                
                return std::make_pair(row, column);

            }
        }
    }
    return std::make_pair(9,9);
}

bool CheckRow(int row,int column,int candidate){

    for(int i = 0; i<9; i++){
        if(sudoku_table[row][i].value == candidate){
            return false;
        }
    }
    return true;
}

bool CheckColumn(int row,int column,int candidate){

    for(int i = 0; i<9; i++){
        if(sudoku_table[i][column].value == candidate){
            return false;
        }
    }
    return true;
}

bool CheckBox(int first_box_row,int first_box_column,int candidate){

    for(int i = first_box_row; i<first_box_row+3; i++){
        for(int j = first_box_column; j<first_box_column+3; j++){
            if(sudoku_table[i][j].value == candidate){
                return false;
            }
        }
    }
    return true;
}

bool NumberCheck(int row,int column,int candidate){
    // Is this a possible number to use in this spot?
    // Check if unused in row, column box.

    int first_box_row = row - row % 3;
    int first_box_column = column - column % 3;

    if(CheckRow(row,column,candidate) && CheckColumn(row,column,candidate) && CheckBox(first_box_row, first_box_column, candidate)){
        return true;
    }
    return false;
}

// Solves sudoku brute force method.
bool SolveSudokuBF(){ 

    size_t row,column;
    
    // Get coordintates of first empty cell.
    std::pair<int,int> row_and_column = GetEmptyCell();

    if(row_and_column.first == 9 && row_and_column.second == 9 ){
        // The table is filled in.
        std::cout << "The table is filled in. First check!";
        return true;
    } else if (std::make_pair(9, 9) == GetEmptyCell()){ 
        // The table is filled in. Another type of check....
        std::cout << "The table is filled in. The other check!";
        return true;
    }else{
        
        row = row_and_column.first;
        column = row_and_column.second;
        std::cout << "The table is NOT filled in. row,column: " << row << "," << column << std::endl;

        // Test for possible number
        for(int candidate=0; candidate<=9; candidate++){

            if(NumberCheck(row,column,candidate)){
                // The proposed number seems ok,
                // Place it in the position.
                // then call recursively and test next empty cell.

                sudoku_table [row] [column].value = candidate;
                if(SolveSudokuBF()){
                    return true;
                }

                // The proposed number did not work, try next.
                sudoku_table [row] [column].value = 0;  // Why, är det inte redan noll???
            }
        }
    }
    // Nope, did not work!
    std::cout << "Does not seem to work...!" << std::endl;
    return false;   

}


int main(){

    std::cout << "Input:" << std::endl;
    ImportDataFromFile();
    PrintCompletedData();

    if(SolveSudokuBF()){
        std::cout << "Solution using brute force:" << std::endl;
        PrintCompletedData();
    }else{
        std::cout << "Cannot solve!" << std::endl;
    }

    return(0);
}

