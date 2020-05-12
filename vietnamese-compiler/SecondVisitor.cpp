/*
 * SecondVisitor.cpp
 *
 *  Created on: May 6, 2020
 *      Author: hadiyah
 */
#include <iostream>
#include <vector>
#include <string>

#include "antlr4-runtime.h"
#include "wci/util/CrossReferencer.h"
#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/SymTabFactory.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/symtabimpl/Predefined.h"

#include "SecondVisitor.h"
#include "VietProgBaseVisitor.h"

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::util;


const bool DEBUG_FLAG_2 = true;

// constructor
SecondVisitor::SecondVisitor() : jf(nullptr), program_name(""), jf_name(""), label_number(0), function_flag(false), function_call_flag(false) {}

// destructor
SecondVisitor::~SecondVisitor() {}

// helpers
ofstream& SecondVisitor::get_jasmin_file()
{
	return jf;
}

void SecondVisitor::emit_program_header()
{
	// emit program header information.
	jf << ".class public " << program_name << endl;
	jf << ".super java/lang/Object" << endl;
}

void SecondVisitor::print_local_func_variables()
{
	string var_name = "";
	string type_letter = "";
	int index = 0;
	TypeSpec* type;
	for (unsigned int i = 0; i < local_func_variables.size(); i++)
	{
		var_name = local_func_variables[i]->VAR_IDENTIFIER()->toString();
		type = local_func_variables[i]->type;
		type_letter 	= (type == Predefined::integer_type)	? "I"
						: (type == Predefined::real_type)		? "F"
					 	: (type == Predefined::boolean_type) 	? "I"
					 	: 										"?";
		index = local_func_variables[i]->local_var->get_local_var_array_index();

		jf << endl <<".var " << index << " is " << var_name << " " << type_letter;
	}

	jf << endl << ".var " << ++index << " is "; // function name and return type will go here.

}

void SecondVisitor::emit_pascalRTL_vars()
{
	// emit the declarations related to the PascalRTL jar.
	jf << endl;
	jf << ".field private static _runTimer LRunTimer;" << endl;
	jf << ".field private static _standardIn LPascalTextIn;" << endl;
}

void SecondVisitor::emit_class_constructor()
{
	// emit the class constructor.
	jf << ".method public <init>()V" << endl;
	jf << endl;
	jf << "\taload_0" << endl;
	jf << "\tinvokenonvirtual java/lang/Object/<init>()V" << endl;
	jf << "\treturn" << endl;
	jf << endl;
	jf << ".limit locals 1" << endl;
	jf << ".limit stack 1" << endl;
	jf << ".end method" << endl;
	jf << endl;

}

void SecondVisitor::emit_main_prologue()
{
	// emit the main program header and prologue.
	jf << ".method public static main([Ljava/lang/String;)V" << endl;
	jf << endl;
	jf << "\tnew RunTimer" << endl;
	jf << "\tdup" << endl;
	jf << "\tinvokenonvirtual RunTimer/<init>()V" << endl;
	jf << "\tputstatic\t" << program_name
			<< "/_runTimer LRunTimer;" << endl;
	jf << "\tnew PascalTextIn" << endl;
	jf << "\tdup" << endl;
	jf << "\tinvokenonvirtual PascalTextIn/<init>()V" << endl;
	jf << "\tputstatic\t" + program_name
			<< "/_standardIn LPascalTextIn;" << endl;
}

void SecondVisitor::emit_main_epilogue()
{
	// emit the main program epilogue.
	jf << endl;
	jf << "\tgetstatic     " << program_name
            << "/_runTimer LRunTimer;" << endl;
	jf << "\tinvokevirtual RunTimer.printElapsedTime()V" << endl;
	jf << endl;
	jf << "\treturn" << endl;
	jf << endl;
	jf << ".limit locals 256" << endl;
	jf << ".limit stack 256" << endl;
	jf << ".end method" << endl;
}

void SecondVisitor::emit_function_epilogue()
{
	jf << ".limit locals 32" << endl;
	jf << ".limit stack 32" << endl;
	jf << ".end method" << endl << endl;
}

