all: hw2

hw2: mainTerm.o prolog.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o prolog.o -lgtest
else
	g++ -o hw2 mainTerm.o prolog.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=gnu++0x -c mainTerm.cpp
prolog.o: prolog.cpp atom.h number.h variable.h
	g++ -std=gnu++0x -c prolog.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
