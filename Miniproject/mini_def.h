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
    Square();
//    void InitSquare(size_t &_row, size_t &_column);
//    void Square::InitSquare(Square *_grid, size_t &_row, size_t &_column);
    void Square::InitSquare(Square (&_grid)[9][9], size_t &_row, size_t &_column);
    void IdentifyPossibleValues();

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
// Taken from brute force version, perhaps not needed!?
void ImportDataFromFile();
void PrintGrid();


// Initialize the squares
void Square::InitSquare(Square (&_grid)[9][9], size_t &_row, size_t &_column){

    Square *grid_ptr = &_grid[0][0]; // Points to the top of the, Grid[0][0]
    Square *my_square_ptr = nullptr;
    Square *peer_square_ptr = nullptr;

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
    ----->  peers.size()
    for (size_t i = 0; i < 9; i++)
    {
        if (i!=my_coordinates.row) // Do not add myself
        {
            this->peers.push_back(peer_square_ptr); // Create new entry
            this->peers[i] = &_grid[my_coordinates.row-1][i];
        }
    }
    // Add all unit peers, disregard my position
    for (size_t i = (my_coordinates.row - my_coordinates.row % 3); i < ((my_coordinates.row - my_coordinates.row % 3)+3); i++)
    {
        for (size_t j = (my_coordinates.column - my_coordinates.column % 3); j < ((my_coordinates.column - my_coordinates.column % 3)+3); j++){

            // Do not add myself or those added by my row or column.
            if ( (i != my_coordinates.row ) && ( j != my_coordinates.column) ) // Do not add myself
            {
                this->peers.push_back(peer_square_ptr); // Create new entry
                this->peers[i] = &_grid[my_coordinates.row-1][i];



                peers.push_back(position()); // Create new entry
                peers[i].row = i;
                peers[i].column = j;
            }
        }
    }
}
// Find values that are not identified in peers.
void Square::IdentifyPossibleValues(){

    for (size_t i = 0; i < this->peers.size(); i++)
    {
        if ( this->peers.at(i).......  != 0 )p
        {
            this->possible_values.push_back(size_t);
//            this->possible_values[i] = Grid[this->peers.at(i).row][this->peers.at(i).column].solved_value;
        }
    }
    
    // If there is only one possible solution 
    // set solved_value
    if(this->possible_values.size() == 1){

        this->solved_value = this->possible_values.front();
    }
}



#endif // MINI_DEF_H
