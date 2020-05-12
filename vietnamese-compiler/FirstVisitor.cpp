/*
 * FirstVisitor.cpp
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
#include "wci/intermediate/symtabimpl/SymTabEntryImpl.h"

#include "FirstVisitor.h"
#include "VietProgBaseVisitor.h"
#include "VietProgParser.h"

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::util;

const bool DEBUG_FLAG_1 = true;

FirstVisitor::FirstVisitor()
{
	function_flag = false;
	current_var_array_index = -1;
//	current_function_ctx = nullptr;

	st_stack = SymTabFactory::create_symtab_stack();
	Predefined::initialize(st_stack);

	//	type = nullptr;
	//	label_number = 0;
	//	error_count = 0;

	if (DEBUG_FLAG_1) cout << "First Visitor: FirstVisitor() - st_stack initialized." << endl;

}

antlrcpp::Any FirstVisitor::visitProgram(VietProgParser::ProgramContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitProgram(): " << endl;

	// read the program name
	string program_name = ctx->PROGRAM_IDENTIFIER()->toString();

	// enter the name in the symbol table stack
	SymTabEntry * pid = st_stack->enter_local(program_name);

	// set definition & attribute
	pid->set_definition((Definition)DF_PROGRAM);
	pid->set_attribute((SymTabKey) ROUTINE_SYMTAB, st_stack->push());

	// set program id
	st_stack->set_program_id(pid);

	auto value = visitChildren(ctx);

	if (DEBUG_FLAG_1) cout << "First Visitor: visitProgram(): Printing the cross-reference table." << endl;

//	if (error_count == 0)
//	{
		// Print the cross-reference table.
		CrossReferencer cr;
		cr.print(st_stack);
//	}

	return value;
}

antlrcpp::Any FirstVisitor::visitDeclaration(VietProgParser::DeclarationContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitDeclaration(): " + ctx->getText() << endl;

	// visit the variable list first to add them to the var_id vector and the symbol table stack.
	auto value = visit(ctx->var_list());

	// then visit the type_id and assign the type to every variable visited above.
	value = visit(ctx->type_id());

	return value;
}

antlrcpp::Any FirstVisitor::visitVar_list(VietProgParser::Var_listContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitVar_list(): " + ctx->getText() << endl;

	var_id_list.resize(0);
	var_ctx_list.resize(0);

	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitVar_id(VietProgParser::Var_idContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitVar_id(): " + ctx->getText() << endl;

	// add variable to symbol table stack
	string var_name = ctx->VAR_IDENTIFIER()->toString();
	SymTabEntry* vid = st_stack->enter_local(var_name);
	vid->set_definition((Definition) DF_VARIABLE);

	// add it to the list, so that the type can be set later.
	var_id_list.push_back(vid);
	var_ctx_list.push_back(ctx);

	// set the position of the variable in the local variables array.
	if(function_flag)
	{
		local_func_variables[var_name] = current_var_array_index++;
		// update the parse tree.
		ctx->local_var = new LocalVariable();
		ctx->local_var->set_local_var_array_index(current_var_array_index);
//		ctx->local_var->set_parent_function(current_function_ctx);
		// update the symbol table stack.
//		vid->set_attribute((SymTabKey) VAR_ARRAY_INDEX, current_var_array_index);
//		vid->set_attribute((SymTabKey) PARENT_FUNCTION, current_function_ctx);
	}

	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitType_id(VietProgParser::Type_idContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitType_id(): " + ctx->getText() << endl;

	string type_name = ctx->TYPE_IDENTIFIER()->toString();

	TypeSpec * type = (type_name == "T_integer") ? Predefined::integer_type
		: (type_name == "T_float") ? Predefined::real_type
		: (type_name == "T_boolean") ? Predefined::boolean_type
		: nullptr;

	ctx->type = type; // set the type

	// if the type_id is the return type node of the function declaration right now,
	// then we don't need to update the nodes or the symbol table entries.
	// it will suffice to simply return.
	//cout << "PRINTING GIUPDO: " << ctx->parent->children[0]->toString();
	if(ctx->parent->children[0]->toString() == "giupdo")
	{
		return visitChildren(ctx);
	}

	// set the type of the symbol table entries
	for (SymTabEntry *id: var_id_list)
	{
		id->set_typespec(type);
	}

	// set the type of the variable nodes in the parse tree
	for (VietProgParser::Var_idContext * var_ctx: var_ctx_list)
	{
		var_ctx->type = type;
	}


	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitAdd_Sub_Expr(VietProgParser::Add_Sub_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitAdd_Sub_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	TypeSpec* type1 = ctx->expr(0)->type;
	TypeSpec* type2 = ctx->expr(1)->type;

	bool integer_mode = (type1 == Predefined::integer_type) && (type2 == Predefined::integer_type);
	bool float_mode   = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);
	bool boolean_mode = (type1 == Predefined::boolean_type) && (type2 == Predefined::boolean_type);

	TypeSpec * type = integer_mode ? Predefined::integer_type
					: float_mode ? Predefined::real_type
					: boolean_mode ? Predefined::boolean_type
					: nullptr;

	ctx->type = type;

	return value;
}

antlrcpp::Any FirstVisitor::visitMul_Div_Expr(VietProgParser::Mul_Div_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitMul_Div_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	TypeSpec* type1 = ctx->expr(0)->type;
	TypeSpec* type2 = ctx->expr(1)->type;

	bool integer_mode = (type1 == Predefined::integer_type) && (type2 == Predefined::integer_type);
	bool float_mode   = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);
	bool boolean_mode = (type1 == Predefined::boolean_type) && (type2 == Predefined::boolean_type);

	TypeSpec * type = integer_mode ? Predefined::integer_type
					: float_mode ? Predefined::real_type
					: boolean_mode ? Predefined::boolean_type
					: nullptr;

	ctx->type = type;

	return value;

}

antlrcpp::Any FirstVisitor::visitRelational_Expr(VietProgParser::Relational_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitRelational_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	TypeSpec* type1 = ctx->expr(0)->type;
	TypeSpec* type2 = ctx->expr(1)->type;

	bool integer_mode = (type1 == Predefined::integer_type) && (type2 == Predefined::integer_type);
	bool float_mode   = (type1 == Predefined::real_type) && (type2 == Predefined::real_type);
	bool boolean_mode = (type1 == Predefined::boolean_type) && (type2 == Predefined::boolean_type);

	TypeSpec * type = integer_mode ? Predefined::integer_type
					: float_mode ? Predefined::real_type
					: boolean_mode ? Predefined::boolean_type
					: nullptr;

	ctx->type = type;

	return value;
}

antlrcpp::Any FirstVisitor::visitVariable_Expr(VietProgParser::Variable_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitVariable_Expr(): " + ctx->getText() << endl;

	string var_name = ctx->variable()->VAR_IDENTIFIER()->toString();
	SymTabEntry* vid = st_stack->lookup(var_name);

	ctx->type = vid->get_typespec();

	if(function_flag)
	{
		unordered_map<string, int>:: iterator it;
		if (local_func_variables.find(var_name) == local_func_variables.end())
		{
			cout << "Attempting to use undeclared variable: " + var_name << endl;
		}
		else
		{
			it = local_func_variables.find(var_name);
			if (DEBUG_FLAG_1) cout << "CURRENT LOCAL VAR: " << var_name << ", INDEX: " << it->second << endl;
			ctx->local_var = new LocalVariable();
			ctx->local_var->set_local_var_array_index(it->second);

		}
	}

	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitNumber_Const_Expr(VietProgParser::Number_Const_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitNumber_Const_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);
	ctx->type = ctx->number()->type;

	return value;
}

antlrcpp::Any FirstVisitor::visitNumber(VietProgParser::NumberContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitNumber(): " + ctx->getText() << endl;

	auto value = visit(ctx->int_float());
	ctx->type = ctx->int_float()->type;

	return value;

}

antlrcpp::Any FirstVisitor::visitIntegerConst(VietProgParser::IntegerConstContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitIntegerConst(): " + ctx->getText() << endl;

	ctx->type = Predefined::integer_type;
	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitFloatConst(VietProgParser::FloatConstContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitFloatConst(): " + ctx->getText() << endl;

	ctx->type = Predefined::real_type;
	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitParen_Expr(VietProgParser::Paren_ExprContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitParen_Expr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);
	ctx->type = ctx->expr()->type;
	return value;
}

antlrcpp::Any FirstVisitor::visitBoolean(VietProgParser::BooleanContext *ctx)
{
	if(DEBUG_FLAG_1) cout << "First Visitor: visitBoolean(): " + ctx->getText() << endl;

	ctx->type = Predefined::boolean_type;
	return visitChildren(ctx);

}

antlrcpp::Any FirstVisitor::visitFunction(VietProgParser::FunctionContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitFunction(): " + ctx->getText() << endl;
	// let every consecutive function being called know that it is currently
	// operating inside a function.
	// this should work fine since nested functions are not allowed.
//	current_function_ctx = ctx;
	function_flag = true;
	current_var_array_index = -1;

	string function_name = ctx->function_name()->FUNC_NAME_IDENTIFIER()->toString();
	string type_name;
	TypeSpec* type;

	if(ctx->type_id() != NULL)
	{
		type_name = ctx->type_id()->TYPE_IDENTIFIER()->toString();
		type = (type_name == "T_integer") ? Predefined::integer_type
			 : (type_name == "T_float")   ? Predefined::real_type
			 : (type_name == "T_boolean") ? Predefined::boolean_type
			 : nullptr;
		ctx->function_name()->type = type;
	}

	SymTabEntry* fid = st_stack->enter_local(function_name);
	fid->set_definition((Definition) DF_FUNCTION);
	fid->set_attribute((SymTabKey) ROUTINE_SYMTAB,
						st_stack->push());
	if (type != NULL) fid->set_typespec(type);

	auto value = visitChildren(ctx);

	if (DEBUG_FLAG_1)
	{
		cout << "Printing the function symbol table: " << endl;
		CrossReferencer cr;
		cr.print(st_stack);
	}

	// clean up.
//	current_function_ctx = nullptr;
	function_flag = false;
	current_var_array_index = 0;
	st_stack->pop();

	return value;
}

antlrcpp::Any FirstVisitor::visitVariable(VietProgParser::VariableContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitVariable(): " + ctx->getText() << endl;

	if (DEBUG_FLAG_1) cout << "CURRENT NESTING LEVEL: " << st_stack->get_current_nesting_level() << endl;
	return visitChildren(ctx);

}

//antlrcpp::Any FirstVisitor::visitParameter_list(VietProgParser::Parameter_listContext *ctx)
//antlrcpp::Any FirstVisitor::visitAssignment_statement(VietProgParser::Assignment_statementContext *ctx)
//antlrcpp::Any FirstVisitor::visitFunction(VietProgParser::FunctionContext *ctx)
//{
//	// TODO: make relevant changes here when the functions can start to return values.
//
//	if (DEBUG_FLAG_1) cout << "First Visitor: visitFunction(): " << endl;
//
//	string function_name = ctx->function_name()->FUNC_NAME_IDENTIFIER()->toString();
//
//	// add function name to the symbol table stack
//	if (DEBUG_FLAG_1) cout << "First Visitor: visitFunction(): Adding function to st_stack. " << endl;
//	SymTabEntry* fid;
//	fid = st_stack->enter_local(function_name);
//
//	// set definition & attributes
//	fid->set_definition((Definition)DF_FUNCTION);
//	fid->set_attribute((SymTabKey) ROUTINE_SYMTAB, st_stack->push());
//
//	var_func_list.resize(0);
//
////	jf << ".method private static " + function_name + "("; // parameter list will follow.
////
////	auto value = visit(ctx->function_name());
////
////	// visit the parameter list node, if there is one.
////	if(ctx->parameter_list() != NULL)
////	{
////		value = visit(ctx->parameter_list());
////	}
////
////	jf << ")" << endl << endl; // close the parameter list
////
////	// visit the function's statements, if they exist.
////	if (ctx->compound_statement() != NULL)
////	{
////		value = visit(ctx->compound_statement());
////	}
////
////	jf << "\treturn" << endl;
////	jf << "\n\n\n.limit stack 32" << endl;
////	jf << ".limit locals 32" << endl;
////	jf << ".end method" << endl;
////	st_stack->pop();
////
////	return value;
//	return visitChildren(ctx);
//}

//	antlrcpp::Any FirstVisitor::visitParameter(VietProgParser::ParameterContext *ctx)
//{
//	// parameter : type_id var_id + (optional) reference;
//	if(DEBUG_FLAG_1) cout << "First Visitor: visitParameter(): " + ctx->getText() << endl;
//
//	var_id_list.resize(0);
//	var_ctx_list.resize(0);
//
//	// visit the children, then use the type_id's type to set your own.
//	auto value = (visit(ctx->var_id()));
//	value = (visit(ctx->type_id()));
//	ctx->type = ctx->type_id()->type;
//
//	// TODO: fix this to allow pass-by-value variables.
//	if (ctx->REFERENCE() != NULL)
//	{
//		value = visit(ctx->REFERENCE());
//	}
//
////	value = visitChildren(ctx);
//
//	return value;
//}

//	antlrcpp::Any visitDeclaration(VietProgParser::DeclarationsContext *ctx);

//	antlrcpp::Any visitFunc_list(VietProgParser::Func_listContext *ctx);
//
//	antlrcpp::Any visitMain(VietProgParser::MainContext *ctx);
//
//	antlrcpp::Any visitCompound_statement(VietProgParser::Compound_statementContext *ctx) override;
//	antlrcpp::Any visitStatement(VietProgParser::StatementContext *ctx) override;
//	antlrcpp::Any visitStatement_list(VietProgParser::Statement_listContext *ctx) override;
//
//	antlrcpp::Any visitFunction_call_statement(VietProgParser::Function_call_statementContext *ctx);
//
//	antlrcpp::Any visitAssignment_statement(VietProgParser::Assignment_statementContext *ctx);
//	antlrcpp::Any visitLoop_statement(VietProgParser::Loop_statementContext *ctx);
//	antlrcpp::Any visitWhen_statement(VietProgParser::When_statementContext *ctx) ;
//	antlrcpp::Any visitIf_statement(VietProgParser::If_statementContext *ctx) ;
//
//	antlrcpp::Any FirstVisitor::visitPrint_statement(VietProgParser::Print_statementContext *ctx);
//
//	antlrcpp::Any visitFormat_string(VietProgParser::Format_stringContext *ctx) ;
//	antlrcpp::Any visitPrint_arg(VietProgParser::Print_argContext *ctx) ;
//
//	antlrcpp::Any visitBoolean(VietProgParser::BooleanContext *ctx) ;
//	antlrcpp::Any visitString(VietProgParser::StringContext *ctx) ;
//
//	antlrcpp::Any visitSign(VietProgParser::SignContext *ctx) override;
//	antlrcpp::Any visitMul_div_operation(VietProgParser::Mul_div_operationContext *ctx) override;
//	antlrcpp::Any visitAdd_sub_operation(VietProgParser::Add_sub_operationContext *ctx) override;
//	antlrcpp::Any visitRel_operation(VietProgParser::Rel_operationContext *ctx) override;
//
//	antlrcpp::Any visitFunc_name(VietProgParser::Func_nameContext *ctx);
//	antlrcpp::Any visitFunction_name(VietProgParser::Function_nameContext *ctx);
//	antlrcpp::Any visitParameter_list(VietProgParser::Parameter_listContext *ctx);
