 #include "mini_def.h"
// #include "minibf_def.h"

// THIS FILE IS TEMPORARILY NOT BEING USED!

void ImportDataFromFile(Cell (&_grid)[9][9]){

    std::ifstream indata ("inputfile.txt");

    if(indata.is_open()){
        
        int row = 0, column = 0;
        
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                indata >> _grid[row][column].solved_value;
            }
        }
    
        indata.close();

    } else {
        std::cout << "Cannot open data file!" << std::endl;
    }

    return;
}


void PrintGrid(Cell (&_grid)[9][9]){

    int row = 0, column = 0;

    std::cout << "----------------------------" << std::endl;

    // Print the first row
    for(row = 0; row < 9; row++){
        for(column = 0; column < 9; column++)
        {
            std::cout << _grid [row] [column].solved_value << " ";
        }
        std::cout << std::endl;
    }
}
