/* Header file "queen.h" */

/* used in queen.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class Queen : public ChessPiece {

public:
  Queen(Colour c, ChessBoard* p) :
    ChessPiece(c, QUEEN, p) {}

  bool isValidMove(const char* source_square,
    const char* destination_square) override;

};

#endif
