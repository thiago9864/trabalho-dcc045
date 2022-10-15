#ifndef C_EXPORT_CPP
#define C_EXPORT_CPP

#ifdef __cplusplus
extern "C"
{
#endif // C++ guard

    void destructorTable();
    void constructorTable();

    void setReservedWord(const char *lexeme, int token);
    void setIdentifier(const char *lexeme);
    void setNum(const char *lexeme);
    void setLiteral(const char *lexeme);

    void printReservedWord();
    void printIdentifier();
    void printLexemeArray();

    int searchReservedWord(const char *lexeme);
    int searchIdentifier(const char *lexeme);
    int searchNum(const char *lexeme);
    int searchLiteral(const char *lexeme);

#ifdef __cplusplus
}
#endif // end C++ guard

#endif // C_EXPORT_CPP