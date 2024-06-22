/*
Author: Matthew VonWahlde
Last Modified: 6/21/24
Project: Command Line Chess
File: main.cpp
Description: The main file for command line chess, or chess played in the command line.
    Right now, this file is used for testing, but eventually it will hold the main game loop.

    Makefile commands (Windows):
        make - builds all object files and creates target file
        make run - builds all object files and creates target file, then runs the target file
        make clean - removes all object files and target file
*/

#include "Board.h"

#define DEBUG /* Leave uncommented for debug mode, comment for main game loop */


// Program entry point
int main(){
    // Create a new game board object
    Board* board = new Board;

    #ifdef DEBUG // Testing 
        // Testing pawn movement
        Pawn* pawn1 = new Pawn(P1);
        Pawn* pawn2 = new Pawn(P2);

        coordinates pawn1p = {2,1};
        coordinates pawn1d = {2,3};
        coordinates pawn2p = {1,3};
        coordinates pawn2d = {2,2};

        board->print();
        board->addPiece(pawn1, pawn1p);
        board->addPiece(pawn2, pawn2p);
        board->print();
        cout << board->movePiece(pawn1p, pawn1d) << endl;
        board->print();
        cout << board->movePiece(pawn2p, pawn2d) << endl;
        board->print();

        // LEFT OFF IN TESTING EN PASSANT
    
    #else // Main game loop
        // Do nothing (still working on testing)

    #endif

    // Delete the game board object before exiting
    delete board;

    return 0;
}
