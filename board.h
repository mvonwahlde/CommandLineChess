#ifndef BOARD_H__
#define BOARD_H__

#include <iostream>
#include "piece.h"
#include "empty.h"

using namespace std;

#define NUM_BOARD_ROWS 8
#define NUM_BOARD_COLS 8

class Board{
    public:
        Board();
        ~Board();

        void print(void);

    private:
        Piece*** board;
        
};


#endif