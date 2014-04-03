#makefile for 229 Project 2 game of life prototype

#compiler to use
CC=g++

#all executables
ALL=life

#executables
all:$(ALL)

life: life.o Simulation.o GridDimension.o Cell.o GameBoard.o View.o CmdView.o GOLOut.o
	$(CC) -o life life.o Simulation.o GridDimension.o Cell.o GameBoard.o View.o CmdView.o GOLOut.o

#object files
life.o: life.cc
	$(CC) -c life.cc
Simulation.o: Simulation.cc Simulation.hh
	$(CC) -c Simulation.cc
GridDimension.o: GridDimension.cc GridDimension.hh
	$(CC) -c GridDimension.cc
Cell.o: Cell.cc Cell.hh
	$(CC) -c Cell.cc
GameBoard.o: GameBoard.cc GameBoard.hh
	$(CC) -c GameBoard.cc
View.o: View.cc View.hh
	$(CC) -c View.cc
CmdView.o: CmdView.cc CmdView.hh
	$(CC) -c CmdView.cc
GOLOut.o: GOLOut.cc GOLOut.hh
	$(CC) -c GOLOut.cc

#clean
clean:
	rm -f $(ALL) *.o

cleanobjects:
	rm -f *.o
