#ifndef MINI_DEF_H
#define MINI_DEF_H
#include <iostream>
#include <fstream> // for reading input file
#include <cstdlib> // for exit function
#include <vector> 
#include <algorithm> // To search in vector. Can be removed when bits are introduced.

// Data structures

typedef struct position{
    size_t row;
    size_t column;
    size_t box_top_row;
    size_t box_left_column;    
}Pos_t;

class Cell{
// Variables

    std::vector<Cell*> peers;

    bool CheckMyRow(size_t candidate_index);
    bool CheckMyColumn(size_t candidate_index);
    bool CheckMyBox(size_t candidate_index);

public:
    std::vector<size_t> possible_values;
    size_t solved_value;   // Hide in function
    Pos_t my_coordinates;  // Hide in function
// Methods
    bool InitCell(Cell (&_grid)[9][9],Cell (&_grid_copy)[9][9], size_t &_row, size_t &_column);    
    bool IdentifyCandidates();
    bool EvaluateCandidates(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]);
    size_t ReturnNumberOfPossibleValues();
    size_t ReturnNumberOfPeers();    
    bool NumberCheck(size_t candidate_index);

};

// Data declarations

// Function declarations
bool ImportDataFromFile(Cell (&_grid)[9][9]);
bool PrintGrid(Cell (&_grid)[9][9]);
Cell* ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]);
bool CopyGrid(Cell (&_grid_copy)[9][9], Cell (&_grid)[9][9]);
bool SolveSudokuBF(Cell *_cell_ptr, Cell (&_grid)[9][9]);

size_t Cell::ReturnNumberOfPossibleValues(){

    return(this->possible_values.size());
}

size_t Cell::ReturnNumberOfPeers(){

    return(this->peers.size());
}


#endif // MINI_DEF_H
