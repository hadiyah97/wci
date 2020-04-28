/*
 * FirstVisitor.h
 *
 *  Created on: Apr 27, 2020
 *      Author: hadiyah
 */

#ifndef FIRSTVISITOR_H_
#define FIRSTVISITOR_H_

#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"

#include "LabeledExprBaseVisitor.h"
#include "antlr4-runtime.h"
#include "LabeledExprVisitor.h"

using namespace wci;
using namespace wci::intermediate;

class FirstVisitor : public LabeledExprBaseVisitor
{
private:
	SymTabStack *st_stack;
	vector<SymTabEntry *> var_id_list;
	vector<LabeledExprParser::Var_idContext *> var_ctx_list;

public:
	FirstVisitor();
	virtual ~FirstVisitor();

	  antlrcpp::Any visitProgram(LabeledExprParser::ProgramContext *ctx) override ;

//	  antlrcpp::Any visitFunc_list(LabeledExprParser::Func_listContext *ctx) override ;

//	  antlrcpp::Any visitFunc(LabeledExprParser::FuncContext *ctx) override ;

//	  antlrcpp::Any visitFunc_name(LabeledExprParser::Func_nameContext *ctx) override ;

//	  antlrcpp::Any visitParam_list(LabeledExprParser::Param_listContext *ctx) override ;

//	  antlrcpp::Any visitParam(LabeledExprParser::ParamContext *ctx) override ;

//	  antlrcpp::Any visitMain(LabeledExprParser::MainContext *ctx) override ;

//	  antlrcpp::Any visitDeclarations(LabeledExprParser::DeclarationsContext *ctx) override ;

	  antlrcpp::Any visitVar_list(LabeledExprParser::Var_listContext *ctx) override ;

	  antlrcpp::Any visitVar_id(LabeledExprParser::Var_idContext *ctx) override ;

	  antlrcpp::Any visitType_id(LabeledExprParser::Type_idContext *ctx) override ;

//	  antlrcpp::Any visitCompound_stmt(LabeledExprParser::Compound_stmtContext *ctx) override ;

//	  antlrcpp::Any visitCompoundStmt(LabeledExprParser::CompoundStmtContext *ctx) override ;

//	  antlrcpp::Any visitAssignmentStmt(LabeledExprParser::AssignmentStmtContext *ctx) override ;

//	  antlrcpp::Any visitLoopStmt(LabeledExprParser::LoopStmtContext *ctx) override ;

//	  antlrcpp::Any visitWhenStmt(LabeledExprParser::WhenStmtContext *ctx) override ;

//	  antlrcpp::Any visitIfStmt(LabeledExprParser::IfStmtContext *ctx) override ;

//	  antlrcpp::Any visitFuncCallStmt(LabeledExprParser::FuncCallStmtContext *ctx) override ;

//	  antlrcpp::Any visitDeclaration(LabeledExprParser::DeclarationContext *ctx) override ;

//	  antlrcpp::Any visitPrintStmt(LabeledExprParser::PrintStmtContext *ctx) override ;

//	  antlrcpp::Any visitEmptyStmt(LabeledExprParser::EmptyStmtContext *ctx) override ;

//	  antlrcpp::Any visitFuncCall_stmt(LabeledExprParser::FuncCall_stmtContext *ctx) override ;

//	  antlrcpp::Any visitAssignment_stmt(LabeledExprParser::Assignment_stmtContext *ctx) override ;

//	  antlrcpp::Any visitLoop_stmt(LabeledExprParser::Loop_stmtContext *ctx) override ;

//	  antlrcpp::Any visitWhen_stmt(LabeledExprParser::When_stmtContext *ctx) override ;

//	  antlrcpp::Any visitIf_stmt(LabeledExprParser::If_stmtContext *ctx) override ;

//	  antlrcpp::Any visitPrint_stmt(LabeledExprParser::Print_stmtContext *ctx) override ;

//	  antlrcpp::Any visitFormat_string(LabeledExprParser::Format_stringContext *ctx) override ;

//	  antlrcpp::Any visitPrint_arg(LabeledExprParser::Print_argContext *ctx) override ;

//	  antlrcpp::Any visitVariable(LabeledExprParser::VariableContext *ctx) override ;

//	  antlrcpp::Any visitIdentifierExpr(LabeledExprParser::IdentifierExprContext *ctx) override ;

	  antlrcpp::Any visitParensExpr(LabeledExprParser::ParensExprContext *ctx) override ;

	  antlrcpp::Any visitAddSubExpr(LabeledExprParser::AddSubExprContext *ctx) override ;

	  antlrcpp::Any visitNumberConstExpr(LabeledExprParser::NumberConstExprContext *ctx) override ;

	  antlrcpp::Any visitRelExpr(LabeledExprParser::RelExprContext *ctx) override ;

	  antlrcpp::Any visitMulDivExpr(LabeledExprParser::MulDivExprContext *ctx) override ;

	  antlrcpp::Any visitNumber(LabeledExprParser::NumberContext *ctx) override ;

//	  antlrcpp::Any visitSign(LabeledExprParser::SignContext *ctx) override ;

//	  antlrcpp::Any visitMul_div_operation(LabeledExprParser::Mul_div_operationContext *ctx) override ;

//	  antlrcpp::Any visitAdd_sub_operation(LabeledExprParser::Add_sub_operationContext *ctx) override ;

//	  antlrcpp::Any visitRel_operation(LabeledExprParser::Rel_operationContext *ctx) override ;

};

#endif /* FIRSTVISITOR_H_ */
