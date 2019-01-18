CXX = g++ -Wall -g
EXE = ChessMain.o ChessBoard.o ChessPiece.o bishop.o castle.o king.o knight.o pawn.o queen.o

chess: $(EXE)
	$(CXX) $(EXE) -o chess

%.o: %.cpp %.h ChessPiece.h
	$(CXX) -c $<

ChessMain.o: ChessBoard.h

ChessBoard.o: bishop.h castle.h king.h knight.h pawn.h queen.h

ChessPiece.o: ChessBoard.h

.PHONY: clean

clean:
	rm -f chess *.o
