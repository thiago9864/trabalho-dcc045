run: 
	gcc -c -std=c99 -o build/ErrorManager.o ErrorManager.c -Wall -g
	gcc -c -std=c99 -o build/LexicalAnalyzer.o LexicalAnalyzer.c -Wall -g
	gcc -c -std=c99 -o build/main.o main.c -Wall -g
	g++ -c -std=c++0x -o build/SymbolTable.o SymbolTable.cpp -Wall -g
	g++ -c -std=c++0x -o build/CExport.o CExport.cpp -Wall -g
	g++ -o main build/*.o