// visitors
antlrcpp::Any SecondVisitor::visitProgram(VietProgParser::ProgramContext *ctx)
{
	if(DEBUG_FLAG_2) cout << "Second Visitor: visitProgram(): creating Jasmin file." << endl;

	program_name = ctx->PROGRAM_IDENTIFIER()->toString();

	// create assembly file.
	jf_name = program_name + ".j";
	jf.open(jf_name);
	if(jf.fail())
	{
		cout << "Second Visitor: visitProgram(): Jasmin file creation/open failed. Exiting..." << endl;
		exit(-99);
	}

	if(DEBUG_FLAG_2) cout << "Second Visitor: visitProgram(): created Jasmin file: " + jf_name << endl;

	// emit the program heaader
	emit_program_header();
	// emit the pascal rtl stuff
	emit_pascalRTL_vars();
	// emit the declarations.
	visit(ctx->main()->declarations());
	jf << endl;
	// emit the constructor
	emit_class_constructor();

	// parse the rest of the program (functions and main).
    auto value = visitChildren(ctx);

    // finished parsing the program. close the assembly file.
    jf.close();
    if (DEBUG_FLAG_2) cout << "Second Visitor: visitProgram(): closed " + jf_name << endl;
    return value;

}

antlrcpp::Any SecondVisitor::visitMain(VietProgParser::MainContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitMainBlock(): " << endl;

	// emit the prologue.
	emit_main_prologue();

	// emit code for the main program's compound statement.
	auto value = visit(ctx->compound_statement());

	// emit the epilogue.
	emit_main_epilogue();

	return value;

}

