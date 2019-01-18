/* Header file "king.h" */

/* used in king.cpp and chessboard.cpp  */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#ifndef KING_H
#define KING_H

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

class King : public ChessPiece {

public:
  King(Colour c, ChessBoard* p) :
    ChessPiece(c, KING, p) {}

    bool isValidMove(const char* source_square,
      const char* destination_square) override;
};

#endif
