/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Board.cpp
Description: The main code for the Board object.
    This object is the game board for the chess game. It mostly consists of a matrix of pointers
    that keep track of the pieces on the board. This object also is responsible for moving pieces.
*/

#include "Board.h"


/*
Function: Board()
Description: Constructor for the Board class. Allocates memory for the board matrix and fills with empty pieces.
Inputs: None
Output: None
*/
Board::Board(void){
    // Creates the rows of the matrix
    board = new Piece**[NUM_BOARD_ROWS];

    // For each row in the board...
    for(int i = 0; i < NUM_BOARD_ROWS; i++){
        // Create a new set of columns
        board[i] = new Piece*[NUM_BOARD_COLS];

        // For each column in that row...
        for(int j = 0; j < NUM_BOARD_COLS; j++){
            // Fill that cell with an empty piece
            board[i][j] = new Empty;
        }
    }
}


/*
Function: ~Board()
Description: Destructor for the Board class. Deletes each piece and array for the board matrix.
Inputs: None
Output: None
*/
Board::~Board(void){
    // Go through and delete each previously allocated piece and array in the board
    for(int i = 0; i < NUM_BOARD_ROWS; i++){
        for(int j = 0; j < NUM_BOARD_COLS; j++){
            // Deleting each piece
            delete board[i][j];
        }

        // Deleting each array of pieces
        delete[] board[i];
    }

    // Deleting the array of arrays to complete the deallocation process
    delete[] board;
}


/*
Function: print()
Description: Prints the board's pieces, row numbers, and column letters to the command line.
Inputs: None
Output: None
*/
void Board::print(void){
    // Start with a blank line
    cout << endl;

    // Starting with the highest number row (print top row first)
    for(int i = NUM_BOARD_ROWS-1; i >= 0; i--){
        // Print the row number
        cout << i+1 << " ";

        // For each piece in that row
        for(int j = 0; j < NUM_BOARD_COLS; j++){    
            // Print the piece's character
            cout << board[i][j]->getChar();

            // Get the player that owns that piece
            int playerNum = board[i][j]->getPlayer();
            
            // Convert that player number to a character (blank if its an empty space)
            char playerChar = ' ';
            if(playerNum != NULL_PLAYER) {
                playerChar = playerNum + 48;
            }

            // Print that player character
            cout << playerChar <<  " ";
        }

        // Go to the next line for the next row
        cout << endl;
    }

    // Print out the letters that are on the bottom of the board
    cout << "  ";
    for(int i = 0; i < NUM_BOARD_COLS; i++){
        cout << (char)('A'+i) << "  ";
    }

    // Finish by going to the next row
    cout << endl;
}


/*
Function: addPiece()
Description: Adds a new piece to the board and deletes the previous piece that was occupying that spot.
Inputs: const Piece* - A pointer to the piece that is being added to the board
        const coordinates& - A set of coordinates for the location of the piece
Output: None
*/
void Board::addPiece(Piece* piece, const coordinates& pos){
    // Keep track of the previous piece that was at that location
    Piece* tmp = board[pos.row][pos.col];

    // Add the new piece to the board
    board[pos.row][pos.col] = piece;
    
    // Delete the previous piece
    delete tmp;
}


/*
Function: movePiece()
Description: Moves a piece from the existing position to the new position in the board. Checks if the move is valid.
Inputs: const coordinates& pos  - the piece's current position
        const coordinates& dest - the piece's intended destination
Output: Returns INVALID_MOVE if unsuccessful or VALID_MOVE if successful 
*/
ret_t Board::movePiece(const coordinates& pos, const coordinates& dest){
    Piece* piece = board[pos.row][pos.col];   // The piece being moved
    coordinates extraDeletedPiece = {-1, -1}; // A set of coordinates for an additional piece being deleted (en passant)

    // Try and move the piece
    ret_t isMoveValid = piece->movePiece(board, pos, dest, turnNum, extraDeletedPiece);

    // If the move was not valid, return
    if(isMoveValid == INVALID_MOVE){
        return INVALID_MOVE;
    }

    // Container used to hold a piece that is being replaced
    Piece* deletedPiece;

    // Check if there was an extra deleted piece
    if(extraDeletedPiece.row != -1 && extraDeletedPiece.col != -1){
        // Delete the previous piece that was there and replace with an empty piece
        deletedPiece = board[extraDeletedPiece.row][extraDeletedPiece.col];
        board[extraDeletedPiece.row][extraDeletedPiece.col] = new Empty;
        delete deletedPiece;
    }

    // Delete the piece at the new location, move the piece to the new location, and replace with an empty piece
    deletedPiece = board[dest.row][dest.col];
    board[dest.row][dest.col] = board[pos.row][pos.col];
    board[pos.row][pos.col] = new Empty;
    delete deletedPiece;

    // If the program reached here, the move was valid
    return VALID_MOVE;
}
