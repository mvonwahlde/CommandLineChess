#ifndef BOARD_H__
#define BOARD_H__

#include "pieces.h"

#define NUM_BOARD_ROWS 8
#define NUM_BOARD_COLS 8

class Board{
    public:
        Board();
        ~Board();

        void print(void);
        void addPiece(Piece* piece, coordinates pos);
        ret_t movePiece(coordinates pos, coordinates dest);

        Piece*** board;

    private:
        int turnNum = 1;
};


#endif