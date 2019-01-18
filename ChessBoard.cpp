/* Implementation file "chessboard.cpp" */

/* Author: Ulrik Stig Hansen
   Program last changed: 9th December 2018 */

#include "ChessBoard.h"

ChessBoard::ChessBoard() {
  initialiseChessBoard();
}

ChessBoard::~ChessBoard() {
  map<string, ChessPiece*>::iterator i = board.begin();
  while(i != board.end()) {
    if(i -> second != nullptr) {
      delete i -> second;
    }
    i++;
  }

  int k = 0;
  while(k < no_of_captured_pieces_) {
    delete captured_pieces[k];
    k++;
  }
}

void ChessBoard::initialiseChessBoard() {
  setupChessBoard();
  whoose_turn_ = WHITE;
  for(int i = 0; i < MAX_CAPTUREDPIECES; i++) {
    captured_pieces[i] = nullptr;
  }
  no_of_captured_pieces_ = 0;
  black_king_position = "E8";
  white_king_position = "E1";
  black_in_check_ = 0;
  white_in_check_ = 0;
  game_is_finished_ = 0;
  cout << "A new chess game is started!" << endl;
}

void ChessBoard::resetBoard() {
  map<string, ChessPiece*>::iterator i = board.begin();
  while(i != board.end()) {
    if (i -> second != nullptr) {
      delete i -> second;
    }
    board.erase(i);
    i++;
  }

  int k = 0;
  while(k < no_of_captured_pieces_) {
    delete captured_pieces[k];
    k++;
  }

  initialiseChessBoard();
}

