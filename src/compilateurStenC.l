/* Inspiré du LEX ANSI C */
D			[0-9]
L			[a-zA-Z_]

%{
	#include "lib.h"
	#include "cfss.y.h"
%}

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

{L}({L}|{D})*		{return(IDENTIFIER);}

{D}+ 					  {return(NUMBER);}

L?\"(\\.|[^\\""])*\"	{return(STRING_LITERAL);}

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

int yywrap()
{
	return(1);
}
