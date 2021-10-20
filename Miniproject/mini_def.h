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

class Cell{
// Variables
    Pos_t my_coordinates;
    std::vector<size_t> possible_values;
    std::vector<Cell*> peers;

public:
    size_t solved_value;

// Methods
    bool InitCell(Cell (&_grid)[9][9], size_t &_row, size_t &_column);
    bool IdentifyCandidates();
    size_t ReturnNumberOfPossibleValues();

};

// Data declarations

// Function declarations
bool ImportDataFromFile(Cell (&_grid)[9][9]);
bool PrintGrid(Cell (&_grid)[9][9]);
Cell* ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]);

size_t Cell::ReturnNumberOfPossibleValues(){

    return(this->possible_values.size());
}


#endif // MINI_DEF_H
