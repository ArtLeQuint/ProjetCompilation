%{
	#include "quad.h"
	#include "symbol.h"
	#include "symbol_table.h"
	#include "array_type.h"
	#include "operation.h"
	#include "gen_code_mips.h"
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>

	int yylex(void);
	void yyerror(char *s);
	void lex_free();
	
	
	extern SymbolTable symbol_table ;
	extern unsigned int next_quad_label;
	Expression program_expression;
	
%}


%union {
	int int_value;                 /* nombre */
	char* string_value;
	Symbol symbol;
	condition_t condition;
	expression_t expression;
	ArrayList array_list;
	array_ref_t reference_to_array;
};
%token <symbol> M
%token STRING_LITERAL MAIN
%token <strval> IDENTIFIER
%token <intval> NUMBER
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN

%token INT STENCIL

%token IF ELSE WHILE FOR RETURN CONTINUE

%type <exprval> additive_expression
%type <exprval> multiplicative_expression
%type <exprval> unary_expression

%left AND_OP
%left OR_OP
%left EQ_OP
%left '+' '-'
%left '*' '/' '%'
%left INC_OP DEC_OP
%left NE_OP
%left UOPE

%start program
%%
/* START */
program
  : function
  ;

function
  : function_declaration '{' statement_list '}'
  ;

function_declaration
  : INT MAIN
  ;

/* EXPRESSIONS */
primary_expression
	: IDENTIFIER
    {

    }
  | NUMBER
    {

    }
	| STRING_LITERAL
	| '(' expression ')'
    {

    }
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
  | '-' unary_expression %prec UOPE
    {
      $$.ptr = newtemp(SYMTAB);
      gencode(CODE,UOP_MINUS,$$.ptr,$2.ptr,NULL);
    }
  | '+' unary_expression %prec UOPE
    {
      $$.ptr = newtemp(SYMTAB);
      gencode(CODE,UOP_PLUS,$$.ptr,$2.ptr,NULL);
    }
  ;

multiplicative_expression
  : unary_expression
	| multiplicative_expression '*' unary_expression
    {
      $$.ptr = newtemp(SYMTAB);
      gencode(CODE,BOP_MULT,$$.ptr,$1.ptr,$3.ptr);
    }
	| multiplicative_expression '/' unary_expression
	| multiplicative_expression '%' unary_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
    {
      $$.ptr = newtemp(SYMTAB);
      gencode(CODE,BOP_PLUS,$$.ptr,$1.ptr,$3.ptr);
    }
	| additive_expression '-' multiplicative_expression
    {
      $$.ptr = newtemp(SYMTAB);
      gencode(CODE,BOP_MINUS,$$.ptr,$1.ptr,$3.ptr);
    }
	;

relational_expression
  : additive_expression
	| relational_expression '<' additive_expression
	| relational_expression '>' additive_expression
	| relational_expression LE_OP additive_expression
	| relational_expression GE_OP additive_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

logical_and_expression
	: equality_expression
	| logical_and_expression AND_OP M equality_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP M logical_and_expression
	;

assignment_expression
	: logical_or_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

/* DECLARATIONS */
declaration
	: type_specifier ';'
  | type_specifier declarator_list ';'
	;

declarator_list
  : declarator
  | declarator_list ',' declarator
  | declarator_list ',' declarator '[' assignment_expression ']'
  | declarator_list ',' declarator '=' assignment_expression
  ;

declarator
  : IDENTIFIER
  ;

type_specifier
	: INT
	| STENCIL
	;

/* STATEMENTS */

statement
	: compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' M statement
	| IF '(' expression ')' M statement ELSE M statement
	;

iteration_statement
	: WHILE '(' expression ')' M statement
	| FOR '(' expression_statement expression_statement ')' M statement
	| FOR '(' expression_statement expression_statement expression ')' M statement
	;

jump_statement
	: CONTINUE ';'
	| RETURN ';'
	| RETURN expression ';'
	;

M
	: {$$ = table_new_number(symbol_table, next_quad_label);}
	;
%%

void yyerror(const char * s)
{
    fprintf(stderr,"%s\n",s);
}
