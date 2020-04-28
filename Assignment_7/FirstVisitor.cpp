/*
 * FirstVisitor.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: hadiyah
 */

#include <iostream>
#include <string>
#include <vector>

#include "FirstVisitor.h"
#include "wci/intermediate/SymTabFactory.h"
#include "wci/intermediate/symtabimpl/Predefined.h"
#include "wci/util/CrossReferencer.h"
#include "wci/intermediate/symtabimpl/Predefined.h"

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::util;

const bool DEBUG_FLAG_1 = false;

FirstVisitor::FirstVisitor()
{
	st_stack = SymTabFactory::create_symtab_stack();
	Predefined::initialize(st_stack);

	if (DEBUG_FLAG_1) cout << "First Visitor: FirstVisitor() - st_stack initialized." << endl;
}

FirstVisitor::~FirstVisitor() {} // empty destructor

antlrcpp::Any FirstVisitor::visitProgram(LabeledExprParser::ProgramContext *ctx)
{

	if (DEBUG_FLAG_1) cout << "First Visitor: visitProgram(): " << endl;

	string name = ctx->IDENTIFIER()->toString();

	SymTabEntry *program_identifier = st_stack->enter_local(name);
	program_identifier->set_definition((Definition)DF_PROGRAM);
	program_identifier->set_attribute( (SymTabKey)ROUTINE_SYMTAB,
										st_stack->push());
	st_stack->set_program_id(program_identifier);

	auto value = visitChildren(ctx);

	if (DEBUG_FLAG_1) cout << "First Visitor: visitProgram() Printing the cross-reference table." << endl;
	CrossReferencer cr;
	cr.print(st_stack);

	return value;

}

antlrcpp::Any FirstVisitor::visitVar_list(LabeledExprParser::Var_listContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitVar_list(): " + ctx->getText() << endl;

	var_id_list.resize(0);
	var_ctx_list.resize(0);

	return visitChildren(ctx);

}

antlrcpp::Any FirstVisitor::visitVar_id(LabeledExprParser::Var_idContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitVar_id(): " + ctx->getText() << endl;

	string var_name = ctx->IDENTIFIER()->toString();
	SymTabEntry *var_id = st_stack->enter_local(var_name);
	var_id->set_definition((Definition) DF_VARIABLE);

	var_id_list.push_back(var_id);
	var_ctx_list.push_back(ctx);

	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitType_id(LabeledExprParser::Type_idContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitType_id(): " + ctx->getText() << endl;

	TypeSpec* ts;
	string name = ctx->IDENTIFIER()->toString();
	ts = (name == "Integer") ? Predefined::integer_type
			: (name == "Boolean") ? Predefined::boolean_type
					: nullptr;
	// TODO: add support for float, and char.

    // Set the type for the symbol table entries.
    for (SymTabEntry *id : var_id_list)
    {
        id->set_typespec(ts);
    }

    // Set the type for the variable parse tree nodes.
    for (LabeledExprParser::Var_idContext *var_ctx : var_ctx_list)
    {
        var_ctx->type = ts;
    }

    return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitParensExpr(LabeledExprParser::ParensExprContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitParens(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);
	ctx->type = ctx->expr()->type;
	return value;
}

antlrcpp::Any FirstVisitor::visitAddSubExpr(LabeledExprParser::AddSubExprContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitAddSubExpr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	// TODO: add support for float, and char.
	TypeSpec* ts1 = ctx->expr(0)->type;
	TypeSpec* ts2 = ctx->expr(1)->type;

	bool integer_mode = (ts1 == Predefined::integer_type) && (ts2 == Predefined::integer_type);

	TypeSpec* ts = integer_mode ? Predefined::integer_type : nullptr;

	ctx->type = ts;

	return value;

}

antlrcpp::Any FirstVisitor::visitNumberConstExpr(LabeledExprParser::NumberConstExprContext *ctx)
{
	// TODO: add support for float numbers
	if (DEBUG_FLAG_1) cout << "First Visitor: visitNumberConst(): " + ctx->getText() << endl;

	ctx->type = Predefined::integer_type;

	return visitChildren(ctx);
}

antlrcpp::Any FirstVisitor::visitNumber(LabeledExprParser::NumberContext *ctx)
{
	// TODO: add support for float numbers
	if (DEBUG_FLAG_1) cout << "First Visitor: visitNumber(): " + ctx->getText() << endl;

	ctx->type = Predefined::integer_type;

	return visitChildren(ctx);

}


antlrcpp::Any FirstVisitor::visitRelExpr(LabeledExprParser::RelExprContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitRelExpr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	// TODO: add support for float, and char.
	TypeSpec* ts1 = ctx->expr(0)->type;
	TypeSpec* ts2 = ctx->expr(1)->type;

	bool integer_mode = (ts1 == Predefined::integer_type) && (ts2 == Predefined::integer_type);

	TypeSpec* ts = integer_mode ? Predefined::integer_type : nullptr;

	ctx->type = ts;

	return value;
}

antlrcpp::Any FirstVisitor::visitMulDivExpr(LabeledExprParser::MulDivExprContext *ctx)
{
	if (DEBUG_FLAG_1) cout << "First Visitor: visitMulDivExpr(): " + ctx->getText() << endl;

	auto value = visitChildren(ctx);

	// TODO: add support for float, and char.
	TypeSpec* ts1 = ctx->expr(0)->type;
	TypeSpec* ts2 = ctx->expr(1)->type;

	bool integer_mode = (ts1 == Predefined::integer_type) && (ts2 == Predefined::integer_type);

	TypeSpec* ts = integer_mode ? Predefined::integer_type : nullptr;

	ctx->type = ts;

	return value;

}


