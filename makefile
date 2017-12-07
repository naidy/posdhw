all: hw7

hw7: main.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 main.o atom.o -lgtest
else
	g++ -o hw7 main.o atom.o -lgtest -lpthread
endif

main.o: main.cpp utIterator.h struct.h variable.h atom.h list.h iterator.h number.h
	g++ -std=gnu++0x -c main.cpp
atom.o: atom.cpp atom.h variable.h iterator.h
	g++ -std=gnu++0x -c atom.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
