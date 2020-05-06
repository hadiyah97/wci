/*
 * FirstVisitor.h
 *
 *  Created on: May 5, 2020
 *      Author: hadiyah
 */

#ifndef FIRSTVISITOR_H_
#define FIRSTVISITOR_H_

#include <iostream>

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
	SymTabEntry *pid;
	vector<string> var_func_list;
	TypeSpec * type;
	string type_indicator;
	ofstream jasmin_file;
	string program_name;
	string n;
	int label_number;
	int error_count;

public:

   FirstVisitor();
   virtual ~FirstVisitor();

   ostream& get_jasmin_file();

   antlrcpp::Any visitProgram(VietProgParser::ProgramContext *ctx) override;

   //   antlrcpp::Any visitFunc_list(VietProgParser::Func_listContext *ctx) override;
   antlrcpp::Any visitFunc(VietProgParser::FuncContext *ctx) override;
//   antlrcpp::Any visitFunc_name(VietProgParser::Func_nameContext *ctx) override;
//   antlrcpp::Any visitParam_list(VietProgParser::Param_listContext *ctx) override;
   antlrcpp::Any visitParam(VietProgParser::ParamContext *ctx) override;

//   antlrcpp::Any visitMain(VietProgParser::MainContext *ctx) override;
   antlrcpp::Any visitDeclarations(VietProgParser::DeclarationsContext *ctx) override;
   antlrcpp::Any visitVar_list(VietProgParser::Var_listContext *ctx) override;
   antlrcpp::Any visitVar_id(VietProgParser::Var_idContext *ctx) override;
   antlrcpp::Any visitType_id(VietProgParser::Type_idContext *ctx) override;

//   antlrcpp::Any visitCompound_stmt(VietProgParser::Compound_stmtContext *ctx) override;
//   antlrcpp::Any visitStmt(VietProgParser::StmtContext *ctx) override;
//   antlrcpp::Any visitStmt_list(VietProgParser::Stmt_listContext *ctx) override;
   antlrcpp::Any visitFuncCall_stmt(VietProgParser::FuncCall_stmtContext *ctx) override;

   antlrcpp::Any visitAssignment_stmt(VietProgParser::Assignment_stmtContext *ctx) override;
   antlrcpp::Any visitLoop_stmt(VietProgParser::Loop_stmtContext *ctx) override;
   antlrcpp::Any visitWhen_stmt(VietProgParser::When_stmtContext *ctx) override;
   antlrcpp::Any visitIf_stmt(VietProgParser::If_stmtContext *ctx) override;

   antlrcpp::Any visitPrint_stmt(VietProgParser::Print_stmtContext *ctx) override;
   antlrcpp::Any visitFormat_string(VietProgParser::Format_stringContext *ctx) override;
   antlrcpp::Any visitPrint_arg(VietProgParser::Print_argContext *ctx) override;

   antlrcpp::Any visitBoolean(VietProgParser::BooleanContext *ctx) override;
   antlrcpp::Any visitAddSubExpr(VietProgParser::AddSubExprContext *ctx) override;
   antlrcpp::Any visitString(VietProgParser::StringContext *ctx) override;
   antlrcpp::Any visitNumberConstExpr(VietProgParser::NumberConstExprContext *ctx) override;
   antlrcpp::Any visitVarIdentifierExpr(VietProgParser::VarIdentifierExprContext *ctx) override;
   antlrcpp::Any visitRelExpr(VietProgParser::RelExprContext *ctx) override;
   antlrcpp::Any visitMulDivExpr(VietProgParser::MulDivExprContext *ctx) override;
   antlrcpp::Any visitParenExpr(VietProgParser::ParenExprContext *ctx) override;
   antlrcpp::Any visitNumber(VietProgParser::NumberContext *ctx) override;
   antlrcpp::Any visitIntegerConst(VietProgParser::IntegerConstContext *ctx) override;
   antlrcpp::Any visitFloatConst(VietProgParser::FloatConstContext *ctx) override;
//   antlrcpp::Any visitSign(VietProgParser::SignContext *ctx) override;
//   antlrcpp::Any visitMul_div_operation(VietProgParser::Mul_div_operationContext *ctx) override;
//   antlrcpp::Any visitAdd_sub_operation(VietProgParser::Add_sub_operationContext *ctx) override;
//   antlrcpp::Any visitRel_operation(VietProgParser::Rel_operationContext *ctx) override;

};

#endif /* FIRSTVISITOR_H_ */
