#include "CExport.h"
#include "SymbolTable.h"

using namespace c_namespace;

namespace
{
    IdentifierTable *identifierTable;
    NumTable *numTable;
    LiteralTable *literalTable;
    ReservedWordTable *reservedWordTable;
} // namespace name

void constructorTable()
{
    identifierTable = new IdentifierTable();
    numTable = new NumTable();
    literalTable = new LiteralTable();
    reservedWordTable = new ReservedWordTable();
}

void destructorTable()
{
    delete identifierTable;
    delete numTable;
    delete literalTable;
    delete reservedWordTable;
}

void setReservedWord(const char *lexeme, int token)
{
    reservedWordTable->insert(lexeme, token);
}

void setIdentifier(const char *lexeme)
{
    identifierTable->insert(lexeme);
}

void setNum(const char *lexeme)
{
    numTable->insert(lexeme);
}

void setLiteral(const char *lexeme)
{
    literalTable->insert(lexeme);
}

void printReservedWordTable()
{
    reservedWordTable->print();
}

void printIdentifierTable()
{
    identifierTable->print();
}

void printLiteralTable()
{
    literalTable->print();
}

void printNumTable()
{
    numTable->print();
}

void printLexemeArray()
{
    std::cout << std::endl
              << "Reserved Word Lexeme Array:";
    reservedWordTable->print_LexArray();
    std::cout << std::endl
              << "Identifier Lexeme Array:";
    identifierTable->print_LexArray();
    std::cout << std::endl
              << "Identifier Lexeme Array:";
    literalTable->print_LexArray();
    std::cout << std::endl
              << "Identifier Lexeme Array:";
    numTable->print_LexArray();
}

int searchReservedWord(const char *lexeme)
{
    if (reservedWordTable->searchLexeme(lexeme) != NULL)
    {
        int result = reservedWordTable->searchLexeme(lexeme)->getToken();
        return result;
    }
    else
        return 0;
}

int searchIdentifier(const char *lexeme)
{
    if (identifierTable->searchLexeme(lexeme) != NULL)
    {
        int result = identifierTable->searchLexeme(lexeme)->getToken();
        return result;
    }
    else
        return 0;
}

int searchNum(const char *lexeme)
{
    if (numTable->searchLexeme(lexeme) != NULL)
    {
        int result = numTable->searchLexeme(lexeme)->getToken();
        return result;
    }
    else
        return 0;
}

int searchLiteral(const char *lexeme)
{
    if (literalTable->searchLexeme(lexeme) != NULL)
    {
        int result = literalTable->searchLexeme(lexeme)->getToken();
        return result;
    }
    else
        return 0;
}
