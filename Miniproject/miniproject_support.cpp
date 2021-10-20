 #include "mini_def.h"
// #include "minibf_def.h"

// THIS FILE IS TEMPORARILY NOT BEING USED!

void ImportDataFromFile(Square (&_grid)[9][9]){

    std::ifstream indata ("inputfile.txt");

    if(indata.is_open()){
        
        int row = 0, column = 0;
        
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                indata >> _grid[row][column].solved_value;

//            std::cout << "Added cell value:" << sudoku_table [row] [column].value << std::endl;
            }
        }
    
        indata.close();

    } else {
        std::cout << "Cannot open data file!" << std::endl;
    }

    return;
}


/* void PrintCompletedData(Square (*_grid[9][9])){

    int row = 0, column = 0;

    std::cout << "----------------------------" << std::endl;

    // Print the first row
    for(row = 0; row < 9; row++){
        for(column = 0; column < 9; column++)
        {
            std::cout << _grid [row] [column].solved_value << " ";
//            std::cout << "," << sudoku_table [row] [column].verified;
//            std::cout << " ";
        }
        std::cout << std::endl;
    }
} */

void PrintGrid(Square (&_grid)[9][9]){

    int row = 0, column = 0;

    std::cout << "----------------------------" << std::endl;

    // Print the first row
    for(row = 0; row < 9; row++){
        for(column = 0; column < 9; column++)
        {
            std::cout << _grid [row] [column].solved_value << " ";
//            std::cout << "," << sudoku_table [row] [column].verified;
//            std::cout << " ";
        }
        std::cout << std::endl;
    }
}
