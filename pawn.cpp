/* Implementation file "pawn.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "pawn.h"

bool Pawn::isValidMove(const char* source_square,
  const char* destination_square) {

  if(myBoard -> isPathClear(source_square, destination_square) == 0) {
    return 0;
  }

  /* A pawn cannot move backwards */
  if((this -> colour == BLACK) && !(destination_square[1] < source_square[1])) {
    return 0;
  }
  if((this -> colour == WHITE) && !(destination_square[1] > source_square[1])) {
    return 0;
  }

  /* A pawn can move 2 squares on its first move */
  bool firstdraw = 0;
  if(source_square[1] == '7' || source_square[1] == '2') {
    firstdraw = 1;
  }

  if(myBoard -> isEmpty(destination_square) == 1) {
    if(source_square[0] != destination_square[0]) {
      return 0;
    } else if(abs(destination_square[1] - source_square[1]) != 1 && firstdraw == 0) {
      return 0;
    } else if(abs(destination_square[1] - source_square[1]) > 2 && firstdraw == 1) {
      return 0;
    }
  }

  /* A pawn can move diagonally to capture an opponent */
  if(myBoard -> isEmpty(destination_square) == 0) {
    if(((abs(destination_square[1] - source_square[1])
    != abs(destination_square[0] - source_square[0]))
    && abs(destination_square[1] - source_square[1]) > 1)
    || abs(destination_square[1] - source_square[1]) > 1
    || abs(destination_square[0] - source_square[0]) > 1
    || (abs(destination_square[1] - source_square[1])
    != abs(destination_square[0] - source_square[0]))) {
      return 0;
    }
  }

  return 1;
}
