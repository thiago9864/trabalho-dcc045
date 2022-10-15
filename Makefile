run: 
	gcc -c -std=c99 -o build/ErrorManager.o ErrorManager.c -Wall -g -ggdb
	gcc -c -std=c99 -o build/LexicalAnalyzer.o LexicalAnalyzer.c -Wall -g -ggdb
	gcc -c -std=c99 -o build/main.o main.c -Wall -g -ggdb
	g++ -c -std=c++0x -o build/SymbolTable.o SymbolTable.cpp -Wall -g -ggdb
	g++ -c -std=c++0x -o build/CExport.o CExport.cpp -Wall -g -ggdb
	g++ -o main build/*.o
