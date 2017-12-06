all: hw7

hw7: main.o atom.o struct.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 main.o atom.o struct.o list.o -lgtest
else
	g++ -o hw7 main.o atom.o struct.o list.o -lgtest -lpthread
endif

main.o: main.cpp utIterator.h struct.h variable.h atom.h list.h iterator.h
	g++ -std=gnu++0x -c main.cpp
atom.o: atom.cpp atom.h variable.h iterator.h
	g++ -std=gnu++0x -c atom.cpp
struct.o: struct.cpp struct.h iterator.h
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h iterator.h
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
