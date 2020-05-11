/*
 * VietProgMain.cpp
 *
 *  Created on: May 6, 2020
 *      Author: hadiyah
 */

/*batdau secondProgram:

HUDUNG:
T_integer H_mango, H_banana;
T_float H_orange, H_peels;
T_boolean H_lies, H_truth.

viecchinh
{
	H_mango <- 24;
	INRA ('H_mango bang %d, H_banana bang %d, H_orange bang %f, H_peels bang %f', H_mango, H_banana, H_orange, H_peels);
}
ketthuc

giupdo G_functionName (T_integer H_firstVariable, T_boolean H_secondVariable)
{
	T_float H_apple;
	H_apple <- 34.5;
	INRA('This is a print statement. %f', H_apple);


	G_functionName(H_mango, H_lies);
}
*/

/*
 * VietProgMain.cpp
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
#include "SecondVisitor.h"

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

	FirstVisitor *pass1 = new FirstVisitor();
	pass1->visit(tree);

	SecondVisitor *pass2 = new SecondVisitor();
	pass2->visit(tree);

	return 0;
}


