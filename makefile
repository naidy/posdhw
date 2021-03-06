all:hw8 shell

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
	g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

hw8: mainExp.o exception.h expression.h atom.o list.o struct.o scanner.h parser.h global.h exp.h
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainExp.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainExp.o atom.o list.o struct.o -lgtest -lpthread
endif

mainExp.o: mainExp.cpp exception.h expression.h
	g++ -std=gnu++0x -c mainExp.cpp

shell: mainShell.o exception.h expression.h atom.o list.o struct.o scanner.h parser.h global.h exp.h
ifeq (${OS}, Windows_NT)
	g++ -o shell mainShell.o atom.o list.o struct.o -lgtest
else
	g++ -o shell mainShell.o atom.o list.o struct.o -lgtest -lpthread
endif

mainShell.o: mainShell.cpp
	g++ -std=gnu++0x -c mainShell.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner
stat:
	wc *.h *.cpp
