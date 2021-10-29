#ifndef MINI_DEF_H
#define MINI_DEF_H
#include <iostream>
#include <fstream>      // for reading input file
#include <cstdlib>      // for exit function
#include <vector> 
#include <algorithm>    // To search in vector. TODO: Can be removed when bits are introduced.
#include <chrono>       // Use for (time) performance measure...

// Definitions
const size_t NUM_PEERS = 20;

// Data structures

typedef struct position{
    size_t row;
    size_t column;
    size_t box_top_row;
    size_t box_left_column;    
}Pos_t;

typedef struct candidate_field{
    unsigned  c1:1;
    unsigned  c2:2;
    unsigned  c3:3;
    unsigned  c4:4;      
    unsigned  c5:5;
    unsigned  c6:6;
    unsigned  c7:7;
    unsigned  c8:8;           
    unsigned  c9:9;           
}Candidate_T;

typedef struct mask_field{
    uint16_t mask1 = 0b0000000000000001;
    uint16_t mask2 = 0b0000000000000010;
    uint16_t mask3 = 0b0000000000000100;
    uint16_t mask4 = 0b0000000000001000;
    uint16_t mask5 = 0b0000000000010000;
    uint16_t mask6 = 0b0000000000100000;
    uint16_t mask7 = 0b0000000001000000;
    uint16_t mask8 = 0b0000000010000000;
    uint16_t mask9 = 0b0000000100000000;
}Mask_T;

class Cell{
// Variables

public:

    uint16_t possible_values_b;
    uint16_t solved_value_b;
    std::vector<size_t> possible_values;
    std::vector<Cell*> peers;    
    size_t solved_value;   // Hide in function
    Pos_t my_coordinates;  // Hide in function
// Methods
    bool InitCell(Cell (&_grid)[9][9], size_t &_row, size_t &_column);    
    bool IdentifyCandidates();
    bool EvaluateCandidates(Cell (&_grid)[9][9], Cell (&_grid_copy)[9][9]);
    bool NumberCheck(size_t candidate_index);
    size_t ReturnNumberOfPossibleValues();
};

// Data declarations

// Function declarations
bool ImportDataFromFile(Cell (&_grid)[9][9]);
bool PrintGrid(Cell (&_grid)[9][9]);
std::pair<int,int> ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]);
Cell& _ReturnCellWithFewestAlternatives(Cell (&_grid)[9][9]);
bool CopyGrid(Cell (&_grid_copy)[9][9], Cell (&_grid)[9][9]);
bool CheckRow(Cell (&_grid)[9][9], int row,int column,int candidate);
bool CheckColumn(Cell (&_grid)[9][9], int row,int column,int candidate);
bool CheckBox(Cell (&_grid)[9][9], int first_box_row,int first_box_column,int candidate);
bool NumberCheck(Cell (&_grid)[9][9], size_t _row,size_t _column,size_t candidate);
std::pair<int,int> GetEmptyCell(Cell (&_grid)[9][9] );
bool SolveSudokuBF(Cell (&_grid)[9][9]);

inline size_t Cell::ReturnNumberOfPossibleValues(){

    return(this->possible_values.size());
}

#endif // MINI_DEF_H
