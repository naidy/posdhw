all: hw4

hw4: main.o atom.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o atom.o list.o -lgtest
else
	g++ -o hw4 main.o atom.o list.o -lgtest -lpthread
endif

main.o: main.cpp utList.h struct.h number.h list.h
	g++ -std=gnu++0x -c main.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
list.o: list.cpp list.h variable.h
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
