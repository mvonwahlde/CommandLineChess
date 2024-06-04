#include "board.h"

Board::Board(){
    // Create the array the holds the column pointers
    board = new Piece**[NUM_BOARD_ROWS];

    // For each row in the board...
    for(int i = 0; i < NUM_BOARD_ROWS; i++){
        // Create a new set of columns
        board[i] = new Piece*[NUM_BOARD_COLS];

        // For each column in that row...
        for(int j = 0; j < NUM_BOARD_COLS; j++){
            // Fill that cell with an empty cell
            board[i][j] = new Empty;
        }
    }
}

Board::~Board(){
    for(int i = 0; i < NUM_BOARD_ROWS; i++){
        for(int j = 0; j < NUM_BOARD_COLS; j++){
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

void Board::print(void){
    int playerNum;
    char playerChar;
    // Rows are numbers 
    // Cols are letters
    
    cout << endl;

    for(int i = NUM_BOARD_ROWS-1; i >= 0; i--){
        // Print the number
        cout << i+1 << " ";
        for(int j = 0; j < NUM_BOARD_COLS; j++){    
            cout << board[i][j]->getChar();
            playerNum = board[i][j]->getPlayer();
            if(playerNum == NULL_PLAYER){
                playerChar = ' ';
            } else {
                playerChar = playerNum + 48;
            }
            cout << playerChar <<  " ";
        }
        cout << endl;
    }

    cout << "  ";
    for(int i = 0; i < NUM_BOARD_COLS; i++){
        cout << (char)('A'+i) << "  ";
    }
    cout << endl;
}

void Board::addPiece(Piece* piece, coordinates pos){
    Piece* tmp = board[pos.row][pos.col];
    board[pos.row][pos.col] = piece;
    delete tmp;
}

ret_t Board::movePiece(coordinates pos, coordinates dest){
    Piece* piece = board[pos.row][pos.col];
    cout << piece->movePiece(board, pos, dest, turnNum) << endl;
    return 0;
}
