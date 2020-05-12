/*
 * FirstVisitor.h
 *
 *  Created on: May 5, 2020
 *      Author: hadiyah
 */

#ifndef FIRSTVISITOR_H_
#define FIRSTVISITOR_H_

#include <iostream>
#include <unordered_map>

#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"

using namespace wci;
using namespace wci::intermediate;

#include "antlr4-runtime.h"
#include "VietProgVisitor.h"
#include "VietProgBaseVisitor.h"

/**
 * This class extends the VietProgBaseVisitor, to create a visitor which only
 * handles a subset of the available methods in the superclass.
 */

class  FirstVisitor : public VietProgBaseVisitor {

private:
	SymTabStack *st_stack;
	vector<SymTabEntry *> var_id_list;
	vector<VietProgParser::Var_idContext *> var_ctx_list;
	bool function_flag;
	unordered_map<string, int> local_func_variables;
	int current_var_array_index;

public:

	// constructor
	FirstVisitor();

	// destructor
	virtual ~FirstVisitor() {}

	// visitors
	antlrcpp::Any visitProgram(VietProgParser::ProgramContext *ctx) override;
	antlrcpp::Any visitDeclaration(VietProgParser::DeclarationContext *ctx);
	antlrcpp::Any visitVar_list(VietProgParser::Var_listContext *ctx) override;
	antlrcpp::Any visitVar_id(VietProgParser::Var_idContext *ctx) override;
	antlrcpp::Any visitType_id(VietProgParser::Type_idContext *ctx) override;
	antlrcpp::Any visitAdd_Sub_Expr(VietProgParser::Add_Sub_ExprContext *ctx) override;
	antlrcpp::Any visitMul_Div_Expr(VietProgParser::Mul_Div_ExprContext *ctx) override;
	antlrcpp::Any visitRelational_Expr(VietProgParser::Relational_ExprContext *ctx) override;
	antlrcpp::Any visitVariable_Expr(VietProgParser::Variable_ExprContext *ctx) override;
	antlrcpp::Any visitVariable(VietProgParser::VariableContext *ctx) override;
	antlrcpp::Any visitNumber_Const_Expr(VietProgParser::Number_Const_ExprContext *ctx) override;
	antlrcpp::Any visitNumber(VietProgParser::NumberContext *ctx) override;
	antlrcpp::Any visitIntegerConst(VietProgParser::IntegerConstContext *ctx) override;
	antlrcpp::Any visitFloatConst(VietProgParser::FloatConstContext *ctx) override;
	antlrcpp::Any visitParen_Expr(VietProgParser::Paren_ExprContext *ctx) override;
	antlrcpp::Any visitBoolean(VietProgParser::BooleanContext *ctx) override;
	antlrcpp::Any visitFunction(VietProgParser::FunctionContext *ctx) override;

};

#endif /* FIRSTVISITOR_H_ */
