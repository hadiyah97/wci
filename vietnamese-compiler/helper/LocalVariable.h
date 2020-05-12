/*
 * LocalVariable.h
 *
 *  Created on: May 11, 2020
 *      Author: hadiyah
 */

#ifndef LOCALVARIABLE_TYPE_H_
#define LOCALVARIABLE_TYPE_H_


class LocalVariable
{
private:
//	VietProgParser::FunctionContext* parent_function;
	int local_var_array_index;

public:
	// constructor
	LocalVariable();

	// destructor
//	~LocalVariable();

	//getters
//	VietProgParser::FunctionContext* get_parent_function();
	int get_local_var_array_index();

	//setters
//	void set_parent_function(VietProgParser::FunctionContext* pf);
	void set_local_var_array_index(int i);

};

#endif /* LOCALVARIABLE_TYPE_H_ */
