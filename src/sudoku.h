
#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>

#include "vec2.h"

/*
Summary: A container to hold the array of numbers and the original positions
            and prototype the class methods
Begin:
   initialize the puzzle to 0 and the original positions to 0
   Declare the function prototypes
End
*/
class Sudoku {
   private:
    // initialize the puzzle to 0 and the original positions to 0
    int puzzle[9][9] = {{0}};
    bool puzzle_og[9][9] = {{false}};

   public:
    // Declare the function prototypes
    Sudoku(int n);

    bool pos_is_valid(vec2i pos, int val);
    std::vector<int> get_row(vec2i pos);
    std::vector<int> get_column(vec2i pos);
    std::vector<int> get_block(vec2i pos);
    vec2i move_back(vec2i pos);
    void solve();
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& m);
};
std::ostream& operator<<(std::ostream& os, const Sudoku& m);

#endif