#include "mini_def.h"
#include "minibf_def.h"


v

// Brute force variant
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

void PrintGrid(){

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
