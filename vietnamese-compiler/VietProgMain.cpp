/*
 * VietProgMain.cpp
 *
 *  Created on: May 6, 2020
 *      Author: hadiyah
 */


/*
 * LabeledExprMain.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: hadiyah
 */
#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "VietProgLexer.h"
#include "VietProgParser.h"
#include "FirstVisitor.h"

using namespace antlrcpp;
using namespace antlr4;
using namespace std;

int main(int argc, const char *args[])
{
	ifstream ins;

	// Create the input stream.
	ins.open(args[1]);
	ANTLRInputStream input(ins);

	// Create a lexer which scans the input stream
	// to create a token stream.
	VietProgLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	// Print the token stream.
	cout << "Tokens:" << endl;
	tokens.fill();
	for (Token *token : tokens.getTokens())
	{
	std::cout << token->toString() << std::endl;
	}

	// Create a parser which parses the token stream
	// to create a parse tree.
	VietProgParser parser(&tokens);
	tree::ParseTree *tree = parser.program();

	// Print the parse tree in Lisp format.
	cout << endl << "Parse tree (Lisp format):" << endl;
	std::cout << tree->toStringTree(&parser) << endl;

	FirstVisitor *pass2 = new FirstVisitor();
	pass2->visit(tree);

	return 0;
}


