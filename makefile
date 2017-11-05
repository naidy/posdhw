all: hw5

hw5: main.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o atom.o -lgtest
else
	g++ -o hw5 main.o atom.o -lgtest -lpthread
endif

main.o: main.cpp utParser.h struct.h number.h list.h term.h global.h scanner.h parser.h variable.h
	g++ -std=gnu++0x -c main.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp
