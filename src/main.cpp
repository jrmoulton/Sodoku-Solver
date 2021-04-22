
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "sudoku.h"

/*
Summary: Generate and print a potential sudoku puzzle given a number of
            pre-initialized positions given by the user. Then solve and print
            the solution
Begin:
   Print the prompt
   Seed the random number generator
   Generate and print a puzzle
   Solve and print the solved puzzle
End
*/
int main() {
    // Print the prompt
    int n;
    std::cout << "\nWelcome to SudokuSolver!!" << std::endl;
    std::cout << "Enter number of squares to prepopulate: ";
    std::cin >> n;
    std::cout << std::endl;

    // Seed the random number generator.
    unsigned seed = time(0);
    srand(seed);

    // Generate and print a puzzle
    std::cout << "\n" << std::endl;
    Sudoku s(n);
    std::cout << s << std::endl;

    // Solve and print the solved puzzle
    s.solve();
    std::cout << "\nSolved!" << std::endl;
    std::cout << s << std::endl;
}