/*
Author: Matthew VonWahlde
Last Modified: 7/9/24
Project: Command Line Chess
File: Board.h
Description: The header file for the Board object.
    This object is the game board for the chess game. It mostly consists of a matrix of pointers
    that keep track of the pieces on the board. This object also is responsible for moving pieces.
*/

#ifndef BOARD_H__
#define BOARD_H__

// Include all game pieces
#include "Game_Pieces/Empty.h"
#include "Game_Pieces/Pawn.h"
#include "Game_Pieces/Knight.h"

// Specify that the board has 8 rows and 8 columns
#define NUM_BOARD_ROWS 8
#define NUM_BOARD_COLS 8

// Board class prototype
class Board{
    public:
        Board(void);
        ~Board(void);

        void print(void);
        void addPiece(Piece* piece, const coordinates& pos);
        ret_t movePiece(const coordinates& pos, const coordinates& dest);

        Piece*** board; // (0,0) is the bottom left corner of the board

    private:
        int turnNum = 1;
        int playersTurn = P1;
};

#endif
