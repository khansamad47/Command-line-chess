/* Implementation file "king.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "king.h"

bool King::isValidMove(const char* source_square,
  const char* destination_square) {

  /* A king can move in either direction, but only one square */
  if(abs(destination_square[1] - source_square[1]) > 1
  || abs(destination_square[0] - source_square[0]) > 1) {
      return 0;
    }

  if(this -> colour == WHITE) {
    myBoard -> white_king_position[0] = destination_square[0];
    myBoard -> white_king_position[1] = destination_square[1];
  }

  if(this -> colour == BLACK) {
    myBoard -> black_king_position[0] = destination_square[0];
    myBoard -> black_king_position[1] = destination_square[1];
  }

  return 1;
}
