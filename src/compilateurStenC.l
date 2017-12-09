%{
    #include "quad.h"
    #include "symbol.h"
    #include "symbol_table.h"
    #include "array_type.h"
    #include <stdlib.h>
    #include <string.h>
    #include "../tmp/cfss.y.h"

    void yyerror(char *);
    extern int _line_number;

%}
%option yylineno

/* Inspiré du LEX ANSI C */
D			[0-9]
N 		0|[1-9]{D}*
L			[a-zA-Z]
ID 		{L}({L}|{D})*
char 	[-\[\]()<>=+*/$;{},%!]
string 		\"[^"\n]*["\n]
comment_multiLigne	"/*"([^*]*[*]+[^*/])*[^*]*[*]+"/"
comment_uniLigne	"//"[^\n]*[\n]
comment 			{comment_uniLigne}|{comment_multiLigne}



%%
"else"				{return(ELSE);}
"for"					{return(FOR);}
"if"					{return(IF);}
"int"					{return(INT);}
"return"			{return(RETURN);}
"while"				{return(WHILE);}
"stencil"			{return(STENCIL);}
"continue"		{return(CONTINUE);}
"main(void)"|"main()"  {return(MAIN);}
"+="		{return(ADD_ASSIGN);}
"-="		{return(SUB_ASSIGN);}
"*="		{return(MUL_ASSIGN);}
"/="		{return(DIV_ASSIGN);}
"%="		{return(MOD_ASSIGN);}
"++"		{return(INC_OP);}
"--"		{return(DEC_OP);}
"&&"		{return(AND_OP);}
"||"		{return(OR_OP);}
"<="		{return(LE_OP);}
">="		{return(GE_OP);}
"=="		{return(EQ_OP);}
"!="		{return(NE_OP);}
{char}  {return yytext[0];}

{ID}		{
         yylval.string_value = strdup(yytext);
			   return(IDENTIFIER);
        }

number {yylval.int_value = atoi(yytext); return(NUMBER);}

{string}  {
           yylval.string_value = strdup(yytext+1);
           if (yylval.string_value[yyleng-2] != '"')
             yyerror("improperly terminated string");
           else
             yylval.string_value[yyleng-2] = 0;
           return(STRING_LITERAL);
          }

[ \n\t]+|{comment} {}
. {}

%%

void yyerror(char* s)
{
	printf("Erreur near line %d : %s , %s\n",yylineno, s, yytext);
}

int yywrap(void)
{
    return 1;
}
