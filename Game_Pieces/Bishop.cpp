/*
Author: Matthew VonWahlde
Last Modified: 7/10/24
Project: Command Line Chess
File: Bishop.cpp
Description: The main code for the Bishop object.
    This object is a bishop piece for chess. This is derived from the Piece class.
*/

#include "Bishop.h"


/*
Function: Bishop()
Description: Constructor for the bishop class. Sets the character that represents the piece and the player that owns the piece.
Inputs: int - player that owns the piece
Output: None
*/
Bishop::Bishop(int player){
    // Set the designated character as a knight and the player as what was inputted
    setChar(BISHOP_CHARACTER);
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
ret_t Bishop::movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete){
    // The difference in the position and destinations x (column) and y (row) positions
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    // Make sure that the Bishop is moving
    if(dx == 0 || dy == 0){
        return INVALID_MOVE;
    }

    // The Bishop must move in a diagonal
    if(abs(dx) != abs(dy)){
        return INVALID_MOVE;
    }

    // Check every space in the diagonal to make sure it is empty
    int curRow = pos.row;
    int curCol = pos.col;

    int rowInc = (dy > 0) ? 1 : -1;
    int colInc = (dx > 0) ? 1 : -1;

    while(curRow != dest.row && curCol != dest.col){
        // Check to see if there is a piece in the way
        Piece* curPiece = board[curRow][curCol];
        int curPieceChar = curPiece->getChar();

        if(curPieceChar != EMPTY_CHARACTER){
            return INVALID_MOVE;
        }
        
        // Check the next space
        curRow += rowInc;
        curCol += colInc;
    }

    // Get the player of the bishop that is moving
    int posPlayer = this->getPlayer();

    // Get the player of the piece that the bishop is landing on
    Piece* destPiece = board[dest.row][dest.col];
    int destPlayer = destPiece->getPlayer();

    // Check to make sure that the bishop is not capturing its own piece
    if(posPlayer == destPlayer){
        return INVALID_MOVE;
    }

    return VALID_MOVE;
}
