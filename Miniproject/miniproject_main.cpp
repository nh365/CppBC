#include "mini_def.h"





// ---------------------------------------------------------
// FUNCTIONS THAT WERE MOVED FROM HEADER FILE TO HERE FOR DEBUGGING PURPOSES

// Initialize cells
bool Cell::InitCell(Cell (&_grid)[9][9], size_t &_row, size_t &_column){

    Cell *grid_ptr = &(_grid[0][0]); // Points to the top of the Grid[0][0]
    Cell *my_cell_ptr = &(_grid[_row][_column]);
    Cell *peer_cell_ptr = nullptr;

    // Receive the instantiated Cell coordinates
    // Init possible value
    // Init all peers
    this->solved_value_b = 0x0000; // Contains the solved value, contains 0 if unsolved.
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
    possible_values_b = 0x01FF;
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
            }
        }
    }
    // std::cout << "Grid element (r/c): " << my_coordinates.row << "," << my_coordinates.column << "   "; 
    // std::cout << "The current number of peers are: " << number_of_peers << std::endl;

    return true;
}

// Find values that are not identified in peers.
bool Cell::IdentifyCandidates(){

    bool ret_val = false;
    Cell *peer_cell_ptr;
    size_t number_of_possible_values = this->possible_values.size();

//     std::cout << "Identifying values in: " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;

    // TODO: edit this when migration to bitfield is done.
    if (this->solved_value_b)
    {
        // This Cell has a solved value.
        // Clear all other possible values.
        possible_values_b = 0x00;
        this->possible_values.clear();
    } else if (this->solved_value)
    {
        // This Cell has a solved value.
        // Clear all other possible values.
        possible_values_b = 0x00;
        this->possible_values.clear();
    } else {

        // For every peer...
        for (size_t i = 0; i < NUM_PEERS; i++)
        {
            // ...check if the peer solved_value is anything but 0
            // and if so, remove it from my list of possible values.
            possible_values_b = possible_values_b ^ this->peers[i]->solved_value_b;

            // Solution without bitfield...TODO! Remove...
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
        
            ret_val = true;  // Value found, return true.
        }
    }
    return ret_val;  // true: only one. false: still more than one possible value, return false.
}

bool Cell::NumberCheck(size_t candidate_index){

    bool ret_val = false;
    // For all peers, make sure the proposed value is not solved in any peer

    for (size_t i = 0; i < NUM_PEERS; i++)
    {
        if (this->peers.at(i)->solved_value == this->possible_values.at(candidate_index))
        {
            // The value is already in use.
            ret_val = true;
            break;
        }
    }
    return ret_val;
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


std::pair<int,int> ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]){
    size_t smallest_found = 9;
    size_t returned_possible = 9;
    size_t row,column;
//    Cell *cell_ptr;

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {    
//            cell_ptr = &(_grid[i][j]);
            returned_possible = _grid[i][j].ReturnNumberOfPossibleValues();  
            if ( (returned_possible < smallest_found) && (returned_possible > 0))
            {
                smallest_found = returned_possible;
                row = i;
                column = j;
//                std::cout << "New smallest detected: " << smallest_found << std::endl;
                
            }
        }
    }
    return std::make_pair(row, column);
}

Cell& _ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]){
    size_t smallest_found = 9;
    size_t nr_possible = 9;
    size_t row,column;
    Cell *cell_ptr = &(_grid[0][0]);
    Cell *ret_cell_ptr = nullptr;

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {    
            cell_ptr = &(_grid[i][j]);
            nr_possible = cell_ptr->ReturnNumberOfPossibleValues();  
            if ( (nr_possible < smallest_found) && (nr_possible > 0))
            {
                smallest_found = nr_possible;
                ret_cell_ptr = &(_grid[i][j]);
//                std::cout << "New smallest detected: " << smallest_found << std::endl;
            }
        }
    }
    return *ret_cell_ptr;
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

            // Information that needs to be copied.
            // Vector with possible values.
            // Solved Value
            for ( size_t k = 0; k < 20; k++){
                // For each peer, copy its possible value vector.
                _grid_copy[i][j].peers.at(k)->possible_values = _grid[i][j].peers.at(k)->possible_values;
            }
            _grid_copy[i][j].solved_value = _grid[i][j].solved_value;
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
            _grid[i][j].InitCell(_grid,i,j);
            _grid_copy[i][j].InitCell(_grid_copy,i,j);
        }
    }
    return true;
}    


bool SolveEasy(Cell (&_grid)[9][9]){

    bool value_added = false;
    bool value_added_return = false;

    do
    {
        value_added = false;

        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {    
                if(_grid[i][j].IdentifyCandidates() ){

                    value_added = true; // New value solved, make another run.
                    value_added_return = true;
                }
            }
        }
    } while (value_added);

    return value_added_return;
}


