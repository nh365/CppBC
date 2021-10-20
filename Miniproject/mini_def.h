#ifndef MINI_DEF_H
#define MINI_DEF_H
#include <iostream>
#include <fstream> // for reading input file
#include <cstdlib> // for exit function
#include <vector> 

// Data structures

typedef struct position{
    size_t row;
    size_t column;
}Pos_t;

class Square{
// Variables
    Pos_t my_coordinates;
    std::vector<size_t> possible_values;
    std::vector<Square*> peers;

public:
    size_t solved_value;

// Methods
    // Default constructor
//    Square();
    void InitSquare(Square (&_grid)[9][9], size_t &_row, size_t &_column);
    bool IdentifyPossibleValues();
    size_t ReturnNumberOfPossibleValues();

/*     void SetValue(const int &_val){
        this->solved_value = _val;
    }
 */
/*     size_t *GetValue(){
        return &solved_value;
    }
 */

};

// Data declarations

// Function declarations
void ImportDataFromFile(Square (&_grid)[9][9]);
void PrintGrid(Square (&_grid)[9][9]);
Square* ReturnSquareWithFewestAlternatives(Square (&_grid)[9][9]);

size_t Square::ReturnNumberOfPossibleValues(){

    return(this->possible_values.size());
}

/* // Initialize the squares
void Square::InitSquare(Square (&_grid)[9][9], size_t &_row, size_t &_column){
//void Square::InitSquare(Square _grid[][9], size_t &_row, size_t &_column){

    Square *grid_ptr = &_grid[0][0]; // Points to the top of the, Grid[0][0]
    Square *my_square_ptr = nullptr;
    Square *peer_square_ptr = nullptr;
    size_t number_of_peers = 0;

    // Receive the instantiated Square coordinates
    // Init possible value
    // Init all peers
    this->solved_value = 0;
    this->my_coordinates.row = _row;
    this->my_coordinates.column = _column;
//    my_square = &grid_ptr[my_coordinates.row][my_coordinates.column];
    my_square_ptr = &_grid[my_coordinates.row-1][my_coordinates.column-1];

    // Init possible values
    for (size_t i = 1; i < 10; i++)
    {
        possible_values.push_back(i);
    }
    // Init list of my peers
    // Add all row peers, disregard my position
    for (size_t i = 0; i < 9; i++)
    {
        if ((i+1)!=this->my_coordinates.column) // Do not add myself
        {
            // Point peer_square_ptr to the correct square.
            this->peers.push_back(peer_square_ptr); // Create new entry
            this->peers[i] = &_grid[i][my_coordinates.column-1];
        }
    }
    // Add all column peers, disregard my position
    // Get the length of the peers vector
    // Really needed??? Always 8?
    number_of_peers = peers.size();
    for (size_t i = 0; i < 9; i++)
    {
        if ((i+1)!=my_coordinates.row) // Do not add myself
        {
            this->peers.push_back(peer_square_ptr); // Create new entry
            this->peers[number_of_peers + i] = &_grid[my_coordinates.row-1][i];
        }
    }
    // Add all unit peers, disregard my position
    // Get the length of the peers vector
    // Really needed??? Always 8?
    number_of_peers = peers.size();
    for (size_t i = (my_coordinates.row - my_coordinates.row % 3); i < ((my_coordinates.row - my_coordinates.row % 3)+3); i++)
    {
        for (size_t j = (my_coordinates.column - my_coordinates.column % 3); j < ((my_coordinates.column - my_coordinates.column % 3)+3); j++){

            // Do not add myself or those added by my row or column.
            if ( (i != (my_coordinates.row - 1) ) && ( j != (my_coordinates.column - 1)) ) // Do not add myself
            {
                this->peers.push_back(peer_square_ptr); // Create new entry
                this->peers[number_of_peers + i] = &_grid[my_coordinates.row-1][i];

            }
        }
    }
    // Print for fun, remove later!
    // Get the length of the peers vector
    // Really needed??? Always 8?
    number_of_peers = peers.size();
    std::cout << "Grid element (r/c): " << my_coordinates.row << "," << my_coordinates.column << "   "; 
    std::cout << "The current number of peers are: " << number_of_peers << std::endl;
} */

// MOVED TO CPP FILE FOR DEBUGGING PURPOSES
/* 
// Find alues that are not identified in peers.
void Square::IdentifyPossibleValues(){

    Square *peer_square_ptr;

    // For every peer...
    for (size_t i = 0; i < this->peers.size(); i++)
    {
        // ...check if the solved_value is anything but 0
        // and if so, remove it from my list of possible values.
        peer_square_ptr = this->peers[i];
        if (peer_square_ptr->solved_value != 0)
        {
            // There is a value defined.
            // Remove this value from my possible values.
            for (size_t i = 0; i < this->possible_values.size(); i++)
            {
                // Is this value the same as my peers?
                if (peer_square_ptr->solved_value == this->possible_values.at(i))
                {
                    // The values match.
                    // Remove it from my list.
                    this->possible_values.erase(this->possible_values.begin() + i);
                    std::cout << "Value: " << peer_square_ptr->solved_value << " erased from possible values vector." << std::endl;
                    break;
                }
                
            }
            
        }
        



// OLD
/*         if ( this->peers.at(i) != 0 ){

            this->possible_values.push_back(size_t);
        } */
/*    }
    
    // If there is only one possible solution 
    // set solved_value
    if(this->possible_values.size() == 1){

        this->solved_value = this->possible_values.front();
    }
} */



#endif // MINI_DEF_H
