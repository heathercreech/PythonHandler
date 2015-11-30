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