#include "sudoku.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "vec2.h"

vec2i Sudoku::move_back(vec2i pos) {
    if (pos.x == 0 && pos.y == 0 &&
        (puzzle_og[pos.y][pos.x] == true ||
         puzzle[pos.y][pos.x] ==
             9)) {  // if first aval. pos. and highest test_num
        std::cout << "Unsolvable" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (puzzle_og[pos.y][pos.x] == false) {
        puzzle[pos.y][pos.x] = 0;
    }
    if (pos.x == 0) {
        pos.y -= 1;
        pos.x = 8;
    } else {
        pos.x -= 1;
    }
    while (puzzle_og[pos.y][pos.x] == true) {
        pos = Sudoku::move_back({pos});
    }
    return pos;
}

void Sudoku::solve() {
    int test_num = 1;
    vec2i pos = {0, 0};
    for (; pos.y < 9; pos.y++) {
        pos.x = 0;
        while (pos.x < 9) {
            if (puzzle_og[pos.y][pos.x] == false) {  // If true dont change spot
                test_num =
                    (puzzle[pos.y][pos.x] == 0) ? 1 : puzzle[pos.y][pos.x];
                while (test_num < 10) {
                    if (pos_is_valid(pos, test_num)) {
                        puzzle[pos.y][pos.x] = test_num;
                        break;
                    } else {
                        test_num += 1;
                    }
                }
                if (test_num > 9) {
                    pos = Sudoku::move_back(pos);
                } else {
                    pos.x += 1;
                }
            } else {
                pos.x += 1;
            }
        }
    }
}

std::vector<int> Sudoku::get_block(vec2i pos) {
    std::vector<int> vec;
    int start_y = int(pos.y / 3) * 3;
    int end_y = start_y + 3;
    int start_x = int(pos.x / 3) * 3;
    int end_x = start_x + 3;
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            vec.push_back(puzzle[y][x]);
        }
    }
    return vec;
}
std::vector<int> Sudoku::get_column(vec2i pos) {
    std::vector<int> vec(puzzle[pos.y], puzzle[pos.y] + 9);
    return vec;
}
std::vector<int> Sudoku::get_row(vec2i pos) {
    std::vector<int> vec;
    for (int i = 0; i < 9; i++) {
        vec.push_back(puzzle[i][pos.x]);
    }
    return vec;
}

bool Sudoku::pos_is_valid(vec2i pos, int val) {
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

Sudoku::Sudoku(int n) {
    vec2i rand_pos;
    int rand_val;
    int count;
    for (int i = 0; i < n; i++) {
        count = 0;
        rand_pos.y = rand() % 9;
        rand_pos.x = rand() % 9;
        rand_val = rand() % 9 + 1;
        while (!pos_is_valid(rand_pos, rand_val) ||
               puzzle[rand_pos.y][rand_pos.x] != 0) {
            rand_pos.y = rand() % 9;
            rand_pos.x = rand() % 9;
            rand_val = rand() % 9 + 1;
            count += 1;
            if (count > 1000000) {
                std::cerr << "Could not find an available spot when generating "
                             "the puzzle"
                          << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        puzzle[rand_pos.y][rand_pos.x] = rand_val;
        puzzle_og[rand_pos.y][rand_pos.x] = true;
    }
}

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