void ChessBoard::setupChessBoard() {
  /* Insert black pieces */
  board.insert(make_pair<string, ChessPiece*>("A8", new Castle(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("B8", new Knight(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("C8", new Bishop(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("D8", new Queen(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("E8", new King(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("F8", new Bishop(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("G8", new Knight(BLACK, this)));
  board.insert(make_pair<string, ChessPiece*>("H8", new Castle(BLACK, this)));
  char square[3];
  square[2] = '\0';
  for(char file = 'A'; file <= 'H'; file++) {
    square[0] = file;
    square[1] = '7';
    board.insert(make_pair<string, ChessPiece*>(square, new Pawn(BLACK, this)));
  }

  /* Insert empty spaces */
  for(char file = 'A'; file <= 'H'; file++) {
    for(char rank = '6'; rank >= '3'; rank--) {
      square[0] = file;
      square[1] = rank;
      board.insert(make_pair<string, ChessPiece*>(square, (ChessPiece*)nullptr));
    }
  }

  /* Insert white pieces */
  for(char file = 'A'; file <= 'H'; file++) {
    square[0] = file;
    square[1] = '2';
    board.insert(make_pair<string, ChessPiece*>(square, new Pawn(WHITE, this)));
  }
  board.insert(make_pair<string, ChessPiece*>("A1", new Castle(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("B1", new Knight(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("C1", new Bishop(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("D1", new Queen(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("E1", new King(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("F1", new Bishop(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("G1", new Knight(WHITE, this)));
  board.insert(make_pair<string, ChessPiece*>("H1", new Castle(WHITE, this)));
}

void ChessBoard::submitMove(const char* source_square, const char* destination_square) {

  if(board[source_square] != nullptr && tryToMove(source_square, destination_square) == 0) {

    invalidMove(source_square, destination_square);

  } else {
    if(board[source_square] == nullptr) {
      cout << "There is no piece at position " << source_square << "!" << endl;
    } else if(!(board[source_square] -> fetchColour() == whoose_turn_)) {
      cout << "It is not ";
      board[source_square] -> printColour();
      cout << "'s turn to move!" << endl;
    } else if((board[source_square] -> isValidMove(source_square, destination_square)) == 0) {

      invalidMove(source_square, destination_square);

    } else if((board[source_square] -> isValidMove(source_square, destination_square)) == 1
      && board[destination_square] == nullptr) {

      board[source_square] -> printColour();
      cout << "'s ";
      board[source_square] -> printType();
      cout << " moves from " << source_square << " to " << destination_square << endl;

      board[destination_square] = board[source_square];
      board[source_square] = nullptr;

      switchTurn();

    } else if((board[source_square] -> isValidMove(source_square, destination_square)) == 1
      && board[destination_square] != nullptr
      && board[source_square] -> fetchColour() != board[destination_square] -> fetchColour()) {

      board[source_square] -> printColour();
      cout << "'s ";
      board[source_square] -> printType();
      cout << " moves from " << source_square << " to " << destination_square
      << " taking ";
      board[destination_square] -> printColour();
      cout << "'s ";
      board[destination_square] -> printType();
      cout << endl;

      captured_pieces[no_of_captured_pieces_] = board[destination_square];
      board[destination_square] = nullptr;
      board[destination_square] = board[source_square];
      board[source_square] = nullptr;

      no_of_captured_pieces_++;

      switchTurn();

    } else if(board[source_square] -> fetchColour() == board[destination_square] -> fetchColour()) {
      invalidMove(source_square, destination_square);
    } else if(board[source_square] == board[destination_square]) {
      invalidMove(source_square, destination_square);
    } else if(withinBoard(source_square, destination_square) == 0) {
      invalidMove(source_square, destination_square);
    }
  }
  checkState();
}

void ChessBoard::printBoard() {
  cout << "    ";
  for (int i = 0; i < 8; i++)
    cout << (char) ('A' + i) << "   "; //print topline
  cout << endl;
  for (int rank = 0; rank < 8; rank++) {
    cout << "  +---+---+---+---+---+---+---+---+" << endl; //print delimiter
    cout << (char) ('8' - rank) << " ";
    for(int file = 0; file < 8; file++) {
      char square[3];
      square[0] = 'A' + file;
      square[1] = '8' - rank;
      cout << "|";
      if(board[square] != NULL) {
        board[square] -> printPiece();
      } else {
        cout << " ";
      }
      cout << " " << " ";
    }
    cout << "| " << (char) ('8' - rank) << endl;
  }
  cout << "  +---+---+---+---+---+---+---+---+" << endl;
  cout << "    ";
  for (int i = 0; i < 8; i++)
    cout << (char) ('A' + i) << "   ";
}

void ChessBoard::switchTurn() {
  if(whoose_turn_ == BLACK) {
    whoose_turn_ = WHITE;
  } else {
    whoose_turn_ = BLACK;
  }
}

bool ChessBoard::isPathClear(const char* source_square, const char* destination_square) {

  int file = abs(destination_square[0] - source_square[0]);
  int rank = abs(destination_square[1] - source_square[1]);

  char square[3];
  square[2] = '\0';
  //moving up or down
  for(int i = 1; i < rank; i++) {
    //moving up
    if(destination_square[1] - source_square[1] > 0) {
      square[0] = source_square[0];
      square[1] = source_square[1] + i;
    }
    //moving down
    if(destination_square[1] - source_square[1] < 0) {
      square[0] = source_square[0];
      square[1] = source_square[1] - i;
    }
    //Moving up and sideways
    if(destination_square[1] - source_square[1] > 0 && destination_square[0] != source_square[0]) {
      if(destination_square[0] > source_square[0])
        square[0] = source_square[0] + i; //moving right

      if(destination_square[0] < source_square[0])
        square[0] = source_square[0] - i; //moving left

      square[1] = source_square[1] + i; //moving up
    }
    //Moving down and sideways
    if(destination_square[1] - source_square[1] < 0 && destination_square[0] != source_square[0]) {
      if(destination_square[0] > source_square[0])
        square[0] = source_square[0] + i; //moving right

      if(destination_square[0] < source_square[0])
          square[0] = source_square[0] - i; //moving left

      square[1] = source_square[1] - i; //moving down
    }
    if(board[square] != nullptr) { //if the path is not clear, return 0
      return 0;
    }
  }
  //moving sideways
  if(destination_square[1] - source_square[1] == 0) {
    for(int i = 1; i < file; i++) {
      if(destination_square[0] > source_square[0]) //moving right
        square[0] = source_square[0] + i;

      if(destination_square[0] < source_square[0]) //moving left
          square[0] = source_square[0] - i;

      square[1] = source_square[1];
      if(board[square] != nullptr) { //if the path is not clear, return 0
        return 0;
      }
    }
  }
  return 1;
}

bool ChessBoard::withinBoard(const char* source_square, const char* destination_square) {
  if(destination_square[1] > '8' || destination_square[1] < 1
  || destination_square[0] < 'A' || destination_square[0] > 'H') {
    return 0;
  }
  if(source_square[1] > '8' || source_square[1] < 1
  || source_square[0] < 'A' || source_square[0] > 'H') {
    return 0;
  }
  return 1;
}

void ChessBoard::invalidMove(const char* source_square, const char* destination_square) {
  board[source_square] -> printColour();
  cout << "'s ";
  board[source_square] -> printType();
  cout << " cannot move to " << destination_square << "!" << endl;
}

bool ChessBoard::isEmpty (const char* square) {
  if(board[square] != nullptr) {
    return 0;
  }
  return 1;
}

void ChessBoard::checkState() {
  inCheck();
  if(black_in_check_ == 1 && notInStalemate() == 1) {
    cout << "Black is in check" << endl;
  }
  if(black_in_check_ == 1 && notInStalemate() == 0) {
    cout << "Black is in checkmate" << endl;
    game_is_finished_ = 1;
  }
  if(white_in_check_ == 1 && notInStalemate() == 1) {
    cout << "White is in check" << endl;
  }
  if(white_in_check_ == 1 && notInStalemate() == 0) {
    cout << "White is in checkmate" << endl;
    game_is_finished_ = 1;
  }
  if(white_in_check_ == 0 && black_in_check_ == 0 && notInStalemate() == 0) {
    cout << "The game is in stalemate" << endl;
    game_is_finished_ = 1;
  }
}

bool ChessBoard::inCheck() {

  findTheKing(whoose_turn_);

  char tochar_black_king_position[3]; //string to char*
  tochar_black_king_position[2] = '\0';
  tochar_black_king_position[0] = black_king_position[0];
  tochar_black_king_position[1] = black_king_position[1];

  char tochar_white_king_position[3];
  tochar_white_king_position[2] = '\0';
  tochar_white_king_position[0] = white_king_position[0];
  tochar_white_king_position[1] = white_king_position[1];

  char keySquare[3];
  keySquare[2] = '\0';
  map<string, ChessPiece*>::iterator i;
  for (i = board.begin(); i != board.end(); ++i) {
    keySquare[0] = i -> first[0];
    keySquare[1] = i -> first[1];
    if(i -> second != nullptr) {
        if(!(keySquare[0] == tochar_black_king_position[0]
          && keySquare[1] == tochar_black_king_position[1])
          && board[keySquare] -> isValidMove(keySquare, tochar_black_king_position)
          && board[keySquare] -> fetchColour() != BLACK
          && isPathClear(keySquare, tochar_black_king_position)) {
	          black_in_check_ = 1;
            return 1; //black is in check
        }

        if(!(keySquare[0] == tochar_white_king_position[0]
          && keySquare[1] == tochar_white_king_position[1])
          && board[keySquare] -> isValidMove(keySquare, tochar_white_king_position)
          && board[keySquare] -> fetchColour() != WHITE
          && isPathClear(keySquare, tochar_white_king_position)) {
            white_in_check_ = 1;
            return 1; //white is in check
        }
    }
  }
  black_in_check_ = 0;
  white_in_check_ = 0;
  return 0;
}

bool ChessBoard::findTheKing(Colour colour) {
  map<string, ChessPiece*>::iterator i = board.begin();
  while(i != board.end()) {
    if (i -> second != nullptr) {
      if ((i -> second->fetchType() == KING) && (i -> second -> fetchColour() == colour)) {
	       if (colour == BLACK) {
	          black_king_position = i -> first;
         } else {
	          white_king_position = i -> first;
	       }
         return 1;
      }
    }
    i++;
  }
  return 0;
}

bool ChessBoard::notInStalemate() {
  char keySquare[3];
  keySquare[2] = '\0';
  map<string, ChessPiece*>::iterator i;
  for (i = board.begin(); i != board.end(); ++i) {
    if(i -> second != nullptr) {
      keySquare[0] = i -> first[0];
      keySquare[1] = i -> first[1];
      if(anyValidMove(keySquare)) {
        return 1; //there is a valid move, the board is not in stalemate
      }
    }
  }
  return 0; //the board is in stalemate
}

bool ChessBoard::anyValidMove(const char* source_square) {
  if(board[source_square] != nullptr) {
    for (int rank = 0; rank < 8; rank++) {
      for(int file = 0; file < 8; file++) {
        char square[3];
        square[0] = 'A' + file;
        square[1] = '8' - rank;
        if(!(source_square[0] == square[0] && source_square[1] == square[1])) {
          if(board[source_square] -> isValidMove(source_square, square) == 1
          && tryToMove(source_square, square) == 1) {
            if(board[square] != nullptr
              && board[source_square] -> fetchColour() != board[square] -> fetchColour()
              && board[source_square] -> fetchColour() == whoose_turn_) {
                return 1; //the move is valid and the destination is occupied by an opponent
            } else if(board[square] == nullptr && board[source_square] -> fetchColour() == whoose_turn_) {
                return 1; //the move is valid and the destination is not occupied
            }
          }
        }
      }
    }
  }
  return 0; //the move is invalid
}

bool ChessBoard::tryToMove(const char* source_square, const char* destination_square) {

  if(board[source_square] -> isValidMove(source_square, destination_square) == 0) {
    return 0;
  }

  ChessPiece* temp_piece;
  temp_piece = board[destination_square];

  if(board[destination_square] != nullptr) {
    if(board[destination_square] -> fetchColour() == board[source_square] -> fetchColour())
      return 0;
  }

  /* Pretend to make a move */
  board[destination_square] = board[source_square];
  board[source_square] = nullptr;

  if(inCheck() == 1 && whoose_turn_ == BLACK && black_in_check_ == 1) {
    board[source_square] = board[destination_square];
    board[destination_square] = temp_piece;
    return 0; //the move puts a players own piece in check
  }

  if(inCheck() == 1 && whoose_turn_ == WHITE && white_in_check_ == 1) {
    board[source_square] = board[destination_square];
    board[destination_square] = temp_piece;
    return 0; //the move puts a players own piece in check
  }

  /* Undo the pretend move */
  board[source_square] = board[destination_square];
  board[destination_square] = temp_piece;

  return 1;
}
