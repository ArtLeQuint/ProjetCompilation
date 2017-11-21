/* Ce code gère l'analyse lexicale pour des expression d'entier actuellement */
{%
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}
ent [0-9]+
ope [\+\-\*\/\(\)]
%%
{ent} {yylval.val=atoi(yytext);printf("entier : %d\n", yylval.val);return ENTIER;}
{ope} {printf("ope\n");return yytext[0];}
"\n"  {printf("truc\n");return yytext[0];}
%%
