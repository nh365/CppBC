#include "mini_def.h"






int main(){

    Square Grid[9][9];  // Global, on stack
    Square *sqr_ptr;

    // Init grid
    size_t a,b;
    for (size_t i = 0; i < 9; i++)
    {
        a = i + 1;
        for (size_t j = 0; j < 9; j++)
        {   
            b = j + 1;
            sqr_ptr = &(Grid[i][j]); 
            sqr_ptr->InitSquare(a,b);

//            Grid[i][j].InitSquare(a,b);
//            Grid[i][j].Square(a,b);
        }
    }



    // Grid initialized
    // Import table to be solved
    ImportDataFromFile();
    // Print data for comparison
    std::cout << "Input:" << std::endl;
    PrintGrid();


    // Identify possible values and solve the easy ones
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {    
            sqr_ptr = &(Grid[i][j]); 
            sqr_ptr->IdentifyPossibleValues();
        }
    }

    // Print data for comparison
    std::cout << "Intermediary result:" << std::endl;
    PrintGrid();

    return(0);
}

