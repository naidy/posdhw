all: hw3

hw3: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o -lgtest
else
	g++ -o hw3 main.o -lgtest -lpthread
endif

main.o: main.cpp utStruct.h utVariable.h atom.h struct.h variable.h number.h
	g++ -std=gnu++0x -c main.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