antlrcpp::Any SecondVisitor::visitDeclarations(VietProgParser::DeclarationsContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitDeclarations(): " << endl;

	return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitDeclaration(VietProgParser::DeclarationContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitDeclaration(): " + ctx->getText() << endl;
	if(!function_flag) jf << "\n; " << ctx->getText() << "\n" << endl;
	return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitVar_id(VietProgParser::Var_idContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitVar_id(): " + ctx->getText() << endl;

	if(!function_flag)
	{
		string var_name = ctx->VAR_IDENTIFIER()->toString();
		TypeSpec *type = ctx->type;
		// emit the field declaration.
		// treat boolean as an integer.
		string type_letter 	= (type == Predefined::integer_type)	? "I"
							 	: (type == Predefined::real_type)		? "F"
							 	: (type == Predefined::boolean_type) 	? "I"
							 	: 										"?";
		jf << ".field private static "
				<< var_name << " " << type_letter << endl;
	}
	else
	{
		local_func_variables.push_back(ctx);
	}

	return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitStatement(VietProgParser::StatementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitStatement(): " + ctx->getText() << endl;

	jf << endl << "; " + ctx->getText() << endl << endl;

	return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitAssignment_statement(VietProgParser::Assignment_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitAssignment_statement(): " + ctx->getText() << endl;

	auto value = visit(ctx->expr());

	TypeSpec * type = ctx->expr()->type;

	// treat boolean as an integer
	string type_letter;
	if(!function_flag)
	{
		type_letter = (type == Predefined::integer_type) ? "I"
					: (type == Predefined::real_type) 	? "F"
					: (type == Predefined::boolean_type) ? "I"
					:									"?";
		// Program variable:
		// emit a field put instruction.
		jf << "\tputstatic\t" << program_name
				<< "/" << ctx->variable()->VAR_IDENTIFIER()->toString()
				<< " " << type_letter << endl;
	}
	else
	{
		type_letter = (type == Predefined::integer_type) ? "i"
					: (type == Predefined::real_type) 	? "f"
					: (type == Predefined::boolean_type) ? "i"
					:									"?";

		// retrieve the local variables array index of the variable.
		string var_name = ctx->variable()->VAR_IDENTIFIER()->toString();
		int index = -1;
		for (unsigned int i = 0; i < local_func_variables.size(); i++)
		{
			if (var_name == local_func_variables[i]->VAR_IDENTIFIER()->toString())
			{
				index = local_func_variables[i]->local_var->get_local_var_array_index();
			}
		}
		if (index == -1)
		{
			cout << "Assignment to undeclared variable: " + var_name << endl;
			cout << "Using the first local variable of the function instead." << endl;
			index = 0;
		}
		jf << "\t" << type_letter << "store_" << index << endl;
	}

	return value;
}


antlrcpp::Any SecondVisitor::visitPrint_statement(VietProgParser::Print_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitPrint_statement(): " + ctx->getText() << endl;

	// get the format string, trim the quotes
	string str = ctx->format_string()->getText();
	string fs = str.substr(1, str.length() - 2);

	// emit the code to the java.lang.System.out object.
	jf << "\tgetstatic\tjava/lang/System/out Ljava/io/PrintStream;" << endl;

	// emit code to push the format string.
	jf << "\tldc\t\"" << fs << "\"" << endl;

	// array size = # of expressions to evaluate and print.
	int arr_size = ctx->print_arg().size();

	// emit the code to create the array of the correct size.
	jf << "\tldc\t" << arr_size << endl;
	jf << "\tanewarray\tjava/lang/Object" << endl;

	// loop to generate code for each expression.
    for (int i = 0; i < arr_size; i++)
    {
        jf << "\tdup" << endl;         // duplicate the array address
        jf << "\tldc\t" << i << endl;  // array element index

        // emit code to evaluate the expression.
        visit(ctx->print_arg(i)->expr());
        TypeSpec *type = ctx->print_arg(i)->expr()->type;

        // emit code to convert a scalar integer, float or boolean value
        // to an Integer, Float or Boolean object, respectively.
        if (type == Predefined::integer_type)
        {
            jf << "\tinvokestatic\tjava/lang/Integer.valueOf(I)"
                   << "Ljava/lang/Integer;"
                   << endl;
        }
        else if (type == Predefined::real_type)
        {
            jf << "\tinvokestatic\tjava/lang/Float.valueOf(F)"
                   << "Ljava/lang/Float;"
                   << endl;
        }

        else if (type == Predefined::boolean_type)
        {
            jf << "\tinvokestatic\tjava/lang/Integer.valueOf(I)"
                   << "Ljava/lang/Integer;"
                   << endl;
        }

        jf << "\taastore" << endl;  // store the value into the array
    }

    // emit the code to call java.io.PrintStream.printf.
    jf << "\tinvokevirtual java/io/PrintStream.printf"
           << "(Ljava/lang/String;[Ljava/lang/Object;)"
           << "Ljava/io/PrintStream;"
           << endl;
    jf << "\tpop" << endl;

    return nullptr;
}


antlrcpp::Any SecondVisitor::visitAdd_Sub_Expr(VietProgParser::Add_Sub_ExprContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitAdd_Sub_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	TypeSpec * type1 = ctx->expr(0)->type;
	TypeSpec * type2 = ctx->expr(1)->type;

	bool integer_mode = (type1 == Predefined::integer_type) && (type2 == Predefined::integer_type);
	bool float_mode = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);

	string op = ctx->add_sub_operation()->getText();
	string opcode;

	if (op == "+")
	{
		opcode = integer_mode ? "iadd"
				: float_mode ? "fadd"
				: 				"????";
	}

	else
	{
		opcode = integer_mode ? "isub"
				: float_mode ? "fsub"
				: 				"????";
	}

	// emit the add/sub instruction.
	jf << "\t" << opcode << endl;

	return value;
}


antlrcpp::Any SecondVisitor::visitMul_Div_Expr(VietProgParser::Mul_Div_ExprContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitMul_Div_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	TypeSpec * type1 = ctx->expr(0)->type;
	TypeSpec * type2 = ctx->expr(1)->type;

	bool integer_mode = (type1 == Predefined::integer_type) && (type2 == Predefined::integer_type);
	bool float_mode = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);

	string op = ctx->mul_div_operation()->getText();
	string opcode;

	if (op == "*")
	{
		opcode = integer_mode ? "imul"
				: float_mode ? "fmul"
				: 				"????";
	}

	else
	{
		opcode = integer_mode ? "idpv"
				: float_mode ? "fdiv"
				: 				"????";
	}

	// emit the mul/div instruction.
	jf << "\t" << opcode << endl;

	return value;
}


antlrcpp::Any SecondVisitor::visitVariable_Expr(VietProgParser::Variable_ExprContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitVariable_Expr(): " + ctx->getText() << endl;

	string var_name = ctx->variable()->VAR_IDENTIFIER()->toString();
	TypeSpec * type = ctx->type;
	string type_indicator;
	if(function_flag)
	{
		// treat boolean as integer from here on.
		type_indicator = (type == Predefined::integer_type) 	? "i"
	            			: (type == Predefined::real_type)  	? "f"
	            			: (type == Predefined::boolean_type)   ? "i"
	            			:                                      "?";
		jf << "\t" << type_indicator << "load_" << ctx->local_var->get_local_var_array_index() << endl;
	}

	else if (function_call_flag)
	{		// treat boolean as integer from here on.
		type_indicator = (type == Predefined::integer_type) 	? "I"
	            			: (type == Predefined::real_type)  	? "F"
	            			: (type == Predefined::boolean_type)  ? "I"
	            			:                                     "?";

		// emit the field put instruction.
		jf << "\tputstatic\t" << program_name
		           << "/" << var_name << " " << type_indicator << endl;
	}

	else
	{
		// treat boolean as integer from here on.
		type_indicator = (type == Predefined::integer_type) 	? "I"
	            			: (type == Predefined::real_type)  	? "F"
	            			: (type == Predefined::boolean_type)  ? "I"
	            			:                                     "?";

		// emit the field get instruction.
		jf << "\tgetstatic\t" << program_name
		           << "/" << var_name << " " << type_indicator << endl;

	}

	return visitChildren(ctx);

}


antlrcpp::Any SecondVisitor::visitNumber(VietProgParser::NumberContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitNumber(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);
	TypeSpec * type = ctx->int_float()->type;

	if (ctx->sign() != NULL)
	{
		if (ctx->sign()->children[0]->children[0] == ctx->sign()->add_sub_operation()->MINUS_OP())
		{
			string opcode = (type == Predefined::integer_type) ? "ineg"
	                		: (type == Predefined::real_type)  ? "fneg"
	                		:                                 	 "?neg";

			// emit the negate instruction.
			jf << "\t" << opcode << endl;
		}

	}

	// don't do anything if sign is positive.

	return value;
}


antlrcpp::Any SecondVisitor::visitIntegerConst(VietProgParser::IntegerConstContext *ctx)
{
    if (DEBUG_FLAG_2) cout << "Second Visitor: visitIntegerConst(): " + ctx->getText() << endl;

    // emit a load constant instruction.
    jf << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitFloatConst(VietProgParser::FloatConstContext *ctx)
{
    if (DEBUG_FLAG_2) cout << "Second Visitor: visitFloatConst(): " + ctx->getText() << endl;

    // emit a load constant instruction.
    jf << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}

// DEPRECATED
antlrcpp::Any SecondVisitor::visitBoolean(VietProgParser::BooleanContext *ctx)
{

/*	Note: Because of the new method of treating boolean as integer, this is never visisted.
		if (DEBUG_FLAG_2) cout << "First Visitor: visitBoolean(): " + ctx->getText() << endl;

		// emit a load instruction depending on value.
		if (ctx->BOOLEAN()->toString() == "true")
		{
			jf << "iconst_1";	// true = 1
		}
		else
		{
			jf << "iconst_0";	// false = 0
		}*/

	return visitChildren(ctx);
}


antlrcpp::Any SecondVisitor::visitRelational_Expr(VietProgParser::Relational_ExprContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitRelational_Expr(): " + ctx->getText() << endl;
	auto value = visitChildren(ctx);

	TypeSpec* type1 = ctx->expr(0)->type;
	TypeSpec* type2 = ctx->expr(1)->type;

	bool boolean_mode = (type1 == Predefined::boolean_type) || (type2 == Predefined::boolean_type);
	bool integer_mode = boolean_mode || ((type1 == Predefined::integer_type) && (type2 == Predefined::integer_type));
	bool float_mode = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);

	string op = ctx->relational_operation()->getText();
	string opcode;

	if (op == "=?")
	{
		opcode = integer_mode 	? "if_icmpeq"
				: float_mode 	? "ifeq"
				: 				"????";
	}
	else if (op == "!=")
	{
		// if_icmpne
		opcode = integer_mode 	? "if_icmpne"
				: float_mode 	? "ifne"
				: 				"????";
	}
	else if (op == "<")
	{
		// if_icmplt
		opcode = integer_mode 	? "if_icmplt"
				: float_mode 	? "iflt"
				: 				"????";
	}
	else if (op == "<=")
	{
		// if_icmple
		opcode = integer_mode 	? "if_icmple"
				: float_mode 	? "ifle"
				: 				"????";
	}
	else if (op == ">")
	{
		// if_icmpgt
		opcode = integer_mode 	? "if_icmpgt"
				: float_mode 	? "ifgt"
				: 				"????";
	}
	else if (op == ">=")
	{
		// if_icmpge
		opcode = integer_mode 	? "if_icmpge"
				: float_mode 	? "ifge"
				: 				"????";
	}

	if (opcode == "????")
	{
		cout << "Unexpected/incorrect relational expression." << endl;
	}

	if (float_mode)
	{
		jf << "\tfcmpl" << endl;
	}

	// emit the comparison code with appropriate labeling.

	jf << "\t" << opcode << "\tL00" << ++label_number << endl;
	jf << "\ticonst_0" << endl;
	jf << "\tgoto\tL00" << ++label_number << endl;
	jf << endl << "L00" << label_number - 1 << ":" << endl << endl;
	jf << "\ticonst_1" << endl;
	jf << endl << "L00" << label_number << ":" << endl << endl;

	return value;
}


antlrcpp::Any SecondVisitor::visitIf_statement(VietProgParser::If_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitIf_statement(): " + ctx->getText() << endl;

	auto value = visit(ctx->expr()); // analyze the relational expression.

	// check if the TOS has a zero. It it does, then go to the else clause.
	int temp = ++label_number;
	jf << "\tifeq\tL00" << temp << endl;

	// emit the true code.
	value = visit(ctx->statement(0));
	// skip the false code.
	jf << "\tgoto\tL00" << ++label_number << endl;

	// emit the false code.
	jf << endl << "L00" << temp << ":" << endl << endl;
	if(ctx->statement(1) != NULL)
	{
		value = visit(ctx->statement(1));
	}

	// move on to the next label.
	jf << endl << "L00" << label_number << ":" << endl << endl;

	return value;

}


antlrcpp::Any SecondVisitor::visitWhen_statement(VietProgParser::When_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitWhen_statement(): " + ctx->getText() << endl;

	// mark the beginning of the loop.
	int start_of_loop = ++label_number;
	jf << endl << "L00" << start_of_loop << ":" << endl << endl;
	auto value = visit(ctx->expr()); // analyze the relational expression.

	// check if the TOS has a zero. It it does, then the loop will not be run.
	int end_of_loop = ++label_number;
	jf << "\tifeq\tL00" << end_of_loop << endl;

	value = visit(ctx->statement());

	jf << "\tgoto\tL00" << start_of_loop << endl;

	jf << endl << "L00" << end_of_loop << ":" << endl << endl;

	return value;
}


antlrcpp::Any SecondVisitor::visitLoop_statement(VietProgParser::Loop_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitLoop_statement(): " + ctx->getText() << endl;

	// mark the beginning of the loop.
	int start_of_loop = ++label_number;
	jf << endl << "L00" << start_of_loop << ":" << endl << endl;

	auto value = visit(ctx->statement());
	value = visit(ctx->expr());

	// if the condition is not true, then go to the start of the loop again.
	jf << "\tifeq\tL00" << start_of_loop << endl;

	return value;
}


antlrcpp::Any SecondVisitor::visitFunction(VietProgParser::FunctionContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitFunction(): " << endl;

	local_func_variables.resize(0);
	function_flag = true;

	string function_name = ctx->function_name()->FUNC_NAME_IDENTIFIER()->toString();

	jf << ".method private static " + function_name + "("; // parameter list will follow.

	auto value = visit(ctx->function_name());
	if(ctx->parameter_list() != NULL) value = visit(ctx->parameter_list());

	jf << ")"; // closing the parameter list.

	// emit the return type information.
	string type_letter = "V";
	if (ctx->type_id() != NULL)
	{
		value = visit(ctx->type_id());
		TypeSpec* type = ctx->type_id()->type;
		type_letter = (type == Predefined::integer_type)	? "I"
			 		: (type == Predefined::real_type)		? "F"
			 		: (type == Predefined::boolean_type) 	? "I"
			 		: 										"V";
	}

	// emit the local variables information.
	print_local_func_variables();
	jf << function_name << " " <<  type_letter << endl;

	// emit the compound statements of the function.
	if (ctx->compound_statement() != NULL) value = visit(ctx->compound_statement());

	// emit the return statement
	if (type_letter == "I")
	{
		jf << "\ti";
	}
	else if (type_letter == "F")
	{
		jf << "\tf";
	}
	else if (type_letter == "V")
	{
		jf << "\t";
	}

	jf << "return" << endl << endl;
	// emit the epilogue
	emit_function_epilogue();

	// unset the function flag.
	function_flag = false;

	return value;
}


antlrcpp::Any SecondVisitor::visitType_id(VietProgParser::Type_idContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitType_id(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	if(function_flag)
	{
		TypeSpec *type = ctx->type;

		string type_letter 	= (type == Predefined::integer_type)		? "I"
							 	: (type == Predefined::real_type)		? "F"
							 	: (type == Predefined::boolean_type) 	? "I"
							 	: 										"V";

		if (type_letter != "V")
		{
			jf << type_letter;
		}
		else
		{
			cout << "Variable of non-standard type: " + ctx->TYPE_IDENTIFIER()->toString() + ", being used in function." << endl;
		}

	}

	return value;
}


antlrcpp::Any SecondVisitor::visitFunction_return_statement(VietProgParser::Function_return_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitFunction_return_statement(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	return value;
}


antlrcpp::Any SecondVisitor::visitFunction_call_statement(VietProgParser::Function_call_statementContext *ctx)
{
	if (DEBUG_FLAG_2) cout << "Second Visitor: visitFunction_call_statement(): " + ctx->getText() << endl;


	string function_name = ctx->function_name()->FUNC_NAME_IDENTIFIER()->toString();
	string parameter_type_letters = "";
	string return_type_letter = "";
	TypeSpec* type;
	auto value = 0;
	int parameter_start_index = 0;
	if(ctx->EQ_OP() != NULL)
	{
		if (DEBUG_FLAG_2) cout << "assignment in function call." << endl;
		parameter_start_index = 1; // the parameters start from expr(1).
		// we have an assignment.
	}

	int parameter_end_index = ctx->expr().size();
	for (int k = parameter_start_index; k < parameter_end_index; k++)
	{
		value = visit(ctx->expr(k));
		type = ctx->expr(k)->type;
		string str = "";
		str = (type == Predefined::integer_type) ? "I"
					: (type == Predefined::real_type) 	? "F"
					: (type == Predefined::boolean_type) ? "I"
					: 									"?";
		if (str == "?") cout << "Argument of unknown type cannot be accepted in function call: " << endl;
		else { parameter_type_letters += str; }
	}

	jf << "\tinvokestatic\t" << program_name << "/" << function_name << "(" << parameter_type_letters << ")";

	type = ctx->function_name()->type;
	if (type != NULL)
	{
		return_type_letter = (type == Predefined::integer_type) ? "I"
					: (type == Predefined::real_type) 	? "F"
					: (type == Predefined::boolean_type) ? "I"
					: 									"?";
		if (return_type_letter == "?")
		{
			cout << "Return type of function: " << function_name <<  ", is unsupported. " << endl;
			return_type_letter = "V";
		}
	}
	else return_type_letter = "V";

	jf << return_type_letter << endl;

	if ((parameter_start_index == 1) || (ctx->EQ_OP() != NULL))
	{
		if (type == ctx->expr(0)->type)
		{
			function_call_flag = true;
			value = visit(ctx->expr(0));
			function_call_flag = false;
		}

		else
		{
			cout << "The variable's type does not match the type returned by the function. Thus, the value will not be transferred." << endl;
			jf << "\tpop" << endl;
		}


	}

	jf << endl << endl;

	return value;
}
