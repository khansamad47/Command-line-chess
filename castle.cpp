/* Implementation file "castle.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "castle.h"

using namespace std;

bool Castle::isValidMove(const char* source_square,
  const char* destination_square) {

  if(myBoard -> isPathClear(source_square, destination_square) == 0) {
    return 0;
  }

  /* A castle can only move vertically and horizontally, not diagonally */
  if(abs(destination_square[1] - source_square[1]) > 0
  && abs(destination_square[0] - source_square[0]) != 0) {
      return 0;
  }

  return 1;
}
