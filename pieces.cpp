#include "pieces.h"

// Base class for a game piece

Piece::Piece(){
    player = NULL_PLAYER;
    setChar(PIECE_CHARACTER);
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

int Piece::getTurnMovedTwo(void){
    return turnMovedTwo;
}

void Piece::setTurnMovedTwo(int turnNum){
    turnMovedTwo = turnNum;
}

ret_t Piece::movePiece(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    if(checkMove(board, pos, dest, turnNum) != true){
        return INVALID_MOVE;
    }
    
    Piece* destPiece = board[dest.row][dest.col];
    board[dest.row][dest.col] = board[pos.row][pos.col];

    delete destPiece;
    board[pos.row][pos.col] = new Empty;

    return VALID_MOVE;
}

ret_t Piece::checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    return INVALID_MOVE;
}

// Empty tile

Empty::Empty(){
    setChar(EMPTY_CHARACTER);
    setPlayer(NULL_PLAYER);
}

ret_t Empty::checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    return INVALID_MOVE;
}

// Pawn

Pawn::Pawn(int player){
    setChar(PAWN_CHARACTER);
    setPlayer(player);
}

ret_t Pawn::movePiece(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    if(checkMove(board, pos, dest, turnNum) != true){
        return INVALID_MOVE;
    }

    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;
    
    hasMoved = true;

    // Jumping two spaces
    if(dy == 2){
        setTurnMovedTwo(turnNum);
    } 

    ////////////////// Left off here with pawn movement (plus bug in Pawn::checkMove)
    
    Piece* destPiece = board[dest.row][dest.col];

    if(destPiece->getChar() == EMPTY_CHARACTER){
        // En passant
        destPiece = board[dest.row-1][dest.col]
    } else {

    }

    board[dest.row][dest.col] = board[pos.row][pos.col];

    delete destPiece;
    board[pos.row][pos.col] = new Empty;

    return VALID_MOVE;
}

ret_t Pawn::checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    //////////////////// Only did this for one player for some reason, so need to fix :(

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
            Piece* frontPiece;
            if(posPlayer == 1){ frontPiece = board[dest.row-1][dest.col]; }
            else { frontPiece = board[dest.row+1][dest.col]; }
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
            if(destChar == EMPTY_CHARACTER){
                // Only valid in en passant
                Piece* sidePiece;
                if(posPlayer == 1){ sidePiece = board[dest.row-1][dest.col]; }
                else { sidePiece = board[dest.row+1][dest.col]; }
                if(sidePiece->getTurnMovedTwo() != turnNum - 1){
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
