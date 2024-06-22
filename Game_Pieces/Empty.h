/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Empty.h
Description: The header file for the Empty object.
    This object is an empty space on the board in a game of chess. This is derived from the Piece class.
*/

#ifndef EMPTY_H__
#define EMPTY_H__

#include "Piece.h"

// Empty class prototype
class Empty : public Piece {
    public:
        Empty(void);

};

#endif
