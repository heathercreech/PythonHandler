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


#include "FunctionManager.h"

//default constructor for lazy initialization
FunctionManager::FunctionManager() {
	good = false;
}


//takes a config line from the config file of the following format: file_name|function_name|arg1_type:arg1_val|arg2_type:arg2_val...
//supported types: int, float, double, string
FunctionManager::FunctionManager(std::string cfl) {
	setConfigLine(cfl);
}


//copy constructor
FunctionManager::FunctionManager(FunctionManager& func) {
	setConfigLine(func.getConfigLine());
}


//destructor
FunctionManager::~FunctionManager() {
	
}


//update the current config line
void FunctionManager::setConfigLine(std::string cfl) {
	config_line = cfl;
	configure();
}


//takes a string of the typical configuration form and updates the config of the function
void FunctionManager::updateParameters(std::string var_cfl) {
	std::string new_cfg_line = file_name + "|" + function_name + "|" + var_cfl;
	setConfigLine(new_cfg_line);
}


//configure the FunctionManager using the current config line
void FunctionManager::configure() {
	py_args.clear();

	std::string temp_cfl = config_line;
	std::vector<std::string> tokens;

	int delim_pos;
	
	while ((delim_pos = temp_cfl.find('|')) != std::string::npos) {
		tokens.push_back(temp_cfl.substr(0, delim_pos));
		temp_cfl.erase(0, delim_pos+1);
	}
	tokens.push_back(temp_cfl);

	file_name = tokens[0];
	function_name = tokens[1];

	for (unsigned int i = 2; i < tokens.size(); i++) {
		PyObject* arg = convert(tokens[i]);
		if (arg != NULL) {
			py_args.push_back(arg);
		}
		else {
			good = false;
			printf("Error: unable to load argument %ld for function %s\n", i, function_name.c_str());
		}
		
	}

	if (isGood()) {
		py_handler.init(file_name, function_name, py_args);
		if (!py_handler.isGood()) {
			good = false;
		}
	}
}


//converts a type value string to it's corresponding PyObject*
PyObject* FunctionManager::convert(std::string type_val) {
	PyObject* arg = NULL;
	int delim_pos = type_val.find(':');
	

	if (delim_pos != std::string::npos) {
		std::string type = type_val.substr(0, delim_pos);
		std::string val = type_val.substr(type.length() + 1);
		
		if (type == "string") {
			arg = PyUnicode_FromString(val.c_str());
		}
		else if (type == "long") {
			arg = PyLong_FromLong(atoi(val.c_str()));
		}
		else if (type == "float") {
			arg = PyFloat_FromString(PyUnicode_FromString(val.c_str()));
		}
		else if (type == "double") {
			arg = PyFloat_FromString(PyUnicode_FromString(val.c_str()));
		}
		else if (type == "bool") {
			arg = PyBool_FromLong(atoi(val.c_str()));
		}
	}
	
	return arg;
}