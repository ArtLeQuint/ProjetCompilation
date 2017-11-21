/* Ce code gère la grammaire pour des expression d'entier actuellement */
%{
#include <stdio.h>
#include <stdlib.h>
%}
%union {int val;}
%token <val> ENTIER
%type <val> E
%type <val> T
%type <val> F
%start ligne
%right '='
%left '+' '-'
%left '*' '/'
%left UMOINS
%%

ligne : E '\n' {printf("%d\n",$1);exit(0);}
        ;
E : E '+' T {printf("E1\n");$$ = $1 + $3; }
    | T
    | '-' E %prec UMOINS {printf("E2\n");$$ = -($2);}
    ;
T : T '*' F {printf("T\n");$$ = $1 * $3; }
    | F
    ;
F : '(' E ')' {printf("F\n");$$ = $2; }
    | ENTIER
    ;

%%

int yyerror(char *s) {
  printf("%s\n",s);
}

int main(void) {
  yyparse();
}
