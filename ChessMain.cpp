#include "ChessBoard.h"

#include <iostream>

using namespace std;

int main() {

    cout << "===========================" << endl;
    cout << "Initiating chessgame..." << endl;
    cout << "===========================" << endl;
    ChessBoard cb;

    cout << endl;
    cb.printBoard();
    cout << endl;

    cout << "Please submit moves in the example format \"A2\", \"B7\"\n(i.e. a capital letter followed by a digit)" << endl;
    cout << endl;

    cout << "===========================" << endl;
    cout << "Let's get started!" << endl;
    cout << "===========================" << endl;

    string source_, destination_;

    while(!cb.game_is_finished_) {
      cout << "It is ";

      switch(cb.whoose_turn_) {
        case 0:   cout << "Black";
                  break;
        case 1:   cout << "White";
                  break;
        default:  cout << "No colour has been specified!";
      }

      cout << "'s turn to move!" << endl;

      cout << "Please enter the square you want to move from: ";
      cin >> source_;
      cout << "Please enter the square you want to move to: ";
      cin >> destination_;

      const char* s = source_.c_str();
      const char* d = destination_.c_str();

      cb.submitMove(s, d);
      cout << endl;

      cout << "The board is now: " << endl;

      cb.printBoard();
      cout << endl;

    }

    cout << endl;
    cout << "--- The game has ended! ---" << endl;

    return 0;
}
