#include <iostream>
#include <iomanip>

using namespace std;

// ======================================================
// Sudoku Solver
// ======================================================

class SudokuSolver {

private:

    int grid[9][9];


    // --------------------------------------------------
    // Check whether a number already exists in a row
    // --------------------------------------------------

    bool usedInRow(int row, int number) {

        for (int col = 0; col < 9; col++) {

            if (grid[row][col] == number) {
                return true;
            }
        }

        return false;
    }


    // --------------------------------------------------
    // Check whether a number already exists in a column
    // --------------------------------------------------

    bool usedInColumn(int col, int number) {

        for (int row = 0; row < 9; row++) {

            if (grid[row][col] == number) {
                return true;
            }
        }

        return false;
    }


    // --------------------------------------------------
    // Check whether a number exists in 3x3 subgrid
    // --------------------------------------------------

    bool usedInBox(int startRow, int startCol, int number) {

        for (int row = 0; row < 3; row++) {

            for (int col = 0; col < 3; col++) {

                if (grid[startRow + row][startCol + col] == number) {
                    return true;
                }
            }
        }

        return false;
    }


    // --------------------------------------------------
    // Check whether a number can be placed
    // --------------------------------------------------

    bool isSafe(int row, int col, int number) {

        return !usedInRow(row, number)
            && !usedInColumn(col, number)
            && !usedInBox(row - row % 3,
                          col - col % 3,
                          number);
    }


    // --------------------------------------------------
    // Find an empty cell
    // --------------------------------------------------

    bool findEmptyCell(int& row, int& col) {

        for (row = 0; row < 9; row++) {

            for (col = 0; col < 9; col++) {

                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }

        return false;
    }


    // --------------------------------------------------
    // Recursive Backtracking Algorithm
    // --------------------------------------------------

    bool solve() {

        int row;
        int col;

        // If no empty cell exists, Sudoku is solved
        if (!findEmptyCell(row, col)) {
            return true;
        }

        // Try numbers 1 to 9
        for (int number = 1; number <= 9; number++) {

            // Check whether number is safe
            if (isSafe(row, col, number)) {

                // Place number
                grid[row][col] = number;

                // Recursively solve remaining puzzle
                if (solve()) {
                    return true;
                }

                // Backtrack
                grid[row][col] = 0;
            }
        }

        // No valid number found
        return false;
    }


public:

    // --------------------------------------------------
    // Constructor
    // --------------------------------------------------

    SudokuSolver(int puzzle[9][9]) {

        for (int row = 0; row < 9; row++) {

            for (int col = 0; col < 9; col++) {

                grid[row][col] = puzzle[row][col];
            }
        }
    }


    // --------------------------------------------------
    // Display Sudoku
    // --------------------------------------------------

    void display() {

        cout << "\n";

        cout << "    ";

        for (int col = 0; col < 9; col++) {

            cout << col + 1 << " ";

            if ((col + 1) % 3 == 0) {
                cout << " ";
            }
        }

        cout << "\n";

        cout << "   -------------------------\n";

        for (int row = 0; row < 9; row++) {

            cout << row + 1 << " | ";

            for (int col = 0; col < 9; col++) {

                if (grid[row][col] == 0) {
                    cout << ". ";
                }
                else {
                    cout << grid[row][col] << " ";
                }

                if ((col + 1) % 3 == 0) {
                    cout << "| ";
                }
            }

            cout << "\n";

            if ((row + 1) % 3 == 0) {
                cout << "   -------------------------\n";
            }
        }
    }


    // --------------------------------------------------
    // Start Solver
    // --------------------------------------------------

    bool solveSudoku() {

        return solve();
    }
};


// ======================================================
// Main Function
// ======================================================

int main() {

    cout << "============================================\n";
    cout << "           CODEALPHA - TASK 3\n";
    cout << "             SUDOKU SOLVER\n";
    cout << "============================================\n";


    // 0 represents an empty cell
    int puzzle[9][9] = {

        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };


    // Create Sudoku Solver object
    SudokuSolver sudoku(puzzle);


    // Display original puzzle
    cout << "\nOriginal Sudoku:";
    sudoku.display();


    // Solve Sudoku
    cout << "\nSolving Sudoku using Backtracking...\n";


    if (sudoku.solveSudoku()) {

        cout << "\n[SUCCESS] Sudoku solved successfully!\n";

        cout << "\nSolved Sudoku:";
        sudoku.display();
    }

    else {

        cout << "\n[ERROR] This Sudoku puzzle cannot be solved.\n";
    }


    cout << "\n============================================\n";
    cout << "              Program Finished\n";
    cout << "============================================\n";

    return 0;
}