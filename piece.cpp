#include "piece.h"

Piece::Piece(){

}

Piece::~Piece(){

}

char Piece::getChar(void){
    return pieceCharacter;
}

void Piece::setChar(char pieceCharacter){
    this->pieceCharacter = pieceCharacter;
}

int Piece::getPlayer(void){
    return player;
}

void Piece::setPlayer(int player){
    this->player = player;
}
