#ifndef PIECE_H__
#define PIECE_H__

#include <math.h>
#include <iostream>

using namespace std;

#define  PIECE_CHARACTER ' '
#define  EMPTY_CHARACTER '-'
#define   PAWN_CHARACTER 'P'
#define BISHOP_CHARACTER 'B'
#define KNIGHT_CHARACTER 'N'
#define   ROOK_CHARACTER 'R'
#define  QUEEN_CHARACTER 'Q'
#define   KING_CHARACTER 'K'

#define NULL_PLAYER 0
#define P1 1
#define P2 2

#define INVALID_MOVE 0
#define VALID_MOVE   1

#define HAS_NOT_MOVED_TWO_SPACES -1

typedef int ret_t;
typedef struct coordinates {
    int col;
    int row;
} coordinates;

class Piece {
    public:
        Piece();

        char getChar(void);
        void setChar(char pieceCharacter);

        int getPlayer(void);
        void setPlayer(int player);

        virtual int getTurnMovedTwo(void);

        virtual ret_t movePiece(Piece*** board, const coordinates pos, const coordinates dest, int turnNum); 

    private:
        int player;
        char pieceCharacter;

        virtual ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum);
};


class Empty : public Piece {
    public:
        Empty();

    private: 
        ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum) override;
};


class Pawn : public Piece {
    public:
        Pawn(int player);

        int getTurnMovedTwo(void) override;

        ret_t movePiece(Piece*** board, const coordinates pos, const coordinates dest, int turnNum) override; // Exists bc en passant

    private:
        bool hasMoved = false;
        int turnMovedTwo = HAS_NOT_MOVED_TWO_SPACES;

        ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum) override;
};

#endif
