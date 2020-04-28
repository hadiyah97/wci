grammar LabeledExpr; 

@header {
#include "wci/intermediate/TypeSpec.h"
using namespace wci::intermediate;
}

program : BATDAU IDENTIFIER (|func_list) main KETTHUC;
func_list  : func (func)* ;

func	   : FUNC func_name '(' param_list ')' compound_stmt;
func_name  : IDENTIFIER ;
param_list : param (',' param)*;
param	   : (|'Ref') variable 'As' type_id;

main   :  MAIN compound_stmt ;

declarations : type_id var_list;
var_list     : var_id ( ',' var_id )* ;
var_id locals [ TypeSpec *type = nullptr ] : IDENTIFIER ;
type_id      : IDENTIFIER ;

compound_stmt : BEGIN stmt ';' ( stmt ';')* END ; 

stmt  locals [ TypeSpec *type = nullptr ]
    : compound_stmt    		# compoundStmt
     | assignment_stmt (|';') 	# assignmentStmt
     | loop_stmt   (|';')		# loopStmt 
     | when_stmt   (|';')  		# whenStmt
	   | if_stmt   (|';')  		# ifStmt	
     | funcCall_stmt (|';')		# funcCallStmt
     | declarations	(|';')		# declaration
     | print_stmt	(|';')		# printStmt
     |                			# emptyStmt
     ;

funcCall_stmt   : func_name '(' var_list ')';     
assignment_stmt : variable '=' expr ;
loop_stmt  		: LAP expr stmt ;
when_stmt       : KHI expr stmt ;
if_stmt         : NEU expr stmt;
print_stmt		: IN '(' format_string print_arg* ')' ;
format_string	: STRING ;

print_arg		: ',' expr ;

variable : IDENTIFIER ;

expr locals [ TypeSpec *type = nullptr ]
	 : expr mul_div_operation expr     # mulDivExpr
     | expr add_sub_operation expr     # addSubExpr
     | expr rel_operation expr         # relExpr
     | number                   # numberConstExpr
     | IDENTIFIER               # identifierExpr
     | '(' expr ')'             # parensExpr
     ;
     
number locals [ TypeSpec *type = nullptr ]
	 : sign? INTEGER ;
sign   : '+' | '-' ;
     
mul_div_operation : MUL_operation | DIV_operation ;
add_sub_operation : ADD_operation | SUB_operation ;
rel_operation     : EQEQ_operation | NE_operation | LT_operation | LE_operation | GT_operation | GE_operation ;

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

MAIN : M A I N ;
FUNC: F U N C ;
BATDAU : B A T D A U ;
KETTHUC : K E T T H U C ;
BEGIN   : '{' ;
END     : '}' ;
VAR     : V A R ;
LAP   : L A P ;
KHI    : K H I ;
NEU       : N E U ;
IN		: I N ;
IDENTIFIER : [a-zA-Z][a-zA-Z0-9]* ;
INTEGER : [0-9]+ ;

MUL_operation :   '*' ;
DIV_operation :   '/' ;
ADD_operation :   '+' ;
SUB_operation :   '-' ;

EQ_operation  : '=' ;
EQEQ_operation: '==';
NE_operation  : '!=' ;
LT_operation  : '<' ;
LE_operation  : '<=' ;
GT_operation  : '>' ;
GE_operation  : '>=' ;

NEWLINE : '\r'? '\n' -> skip  ;
WS      : [ \t]+ -> skip ; 

QUOTE	: '\'' ;
STRING	: QUOTE STRING_CHAR* QUOTE ;

fragment STRING_CHAR :	 QUOTE QUOTE // double quotes
						| ~('\'')
						;