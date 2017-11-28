%{
#include <stdio.h>
#include <stdlib.h>
%}

%token IDENTIFIER NUMBER STRING_LITERAL MAIN
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
	| STRING_LITERAL
	| '(' expression ')'
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
  | unary_expression INC_OP
  | unary_expression DEC_OP
  | '-' unary_expression %prec UOPE
  | '+' unary_expression %prec UOPE
  ;

multiplicative_expression
  : unary_expression
	| multiplicative_expression '*' unary_expression
	| multiplicative_expression '/' unary_expression
	| multiplicative_expression '%' unary_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
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
declaration
	: type_specifier ';'
  | type_specifier declarator_list ';'
	;

declarator_list
  : declarator
  | declarator_list ',' declarator
  ;

declarator
  : IDENTIFIER
  | declarator [assignement_expression]
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

int main(int argc, char *argv) {
  if (argc != 2) {
    fprintf(stderr, "usage : %s file_name\n", argv[0]);
    exit(1);
  }
  FILE *yyin = fopen(argv[1], "r");
  char *outname = "mips.s";
  FILE *yyout = fopen(outname, "w");
  if (yyin == NULL || yyout == NULL) {
    fprintf(stderr, "usage : cannot open file %s or cannot open outfile\n", argv[1]);
    exit(1);
  }
  int result = yyparse();
  printf("Compilation result : %d\n", result);
}
