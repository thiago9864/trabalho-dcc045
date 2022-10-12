#include <stdio.h>
#include "CExport.h"
#include "LexicalAnalyzer.h"


int main()
{
    printf("Hello World\n");

    printObjValue();
    setObjValue(123456);
    printObjValue();

    return 0;
}

