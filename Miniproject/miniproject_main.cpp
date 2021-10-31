#include "mini_def.h"


bool ImportDataFromFile(Cell (&_grid)[9][9]){

    std::ifstream indata ("inputfile2.txt");

    if(indata.is_open()){
        
        int row = 0, column = 0;
        
        for (row = 0; row < 9; row++)
        {
            for (column = 0; column < 9; column++)
            {
                indata >> _grid[row][column].solved_value;

//                 std::cout << "Added cell value:" << _grid[row][column].solved_value << std::endl;
            }
        }
    
        indata.close();

    } else {
        std::cout << "Cannot open data file!" << std::endl;
    }

    return true;
}





int main(){

    Cell Grid[9][9];  // Global, on stack
    Cell GridCopy[9][9];  // Global, on stack

    Cell *cell_ptr = nullptr;
    Cell *cell_copy_ptr = nullptr;    


    // Init grid
    InitGrid(Grid,GridCopy);
    std::cout << "Initialized empty Grid:" << std::endl;
    PrintGrid(Grid);

    // Import table to be solved
    ImportDataFromFile(Grid);
    std::cout << "Input table:" << std::endl;
    PrintGrid(Grid);
//    PrintGridSimple(Grid);

auto start_program = std::chrono::high_resolution_clock::now();

    // Identify possible values and solve the easy ones
    SolveEasy(Grid);
    // Print data for comparison
    std::cout << "Intermediary result using constraint propagation:" << std::endl;
    PrintGrid(Grid);
//    PrintGridSimple(Grid);


    // Make a sandbox grid for evalating guesses in
    CopyGrid(Grid,GridCopy);
//    if (CopyGrid(Grid,GridCopy)) {
//        std::cout << "Copy of Grid:" << std::endl;
//        PrintGrid(GridCopy);
//    }

    // Try solving those with few unknowns
/*    if (SolveDifficult(GridCopy)){
        // Copy GridCopy
        CopyGrid(GridCopy,Grid);

        std::cout << "GridCopy now copied." << std::endl;
        PrintGrid(GridCopy);
        PrintGrid(Grid);
    }
*/       
    // Solve the last unknowns with brute force 
    if(SolveSudokuBF(Grid)){
        std::cout << "Solution using brute force as final step:" << std::endl;
//        PrintGrid(GridCopy);
//        CopyGrid(GridCopy,Grid); // Copy GridCopy to Grid
//        std::cout << "Copied back to Grid:" << std::endl;            
        PrintGridSimple(Grid);
    }else{
        std::cout << "Cannot solve!" << std::endl;
        PrintGrid(Grid);
    }

    auto end_program = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
    std::cout << "Total execution time (ms): " << duration.count() << std::endl;

    return(0);
}

