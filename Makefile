run: 
	gcc -c -std=c++0x -o build/main.o main.cpp -Wall -g -ggdb
	gcc -c -std=c++0x -o build/LexicalAnalyzer.o LexicalAnalyzer.cpp -Wall -g -ggdb
	gcc -c -std=c++0x -o build/ErrorManager.o ErrorManager.cpp -Wall -g -ggdb
	g++ -c -std=c++0x -o build/TableEntry.o TableEntry.cpp -Wall -g -ggdb
	g++ -c -std=c++0x -o build/SymbolTable.o SymbolTable.cpp -Wall -g -ggdb
	g++ -c -std=c++0x -o build/RDParser.o RDParser.cpp -Wall -g -ggdb
	g++ -c -std=c++0x -o build/CExport.o CExport.cpp -Wall -g -ggdb
	g++ -o main build/*.o
