/* Ce code gère la grammaire pour des expression d'entier actuellement */
%{
#include <stdio.h>
#include <stdlib.h>
%}
%union {
  int Val;
  char *String;
  char [2]Ope;
}
%token <String> DECLARATION
%token <String> ID
%token <Val> INT
%token <Val> STENCIL
%token <Ope> PLUSMOINS
%token <Ope> FOISDIV
%token <Ope> LOGIQUE
%type <val> E
%type <val> T
%type <val> F
%start ligne
%right '='
%left '+' '-'
%left '*' '/'
%left UMOINS
%%

ligne : E '\n'           {printf("%d\n",$1);exit(0);}
        ;
E : E '+' T              {$$ = $1 + $3;}
  | E '-' T              {$$ = $1 - $3;}
  | T
  | '-' E %prec UMOINS   {$$ = -($2);}
  ;
T : T '*' F              {$$ = $1 * $3;}
  | T '/' F              {$$ = $1 / $3;}
  | F
  ;
F : '(' E ')'            {$$ = $2;}
  | INT
  ;
%%

int yyerror(char *s) {
  printf("%s\n",s);
}

int main(void) {
  yyparse();
}
