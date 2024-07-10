/*
Author: Matthew VonWahlde
Last Modified: 7/9/24
Project: Command Line Chess
File: Knight.h
Description: The header file for the Knight object.
    This object is a knight piece for chess. This is derived from the Piece class.
*/

#ifndef KNIGHT_H__
#define KNIGHT_H__

#include "Piece.h"

// Knight class prototype
class Knight : public Piece {
    public:
        Knight(int player);

        ret_t movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete) override;
};

#endif
