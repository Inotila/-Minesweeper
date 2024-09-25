#ifndef BOARD_H
#define BOARD_H

#include <vector>
using namespace std;

class Board {
private:
    int rows, cols, numberOfMines;
    vector<vector<char>> board; 
    vector<vector<bool>> revealedCells; 
    vector<vector<int>> mineCounts;

    bool isAValidCell(int row, int col);
    void placeMines();
    void calculateAdjacentMines();

public:
    Board(int rowsToPass, int columnsToPass, int numberOfMines);  // Constructor to initialize the board
    void displayBoard();  
    bool revealCell(int row, int col);  // Reveal a cell chosen by the player
    void markCell(int row, int col);  // Mark a cell as a potential mine
};

#endif
