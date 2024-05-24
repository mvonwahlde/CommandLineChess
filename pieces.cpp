#include "pieces.h"

// Base class for a game piece

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

ret_t Piece::movePiece(Piece*** board, const coordinates pos, const coordinates dest){
    return INVALID_MOVE;
}

ret_t Piece::checkMove(Piece*** board, const coordinates pos, const coordinates dest){
    return INVALID_MOVE;
}

bool Piece::getEnPassant(void){
    return canEnPassant;
}

void Piece::setEnPassant(bool canEnPassant){
    this->canEnPassant = canEnPassant;
}


// Empty tile

Empty::Empty(){
    setChar(EMPTY_CHARACTER);
    setPlayer(NULL_PLAYER);
}

Empty::~Empty(){

}

ret_t Empty::movePiece(Piece*** board, const coordinates pos, const coordinates dest){
    return INVALID_MOVE;
}

ret_t Empty::checkMove(Piece*** board, const coordinates pos, const coordinates dest){
    return INVALID_MOVE;
}

// Pawn

Pawn::Pawn(int player){
    setChar(PAWN_CHARACTER);
    setPlayer(player);
}

Pawn::~Pawn(){

}

ret_t Pawn::movePiece(Piece*** board, const coordinates pos, const coordinates dest){
    return checkMove(board, pos, dest);
    ////////////////////////// HERE /////////////////////////////////
}

ret_t Pawn::checkMove(Piece*** board, const coordinates pos, const coordinates dest){
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    // Checks if the pawn is trying to move too far forwards or backwards
    if(dy > 2 || dy < 1){
        return INVALID_MOVE;
    }

    // Checks if the pawn is trying to move too far to the left or right
    if(abs(dx) > 1){
        return INVALID_MOVE;
    }

    Piece* destPiece = board[dest.row][dest.col];
    char destChar = destPiece->getChar();
    int destPlayer = destPiece->getPlayer();
    int posPlayer = this->getPlayer();

    // Checks if the pawn is traveling straight
    if(dx == 0){
        // Check to make sure the pawn is moving to an empty space
        if(destChar != EMPTY_CHARACTER){
            return INVALID_MOVE;
        }

        // If moving two spaces, there are additional checks
        if(dy == 2){
            // Check if the pawn has already moved from its starting square
            if(hasMoved == true){
                return INVALID_MOVE;
            }

            // Check that there is no piece in front of the pawn
            Piece* frontPiece = board[dest.row-1][dest.col];
            if(frontPiece->getChar() != EMPTY_CHARACTER){
                return INVALID_MOVE;
            }
        }
    
    // Checks if the pawn is traveling one space to the left or right
    } else {
        // Pawn must be traveling up and to the right or left
        if(dy != 1){
            return INVALID_MOVE;
        } else {
            // dx == 1 or -1, dy == 1
            
            // Checking if the destination space is empty
            if(destChar == EMPTY_CHARACTER || destChar == PIECE_CHARACTER){
                // Only valid in en passant
                Piece* sidePiece = board[dest.row-1][dest.col];
                if(sidePiece->getEnPassant() != true){
                    return INVALID_MOVE;
                }
                
            } else {
                // Check for other team's piece
                if( !(posPlayer == P1 && destPlayer == P2 || posPlayer == P2 && destPlayer == P1) ){
                    return INVALID_MOVE;
                } 
            }
        }
    }

    return VALID_MOVE;
}
