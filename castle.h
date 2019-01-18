/* Header file "castle.h" */

/* used in castle.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef CASTLE_H
#define CASTLE_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class Castle : public ChessPiece {

public:
  Castle(Colour c, ChessBoard* p) :
    ChessPiece(c, CASTLE, p) {}

    bool isValidMove(const char* source_square,
      const char* destination_square) override;
};

#endif
