#include "board.h"

int main(){

    Board* board = new Board;
    board->print();
    delete board;

    return 0;
}
