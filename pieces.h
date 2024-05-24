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

typedef int ret_t;
typedef struct coordinates {
    int col;
    int row;
} coordinates;

class Piece {
    public:
        Piece();
        ~Piece();

        char getChar(void);
        void setChar(char pieceCharacter);

        int getPlayer(void);
        void setPlayer(int player);

        bool getEnPassant(void);
        void setEnPassant(bool canEnPassant);

        virtual ret_t movePiece(Piece*** board, const coordinates pos, const coordinates dest);

    private:
        int player;
        char pieceCharacter;
        bool canEnPassant = false;

        virtual ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest);
};

class Empty : public Piece {
    public:
        Empty();
        ~Empty();

        ret_t movePiece(Piece*** board, const coordinates pos, const coordinates dest);

    private: 
        ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest);

};

class Pawn : public Piece {
    public:
        Pawn(int player);
        ~Pawn();

        ret_t movePiece(Piece*** board, const coordinates pos, const coordinates dest);

    private:
        bool hasMoved = false;

        ret_t checkMove(Piece*** board, const coordinates pos, const coordinates dest);
};

#endif
