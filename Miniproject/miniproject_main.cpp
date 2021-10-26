#include "mini_def.h"





// ---------------------------------------------------------
// FUNCTIONS THAT WERE MOVED FROM HEADER FILE TO HERE FOR DEBUGGING PURPOSES

// Initialize cells
bool Cell::InitCell(Cell (&_grid)[9][9],Cell (&_grid_copy)[9][9], size_t &_row, size_t &_column){

    Cell *grid_ptr = &(_grid[0][0]); // Points to the top of the Grid[0][0]
    Cell *grid_copy_ptr = &(_grid_copy[0][0]); // TBD: Points to the top of the sandbox (sb) Grid[0][0]    
    Cell *my_cell_ptr = &(_grid[_row][_column]);
    Cell *peer_cell_ptr = nullptr;
    size_t number_of_peers = 0;

    // Receive the instantiated Cell coordinates
    // Init possible value
    // Init all peers
    this->solved_value = 0; // Contains the solved value, contains 0 if unsolved.
    this->my_coordinates.row = _row;
    this->my_coordinates.column = _column;
//    this->my_coordinates.box_top_row = _row - _row % 3;
//    this->my_coordinates.box_left_column = _column - _column % 3;

// UGLY INIT OF BOX VALUES...CHANGE LATER

    if (_row < 3 )
    {
        this->my_coordinates.box_top_row = 0;
    } else if ( (2 < _row ) && (_row < 6) )
    {
        this->my_coordinates.box_top_row = 3;
    } else if ( (5 < _row ) && (_row < 9) ) 
    {
        this->my_coordinates.box_top_row = 6;
    } else std::cout << "Row is out of bounds." << std::endl;

    if (_column < 3 )
    {
        this->my_coordinates.box_left_column = 0;
    } else if ( (2 < _column ) && (_column < 6) )
    {
        this->my_coordinates.box_left_column = 3;
    } else if ( (5 < _column ) && (_column < 9) ) 
    {
        this->my_coordinates.box_left_column = 6;
    } else std::cout << "Column is out of bounds." << std::endl;


    // Init possible values
    for (size_t i = 1; i < 10; i++)
    {
        possible_values.push_back(i);
    }
    // Init list of my peers
    // Add all row peers, disregard my position
    for (size_t i = 0; i < 9; i++)
    {
        if (i != (this->my_coordinates.column)) // Do not add myself
        {
            // Create new entry of Cell pointer in peer vector
            // Point peer_cell_ptr to the correct cell.
            this->peers.push_back(&(_grid[my_coordinates.row][i]));             
            number_of_peers++;
// std::cout << "Row peer added, the current number of peers are: " << number_of_peers << std::endl;

        }
    }
    // Add all column peers, disregard my position
    for (size_t i = 0; i < 9; i++)
    {
        if (i != (my_coordinates.row)) // Do not add myself
        {
            // Create new entry of Cell pointer in peer vector
            // Point peer_cell_ptr to the correct cell.
            this->peers.push_back(&(_grid[i][my_coordinates.column])); 
            number_of_peers++;
// std::cout << "Column peer added, the current number of peers are: " << number_of_peers << std::endl;
        }
    }
    // Add all box peers, disregard my position
    for (size_t i = my_coordinates.box_top_row; i < (my_coordinates.box_top_row + 3); i++)
    {
        for (size_t j = my_coordinates.box_left_column; j < (my_coordinates.box_left_column + 3); j++){

            // Do not add myself or those added by my row or column.
            if ( (i !=  my_coordinates.row ) && ( j != my_coordinates.column ) ) // Do not add myself or any peer in my row or column
            {              
                // Create new entry of Cell pointer in peer vector
                // Point peer_cell_ptr to the correct cell.                
                this->peers.push_back(&(_grid[i][j]));
                number_of_peers++;
// std::cout << "Unit peer added, the current number of peers are: " << number_of_peers << std::endl;
            }
        }
    }
    // std::cout << "Grid element (r/c): " << my_coordinates.row << "," << my_coordinates.column << "   "; 
    // std::cout << "The current number of peers are: " << number_of_peers << std::endl;

    return true;
}

