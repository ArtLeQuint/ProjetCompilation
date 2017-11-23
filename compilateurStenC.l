/* Ce code gère l'analyse lexicale pour des expression d'entier actuellement */
{%
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int m; // Cet entier va permettre de savoir si on ferme un MAIN = 1, un IF = 2, un WHILE = 3, un FOR = 4..., 0 si jamais rien ouvert
%}
ent [0-9]+
declaration "int "|"stencil "
%%
"int main(void) {" {m = 1; return DEBUTMAIN;}
'}' {if (m == 1) return FINMAIN;}
{ent} {yylval.val=atoi(yytext);return INT;}
declaration {return DECLARATION;}
"if "
"for"
'+'|'-' {return PLUSMOINS;}
'*'|'/' {return FOISDIV;}
"\n"  {return yytext[0];}
%%
