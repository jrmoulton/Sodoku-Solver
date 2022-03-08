
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

    /*
    Summary: An initializer function to generate a puzzle given a number of
                positions to prefill
    Begin:
        initialize variables
        loop n number of times
        get random position and number
        if position is not valid:
            get another random position and number
            if we sit in this loop too long exit with error
        else set pos and mark as unchangable
    End
    */
    Sudoku(int n);

    /*
    Summary: A function to see if there are no conflicts in rows, columns or
    blocks Begin: loop through all vectors and if there is a single value match
    return false End
    */
    bool pos_is_valid(vec2i pos, int val);

    /*
    Summary: A function to get a row
    Begin:
        initialize vec and push values to it
        return vec
    End
    */
    std::vector<int> get_row(vec2i pos);

    /*
    Summary: A function to get a column
    Begin:
        initialize vec and push values to it
        return vec
    End
    */
    std::vector<int> get_column(vec2i pos);

    /*
    Summary: A function to get a block
    Begin:
        initialize variables
        loop through y values:
            loop through x values:
            push values to vec
        return vec
    End
    */
    std::vector<int> get_block(vec2i pos);

    /*
    Summary: A function to set the invalid positions back to 0 and set the
    position recursively to the last avaliable position Begin: if the position
    is at 0,0 and there is nothing left to change: print unsolvable if the
    puzzle position is changeable: set to 0 if x is 0: move the y back one and
    set x = 8 else: move x back one while pos is not changeable: recurse
    move_back return new pos End
    */
    vec2i move_back(vec2i pos);

    /*
    Summary: A function that implements the backtracing algorithm to solve a
                pre-generated sudoku puzzle
    Begin:
        initialize variables
        loop through y values:
            set pos.x = 0
            loop through x values:
                if pos is changeable:
                    set the number to test to 1 if it is 0 otherwise itself
                    while test_num < 10:
                        if pos and num is valid:
                            set that pos to that num
                        else:
                            increment the test num to check another position
                    if no test nums worked in that position:
                        move_back and get new pos
                    else if the test num did work:
                        increment the position
                else catch case that test_num worked:
                    increment pos.x
    End
    */
    void solve();

    friend std::ostream &operator<<(std::ostream &os, const Sudoku &m);
};

/*
Summary: An overloaded function to print a formatted sodoku puzzle
*/
std::ostream &operator<<(std::ostream &os, const Sudoku &m);

#endif
