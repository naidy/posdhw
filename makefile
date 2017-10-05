all: hw2

hw2: mainTerm.o prolog.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o prolog.o -lgtest
else
	g++ -o hw2 mainTerm.o prolog.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=c++11 -c mainTerm.cpp
prolog.o: prolog.cpp atom.h number.h variable.h
	g++ -std=c++11 -c prolog.cpp

clean:
	rm -f *.o madRace utAtom
stat:
	wc *.h *.cpp
