/* Header file "chesspiece.h" */

/* used in chessboard.cpp, bishop.cpp, castle.cpp, king.cpp, knight.cpp
  pawn.cpp, queen.cpp */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>

using namespace std;

enum Colour {BLACK, WHITE};
enum PieceType {KING, CASTLE, BISHOP, QUEEN, KNIGHT, PAWN};

class ChessBoard; //forward class declaration

class ChessPiece {

protected:
  Colour colour;
  PieceType type;
  ChessBoard* myBoard;

public:
  ChessPiece(Colour c, PieceType t, ChessBoard* p) :
    colour(c), type(t), myBoard(p) { }

  virtual ~ChessPiece();
  /* This function prints the chesspiece to the screen in Unicode format */
  void printPiece();
  /* This function fetches the chesspiece type */
  PieceType fetchType();
  /* This function fetches the chesspiece colour */
  Colour fetchColour();
  /* This function prints the chesspiece type to the screen */
  void printType();
  /* This function prints the chesspiece colour to the screen */
  void printColour();
  /* This function checks if a given chesspiece move is valid */
  virtual bool isValidMove(const char* source_square,
    const char* destination_square) = 0;

};

#endif
