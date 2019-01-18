/* Implementation file "queen.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "queen.h"

bool Queen::isValidMove(const char* source_square,
  const char* destination_square) {  //check if move is valid

  if(myBoard -> isPathClear(source_square, destination_square) == 0) {
    return 0;
  }

  /* A queen can move in either direction */
  if((abs(destination_square[0] - source_square[0]) != 0
  && abs(destination_square[1] - source_square[1])
  != abs(destination_square[0] - source_square[0]))
  && !(abs(destination_square[0] - source_square[0]) > 0
  && destination_square[1] == source_square[1])) {
      return 0;
  }

  return 1;
}
