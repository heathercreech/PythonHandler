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
#include "PythonHandler.h"
#include <algorithm>


//responsible for setting up PythonArgLists for python functions
class FunctionManager {
public:
	FunctionManager();
	FunctionManager(std::string);
	FunctionManager(FunctionManager&);

	~FunctionManager();

	void setConfigLine(std::string);
	void updateParameters(std::string);
	PyObject* execute() { return py_handler.execute(); };

	bool isGood() { return good && py_handler.isGood(); };
	const std::string getConfigLine() { return config_line; };

private:
	void configure();
	PyObject* convert(std::string);

	std::string config_line;

	std::string file_name;
	std::string function_name;

	PythonHandler py_handler;
	PythonArgList py_args;

	bool good = false;
};