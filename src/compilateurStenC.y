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
};

%type <expression> program function function_declaration
%type <expression> primary_expression

%token <string_value> STRING_LITERAL MAIN IDENTIFIER
%token <int_value> NUMBER
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN

%token INT STENCIL

%token IF ELSE WHILE FOR RETURN CONTINUE

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
		{
			program_expression = &$1;
		}
  ;

function
  : function_declaration '{' statement_list '}'
  ;

function_declaration
  : INT MAIN {}
  ;

/* EXPRESSIONS */
primary_expression
	: IDENTIFIER
    {

    }
  | NUMBER
			{
				init_to_null(&$$);
				$$.result = table_new_number(symbol_table,$1) ;
    	}
	| STRING_LITERAL
		{

		}
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

    }
  | '+' unary_expression %prec UOPE
    {

    }
  ;

multiplicative_expression
  : unary_expression
	| multiplicative_expression '*' unary_expression
    {

    }
	| multiplicative_expression '/' unary_expression
	| multiplicative_expression '%' unary_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
    {

    }
	| additive_expression '-' multiplicative_expression
    {

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
	| logical_and_expression AND_OP equality_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
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

integer_declaration
	: INT expression { }
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
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	| integer_declaration ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| RETURN ';'
	| RETURN expression ';'
	;

%%
