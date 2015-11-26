makeTestSymboltable : SymboltableTarget TestSymboltableTarget  
	g++ -g objs/Symboltable.o objs/Info.o objs/Key.o objs/SymtabEntry.o debug/TestSymboltable.o -o debug/SymboltableTest

SymboltableTarget :  src/Symboltable.cpp includes/Symboltable.h 
	g++ -g  -c -Wall src/Symboltable.cpp -o objs/Symboltable.o
	g++ -g  -c -Wall src/Info.cpp        -o objs/Info.o  
	g++ -g  -c -Wall src/SymtabEntry.cpp -o objs/SymtabEntry.o  
	g++ -g  -c -Wall src/Key.cpp         -o objs/Key.o  

TestSymboltableTarget :  src/TestSymboltable.cpp includes/Symboltable.h
	g++ -g  -c -Wall src/TestSymboltable.cpp  -o debug/TestSymboltable.o  

cleanSymboltable:
	rm -f objs/*.o
	rm -f debug/*
	$(MAKE) makeTestSymboltable
	
SymboltableOBJTarget:
	$(MAKE) SymboltableTarget
