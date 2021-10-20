#include "mini_def.h"
// ---------------------------------------------------------
// FUNCTIONS THAT WERE MOVED FROM HEADER FILE TO HERE FOR DEBUGGING PURPOSES

// Initialize cells
void Cell::InitCell(Cell (&_grid)[9][9], size_t &_row, size_t &_column){

    Cell *grid_ptr = &(_grid[0][0]); // Points to the top of the, Grid[0][0]
    Cell *my_cell_ptr = &(_grid[_row - 1][_column - 1]);
    Cell *peer_cell_ptr = nullptr;
    size_t number_of_peers = 0;

    // Receive the instantiated Cell coordinates
    // Init possible value
    // Init all peers
    this->solved_value = 0; // Contains the solved value, contains 0 if unsolved.
    this->my_coordinates.row = _row;
    this->my_coordinates.column = _column;

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
            this->peers.push_back(&(_grid[i][my_coordinates.column-1])); 
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
            this->peers.push_back(&(_grid[my_coordinates.row-1][i])); 
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
}

// Find values that are not identified in peers.
bool Cell::IdentifyCandidates(){

    Cell *peer_cell_ptr;
    size_t number_of_peers = this->peers.size();
    size_t number_of_possible_values = this->possible_values.size();

//     std::cout << "Identifying values in: " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;

    if (this->solved_value)
    {
//         std::cout << "Value given at start: " << this->solved_value << " in " << this->my_coordinates.row << "," << this->my_coordinates.column << std::endl;

        // This Cell has a solved value.
        // Clear all other possible values.
        this->possible_values.clear();
    } else {

        // For every peer...
        for (size_t i = 0; i < number_of_peers; i++)
        {
            // ...check if the solved_value is anything but 0
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
    Cell *closest_ptr, *cell_ptr;
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
std::cout << "New smallest detected: " << smallest_found << std::endl;

            }
            
        }
    }
    return closest_ptr;    
}

void ImportDataFromFile(Cell (&_grid)[9][9]){

    std::ifstream indata ("inputfile.txt");

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

    return;
}


void PrintGrid(Cell (&_grid)[9][9]){

    int row = 0, column = 0;

    std::cout << "----------------------------" << std::endl;

    for(row = 0; row < 9; row++){
        for(column = 0; column < 9; column++)
        {
            std::cout << _grid [row] [column].solved_value << " ";
        }
        std::cout << std::endl;
    }
}


// END OF SUPPORT FUNCTIONS TO BE MOVED TO SEPARATE CPP-FILE
// ---------------------------------------------------------


int main(){

    Cell Grid[9][9];  // Global, on stack
    Cell *cell_ptr;
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
            cell_ptr->InitCell(Grid,a,b);
        }
    }

    // Grid initialized
    // Import table to be solved
    ImportDataFromFile(Grid);

    // Print original table
    std::cout << "Input table:" << std::endl;
    PrintGrid(Grid);


    // Identify possible values and solve the easy ones
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
    std::cout << "Intermediary result:" << std::endl;
    PrintGrid(Grid);

    // Find the Cell with the lowest number of possible entries.
    cell_ptr = ReturnCellWithFewestAlternatives(Grid);

    // Make a sandbox table and play around in that
    // Full copy or simple copy?
    // Select the first alternative and call IdentifyCandidates()
    // Probably need recursive call...
    


    return(0);
}