bool SolveDifficult(Cell (&_grid)[9][9]){

    bool ret_val = false;
    Cell *cell_copy_ptr = &(_grid[0][0]);
    size_t value_under_evaluation = 0;
    size_t row, column;

// ALTERNATIVE 1


    // Find the Cell with the lowest number of possible entries.
    // Set first value and evaluate using brute force...
    cell_copy_ptr = &(_ReturnCellWithFewestAlternatives(_grid));

    if (cell_copy_ptr->ReturnNumberOfPossibleValues() < 4)
    {
        // The Cell has two possible values.
        // Choose the first one and see if that works.
        value_under_evaluation = cell_copy_ptr->possible_values.at(0);
        cell_copy_ptr->solved_value = value_under_evaluation;
    
        // Remove it from my list of possible values.
        std::cout << "Setting solved value (" << value_under_evaluation << ") and removing from possible list: " << cell_copy_ptr->my_coordinates.row << "," << cell_copy_ptr->my_coordinates.column << std::endl;
        cell_copy_ptr->possible_values.erase(std::remove(cell_copy_ptr->possible_values.begin(), cell_copy_ptr->possible_values.end(), value_under_evaluation), cell_copy_ptr->possible_values.end());        

        // If this value is present in peers, remove it.
        for (size_t j = 0; j < NUM_PEERS; j++)
        {
            if ( std::find(cell_copy_ptr->peers[j]->possible_values.begin(), cell_copy_ptr->peers[j]->possible_values.end(), value_under_evaluation) != cell_copy_ptr->peers[j]->possible_values.end() ){
                // The value is available, remove it from possible values.
                std::cout << "Removing (" << value_under_evaluation << ") from peer possible list: " << cell_copy_ptr->peers[j]->my_coordinates.row << "," << cell_copy_ptr->peers[j]->my_coordinates.column << std::endl;
                cell_copy_ptr->peers[j]->possible_values.erase(std::remove(cell_copy_ptr->peers[j]->possible_values.begin(), cell_copy_ptr->peers[j]->possible_values.end(), value_under_evaluation), cell_copy_ptr->peers[j]->possible_values.end());                    
            }
PrintGrid(_grid);
        }
    } else std::cout << "There are only cells with four or more alternatives, use brute force." << std::endl;

    if( SolveDifficult(_grid)){
        ret_val = true;
    } else {

        // Solved value restore and put failed value at the end of the vector.
        cell_copy_ptr->possible_values.push_back(value_under_evaluation);
        cell_copy_ptr->solved_value = 0;
    }

// ALTERNATIVE 2
    // Find the Cell with the lowest number of possible entries.
    // Set first value and evaluate using brute force...
/*     std::pair<int,int> row_and_column = ReturnCellWithFewestAlternatives(_grid);

    row = row_and_column.first;
    column = row_and_column.second;

    if (_grid[row][column].ReturnNumberOfPossibleValues() == 2)
    {
        // The Cell has two possible values.
        // Choose the first one and see if that works.
        value_under_evaluation = _grid[row][column].possible_values.at(0);
        _grid[row][column].solved_value = value_under_evaluation;
    
        // Remove it from my list of possible values.
        std::cout << "Setting solved value (" << value_under_evaluation << ") and removing from possible list: " << row << "," << column << std::endl;
        _grid[row][column].possible_values.erase(std::remove(_grid[row][column].possible_values.begin(), _grid[row][column].possible_values.end(), value_under_evaluation), _grid[row][column].possible_values.end());        

        // If this value is present in peers, remove it.
        for (size_t j = 0; j < NUM_PEERS; j++)
        {
            if ( std::find(_grid[row][column].peers[j]->possible_values.begin(), _grid[row][column].peers[j]->possible_values.end(), value_under_evaluation) != _grid[row][column].peers[j]->possible_values.end() ){
                // The value is available, remove it from possible values.
                std::cout << "Removing (" << value_under_evaluation << ") from peer possible list: " << _grid[row][column].peers[j]->my_coordinates.row << "," << _grid[row][column].peers[j]->my_coordinates.column << std::endl;
                _grid[row][column].peers[j]->possible_values.erase(std::remove(_grid[row][column].peers[j]->possible_values.begin(), _grid[row][column].peers[j]->possible_values.end(), value_under_evaluation), _grid[row][column].peers[j]->possible_values.end());                    
            }
PrintGrid(_grid);
        }
    } else std::cout << "There are only cells with three or more alternatives, use brute force." << std::endl;

 */
// END OF ALTERNATIVES


    PrintGrid(_grid);

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

    return ret_val;
}

// END OF SUPPORT FUNCTIONS TO BE MOVED TO SEPARATE CPP-FILE
// ---------------------------------------------------------


// Move to other cpp-file...
// Not yet in use...
bool Cell::EvaluateCandidates(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]){ 

        bool ret_val = false;
        Cell *cell_ptr = &_grid[this->my_coordinates.row][this->my_coordinates.column];
        Cell *cell_copy_ptr = &_grid_copy[this->my_coordinates.row][this->my_coordinates.column];


        // Test with the first candidate, then the second etc...
        // Loop for nr of candidates
        size_t nr_candidates = this->ReturnNumberOfPossibleValues();

        for (size_t i = 0; i < nr_candidates; i++)
        {
           if(!NumberCheck(i)){
                // The proposed number candidate is not used by peers,
                // Set as solved value.
                // Then call recursively and test next empty cell.

                this->solved_value = this->possible_values.at(i);

                // Remove this candidate from all my peers
                // Erase candidate from my list of possible candidates...!
                //this->possible_values.erase(this->possible_values.begin());  // Removes the first item
                std::cout << "Setting solved value and removing from possible list: " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;
                this->possible_values.erase(std::remove(this->possible_values.begin(), this->possible_values.end(), this->solved_value), this->possible_values.end());                
//                cell_copy_ptr->possible_values.erase(cell_copy_ptr->possible_values.begin() + i);

                for (size_t j = 0; j < NUM_PEERS; j++)
                {
                    if ( std::find(peers[j]->possible_values.begin(), peers[j]->possible_values.end(), this->solved_value) != peers[j]->possible_values.end() ){
                        // The value is available, remove it from possible values.
                        std::cout << "Removing from peer possible list: " << this->solved_value << std::endl;
                        peers[j]->possible_values.erase(std::remove(peers[j]->possible_values.begin(), peers[j]->possible_values.end(), this->solved_value), peers[j]->possible_values.end());                    
                    }
                }

                for (size_t j = 0; j < NUM_PEERS; j++)
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
                        ret_val = true;
                        break;
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
                } else {
                    ret_val = false;  // No more 
                    break;
                }
            }        
        }

    return ret_val;   
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

