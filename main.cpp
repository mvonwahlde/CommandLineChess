/*
Author: Matthew VonWahlde
Last Modified: 7/9/24
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

// Macros to check if a character is a letter or number
#define IS_LETTER(ch) (bool)(ch >= 'A' && ch <= 'Z')
#define IS_NUMBER(ch) (bool)(ch >= '0' && ch <= '9')

// Macros to convert user inputted coordinates to integer coordinate pairs
#define CAPITAL_LETTER_TO_ROW(ch) (int)(ch - 65)  // 'A' corresponds to 0
#define NUMBER_TO_COLUMN(num)     (int)(num - 49) // '1' corresponds to 0

// Function Prototypes (declared below main)
ret_t parseCoordinates(string str, coordinates& pos, coordinates& dest);
void parseNextCoordinatePair(string str, int& idx, coordinates& coords);
ret_t checkValidCoordinates(const coordinates& coords);
bool emptyString(string str, int idx);


// Program entry point
int main(){
    
    #ifdef DEBUG // Testing 
        
        // Create a new game board object
        Board* board = new Board;
        board->print();

        delete board;

     
    #else // Main game loop
        // Do nothing (still working on testing)

    #endif


    return 0;
}


/*
Function: parseCoordinates()
Description: Takes an input string and parses into position and destination coordinates. Checks if the coordinates are valid
Inputs: string str - the input from the command line that contains coordaintes pairs (ex: "E2 E4")
        const coordinates& pos  - returns the piece's current position
        const coordinates& dest - returns the piece's intended destination
Output: Returns INVALID_MOVE if coordinates are out of bounds or VALID_MOVE if coordiantes are in bounds 
*/
ret_t parseCoordinates(string str, coordinates& pos, coordinates& dest){
    // Holds the current index in the string
    int idx = 0;

    // Parse next set of coordiantes and check if they are within the board
    parseNextCoordinatePair(str, idx, pos);
    if(checkValidCoordinates(pos) == INVALID_MOVE){
        return INVALID_MOVE;
    }
    
    // Parse next set of coordinates and check if they are within the board
    parseNextCoordinatePair(str, idx, dest);
    if(checkValidCoordinates(dest) == INVALID_MOVE){
        return INVALID_MOVE;
    }

    // Check if the rest of the string is empty after
    if(emptyString(str, idx) == false){
        return INVALID_MOVE;
    }

    // Return valid move because there are two (and only two) valid sets of coordinates
    return VALID_MOVE;
}


/*
Function: parseNextCoordinatePair()
Description: Takes an input string and finds/parses the next set of coordinates. If there are no coordinates, coords row and col fields are set to -1
Inputs: string str - the input from the command line that contains coordaintes pairs (ex: "E2 E4")
        int& idx - the current index in the string
        const coordinates& coords - returns the next set of coordinates (or {-1, -1} if there is no next coordinate pair)
Output: None
*/
void parseNextCoordinatePair(string str, int& idx, coordinates& coords){
    // Set the error return value if the coordinates are not valid
    coords.row = -1;
    coords.col = -1;

    // Check that the index is in the bounds of the string
    if(idx >= (int)str.length()){
        return;
    }

    // Find the next character that is not a space
    while(str[idx] == ' '){
        idx++;
    }

    // Make sure that the next character is a letter (if null terminator, this will fail)
    char rowChar = str[idx++];
    if(IS_LETTER(rowChar) == false){
        return;
    }

    // Make sure that the next character is a number (if null terminator, this will fail)
    char colChar = str[idx++];
    if(IS_NUMBER(colChar) == false){
        return;
    }

    // Make sure that the next character is either a space or a null terminator
    if(str[idx] != ' ' && str[idx] != '\0'){
        return;
    }

    // Convert the characters to row and column integers
    coords.row = CAPITAL_LETTER_TO_ROW(rowChar);
    coords.col = NUMBER_TO_COLUMN(colChar);
}


/*
Function: checkValidCoordinates()
Description: Checks that the inputted coordinates are within the minimum and maximum row and column values of the board
Inputs: const coordinates& coords - The coordinates that are being verified
Output: Returns INVALID_MOVE if coordinates are out of bounds or VALID_MOVE if coordiantes are in bounds 
*/
ret_t checkValidCoordinates(const coordinates& coords){
    // Check valid row
    if(coords.row < 0 || coords.row >= NUM_BOARD_ROWS){
        return INVALID_MOVE;
    }
    
    // Check valid column
    if(coords.col < 0 || coords.col >= NUM_BOARD_COLS){
        return INVALID_MOVE;
    }

    // Valid coordinates
    return VALID_MOVE;
}


/*
Function: emptyString()
Description: Checks if the rest of the string at and after index are spaces
Inputs: string str - The string that is being checked
        int idx - The current index for the string
Output: Returns false if the remaining string contains characters besides spaces (and the null terminator)
*/
bool emptyString(string str, int idx){
    // Check for an out of bounds index
    if(idx > (int)str.length()){
        return false;
    }
     
    // Check if the remaining characters are spaces
    while(str[idx] != '\0'){
        if(str[idx] != ' '){
            return false;
        }

        idx++;
    }

    return true;
}