// Find values that are not identified in peers.
bool Cell::IdentifyCandidates(){

    Cell *peer_cell_ptr;
    size_t number_of_peers = this->peers.size();
    size_t number_of_possible_values = this->possible_values.size();

//     std::cout << "Identifying values in: " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;

    if (this->solved_value)
    {
        // This Cell has a solved value.
        // Clear all other possible values.
        this->possible_values.clear();
    } else {

        // For every peer...
        for (size_t i = 0; i < number_of_peers; i++)
        {
            // ...check if the peer solved_value is anything but 0
            // and if so, remove it from my list of possible values.
            peer_cell_ptr = this->peers[i];
            if (peer_cell_ptr->solved_value != 0)
            {
                // There is a value defined.
                // Remove this value from my possible values.
                for (size_t j = 0; j < number_of_possible_values; j++)
                {
                    // Is this value the same as my peers?
                    if (peer_cell_ptr->solved_value == this->possible_values.at(j))
                    {
                        // The values match.
                        // Remove it from my list.
                        this->possible_values.erase(this->possible_values.begin() + j);
                        number_of_possible_values--;
//                         std::cout << "Value: " << peer_cell_ptr->solved_value << " erased from possible values vector." << std::endl;
                        break;
                    }
                }
            }
        }
        // If there is only one possible solution 
        // set solved_value
        if(this->possible_values.size() == 1){

            this->solved_value = this->possible_values.front();
            std::cout << "There is only one possible value: " << this->solved_value << " in " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;
        
            return true;  // Value found, return true.
        }
    }
    return false; // Still more than one possible value, return false.
}

bool Cell::NumberCheck(size_t candidate_index){

    // For all peers, make sure the proposed value is not solved in any peer

    size_t nr_peers = ReturnNumberOfPeers();

    for (size_t i = 0; i < nr_peers; i++)
    {
        if (this->peers.at(i)->solved_value == this->possible_values.at(candidate_index))
        {
            // The value is already in use.
            return true;
        }
    }
    return false;
}


// END OF HEADER FILE INSERT
// ---------------------------------------------------------


// ---------------------------------------------------------
// FUNCTIONS THAT WERE MOVED FROM SEPARATE CPP-FILE SINCE IT WOULD NOT BUILD.
// MOVE BACK WHEN ISSUE IS UNDERSTOOD.
// ERROR MESSAGE:
/*
nhanss10@nhanss10-HP-ZBook-15-G3:~/bootcamp/projects/repos/CppBC/Miniproject$ g++ miniproject_main.cpp miniproject_support.cpp -o miniproject
/usr/bin/ld: /tmp/ccHsG31u.o: in function `Cell::InitCell(Cell (&) [9][9], unsigned long&, unsigned long&)':
miniproject_support.cpp:(.text+0x0): multiple definition of `Cell::InitCell(Cell (&) [9][9], unsigned long&, unsigned long&)'; /tmp/ccxmDNkw.o:miniproject_main.cpp:(.text+0x0): first defined here
/usr/bin/ld: /tmp/ccHsG31u.o: in function `Cell::IdentifyCandidates()':
miniproject_support.cpp:(.text+0x514): multiple definition of `Cell::IdentifyCandidates()'; /tmp/ccxmDNkw.o:miniproject_main.cpp:(.text+0x514): first defined here
collect2: error: ld returned 1 exit status
*/


Cell* ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]){
    size_t smallest_found = 9;
    size_t returned_possible = 9;
    Cell *smallest_ptr = nullptr;
    Cell *cell_ptr;

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {    
            cell_ptr = &(_grid[i][j]);
            returned_possible = cell_ptr->ReturnNumberOfPossibleValues();  
            if ( (returned_possible < smallest_found) && (returned_possible > 0))
            {
                smallest_found = returned_possible;
                smallest_ptr = cell_ptr;
//                std::cout << "New smallest detected: " << smallest_found << std::endl;

            }
            
        }
    }
    return smallest_ptr;    
}

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


