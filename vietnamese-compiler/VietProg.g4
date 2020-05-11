grammar VietProg;  // procedural language written in Vietnamese.

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
// HUDUNG - container (for variables)
// replace equals with <-
// replace == with =?


program		: START PROGRAM_IDENTIFIER ':' (|function_list) main END;

main		: declarations MAIN compound_statement ;

function_list	: function (function)* ;

function	: HELPER function_name '(' (|parameter_list) ')' (|type_id) function_block (| function_return_statement);
function_name	: FUNC_NAME_IDENTIFIER ;
function_block	: (| declaration_list)	compound_statement ;
function_return_statement : RETURN expr;
parameter_list	: parameter (',' parameter)*;

//param		: (|'Ref') variable 'As' type_id;
parameter	locals [ TypeSpec *type = nullptr ]
			: declaration
			| declaration REFERENCE
			;

declarations		: CONTAINERS ':' declaration_list '.';
declaration_list	: declaration ( ';' declaration)* ;
declaration			: type_id var_list;
var_list			: var_id ( ',' var_id )* ;
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
			| COMMENT
			|                	
			;
			
statement_list 				: statement ( ';' statement )* ;
assignment_statement 		: variable EQ_OP expr ;
loop_statement  			: LOOP '(' expr ')' statement ;
when_statement       		: WHEN '(' expr ')' statement ;
if_statement         		: IF expr statement
							| IF expr statement ELSE statement;
function_call_statement   	: function_name '(' variable_list ')';
print_statement				: PRINT '(' format_string print_arg* ')' ;

format_string				: STRING ;
print_arg					: ',' expr ;

//variable locals [ TypeSpec *type = nullptr ]
//	: VAR_IDENTIFIER ;

variable : VAR_IDENTIFIER ;
	
variable_list	: variable ( ',' variable)*;

expr locals [ TypeSpec *type = nullptr ]
	 : expr mul_div_operation expr		# mul_Div_Expr
     | expr add_sub_operation expr		# add_Sub_Expr
     | expr relational_operation expr	# relational_Expr
     | number                   		# number_Const_Expr
     | variable               			# variable_Expr
     | '(' expr ')'             		# paren_Expr	
     | BOOLEAN							# boolean
     | STRING							# string			
     ;

//rel_expr locals [ TypeSpec *type = nullptr ]
//			: '(' expr rel_operation expr ')'  ;

mul_div_operation 		: MUL_OP | DIV_OP ;
add_sub_operation 		: PLUS_OP | MINUS_OP ;
relational_operation    : EQ_QUES_OP | NE_OP | LT_OP | LTE_OP | GT_OP | GTE_OP ;

number locals [ TypeSpec *type = nullptr ]
	 		: sign? int_float ;

sign		: add_sub_operation ;

int_float locals [ TypeSpec *type = nullptr ]
			: INTEGER					# integerConst
			| FLOAT						# floatConst
			;

fragment A: [Aa];
fragment B: [Bb];
fragment C: [Cc];
fragment D: [Dd];
fragment E: [Ee];
fragment F: [Ff];
fragment G: [Gg];
fragment H: [Hh];
fragment I: [Ii];
fragment K: [Kk];
fragment L: [Ll];
fragment M: [Mm];
fragment N: [Nn];
fragment O: [oO];
fragment P: [Pp];
fragment R: [Rr];
fragment S: [Ss];
fragment T: [Tt];
fragment U: [Uu];
fragment V: [Vv];

START 		: B A T D A U ;
END			: K E T T H U C ;
MAIN		: V I E C C H I N H ;
HELPER		: G I U P D O ;
//VAR     : V A R ;
LOOP		: L A P ; // similar to repeat...until
WHEN		: K H I ; // similar to loop...while
IF			: N E U ;
ELSE		: K H A C;
PRINT		: I N R A;
LEFT_BRACE  : '{' ;
RIGHT_BRACE : '}' ;
REFERENCE	: C O N T R O ;
CONTAINERS		: H U D U N G ;
PROGRAM_IDENTIFIER 		: [a-zA-Z][a-zA-Z0-9]* ;
FUNC_NAME_IDENTIFIER	: 'G_' [a-zA-Z][a-zA-Z0-9]* ;
TYPE_IDENTIFIER			: 'T_' [a-zA-Z][a-zA-Z0-9]* ;
VAR_IDENTIFIER			: 'H_' [a-zA-Z][a-zA-Z0-9]* ;

BOOLEAN			: T
				| F
				; 
				
RETURN 			: T R A L O I ;

COMMENT			: '//' [a-zA-Z_]*[ ]*;


INTEGER 	: [0-9]+ ;
FLOAT		: [0-9]+ '.' [0-9]+ ;

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

fragment STRING_CHAR 	: QUOTE QUOTE 	// double quotes
						| ~('\'')		// any non-quote char
						;