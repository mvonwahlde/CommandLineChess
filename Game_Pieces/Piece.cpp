/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Piece.cpp
Description: The main code for the Piece object.
    This object is a generic piece for the game of chess. This is meant to be a base class
    that other piece classes can derive from.
*/

#include "Piece.h"


/*
Function: Piece()
Description: Constructor for the Piece class. Sets the character that represents the piece and the player that owns the piece.
Inputs: None
Output: None
*/
Piece::Piece(void){
    // Set the designated character and player for the piece
    setChar(PIECE_CHARACTER);
    setPlayer(NULL_PLAYER);
}


/*
Function: ~Piece()
Description: Destructor for the piece class. Does not do anything, but has to exist as a virtual function for the derived classes.
Inputs: None
Output: None
*/
Piece::~Piece(void){
    // Do nothing
}


/*
Function: getChar()
Description: Returns the piece's character.
Inputs: None
Output: char - the piece's character 
        'K' = King, 'Q' = Queen, 'R' = Rook, 'B' = Bishop, 'N' = Knight, 'P' = Pawn, '-' = Empty, ' ' = Generic Piece
*/
char Piece::getChar(void){
    return pieceCharacter;
}


/*
Function: setChar()
Description: Sets the piece's character
Inputs: char - the piece's character
        'K' = King, 'Q' = Queen, 'R' = Rook, 'B' = Bishop, 'N' = Knight, 'P' = Pawn, '-' = Empty, ' ' = Generic Piece
Output: None
*/
void Piece::setChar(char pieceCharacter){
    this->pieceCharacter = pieceCharacter;
}


/*
Function: getPlayer()
Description: Returns the piece's player number.
Inputs: None
Output: int - the piece's player number
*/
int Piece::getPlayer(void){
    return player;
}


/*
Function: setPlayer()
Description: Sets the piece's player number.
Inputs: int - the piece's player number
Output: None
*/
void Piece::setPlayer(int player){
    this->player = player;
}


/*
Function: getTurnMovedTwo()
Description: Returns the move that a pawn moved two spaces (for en passant)
Inputs: None
Output: int - the turn that a pawn moved two spaces
*/
int Piece::getTurnMovedTwo(void){
    // For all pieces except pawns (that have moved two spaces), this value is returned
    return HAS_NOT_MOVED_TWO_SPACES;
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
ret_t Piece::movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete){
    return INVALID_MOVE;
}
