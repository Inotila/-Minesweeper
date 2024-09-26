#include "Board.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>

using namespace std;

// Constructor to initialize the board
Board::Board(int rowsToPass, int columnsToPass, int numberOfMinesToPass) 
    : rows(rowsToPass), cols(columnsToPass), numberOfMines(numberOfMinesToPass) {
    // Initialize board with hidden cells
    board.resize(rows, vector<char>(cols, '#'));
    revealedCells.resize(rows, vector<bool>(cols, false));  // No cells are revealed initially
    mineCounts.resize(rows, vector<int>(cols, 0));  // Initialize mine counts to 0

    srand(time(0));  // Seed the random number generator
    placeMines();  // Place mines on the board
    calculateAdjacentMines();  // Calculate the number of adjacent mines
}

// Check if a given cell is within bounds of the board
bool Board::isAValidCell(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

// Function to randomly place mines on the board
void Board::placeMines() {
    int placedMines = 0;
    while (placedMines < numberOfMines) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (board[r][c] != 'M') {  // Place mine only if there's no mine already
            board[r][c] = 'M';
            placedMines++;
        }
    }
}

// Function to calculate the number of adjacent mines for each cell
void Board::calculateAdjacentMines() {
    int rowOffsets[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int columnOffsets[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] == 'M') continue;
            int mineCount = 0;
            // Check all surrounding cells
            for (int i = 0; i < 8; ++i) {
                int newRow = r + rowOffsets[i];
                int newCol = c + columnOffsets[i];
                if (isAValidCell(newRow, newCol) && board[newRow][newCol] == 'M') {
                    mineCount++;
                }
            }
            mineCounts[r][c] = mineCount;  // Store the count of adjacent mines
        }
    }
}

// Function to display the current state of the board
void Board::displayBoard() {
    cout << "  ";
    for (int c = 1; c <= cols; ++c) cout << c << " ";  // Print column numbers
    cout << endl;

    for (int r = 0; r < rows; ++r) {
        cout << char('a' + r) << " ";  // Print row letters
        for (int c = 0; c < cols; ++c) {
            if (revealedCells[r][c]) {
                if (board[r][c] == 'M') cout << "M ";  // Show mine if revealed
                else cout << mineCounts[r][c] << " ";  // Show the count of adjacent mines
            } else {
                if (board[r][c] == 'X') cout << "X ";  // Display marked cells
                else cout << "# ";  // Display hidden cell
            }
        }
        cout << endl;
    }
}

// Function to reveal a cell chosen by the player
bool Board::revealCell(int row, int col) {
    if (!isAValidCell(row, col) || revealedCells[row][col]) {
        cout << "Invalid move or cell already revealed." << endl;
        return false;
    }
    revealedCells[row][col] = true;  // Mark the cell as revealed

    if (board[row][col] == 'M') {
        // Game over if a mine is revealed
        cout << "Oh no! You stepped on a mine! Game over :-(" << endl;
        return true;  // Game over
    }

    return false;  // Game continues
}

// Function to mark a cell as a potential mine
void Board::markCell(int row, int col) {
    if (isAValidCell(row, col) && !revealedCells[row][col]) {
        board[row][col] = 'X';  // Mark as a mine an 'X'
        cout << "Cell " << char('a' + row) << (col + 1) << " marked as a potential mine." << endl; // User Feedback for marking
    } else {
        cout << "Invalid move or cell already revealed." << endl;
    }
}

// Function to check if the player has won
bool Board::checkWin() {
    int nonMineCells = 0;    // Count of non-mine cells
    int revealedNonMineCells = 0; // Count of revealed non-mine cells

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] != 'M') { // if its a non-mine cell increment nonMineCell
                nonMineCells++; 
                if (revealedCells[r][c]) { // Check if it's revealed
                    revealedNonMineCells++;
                }
            }
        }
    }

    // If all non-mine cells are revealed, the player wins
    return revealedNonMineCells == nonMineCells;
}
