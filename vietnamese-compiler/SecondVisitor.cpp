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


const bool DEBUG_FLAG_2 = false;
// if (DEBUG_FLAG_2) cout << "First Visitor: visitVar_list(): " + ctx->getText() << endl;


antlrcpp::Any SecondVisitor::visitProgram(VietProgParser::ProgramContext *ctx)
{
	// read the program name
	program_name = ctx->PROGRAM_IDENTIFIER()->toString();

	// create the Jasmin assembly file as an output
	if (DEBUG_FLAG_2) cout << "First Visitor: visitProgram(): creating the Jasmin assembly file..." << endl;

	jf.open(program_name + ".j"); // append .j extension
	if (jf.fail())
	{
		cout << " Jasmin assembly file creation failed. Exiting..." << endl;
		exit(-1);
	}

	if (DEBUG_FLAG_2) cout << "First Visitor: visitProgram(): created the Jasmin assembly file. " << endl;

	// write the program name to the Jasmin file
	jf << ".class public " << program_name << endl;
	jf << ".super java/lang/Object" << endl;

	// write the PascalRTL jar information
	jf << endl << ".field private static _runTimer LRunTimer;" << endl;
	jf << ".field private static _standardIn LPascalTextIn;" << endl << endl << endl;

	if (DEBUG_FLAG_2) cout << "First Visitor: visitProgram(): Printing the cross-reference table." << endl;

	return visitChildren(ctx);

}

antlrcpp::Any SecondVisitor::visitFunction(VietProgParser::FunctionContext *ctx)
{
	// TODO: make relevant changes here when the functions can start to return values.

	if (DEBUG_FLAG_2) cout << "First Visitor: visitFunction(): Printing the cross-reference table." << endl;

	string function_name = ctx->function_name()->FUNC_NAME_IDENTIFIER()->toString();

	jf << ".method private static " + function_name + "("; // parameter list will follow.

	auto value = visit(ctx->function_name());

	// visit the parameter list node, if there is one.
	if(ctx->parameter_list() != NULL)
	{
		value = visit(ctx->parameter_list());
	}

	jf << ")" << endl << endl; // close the parameter list

	// visit the function's statements, if they exist.
	if (ctx->compound_statement() != NULL)
	{
		value = visit(ctx->compound_statement());
	}

	jf << "\treturn" << endl;
	jf << "\n\n\n.limit stack 32" << endl;
	jf << ".limit locals 32" << endl;
	jf << ".end method" << endl;
	st_stack->pop();

	return value;
}

