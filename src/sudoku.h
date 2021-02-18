
#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>

#include "vec2.h"

class Sudoku {
   public:
    int puzzle[9][9] = {{0}};
    bool puzzle_og[9][9] = {{false}};

    Sudoku(int n);

    bool pos_is_valid(vec2i pos, int val);
    std::vector<int> get_row(vec2i pos);
    std::vector<int> get_column(vec2i pos);
    std::vector<int> get_block(vec2i pos);
    vec2i move_back(vec2i pos);
    void solve();
};
std::ostream& operator<<(std::ostream& os, const Sudoku& m);

#endif