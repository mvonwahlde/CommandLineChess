/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: Piece.h
Description: The header file for the Piece object.
    This object is a generic piece for the game of chess. This is meant to be a base class
    that other piece classes can derive from.
*/

#ifndef PIECE_H__
#define PIECE_H__

// Top of the include chain, so I figured this would be a good place for including libraries and specifying that std namespace
#include <math.h>
#include <iostream>

using namespace std;

// The characters that represent each of the pieces
#define  PIECE_CHARACTER ' '
#define  EMPTY_CHARACTER '-'
#define  PAWN_CHARACTER 'P'

// The integers that represent each of the players (and lack of)
#define NULL_PLAYER 0
#define P1 1
#define P2 2

// Return codes for if a move is valid or not
#define INVALID_MOVE 0
#define VALID_MOVE   1

// If a piece is not a pawn that has moved two spaces (used for en passant)
#define HAS_NOT_MOVED_TWO_SPACES -1

// Type defintions for a return type and a coordinate set
typedef int ret_t;
typedef struct coordinates {
    int col;
    int row;
} coordinates;

// Piece class prototype
class Piece {
    public:
        Piece(void);
        virtual ~Piece(void);

        char getChar(void);
        void setChar(char pieceCharacter);

        int getPlayer(void);
        void setPlayer(int player);

        virtual int getTurnMovedTwo(void);

        virtual ret_t movePiece(Piece*** board, const coordinates& pos, const coordinates& dest, int turnNum, coordinates& extraDelete); 

    private:
        int player;
        char pieceCharacter;
};

#endif
