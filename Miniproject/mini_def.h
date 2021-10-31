#ifndef MINI_DEF_H
#define MINI_DEF_H
#include <iostream>
#include <fstream>      // for reading input file
#include <cstdlib>      // for exit function
#include <bitset>
#include <vector> 
#include <algorithm>    // To search in vector. TODO: Can be removed when bits are introduced.
#include <chrono>       // Use for (time) performance measure...

// Definitions
#define SET(x,y) x |= (1 << y)
#define CLEAR(x,y) x &= ~(1<< y)
#define READ(x,y) ((0u == (x & (1<<y)))?0u:1u)
#define TOGGLE(x,y) (x ^= (1<<y))  // May not be needed
#define VALUE1 0
#define VALUE2 1
#define VALUE3 2
#define VALUE4 3
#define VALUE5 4
#define VALUE6 5
#define VALUE7 6
#define VALUE8 7
#define VALUE9 8
#define SET_ALL_VALUES 0b0000000011111111
#define CLEAR_ALL_VALUES 0b1111111100000000

const size_t NUM_PEERS = 20;

// Data structures

typedef struct position{
    size_t row;
    size_t column;
    size_t box_top_row;
    size_t box_left_column;    
}Pos_t;

typedef struct Unit{

    size_t unit_nr;         // Which row, column or box am I. For box: numbered 0 through 8: row 0 column 0 -> box 0, row 1 col 0 -> box 3...
    uint16_t unit_state_b;  // bit 0-8 cell value set, bit 9 unit complete
}Unit_t;

class Grid{

    Unit_t row_unit[9]; 
    Unit_t column_unit[9];
    Unit_t box_unit[9];
    std::pair<size_t,size_t> lowest_nr_of_candidates;   // Cell with lowest number of candidates, first is row, second is column
    size_t number_of_solved_squares;
};


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
bool CheckRow(Cell (&_grid)[9][9],const size_t row,const size_t _candidate);
bool CheckColumn(Cell (&_grid)[9][9],const size_t column,const size_t _candidate);
bool CheckBox(Cell (&_grid)[9][9],const size_t row,const size_t column,const size_t _candidate);
bool NumberCheck(Cell (&_grid)[9][9], size_t _row,size_t _column,size_t candidate);
std::pair<int,int> GetEmptyCell(Cell (&_grid)[9][9] );
bool SolveSudokuBF(Cell (&_grid)[9][9]);
bool SetTopLeft(Cell &_cell);


inline size_t Cell::ReturnNumberOfPossibleValues(){

    return(this->possible_values.size());
}

#endif // MINI_DEF_H
