#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\Trabalho-DCC045.exe

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\Trabalho-DCC045.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\CExport.o $(OBJDIR_DEBUG)\\ErrorManager.o $(OBJDIR_DEBUG)\\LexicalAnalyzer.o $(OBJDIR_DEBUG)\\SymbolTable.o $(OBJDIR_DEBUG)\\TableEntry.o $(OBJDIR_DEBUG)\\main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\CExport.o $(OBJDIR_RELEASE)\\ErrorManager.o $(OBJDIR_RELEASE)\\LexicalAnalyzer.o $(OBJDIR_RELEASE)\\SymbolTable.o $(OBJDIR_RELEASE)\\TableEntry.o $(OBJDIR_RELEASE)\\main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG) md $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\CExport.o: CExport.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c CExport.cpp -o $(OBJDIR_DEBUG)\\CExport.o

$(OBJDIR_DEBUG)\\ErrorManager.o: ErrorManager.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ErrorManager.c -o $(OBJDIR_DEBUG)\\ErrorManager.o

$(OBJDIR_DEBUG)\\LexicalAnalyzer.o: LexicalAnalyzer.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c LexicalAnalyzer.c -o $(OBJDIR_DEBUG)\\LexicalAnalyzer.o

$(OBJDIR_DEBUG)\\SymbolTable.o: SymbolTable.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c SymbolTable.cpp -o $(OBJDIR_DEBUG)\\SymbolTable.o

$(OBJDIR_DEBUG)\\TableEntry.o: TableEntry.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c TableEntry.cpp -o $(OBJDIR_DEBUG)\\TableEntry.o

$(OBJDIR_DEBUG)\\main.o: main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.c -o $(OBJDIR_DEBUG)\\main.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\CExport.o: CExport.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c CExport.cpp -o $(OBJDIR_RELEASE)\\CExport.o

$(OBJDIR_RELEASE)\\ErrorManager.o: ErrorManager.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ErrorManager.c -o $(OBJDIR_RELEASE)\\ErrorManager.o

$(OBJDIR_RELEASE)\\LexicalAnalyzer.o: LexicalAnalyzer.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c LexicalAnalyzer.c -o $(OBJDIR_RELEASE)\\LexicalAnalyzer.o

$(OBJDIR_RELEASE)\\SymbolTable.o: SymbolTable.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c SymbolTable.cpp -o $(OBJDIR_RELEASE)\\SymbolTable.o

$(OBJDIR_RELEASE)\\TableEntry.o: TableEntry.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c TableEntry.cpp -o $(OBJDIR_RELEASE)\\TableEntry.o

$(OBJDIR_RELEASE)\\main.o: main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.c -o $(OBJDIR_RELEASE)\\main.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

