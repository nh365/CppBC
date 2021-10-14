#ifndef MINIBF_DEF_H
#define MINIBF_DEF_H
#include <iostream>
#include <fstream> // for reading input file
#include <cstdlib> // for exit function

// Data structures

typedef struct sudoku_entry{
    int value;
    bool verified;
}SE_t;


// Function declarations
void ImportDataFromFile();
void PrintCompletedData();
std::pair<int,int> GetEmptyCell();
bool CheckRow(int row,int column,int candidate);
bool CheckColumn(int row,int column,int candidate);
bool CheckBox(int first_box_row,int first_box_column,int candidate);
bool NumberCheck(int row,int column,int candidate);
bool SolveSudokuBF();






#endif // MINIBF_DEF_H
