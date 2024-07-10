/*
Author: Matthew VonWahlde
Last Modified: 7/10/24
Project: Command Line Chess
File: Bishop.h
Description: The header file for the Bishop object.
    This object is a bishop piece for chess. This is derived from the Piece class.
*/

#ifndef BISHOP_H__
#define BISHOP_H__

#include "Piece.h"

// Bishop class prototype
class Bishop : public Piece {
    public:
        Bishop(int player);

        ret_t movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete) override;
};

#endif
