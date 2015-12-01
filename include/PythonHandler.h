/*
PythonHandler is a utility that makes embedding Python into C++ applications easier.
Copyright (C) 2015  Seth Creech

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include "Python.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>

typedef std::string PythonError; //allow future expansion of an error system, just using a typedef for now
typedef std::vector<PyObject*> PythonArgList;


class PythonHandler{
public:
	PythonHandler() { good = false; };
	PythonHandler(std::string, std::string, PythonArgList);
	~PythonHandler();


	PyObject* execute();

	bool isGood();
	PythonError getLastError();

	void init(std::string, std::string, PythonArgList);

	PyObject* py_mod;
private:

	//setup functions
	void loadName(std::string);
	void loadModule();
	void loadFunction(std::string);
	void packArgs(PythonArgList); //packs args into a tuple for PyObject_CallObject


	bool good = true;

	PyObject* py_name;
	
	PyObject* py_func;
	PyObject* py_func_args;

	PyObject* py_ret_value;

	std::queue<PyObject*> function_args;
	
	std::stack<PythonError> errors; //support for future non-fatal errors?
};