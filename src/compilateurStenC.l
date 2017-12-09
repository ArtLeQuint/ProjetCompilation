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
L			[a-zA-Z_]


%%
(\/\*[^\*\/]*\*\/) {/* Commentaire, pour l'instant on ne fait rien, peut être à ajouter au fichier mips après. */}
(\/\/.*\n)         {/* Commentaire, pour l'instant on ne fait rien, peut être à ajouter au fichier mips après. */}

"else"				{return(ELSE);}
"for"					{return(FOR);}
"if"					{return(IF);}
"int"					{return(INT);}
"return"			{return(RETURN);}
"while"				{return(WHILE);}
"stencil"			{return(STENCIL);}
"continue"		{return(CONTINUE);}
"main(void)"  {return(MAIN);}

{L}({L}|{D})*		{
                 yylval.string_value = strdup(yytext);
			           return(IDENTIFIER);
                }

{D}+ 					  {yylval.int_value = atoi(yytext); return(NUMBER);}

L?\"(\\.|[^\\""])*\"	{
                       yylval.string_value = strdup(yytext+1);
              				 if (yylval.string_value[yyleng-2] != '"')
              				 	 yyerror("improperly terminated string");
              				 else
              					 yylval.string_value[yyleng-2] = 0;

                       return(STRING_LITERAL);
                     }

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
";"			{return(';');}
"{"		  {return('{');}
"}"	    {return('}');}
","			{return(',');}
":"			{return(':');}
"="			{return('=');}
"("			{return('(');}
")"			{return(')');}
"["		  {return('[');}
"]"		  {return(']');}
"-"			{return('-');}
"+"			{return('+');}
"*"			{return('*');}
"/"			{return('/');}
"%"			{return('%');}
"<"			{return('<');}
">"			{return('>');}

[ \t\v\n\f]		{}
.			        {}

%%

void yyerror(char* s)
{
	printf("Erreur near line %d : %s \n",yylineno, s);
}

int yywrap(void)
 {
    return 1;
}
