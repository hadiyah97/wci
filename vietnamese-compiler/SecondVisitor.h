/*
 * SecondVisitor.h
 *
 *  Created on: May 5, 2020
 *      Author: hadiyah
 */

#ifndef SECONDVISITOR_H_
#define SECONDVISITOR_H_

#include <iostream>
#include <string>

#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"

using namespace wci;
using namespace wci::intermediate;

#include "antlr4-runtime.h"
#include "VietProgVisitor.h"
#include "VietProgBaseVisitor.h"
#include <unordered_map>
#include <boost/any.hpp>


/**
 * This class extends the VietProgBaseVisitor, to create a visitor which only
 * handles a subset of the available methods in the superclass.
 */

class SecondVisitor : public VietProgBaseVisitor {

private:

	ofstream jf;
	string program_name;
	string jf_name;
	int label_number;
	bool function_flag;
	bool function_call_flag;
	vector<VietProgParser::Var_idContext *> local_func_variables;

public:

	// constructor
	SecondVisitor();

	// destructor
	virtual ~SecondVisitor();

	// helpers
	ofstream& get_jasmin_file();
	void print_local_func_variables();
	void emit_program_header();
	void emit_pascalRTL_vars();
	void emit_class_constructor();
	void emit_main_prologue();
	void emit_main_epilogue();
	void emit_function_epilogue();

	// visitors
	antlrcpp::Any visitProgram(VietProgParser::ProgramContext *ctx) override;
	antlrcpp::Any visitMain(VietProgParser::MainContext *ctx) override;
	antlrcpp::Any visitDeclarations(VietProgParser::DeclarationsContext *ctx) override;
	antlrcpp::Any visitDeclaration(VietProgParser::DeclarationContext *ctx) override;
	antlrcpp::Any visitVar_id(VietProgParser::Var_idContext *ctx) override;
	antlrcpp::Any visitStatement(VietProgParser::StatementContext *ctx) override ;
	antlrcpp::Any visitAssignment_statement(VietProgParser::Assignment_statementContext *ctx)override;
	antlrcpp::Any visitPrint_statement(VietProgParser::Print_statementContext *ctx)override;
	antlrcpp::Any visitAdd_Sub_Expr(VietProgParser::Add_Sub_ExprContext *ctx) override;
	antlrcpp::Any visitMul_Div_Expr(VietProgParser::Mul_Div_ExprContext *ctx) override;
	antlrcpp::Any visitVariable_Expr(VietProgParser::Variable_ExprContext *ctx) override;
	antlrcpp::Any visitNumber(VietProgParser::NumberContext *ctx) override;
	antlrcpp::Any visitIntegerConst(VietProgParser::IntegerConstContext *ctx) override;
	antlrcpp::Any visitFloatConst(VietProgParser::FloatConstContext *ctx) override;
	antlrcpp::Any visitRelational_Expr(VietProgParser::Relational_ExprContext *ctx) override;
	antlrcpp::Any visitBoolean(VietProgParser::BooleanContext *ctx) override;
	antlrcpp::Any visitLoop_statement(VietProgParser::Loop_statementContext *ctx)override;
	antlrcpp::Any visitWhen_statement(VietProgParser::When_statementContext *ctx) override;
	antlrcpp::Any visitIf_statement(VietProgParser::If_statementContext *ctx) override;
	antlrcpp::Any visitFunction(VietProgParser::FunctionContext *ctx) override;
	antlrcpp::Any visitType_id(VietProgParser::Type_idContext *ctx) override;
	antlrcpp::Any visitFunction_return_statement(VietProgParser::Function_return_statementContext *ctx) override;
	antlrcpp::Any visitFunction_call_statement(VietProgParser::Function_call_statementContext *ctx) override;

};


#endif /* SECONDVISITOR_H_ */
