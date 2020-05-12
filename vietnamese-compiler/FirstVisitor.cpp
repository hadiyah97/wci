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
	current_var_array_index = 0;
	st_stack = SymTabFactory::create_symtab_stack();
	Predefined::initialize(st_stack);
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

	CrossReferencer cr;
	cr.print(st_stack);

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
	function_flag = true;
	current_var_array_index = 0;

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
