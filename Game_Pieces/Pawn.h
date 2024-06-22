/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Pawn.h
Description: The header file for the Pawn object.
    This object is a pawn piece for chess. This is derived from the Piece class.
*/

#ifndef PAWN_H__
#define PAWN_H__

#include "Piece.h"

// Pawn class prototype
class Pawn : public Piece {
    public:
        Pawn(int player);

        int getTurnMovedTwo(void) override;

        ret_t movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete) override;

    private:
        bool hasMoved = false;
        int turnMovedTwo = HAS_NOT_MOVED_TWO_SPACES;
};

#endif
