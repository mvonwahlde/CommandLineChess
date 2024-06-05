#include "pieces.h"


/////////////////////////////////////////////////////////////////////////////////
// Base class for a game piece
/////////////////////////////////////////////////////////////////////////////////

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
    return HAS_NOT_MOVED_TWO_SPACES;
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


/////////////////////////////////////////////////////////////////////////////////
// Empty Tile
/////////////////////////////////////////////////////////////////////////////////

Empty::Empty(){
    setChar(EMPTY_CHARACTER);
    setPlayer(NULL_PLAYER);
}


ret_t Empty::checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    return INVALID_MOVE;
}


/////////////////////////////////////////////////////////////////////////////////
// Pawn
/////////////////////////////////////////////////////////////////////////////////

Pawn::Pawn(int player){
    setChar(PAWN_CHARACTER);
    setPlayer(player);
}


int Pawn::getTurnMovedTwo(void){
    return turnMovedTwo;
}


ret_t Pawn::movePiece(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    if(checkMove(board, pos, dest, turnNum) != true){
        return INVALID_MOVE;
    }

    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;
    
    int player = board[pos.row][pos.col]->getPlayer();
    
    hasMoved = true;

    // Jumping two spaces
    if(abs(dy) == 2){
        turnMovedTwo = turnNum;
    } 

    // Check for en passant
    if( abs(dy) == 1 && abs(dx == -1) ){
        if(board[dest.row][dest.col]->getChar() == EMPTY_CHARACTER){
            // En passant
            int enPassantPieceRow = (player == P1) ? dest.row-1 : dest.row+1;
            Piece* enPassantPiece = (player == P1) ? board[enPassantPieceRow][dest.col] : board[enPassantPieceRow][dest.col];
            delete enPassantPiece;
            board[enPassantPieceRow][dest.col] = new Empty;
        }    
    }
    
    Piece* destPiece = board[dest.row][dest.col];
    board[dest.row][dest.col] = board[pos.row][pos.col];

    delete destPiece;
    board[pos.row][pos.col] = new Empty;

    return VALID_MOVE;
}


ret_t Pawn::checkMove(Piece*** board, const coordinates pos, const coordinates dest, int turnNum){
    int dx = dest.col - pos.col;
    int dy = dest.row - pos.row;

    int posPlayer = this->getPlayer();
    
    // If its the second play, dy will be negative before this multplication
    if(posPlayer == P2){
        dy *= -1;
    }

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
            Piece* frontPiece = (posPlayer == P1) ? board[dest.row-1][dest.col] : board[dest.row+1][dest.col];

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
                Piece* sidePiece = (posPlayer == P1) ? board[dest.row-1][dest.col] : board[dest.row+1][dest.col];

                if(sidePiece->getChar() != PAWN_CHARACTER && sidePiece->getTurnMovedTwo() != turnNum - 1){
                    if( (posPlayer == P1 && destPlayer != P2) || (posPlayer == P2 && destPlayer != P1) ){
                        return INVALID_MOVE;
                    }
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
