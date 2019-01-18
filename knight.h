/* Header file "knight.h" */

/* used in knight.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class Knight : public ChessPiece {

public:
  Knight(Colour c, ChessBoard* p) :
    ChessPiece(c, KNIGHT, p) {}

  bool isValidMove(const char* source_square,
    const char* destination_square) override;

};

#endif
