#include "mini_def.h"
// ---------------------------------------------------------
// FUNCTIONS THAT WERE MOVED FROM HEADER FILE TO HERE FOR DEBUGGING PURPOSES

// Initialize cells
bool Cell::InitCell(Cell (&_grid)[9][9],Cell (&_grid_copy)[9][9], size_t &_row, size_t &_column){

    Cell *grid_ptr = &(_grid[0][0]); // Points to the top of the Grid[0][0]
    Cell *grid_copy_ptr = &(_grid_copy[0][0]); // TBD: Points to the top of the sandbox (sb) Grid[0][0]    
    Cell *my_cell_ptr = &(_grid[_row - 1][_column - 1]);
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
    if (_row < 4 )
    {
        this->my_coordinates.box_top_row = 1;
    } else if (3 < _row < 7 )
    {
        this->my_coordinates.box_top_row = 4;
    } else if ( 6 < _row )
    {
        this->my_coordinates.box_top_row = 7;
    }

    if (_column < 4 )
    {
        this->my_coordinates.box_left_column = 1;
    } else if (3 < _row < 7 )
    {
        this->my_coordinates.box_left_column = 4;
    } else if ( 6 < _row )
    {
        this->my_coordinates.box_left_column = 7;
    }
    

    // Init possible values
    for (size_t i = 1; i < 10; i++)
    {
        possible_values.push_back(i);
    }
    // Init list of my peers
    // Add all row peers, disregard my position
    for (size_t i = 0; i < 9; i++)
    {
        if (i != (this->my_coordinates.column - 1)) // Do not add myself
        {
            // Create new entry of Cell pointer in peer vector
            // Point peer_cell_ptr to the correct cell.
            this->peers.push_back(&(_grid[my_coordinates.row-1][i]));             
// FEL?            this->peers.push_back(&(_grid[i][my_coordinates.column-1])); 
            number_of_peers++;
// std::cout << "Row peer added, the current number of peers are: " << number_of_peers << std::endl;

        }
    }
    // Add all column peers, disregard my position
    for (size_t i = 0; i < 9; i++)
    {
        if (i != (my_coordinates.row - 1)) // Do not add myself
        {
            // Create new entry of Cell pointer in peer vector
            // Point peer_cell_ptr to the correct cell.
            this->peers.push_back(&(_grid[i][my_coordinates.column-1])); 
            number_of_peers++;
// std::cout << "Column peer added, the current number of peers are: " << number_of_peers << std::endl;
        }
    }
    // Add all unit peers, disregard my position
    for (size_t i = ((my_coordinates.row -1 ) - (my_coordinates.row - 1) % 3); i < (((my_coordinates.row - 1) - (my_coordinates.row - 1) % 3) + 3); i++)
    {
        for (size_t j = ((my_coordinates.column - 1) - (my_coordinates.column - 1) % 3); j < (((my_coordinates.column - 1) - (my_coordinates.column - 1) % 3) + 3); j++){

            // Do not add myself or those added by my row or column.
            if ( (i != (my_coordinates.row - 1) ) && ( j != (my_coordinates.column - 1)) ) // Do not add myself or any peer in my row or column
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

/*     if(CheckMyRow(candidate_index) && CheckMyColumn(candidate_index) && CheckMyBox(candidate_index)){
        return true;
    }
    return false;
 */
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
    Cell *closest_ptr = nullptr;
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
                closest_ptr = cell_ptr;
//                std::cout << "New smallest detected: " << smallest_found << std::endl;

            }
            
        }
    }
    return closest_ptr;    
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




// END OF SUPPORT FUNCTIONS TO BE MOVED TO SEPARATE CPP-FILE
// ---------------------------------------------------------


// Move to header file...
// Solves sudoku brute force method.
bool Cell::EvaluateCandidates(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]){ 

        Cell *cell_ptr = &_grid[this->my_coordinates.row -1][this->my_coordinates.column -1];
        Cell *cell_copy_ptr = &_grid_copy[this->my_coordinates.row -1][this->my_coordinates.column -1];


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
//        std::cout << "The table is filled in. First check!" << std::endl;
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


int main(){

    Cell Grid[9][9];  // Global, on stack
    Cell GridCopy[9][9];  // Global, on stack

    Cell *cell_ptr = nullptr;
    Cell *cell_copy_ptr = nullptr;    
    bool value_added = false;

    // Init grid
    size_t a,b;
    for (size_t i = 0; i < 9; i++)
    {
        a = i + 1;
        for (size_t j = 0; j < 9; j++)
        {   
            b = j + 1;
            cell_ptr = &(Grid[i][j]); 
            cell_ptr->InitCell(Grid,GridCopy,a,b);
        }
    }

    // Grid initialized
    // Import table to be solved
    ImportDataFromFile(Grid);

    // Print original table

    std::cout << "Input table:" << std::endl;

    PrintGridSimple(Grid);

    // Identify possible values and solve the easy ones
    // TODO: move to separate function
    do
    {
        value_added = false;

        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {    
                cell_ptr = &(Grid[i][j]); 
                if(cell_ptr->IdentifyCandidates())
                {
                    value_added = true; // New value solved, make another run.
                }
            }
        }
    } while (value_added);
    

    // Print data for comparison
    std::cout << "Intermediary result using constraint propagation:" << std::endl;
    PrintGridSimple(Grid);

    // Make a sandbox table to play around in
    // Make a copy of the grid and print it for comparison
    if (CopyGrid(Grid,GridCopy)) {
//        std::cout << "Copy of Grid:" << std::endl;
//        PrintGrid(GridCopy);
    }


    // Find the Cell with the lowest number of possible entries.
    // Set first value and evaluate using brute force...

    cell_copy_ptr = ReturnCellWithFewestAlternatives(GridCopy);

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

//    } else std::cout << "Table filled in, brute force not needed." << std::endl;


    return(0);
}

