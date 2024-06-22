/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Pawn.cpp
Description: The main code for the Pawn object.
    This object is a pawn piece for chess. This is derived from the Piece class.
*/

#include "Pawn.h"


/*
Function: Pawn()
Description: Constructor for the Pawn class. Sets the character that represents the piece and the player that owns the piece.
Inputs: int - player that owns the piece
Output: None
*/
Pawn::Pawn(int player){
    // Set the designated character as a pawn and the player as what was inputted
    setChar(PAWN_CHARACTER);
    setPlayer(player);
}


/*
Function: getTurnMovedTwo()
Description: Returns the move that a pawn moved two spaces (for en passant)
Inputs: None
Output: int - the turn that a pawn moved two spaces
*/
int Pawn::getTurnMovedTwo(void){
    return turnMovedTwo;
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
ret_t Pawn::movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete){
    // The difference in the position and destinations x (column) and y (row) positions
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    // Get the player of the pawn that is moving
    int posPlayer = this->getPlayer();
    
    // If it's the second player, dy will be negative before this multplication
    if(posPlayer == P2){
        dy *= -1;
    }

    // Checks if the pawn is trying to move too far forwards or backwards
    if(dy > 2 || dy < 1){
        return INVALID_MOVE;
    }

    // Checks if the pawn is trying to move too far to the left or right
    if(abs(dx) > 1){
        return INVALID_MOVE;
    }

    // A pointer to the piece at the destination, along with its character and player number
    Piece* destPiece = board[dest.row][dest.col];
    char destChar = destPiece->getChar();
    int destPlayer = destPiece->getPlayer();

    // Checks if the pawn is traveling straight
    if(dx == 0){
        // Check to make sure the pawn is moving to an empty space
        if(destChar != EMPTY_CHARACTER){
            return INVALID_MOVE;
        }

        // If moving two spaces, there are additional checks
        if(dy == 2){
            // Check if the pawn has already moved from its starting square
            if(hasMoved == true){
                return INVALID_MOVE;
            }

            // Check that there is no piece in front of the pawn
            Piece* frontPiece = (posPlayer == P1) ? board[pos.row+1][pos.col] : board[pos.row-1][pos.col];
            if(frontPiece->getChar() != EMPTY_CHARACTER){
                return INVALID_MOVE;
            }
        }
    
    // Checks if the pawn is traveling one space to the left or right
    } else {
        // Pawn must be traveling up and to the right or left
        if(dy != 1){
            return INVALID_MOVE;
        }
            
        // Checking if the destination space is empty
        if(destChar == EMPTY_CHARACTER){
            // Only valid in en passant
            int sidePieceRow = (posPlayer == P1) ? dest.row-1 : dest.row+1;
            Piece* sidePiece =  board[sidePieceRow][dest.col];

            // Can only en passant if the captured pawn had just moved two spaces
            // This value is only ever set for a pawn, otherwise it is -1
            if(sidePiece->getTurnMovedTwo() != turnNum - 1){
                return INVALID_MOVE;
            }
            
            // This really shouldn't ever happen
            int sidePlayer = sidePiece->getPlayer();
            if( (posPlayer == P1 && sidePlayer != P2) || (posPlayer == P2 && sidePlayer != P1) ){
                return INVALID_MOVE;
            }

            // Valid en passant, so set the extra delete coordiantes
            extraDelete.row = sidePieceRow;
            extraDelete.col = dest.col;
            
        } else {
            // Check for other team's piece
            if( (posPlayer == P1 && destPlayer != P2) || (posPlayer == P2 && destPlayer != P1) ){
                return INVALID_MOVE;
            } 
        }
    }

    // If all the checks were passed, then this move is valid
    if(dy == 2){
        turnMovedTwo = turnNum;
    }
    hasMoved = true;

    return VALID_MOVE;
}