bool PrintGridSimple(Cell (&_grid)[9][9]){

    int row = 0, column = 0;

    std::cout << "-------------------------" << std::endl;

    for(row = 0; row < 9; row++){

        if ((row == 3)||(row == 6)||(row == 9)) std::cout << "-------------------------" << std::endl;

        for(column = 0; column < 9; column++)
        {
            if ((column == 0)||(column == 3)||(column == 6)) std::cout << "| ";            
            std::cout << _grid [row] [column].solved_value << " ";
            if (column == 8) std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
    return true;
}

bool PrintGrid(Cell (&_grid)[9][9]){

    int row = 0, column = 0;

    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    for(row = 0; row < 9; row++){

        if ((row == 3)||(row == 6)||(row == 9)) std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

        for(column = 0; column < 9; column++){

            if ((column == 0)||(column == 3)||(column == 6)) std::cout << "| ";

            std::cout << "    " << _grid [row] [column].solved_value << "     ";
            
            if (column == 8) std::cout << "|";
        }
        std::cout << std::endl;

        // Print the candidates 
        for(column = 0; column < 9; column++){

            if ((column == 0)||(column == 3)||(column == 6)) std::cout << "| ";

            for (size_t i = 0; i < _grid[row][column].possible_values.size() ; i++)
            {
                std::cout << _grid[row][column].possible_values.at(i);
                
            }
            for (size_t i = 0; i < (10-_grid[row][column].possible_values.size()) ; i++)
            {
                // Print remaining spaces
                std::cout << " ";    
            } 
            if (column == 8) std::cout << "|";
        }
        std::cout << std::endl;
        std::cout << "|                               |                               |                               |" << std::endl;

    }
    std::cout << "-------------------------------------------------------------------------------------------------" << std::endl;

    return true;
}

bool CopyGrid(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]){

//    std::copy(&_grid,&grid+9x9,&_grid_copy);


    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            _grid_copy[i][j] = _grid[i][j];
        }
        
    }
    return true;

}

bool InitGrid(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]){

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {   
//            cell_ptr = &(Grid[i][j]); 
//            cell_ptr->InitCell(Grid,GridCopy,i,j);
            _grid[i][j].InitCell(_grid,_grid_copy,i,j);
        }
    }
    return true;
}    


bool SolveEasy(Cell (&_grid)[9][9]){

//    Cell *cell_ptr = nullptr;
    bool value_added = false;
    bool value_added_return = false;

    do
    {
        value_added = false;

        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {    
//                cell_ptr = &(_grid[i][j]); 
//                if(cell_ptr->IdentifyCandidates())
                if(_grid[i][j].IdentifyCandidates() )

                {
                    value_added = true; // New value solved, make another run.
                    value_added_return = true;
                }
            }
        }
    } while (value_added);

    return value_added_return;
}


bool SolveDifficult(Cell (&_grid)[9][9]){

    Cell *cell_copy_ptr;
    // Find the Cell with the lowest number of possible entries.
    // Set first value and evaluate using brute force...
    cell_copy_ptr = ReturnCellWithFewestAlternatives(_grid);

    // Use the copied grid first
//    do
//    {
//        // Store the first item to try
//        size_t candidate_under_test = cell_copy_ptr->possible_values.at(i);
//        if(cell_copy_ptr->EvaluateCandidates(Grid, GridCopy)){
//            std::cout << "Solution using brute force:" << std::endl;
//            PrintGrid(Grid);
//        }else{
//            std::cout << "Cannot solve! Try the next alternative..." << std::endl;
//
//        }    
//    } while ( 1 );

    return true;
}

// END OF SUPPORT FUNCTIONS TO BE MOVED TO SEPARATE CPP-FILE
// ---------------------------------------------------------


