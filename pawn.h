/* Header file "pawn.h" */

/* used in pawn.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef PAWN_H
#define PAWN_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class Pawn : public ChessPiece {

public:
  Pawn(Colour c, ChessBoard* p) :
    ChessPiece(c, PAWN, p) {}

  bool isValidMove(const char* source_square,
    const char* destination_square) override;

};

#endif
