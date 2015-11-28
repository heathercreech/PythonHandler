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

	bool good = true;
};