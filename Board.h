#ifndef BOARD_H 
#define BOARD_H

#include <vector>
using namespace std;

class Board {
private:
    int rows, cols, numberOfMines;
    vector<vector<char> > board;  // Represents the board 
    vector<vector<bool> > revealedCells;  // Tracks which cells have been revealed
    vector<vector<int> > mineCounts;  // Stores the count of adjacent mines for each cell

    bool isAValidCell(int row, int col); //checks if a cell is valid
    void placeMines(); //places mines at random
    void calculateAdjacentMines(); //calulates adacent mindes

public:
    Board(int rowsToPass, int columnsToPass, int numberOfMinesToPass);  // Constructor to initialize the board
    void displayBoard();  
    bool revealCell(int row, int col);  // Reveal a cell chosen by the player
    void markCell(int row, int col);  // Mark a cell as a potential mine
    bool checkWin();  // Check if the player has won
};

#endif // Ends header guard to ensure that the contents of the file are not processed multiple times
