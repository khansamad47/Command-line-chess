/* Header file "chessboard.h" */

/* used in chessboard.cpp, bishop.cpp, castle.cpp, king.cpp, knight.cpp
  pawn.cpp, queen.cpp */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <map>
#include <string>
#include "ChessPiece.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "castle.h"
#include "king.h"
using namespace std;

#define MAX_CAPTUREDPIECES 30

class ChessBoard {

private:
  map <string, ChessPiece*> board;
  /* I save the captured pieces in an array for future functionality extensions
  e.g. pawn promotion */
  ChessPiece* captured_pieces[MAX_CAPTUREDPIECES];
  int no_of_captured_pieces_;
  bool black_in_check_;
  bool white_in_check_;
  /* This function initialises the chessboard and calls the board setup */
  void initialiseChessBoard();
  /* This function sets up the board with standard starting positions */
  void setupChessBoard();
  /* This function switch turns */
  void switchTurn();
  /* This function prints a message to the screen if the move is invalid */
  void invalidMove(const char* source_square, const char* destination_square);
  /* This function checks the state of the board and prints a message
  to the screen if the game is in check, checkmate or stalemate */
  void checkState();
  /* This function iterates through the board and checks if any piece
  can capture the king - if true, the game is in check */
  bool inCheck();
  /* This function iterates through the board and finds the king */
  bool findTheKing(Colour colour);
  /* This function iterates through the board and checks if any piece
  on the board can move legally - if false, the game is in stalemate */
  bool notInStalemate();
  /* This function helps the notInStalemate function to check any valid move
  for a given piece */
  bool anyValidMove(const char* source_square);
  /* This function helps the notInStalemate and anyValidMove function
  by pretending to move a piece to check if it is legal (e.g. preventing
  that a player makes a move that would put its own king in check)*/
  bool tryToMove(const char* source_square, const char* destination_square);

public:
  /* Chessboard constructor */
  ChessBoard();
  /* Chessboard deconstructor */
  ~ChessBoard();
  string black_king_position;
  string white_king_position;
  Colour whoose_turn_;
  /* Is the game in checkmate or stalemate? */
  bool game_is_finished_;
  /* This function resets the chessboard and starts a new game */
  void resetBoard();
  /* This function moves a given piece from the specified source_square
  to the destination_square */
  void submitMove(const char* source_square, const char* destination_square);
  /* This function prints the board for visual aid */
  void printBoard();
  /* This function checks if the path is clear */
  bool isPathClear(const char* source_square, const char* destination_square);
  /* This function checks if a move is within the boundaries of the board */
  bool withinBoard(const char* source_square, const char* destination_square);
  /* This function checks if a given square is empty */
  bool isEmpty(const char* square);
};

#endif
