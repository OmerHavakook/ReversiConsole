#Name: Lee alima
#ID: 313467441

a.out: Cell.o Board.o ConsoleScreen.o HumanPlayer.o GameLogic.o GameFlow.o main.o
	g++ Cell.o Board.o ConsoleScreen.o HumanPlayer.o GameLogic.o GameFlow.o main.o

Cell.o: Cell.cpp Cell.h
	g++ -c Cell.cpp Cell.h

Board.o: Board.cpp Board.h Cell.h Screen.h
	g++ -c Board.cpp Board.h Cell.h Screen.h

ConsoleScreen.o: ConsoleScreen.cpp ConsoleScreen.h Screen.h
	g++ -c ConsoleScreen.cpp ConsoleScreen.h Screen.h

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Player.h
	g++ -c HumanPlayer.cpp HumanPlayer.h Player.h

GameLogic.o: GameLogic.cpp GameLogic.h Player.h Board.h HumanPlayer.h Screen.h
	g++ -c GameLogic.cpp GameLogic.h Player.h Board.h HumanPlayer.h Screen.h

GameFlow.o: GameFlow.cpp GameFlow.h GameLogic.h
	g++ -c GameFlow.cpp GameFlow.h GameLogic.h

main.o: main.cpp GameFlow.h
	g++ -c main.cpp GameFlow.h

run:
	./a.out



