# PythonHandler

PythonHandler is a utility that makes it easy to use Python functions in C++ applications.


##Dependencies
The only requirement for this utility is Python's libraries, which are included in every Python installation. Currently, only Python 3.5.0+ is supported.

##Using a PythonHandler

####Purpose
Python's provided libraries for embedding it's functionality into C++ is cumbersome and requires knowledge of when to dereference Python objects. The purpose for the PythonHandler is to take the dereferencing out of the users hands, and to provide a quicker (less code) way to use Python functions.

####Use


##Using a FunctionManager
*Note: the FunctionManager is a temporary interface to make handling arguments easier. A more permanent solution will be developed later.

####Purpose

####Use
To construct a FunctionManager, the constructor must be provided with a configure line. This configure line needs to be of the form "filename|function_name|arg1:val1|argn:valn...." File name refers to the Python source file, and the ".py" extension should be omitted (the class will handle accidental inclusion of the extension later). Function name is the name of the function you are trying to call. Arg1 through argn are the types of the parameters of the target function, with val1 and valn being their actual values. There arguments are represented as a string containing the name of their intended type.

Currently Supported Values |
-------------------------- |
String	|
Long	|
Float	|
Double	|
Bool	|

As an example of the initialization of a FunctionManager, consider the following: a C++ project's goal is the evaluation of different mathematical formulas. Recompiling code every time you want to change the currently targeted formula gets tiresome, so we will use a Python function that will perform the formula for us. The formula function is located in "formula.py" and is named "use_formula" with a single argument of type double.
```c++
	double x = 1;
	FunctionManager fm("formula|use_formula|double:" + to_string(x));
	double formula_value = PyFloat_AsDouble(fm.execute());
```

In the instance above, the execution of code and storage of its result can be compressed into one line:
```c++
	double x = 1;
	double formula_value = PyFloat_AsDouble(FunctionManager("formula|use_formula|double:" + to_string(x)).execute());
```
For the more permanent version of this class, the Python function "PyFloat_AsDouble" will possibly be omitted for some form of automatic typing. The system for this type determination is yet to be decided, but it could involve the user specifying the return value ahead of time, or something more like boost::any.