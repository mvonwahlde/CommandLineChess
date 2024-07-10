/*
Author: Matthew VonWahlde
Last Modified: 7/9/24
Project: Command Line Chess
File: Knight.cpp
Description: The main code for the Knight object.
    This object is a knight piece for chess. This is derived from the Piece class.
*/

#include "Knight.h"


/*
Function: Knight()
Description: Constructor for the knight class. Sets the character that represents the piece and the player that owns the piece.
Inputs: int - player that owns the piece
Output: None
*/
Knight::Knight(int player){
    // Set the designated character as a knight and the player as what was inputted
    setChar(KNIGHT_CHARACTER);
    setPlayer(player);
}


/*
Function: movePiece()
Description: Returns whether or not the piece can move to the intended destination, but does not actually move the piece.
             Sets the coordinates in extraDelete if there is a piece not in the pos or dest coordinates that needs to be deleted (en passant).
Inputs: Piece*** board - 2D matrix of piece pointers that represents that game board
        const coordinates& pos  - the piece's current position
        const coordinates& dest - the piece's intended destination
        int turnNum - the current turn number
        coordiantes& extraDelete - coordinates to an extra piece that the calling function should delete
Output: Returns VALID_MOVE for a move that is valid and INVALID_MOVE for a move that is invalid
*/
ret_t Knight::movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete){
    // The difference in the position and destinations x (column) and y (row) positions
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    // Check that the knight is moving the proper L shape
    if(abs(dx) == 1){
        // If the knight is moving one space left or right, it must move two spaces up or down
        if(abs(dy) != 2){
            return INVALID_MOVE;
        }
    } else if(abs(dx) == 2){
        // If the knight is moving two spaces left or right, it must move one space up or down
        if(abs(dy) != 1){
            return INVALID_MOVE;
        }
    } else {
        // Too much or too little to the left or right
        return INVALID_MOVE;
    }

    // Get the player of the knight that is moving
    int posPlayer = this->getPlayer();

    // Get the player of the piece that the knight is landing on
    Piece* destPiece = board[dest.row][dest.col];
    int destPlayer = destPiece->getPlayer();

    // Check to make sure that the knight is not capturing its own piece
    if(posPlayer == destPlayer){
        return INVALID_MOVE;
    }

    return VALID_MOVE;
}
