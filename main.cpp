#include "Board.h"
#include <iostream>
#include <sstream> 
using namespace std;

int main() {
    Board gameBoard(6, 6, 5);  // Create a 6x6 board with 5 mines
    bool gameOver = false;

    while (!gameOver) {
        gameBoard.displayBoard();
        string action;
        char rowChar; 
        int col;

        cout << "Enter action (r for reveal, m for mark), followed by row (a-f) and column (1-6): ";
        getline(cin, action);  // Read the entire line

        // Parse the input
        istringstream iss(action);
        string command;

        // Extract the command
        iss >> command >> rowChar >> col;

        // Validate the inputs
        if (command != "r" && command != "m" || 
            rowChar < 'a' || rowChar > 'f' || 
            col < 1 || col > 6) {
            cout << "Invalid input format! Please enter in the format: r a 1 or m a 1." << endl;
            continue; // Ask for input again
        }

        int row = rowChar - 'a';  // Convert row from char to int
        col -= 1;  // Convert column to 0-indexed for internal program use

        // Check if the action is valid
        if (command == "r") {
            gameOver = gameBoard.revealCell(row, col); // Reveal the cell
            if (gameOver) {
                cout << "You stepped on a mine! Game Over." << endl;
            } else if (gameBoard.checkWin()) {
                cout << "You are safe now! You win!" << endl;
                gameOver = true;
            }
        } else if (command == "m") {
            gameBoard.markCell(row, col); // Mark the cell as a potential mine
            cout << "Cell " << rowChar << col << " marked as a potential mine." << endl;
        } else {
            cout << "Invalid action! Please enter 'r' or 'm'." << endl;
        }
    }

    return 0;
}
