all: hw2

hw2: mainTerm.o prolog.o
	g++ -o hw2 mainTerm.o prolog.o -lgtest -lpthread
mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=c++11 -c mainTerm.cpp
prolog.o: prolog.cpp atom.h number.h variable.h
	g++ -std=c++11 -c prolog.cpp

clean:
	rm -f *.o madRace utAtom
stat:
	wc *.h *.cpp
