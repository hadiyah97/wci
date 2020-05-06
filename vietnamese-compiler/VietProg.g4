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


program		: START PROGRAM_IDENTIFIER ':' (|func_list) main END;
func_list	: func (func)* ;

func		: HELPER func_name '(' param_list ')' compound_stmt;
func_name	: FUNC_NAME_IDENTIFIER ;
param_list	: param (',' param)*;
//param		: (|'Ref') variable 'As' type_id;
param		: type_id var_id
			| type_id var_id REFERENCE
			;
			
main		: MAIN compound_stmt ;

declarations: type_id var_list;
var_list	: var_id ( ',' var_id )* ;
var_id locals [ TypeSpec *type = nullptr ] : VAR_IDENTIFIER ;
type_id		: TYPE_IDENTIFIER ;

compound_stmt: LEFT_BRACE stmt_list RIGHT_BRACE ;

// (|';')
stmt		: compound_stmt
			| assignment_stmt
			| loop_stmt
			| when_stmt
			| if_stmt
			| funcCall_stmt
			| declarations
			| print_stmt
			|                	
			;
stmt_list 		: stmt ( ';' stmt )* ;
funcCall_stmt   : func_name '(' var_list ')';     
assignment_stmt : var_id EQ_operator expr ;
loop_stmt  		: LOOP '(' expr rel_operation expr ')' stmt ;
when_stmt       : WHEN '(' expr rel_operation expr ')' stmt ;
if_stmt         : IF expr stmt;
print_stmt		: PRINT '(' format_string print_arg* ')' ;
format_string	: STRING ;
print_arg		: ',' expr ;

//variable : IDENTIFIER ;

expr locals [ TypeSpec *type = nullptr ]
	 : expr mul_div_operation expr		# mulDivExpr
     | expr add_sub_operation expr		# addSubExpr
     | expr rel_operation expr			# relExpr
     | number                   		# numberConstExpr
     | STRING							# string
     | BOOLEAN							# boolean
     | VAR_IDENTIFIER               	# varIdentifierExpr
     | '(' expr ')'             		# parenExpr					
     ;

//rel_expr locals [ TypeSpec *type = nullptr ]
//			: '(' expr rel_operation expr ')'  ;
     
number locals [ TypeSpec *type = nullptr ]
	 		: sign? int_float ;	
int_float locals [ TypeSpec *type = nullptr ]
			: INTEGER					# integerConst
			| FLOAT						# floatConst
			;
sign		: add_sub_operation ;
     
mul_div_operation : MUL_operator | DIV_operator ;
add_sub_operation : ADD_operator | SUB_operator ;
rel_operation     : EQ_QUES_operator | NE_operator | LT_operator | LE_operator | GT_operator | GE_operator ;

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

MUL_operator	:   '*' ;
DIV_operator	:   '/' ;
ADD_operator	:   '+' ;
SUB_operator	:   '-' ;

EQ_operator 		: '<-' ;
EQ_QUES_operator	: '=?';
NE_operator			: '!=' ;
LT_operator			: '<' ;
LE_operator			: '<=' ;
GT_operator			: '>' ;
GE_operator			: '>=' ;

NEWLINE : '\r'? '\n' -> skip  ;
WS      : [ \t]+ -> skip ; 

QUOTE	: '\'' ;
STRING	: QUOTE STRING_CHAR* QUOTE ;

fragment STRING_CHAR 	: QUOTE QUOTE // double quotes
						| ~('\'')
						;