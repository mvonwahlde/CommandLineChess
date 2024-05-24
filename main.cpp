#include "board.h"

int main(){

    Board* board = new Board;
    Pawn* pawn1 = new Pawn(P1);
    Pawn* pawn2 = new Pawn(P2);
    coordinates pawn1p = {2,1};
    coordinates pawn1f = {1,2};
    coordinates pawn2p = {3,2};

    board->print();
    board->addPiece(pawn1, pawn1p);
    board->addPiece(pawn2, pawn2p);
    board->print();
    board->movePiece(pawn1p, pawn1f);

    //board->print();
    delete board;

    return 0;
}
