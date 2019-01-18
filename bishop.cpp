/* Implementation file "bishop.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "bishop.h"

bool Bishop::isValidMove(const char* source_square,
  const char* destination_square) {

  if(myBoard -> isPathClear(source_square, destination_square) == 0) {
    return 0;
  }

  /* A bishop can only move diagonally, not vertically or horizontally */
  if(abs(destination_square[1] - source_square[1])
  != abs(destination_square[0] - source_square[0])) {
      return 0;
  }

  return 1;
}
