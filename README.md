# PythonHandler

PythonHandler is a utility that makes it easy to use Python functions in C++ applications.


##Dependencies
The only requirement for this utility is Python's libraries, which are included in every Python installation. Currently, only Python 3.5.0+ is supported.

##Using a PythonHandler

####Purpose
Python's provided libraries for embedding it's functionality into C++ is cumbersome and requires knowledge of when to dereference Python objects. The purpose for the PythonHandler is to take the dereferencing out of the users hands, and to provide a quicker (less code) way to use Python functions.

####Initialization



####Executing a Function

##Using a FunctionManager
*Note: the FunctionManager is a temporary interface to make handling arguments easier. A more permanent solution will be developed later.

####Purpose

####Initialization
To construct a FunctionManager, the constructor must be provided with a configure line. This configure line needs to be of the form "filename|function_name|arg1|argn...." File name refers to the Python source file, and the ".py" extension should be omitted (the class will handle accidental inclusion of the extension later). Function name is the name of the function you are trying to call. Finally arg1 through argn are the parameters of the target function. There arguments are represented as a string containing the name of their intended type.

####Executing a Function