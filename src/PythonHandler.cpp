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


#include "PythonHandler.h"


//Function constructor
PythonHandler::PythonHandler(std::string filename, std::string functionname, PythonArgList arg_list) : function_args(){
	init(filename, functionname, arg_list);
}


//Clean up references
PythonHandler::~PythonHandler() {
	Py_DECREF(py_func_args);
	Py_DECREF(py_mod);
	Py_DECREF(py_ret_value);
}


//Enable lazy initialization
//Loads the function and arguments
void PythonHandler::init(std::string filename, std::string functionname, PythonArgList arg_list) {
	good = true;
	loadName(filename);
	loadModule();
	loadFunction(functionname);
	packArgs(arg_list);
}

//returns true if there has not been an error in the handler
bool PythonHandler::isGood() {
	return good;
}


//returns the last experienced error (future support for returning all errors, not implemented yet)
PythonError PythonHandler::getLastError() {
	return errors.top();
}


//executes the function and returns what it gets, or returns NULL if something is wrong
PyObject* PythonHandler::execute() {
	if (isGood()) {
		py_ret_value = PyObject_CallObject(py_func, py_func_args);

		if (py_ret_value == NULL) {
			Py_DECREF(py_func);
			Py_DECREF(py_mod);
			printf("PyErr: ");
			PyErr_Print();
			errors.push("Refer to PyErr output for more information.");
		}

		return py_ret_value;
	}
	return NULL;
}


//Loads the functions file's name
void PythonHandler::loadName(std::string filename) {
	py_name = PyUnicode_FromString(filename.c_str());
}


//Loads the actual file
void PythonHandler::loadModule() {
	//check not really needed, just being safe
	if (isGood()) {
		py_mod = PyImport_Import(py_name);
		Py_DECREF(py_name);
		if (py_mod == NULL) {
			good = false;
			errors.push("Unable to load file.\n");
		}
	}
}


//Loads the function
void PythonHandler::loadFunction(std::string functionname) {
	if (isGood()) {
		py_func = PyObject_GetAttrString(py_mod, functionname.c_str());

		if (!py_func || !PyCallable_Check(py_func)) {
			good = false;
			Py_DECREF(py_mod);
			errors.push("Function not callable or doesn't exist.\n");
		}
	}
}


//packs args into a tuple (py_func_args) for PyObject_CallObject
void PythonHandler::packArgs(PythonArgList arg_list) {
	if (isGood()) {
		if (arg_list.size() > 0) {
			py_func_args = PyTuple_New(arg_list.size());
			for (unsigned int i = 0; i < arg_list.size(); i++) {
				PyObject* py_argument = arg_list.at(i);
				if (!py_argument) {
					good = false;
					Py_DECREF(py_func_args);
					Py_DECREF(py_mod);
					errors.push("Unable to load parameter " + std::to_string(i+1) + "\n");
				}
				PyTuple_SetItem(py_func_args, i, py_argument);
			}
		}
		else {
			py_func_args = NULL; //runs the function with no arguments (if it can)
		}
	}
}