all:hello

hello: main.o player.o boardanddice.o
	 g++ -pthread main.o player.o boardanddice.o -o playGame
	 rm *o

main.o: main.cpp
	   g++ -c main.cpp
player.o: player.cpp	
	   g++  -c player.cpp
boardanddice.o: boardanddice.cpp
	   g++ -c boardanddice.cpp

clean.o: 
	rm *o