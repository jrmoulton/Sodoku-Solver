
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "sudoku.h"

int main() {
    int n;
    std::cout << "\nWelcome to SudokuSolver!!" << std::endl;
    std::cout << "Enter number of squares to prepopulate: ";
    std::cin >> n;
    unsigned seed = time(0);
    // Seed the random number generator.
    srand(seed);

    std::cout << "\n" << std::endl;
    Sudoku s(n);
    std::cout << s << std::endl;

    s.solve();
    std::cout << "\nSolved!" << std::endl;
    std::cout << s << std::endl;
}