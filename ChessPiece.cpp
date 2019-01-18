#include "ChessPiece.h"

ChessPiece::~ChessPiece() {}

void ChessPiece::printPiece() {
  if(colour == BLACK && type == KING)   cout << "♚";
  if(colour == BLACK && type == CASTLE) cout << "♜";
  if(colour == BLACK && type == BISHOP) cout << "♝";
  if(colour == BLACK && type == QUEEN)  cout << "♛";
  if(colour == BLACK && type == KNIGHT) cout << "♞";
  if(colour == BLACK && type == PAWN)   cout << "♟";

  if(colour == WHITE && type == KING)   cout << "♔";
  if(colour == WHITE && type == CASTLE) cout << "♖";
  if(colour == WHITE && type == BISHOP) cout << "♗";
  if(colour == WHITE && type == QUEEN)  cout << "♕";
  if(colour == WHITE && type == KNIGHT) cout << "♘";
  if(colour == WHITE && type == PAWN)   cout << "♙";
}

PieceType ChessPiece::fetchType() {
  return type;
}

Colour ChessPiece::fetchColour() {
  return colour;
}

void ChessPiece::printType() {
  switch(type) {
    case 0:   cout << "King";
              break;
    case 1:   cout << "Castle";
              break;
    case 2:   cout << "Bishop";
              break;
    case 3:   cout << "Queen";
              break;
    case 4:   cout << "Knight";
              break;
    case 5:   cout << "Pawn";
              break;
    default:  cout << "No piece type has been specified!";
  }
}

void ChessPiece::printColour() {
  switch(colour) {
    case 0:   cout << "Black";
              break;
    case 1:   cout << "White";
              break;
    default:  cout << "No colour has been specified!";
  }
}
