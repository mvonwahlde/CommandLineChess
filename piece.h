#ifndef PIECE_H__
#define PIECE_H__

#define PIECE_CHARACTER
#define NULL_PLAYER 0
#define P1 1
#define P2 2

class Piece {
    public:
        Piece();
        ~Piece();

        char getChar(void);
        void setChar(char pieceCharacter);

        int getPlayer(void);
        void setPlayer(int player);

    private:
        int player;
        char pieceCharacter;
};

#endif