// Move to header file...
// Solves sudoku brute force method.
bool Cell::EvaluateCandidates(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]){ 

        Cell *cell_ptr = &_grid[this->my_coordinates.row][this->my_coordinates.column];
        Cell *cell_copy_ptr = &_grid_copy[this->my_coordinates.row][this->my_coordinates.column];


        // Test with the first candidate, then the second etc...
        // Loop for nr of candidates
        size_t nr_candidates = this->ReturnNumberOfPossibleValues();
        size_t nr_peers = this->ReturnNumberOfPeers();
//        size_t remaining_values = nr_candidates;
//        size_t candidate_under_eval = 0;

        for (size_t i = 0; i < nr_candidates; i++)
        {
           if(!NumberCheck(i)){
                // The proposed number seems ok,
                // Place it in the position.
                // then call recursively and test next empty cell.
                // candidate_under_eval = this->possible_values.at(i);
                
                // Set candidate under evaluation in copy and try to solve.
//                cell_copy_ptr->solved_value = this->possible_values.at(i);

                this->solved_value = this->possible_values.at(i);

                // Remove this candidate from all my peers
                // Erase candidate from my list of possible candidates...!
                //this->possible_values.erase(this->possible_values.begin());  // Removes the first item
                std::cout << "Setting solved value and removing from possible list: " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;
                this->possible_values.erase(std::remove(this->possible_values.begin(), this->possible_values.end(), this->solved_value), this->possible_values.end());                
//                cell_copy_ptr->possible_values.erase(cell_copy_ptr->possible_values.begin() + i);

                for (size_t j = 0; j < nr_peers; j++)
                {
                    if ( std::find(peers[j]->possible_values.begin(), peers[j]->possible_values.end(), this->solved_value) != peers[j]->possible_values.end() ){
                        // The value is available, remove it from possible values.
                        std::cout << "Removing from peer possible list: " << this->solved_value << std::endl;
                        peers[j]->possible_values.erase(std::remove(peers[j]->possible_values.begin(), peers[j]->possible_values.end(), this->solved_value), peers[j]->possible_values.end());                    
                    }
                }

                for (size_t j = 0; j < nr_peers; j++)
                {
                    
                    std::cout << "Recursive call: " << j << " " << cell_copy_ptr->peers[j]->my_coordinates.row << " " << cell_copy_ptr->peers[j]->my_coordinates.column << std::endl;
                    
                    // Do not check myself
                    // TODO: Remove this check later
                    if (( cell_copy_ptr->peers[j]->my_coordinates.row == cell_copy_ptr->my_coordinates.row ) &&
                        (cell_copy_ptr->peers[j]->my_coordinates.column == cell_copy_ptr->my_coordinates.column))
                    {
                        std::cout << "ERROR: I am in my own peerslist..." << std::endl;
                        break;
                    }

                    if (cell_copy_ptr->peers[j]->EvaluateCandidates(_grid, _grid_copy)){
                        // Things worked out, set the candidate as permanent
                        // this->solved_value = this->possible_values.at(i);

                        std::cout << "Returned from recursion..." << std::endl;

                        cell_copy_ptr->solved_value = this->possible_values.at(i);  // Copy to both original and copy
                        cell_ptr->solved_value = this->possible_values.at(i);       // Copy to both original and copy
                        // Delete possible values vector.
                        cell_copy_ptr->possible_values.clear();
                        cell_ptr->possible_values.clear();
                        // Value worked out!
                        return true;
                    }
                }
            } else {
                // Candidate at i is used
                // Remove candidate and start over
                this->possible_values.erase(this->possible_values.begin() + i);

                if (this->ReturnNumberOfPossibleValues()) // Are there more values to check?
                {
                    // Yes, restart (reason to restart is to not miss any possible solutions in vector, re-evaluate later...)
                    i = 0;
                } else return false;  // No more 
            }        
        }
    
    return false;   

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
    if (SolveDifficult(GridCopy)){
        // Copy GridCopy
        CopyGrid(GridCopy,Grid);
    }
        
    // Solve the last unknowns with brute force 
    if(SolveSudokuBF(GridCopy)){
        std::cout << "Solution using brute force as final step:" << std::endl;
//        PrintGrid(GridCopy);
        CopyGrid(GridCopy,Grid); // Copy GridCopy to Grid
//        std::cout << "Copied back to Grid:" << std::endl;            
        PrintGridSimple(Grid);
    }else{
        std::cout << "Cannot solve!" << std::endl;
        PrintGrid(GridCopy);
    }

    return(0);
}

