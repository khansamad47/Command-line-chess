/* Implementation file "knight.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "knight.h"

bool Knight::isValidMove(const char* source_square,
  const char* destination_square) {
    
  /* A knight can only move to squares and to the side */
  if(abs(destination_square[1] - source_square[1]) == 2
  && abs(destination_square[0] - source_square[0]) == 1) {
      return 1;
    }

  if(abs(destination_square[0] - source_square[0]) == 2
  && abs(destination_square[1] - source_square[1]) == 1) {
      return 1;
  }

  return 0;
}
