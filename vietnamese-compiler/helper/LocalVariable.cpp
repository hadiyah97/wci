/*
 * LocalVariable.cpp
 *
 *  Created on: May 11, 2020
 *      Author: hadiyah
 */

#include "./LocalVariable.h"
//#include <boost/any.hpp>
// constructor
LocalVariable::LocalVariable() : local_var_array_index(-1) {}

// destructor
//LocalVariable::~LocalVariable()
//{
//	delete parent_function;
//}

//getters
//VietProgParser::FunctionContext* LocalVariable::get_parent_function()
//{
//	return parent_function;
//}

int LocalVariable::get_local_var_array_index()
{
	return local_var_array_index;
}

//setters
//void LocalVariable::set_parent_function(VietProgParser::FunctionContext* pf)
//{
//	parent_function = pf;
//}

void LocalVariable::set_local_var_array_index(int i)
{
	local_var_array_index = i;
}
