#include <mini_def.h>


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