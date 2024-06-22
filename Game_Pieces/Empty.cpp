/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Empty.cpp
Description: The main code for the Empty object.
    This object is an empty space on the board in a game of chess. This is derived from the Piece class.
*/

#include "Empty.h"


/*
Function: Empty()
Description: Constructor for the Empty class. Sets the character that represents the piece and the player that owns the piece.
Inputs: None
Output: None
*/
Empty::Empty(void){
    // Set the designated character as empty and the player as null
    setChar(EMPTY_CHARACTER);
    setPlayer(NULL_PLAYER);
}
