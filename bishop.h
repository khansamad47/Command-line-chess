/* Header file "bishop.h" */

/* used in bishop.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class Bishop : public ChessPiece {

public:
  Bishop(Colour c, ChessBoard* p) :
    ChessPiece(c, BISHOP, p) {}

    bool isValidMove(const char* source_square,
      const char* destination_square) override;
};

#endif
