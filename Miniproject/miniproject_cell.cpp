#include <mini_def.h>

// Initialize cells
bool Cell::InitCell(Cell (&_grid)[9][9], size_t &_row, size_t &_column){

//    Cell *grid_ptr = &(_grid[0][0]); // Points to the top of the Grid[0][0]
//    Cell *my_cell_ptr = &(_grid[_row][_column]);
//    Cell *peer_cell_ptr = nullptr;

    // Receive the instantiated Cell coordinates
    // Init possible value
    // Init all peers
    this->solved_value_b = 0x0000; // Contains the solved value, contains 0 if unsolved.
    this->solved_value = 0; // Contains the solved value, contains 0 if unsolved.
    this->my_coordinates.row = _row;
    this->my_coordinates.column = _column;

    // Set the top left coordinates of my square.
    SetTopLeft(_grid[this->my_coordinates.row][this->my_coordinates.column]);

    // Init possible values
    this->possible_values_b = 0x01FF;
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



bool SetTopLeft(Cell &_cell){

    bool ret_val = true;
    size_t row = _cell.my_coordinates.row;
    size_t column = _cell.my_coordinates.column;

    if (row < 3 )
    {
        _cell.my_coordinates.box_top_row = 0;
    } else if ( (2 < row) && (row < 6) )
    {
        _cell.my_coordinates.box_top_row = 3;
    } else if ( (5 < row) && (row < 9) ) 
    {
        _cell.my_coordinates.box_top_row = 6;
    } else {
        std::cout << "Row is out of bounds." << std::endl;
        ret_val = false;
    }

    if (column < 3 )
    {
        _cell.my_coordinates.box_left_column = 0;
    } else if ( (2 < column) && (column < 6) )
    {
        _cell.my_coordinates.box_left_column = 3;
    } else if ( (5 < column) && (column < 9) ) 
    {
        _cell.my_coordinates.box_left_column = 6;
    } else {
        std::cout << "Column is out of bounds." << std::endl;
        ret_val = false;
    }

    return ret_val;
}

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
