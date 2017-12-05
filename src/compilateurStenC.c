
#include "compilateurStenC.h"

int main()
{
    SYMTAB = symtable_new();
    CODE = code_new();
    int r = yyparse();
    symtable_dump(SYMTAB);
    code_dump(CODE);
    intermediaryToMIPS(SYMTAB, CODE);
    symtable_free(SYMTAB);
    code_free(CODE);
    return r;
}