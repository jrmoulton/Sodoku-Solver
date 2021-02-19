#include "sudoku.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "vec2.h"

/*
Summary: A function to set the invalid positions back to 0 and set the position
            recursively to the last avaliable position
Begin:
    if the position is at 0,0 and there is nothing left to change:
        print unsolvable
    if the puzzle position is changeable:
        set to 0
    if x is 0:
        move the y back one and set x = 8
    else:
        move x back one
    while pos is not changeable:
        recurse move_back
    return new pos
End
*/
vec2i Sudoku::move_back(vec2i pos) {
    // if the position is at 0,0 and there is nothing left to change:
    if (pos.x == 0 && pos.y == 0 &&
        (puzzle_og[pos.y][pos.x] == true || puzzle[pos.y][pos.x] == 9)) {
        // print unsolvable
        std::cout << "Unsolvable" << std::endl;
        exit(EXIT_FAILURE);
    }
    // if the puzzle position is changeable:
    if (puzzle_og[pos.y][pos.x] == false) {
        puzzle[pos.y][pos.x] = 0;  // set to 0
    }
    // if x is 0:
    if (pos.x == 0) {
        // move the y back one and set x = 8
        pos.y -= 1;
        pos.x = 8;
    } else {         // else:
        pos.x -= 1;  // move x back one
    }
    // while pos is not changeable:
    while (puzzle_og[pos.y][pos.x] == true) {
        // recurse move_back
        pos = Sudoku::move_back({pos});
    }
    return pos;  // return new pos
}

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
void Sudoku::solve() {
    // initialize variables
    int test_num = 1;
    vec2i pos = {0, 0};
    // loop through y values:
    for (; pos.y < 9; pos.y++) {
        // set pos.x = 0
        pos.x = 0;
        // loop through x values:
        while (pos.x < 9) {
            // if pos is changeable:
            if (!(puzzle_og[pos.y][pos.x] == true)) {
                // set the number to test to 1 if it is 0 otherwise itself
                test_num =
                    (puzzle[pos.y][pos.x] == 0) ? 1 : puzzle[pos.y][pos.x];
                // while test_num < 10:
                while (test_num < 10) {
                    // if pos and num is valid:
                    if (pos_is_valid(pos, test_num)) {
                        // set that pos to that num
                        puzzle[pos.y][pos.x] = test_num;
                        break;
                        // else:
                    } else {
                        // increment the test num to check another position
                        test_num += 1;
                    }
                }
                // if no test nums worked in that position:
                if (test_num > 9) {
                    // move_back and get new pos
                    pos = Sudoku::move_back(pos);
                    // else if the test num did work:
                } else {
                    // increment the position
                    pos.x += 1;
                }
                // else catch case that test_num worked:
            } else {
                // increment pos.x
                pos.x += 1;
            }
        }
    }
}

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
std::vector<int> Sudoku::get_block(vec2i pos) {
    // initialize variables
    std::vector<int> vec;
    int start_y = int(pos.y / 3) * 3;
    int end_y = start_y + 3;
    int start_x = int(pos.x / 3) * 3;
    int end_x = start_x + 3;
    // loop through y values:
    for (int y = start_y; y < end_y; y++) {
        // loop through x values:
        for (int x = start_x; x < end_x; x++) {
            // push values to vec
            vec.push_back(puzzle[y][x]);
        }
    }
    // return vec
    return vec;
}

/*
Summary: A function to get a column
Begin:
    initialize vec and push values to it
    return vec
End
*/
std::vector<int> Sudoku::get_column(vec2i pos) {
    // initialize vec and push values to it
    std::vector<int> vec(puzzle[pos.y], puzzle[pos.y] + 9);
    // return vec
    return vec;
}

/*
Summary: A function to get a row
Begin:
    initialize vec and push values to it
    return vec
End
*/
std::vector<int> Sudoku::get_row(vec2i pos) {
    // initialize vec and push values to it
    std::vector<int> vec;
    for (int i = 0; i < 9; i++) {
        vec.push_back(puzzle[i][pos.x]);
    }
    // return vec
    return vec;
}

/*
Summary: A function to see if there are no conflicts in rows, columns or blocks
Begin:
    loop through all vectors and if there is a single value match return false
End
*/
bool Sudoku::pos_is_valid(vec2i pos, int val) {
    // loop through all vectors and if there is a single value match return
    // false
    for (auto i : Sudoku::get_block(pos)) {
        if (i == val) {
            return false;
        }
    }
    for (auto i : Sudoku::get_column(pos)) {
        if (i == val) {
            return false;
        }
    }
    for (auto i : Sudoku::get_row(pos)) {
        if (i == val) {
            return false;
        }
    }
    return true;
}

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
Sudoku::Sudoku(int n) {
    // initialize variables
    vec2i rand_pos;
    int rand_val;
    int count;
    // loop n number of times
    for (int i = 0; i < n; i++) {
        // get random position and number
        count = 0;
        rand_pos.y = rand() % 9;
        rand_pos.x = rand() % 9;
        rand_val = rand() % 9 + 1;
        // if position is not valid:
        while (!pos_is_valid(rand_pos, rand_val) ||
               puzzle[rand_pos.y][rand_pos.x] != 0) {
            // get another random position and number
            rand_pos.y = rand() % 9;
            rand_pos.x = rand() % 9;
            rand_val = rand() % 9 + 1;
            count += 1;
            // if we sit in this loop too long exit with error
            if (count > 2000000) {
                std::cerr << "Could not find an available spot when generating "
                             "the puzzle"
                          << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        // else set pos and mark as unchangable
        puzzle[rand_pos.y][rand_pos.x] = rand_val;
        puzzle_og[rand_pos.y][rand_pos.x] = true;
    }
}

/*
Summary: An overloaded function to print a formatted sodoku puzzle
*/
std::ostream& operator<<(std::ostream& os, const Sudoku& m) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (m.puzzle[i][j] != 0) {
                os << " " << m.puzzle[i][j] << " ";
            } else {
                os << " "
                   << "*"
                   << " ";
            }
            if (j % 3 == 2 && j != 8) {
                std::cout << "|";
            } else {
                os << " ";
            }
        }

        os << "\n";
        if (i % 3 == 2 && i != 8) {
            os << (std::string(11, '-')).append("+")
               << (std::string(11, '-')).append("+") << std::string(12, '-');
        } else if (i < 8) {
            os << (std::string(11, ' ')).append("|")
               << (std::string(11, ' ')).append("|");
        }
        os << "\n";
    }
    return os;
}