grammar VietProg; 

@header {
#include "wci/intermediate/TypeSpec.h"
using namespace wci::intermediate;
}

// BATDAU - start
// KETTHUC - end
// LAP - loop
// KHI - when
// NEU - if
// INRA - print
// VIECCHINH - main task
// GIUPDO - helper
// CONSO - number
// HUDUNG - container (for variables) - dont need this
// replace equals with <-
// replace == with =?


program		: START PROGRAM_IDENTIFIER ':' (|function_list) main END;
function_list	: function (function)* ;

function	locals [ TypeSpec *type = nullptr ]
			: HELPER function_name '(' parameter_list ')' compound_statement;
function_name	: FUNC_NAME_IDENTIFIER ;
parameter_list	: parameter (',' parameter)*;
//param		: (|'Ref') variable 'As' type_id;
parameter	locals [ TypeSpec *type = nullptr ]
			: type_id var_id
			| type_id var_id REFERENCE
			;
			
main		: MAIN compound_statement ;

declarations: type_id var_list;
var_list	: var_id ( ',' var_id )* ;
var_id locals [ TypeSpec *type = nullptr ] 	: VAR_IDENTIFIER ;
type_id	locals [ TypeSpec *type = nullptr ]	: TYPE_IDENTIFIER ;

compound_statement	: LEFT_BRACE statement_list RIGHT_BRACE ;

// (|';')
statement	: compound_statement
			| assignment_statement
			| loop_statement
			| when_statement
			| if_statement
			| function_call_statement
			| declarations
			| print_statement
			|                	
			;
statement_list 				: statement ( ';' statement )* ;
function_call_statement   	: function_name '(' var_list ')';     
assignment_statement 		: var_id EQ_OP expr ;
loop_statement  			: LOOP '(' expr relational_operation expr ')' statement ;
when_statement       		: WHEN '(' expr relational_operation expr ')' statement ;
if_statement         		: IF expr statement;
print_statement				: PRINT '(' format_string print_arg* ')' ;
format_string				: STRING ;
print_arg					: ',' expr ;

//variable : IDENTIFIER ;

expr locals [ TypeSpec *type = nullptr ]
	 : expr mul_div_operation expr		# mul_Div_Expr
     | expr add_sub_operation expr		# add_Sub_Expr
     | expr relational_operation expr	# relational_Expr
     | number                   		# number_Const_Expr
     | STRING							# string
     | BOOLEAN							# boolean
     | VAR_IDENTIFIER               	# var_Identifier_Expr
     | '(' expr ')'             		# paren_Expr					
     ;

//rel_expr locals [ TypeSpec *type = nullptr ]
//			: '(' expr rel_operation expr ')'  ;
  
int_float locals [ TypeSpec *type = nullptr ]
			: INTEGER					# integerConst
			| FLOAT						# floatConst
			;
   
number locals [ TypeSpec *type = nullptr ]
	 		: sign? int_float ;
	 			

sign		: add_sub_operation ;
     
mul_div_operation 		: MUL_OP | DIV_OP ;
add_sub_operation 		: PLUS_OP | MINUS_OP ;
relational_operation    : EQ_QUES_OP | NE_OP | LT_OP | LTE_OP | GT_OP | GTE_OP ;

fragment M: [Mm];
fragment A: [Aa];
fragment I: [Ii];
fragment N: [Nn];

fragment F: [Ff];
fragment U: [Uu];
fragment C: [Cc];

fragment B: [Bb];
fragment T: [Tt];
fragment D: [Dd];

fragment K: [Kk];
fragment E: [Ee];
fragment H: [Hh];

fragment V: [Vv];
fragment R: [Rr];

fragment L: [Ll];
fragment P: [Pp];
fragment O: [oO];
fragment G: [Gg];

MAIN		: V I E C C H I N H ;
HELPER		: G I U P D O ;
START 		: B A T D A U ;
END			: K E T T H U C ;
//VAR     : V A R ;
LOOP		: L A P ; // similar to repeat...until
WHEN		: K H I ; // similar to loop...while
IF			: N E U ;
PRINT		: I N R A;
LEFT_BRACE  : '{' ;
RIGHT_BRACE : '}' ;
INTEGER 	: [0-9]+ ;
FLOAT		: [0-9]+ '.' [0-9]+ ;
REFERENCE	: C O N T R O ;
PROGRAM_IDENTIFIER : [a-zA-Z][a-zA-Z0-9]* ;
FUNC_NAME_IDENTIFIER	: 'G_' [a-zA-Z][a-zA-Z0-9]* ;
TYPE_IDENTIFIER			: 'T_' [a-zA-Z][a-zA-Z0-9]* ;
VAR_IDENTIFIER			: 'H_' [a-zA-Z][a-zA-Z0-9]* ;

BOOLEAN			: [TF] ; 

MUL_OP		:   '*' ;
DIV_OP		:   '/' ;
PLUS_OP		:   '+' ;
MINUS_OP	:   '-' ;

EQ_OP 		: '<-' ;
EQ_QUES_OP	: '=?';
NE_OP		: '!=' ;
LT_OP		: '<' ;
LTE_OP		: '<=' ;
GT_OP		: '>' ;
GTE_OP		: '>=' ;

NEWLINE : '\r'? '\n' -> skip  ;
WS      : [ \t]+ -> skip ; 

QUOTE	: '\'' ;
STRING	: QUOTE STRING_CHAR* QUOTE ;

fragment STRING_CHAR 	: QUOTE QUOTE // double quotes
						| ~('\'')
						;