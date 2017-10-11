// References:
// - https://docs.python.org/3/extending/embedding.html

#include <cstdio>

#include <Python.h>


//====================================================
void runFile (const char * filename) {
	FILE * pyfile = std::fopen(filename, "rt");
	PyRun_SimpleFileEx(
		pyfile,
		filename, // for debugging
		true // close the file for me
	);
}


//====================================================
bool callFunction (const char * moduleName, const char * funcName) {
	PyObject * module_name = PyString_FromString(moduleName);
	PyObject * module = PyImport_Import(module_name);
	Py_DECREF(module_name);
	module_name = nullptr;

	if (!module) {
		PyErr_Print();
		std::fprintf(stderr, "Failed to load Python module {%s}.\n", moduleName);
		return false;
	}

	PyObject * func = PyObject_GetAttrString(module, funcName);
	if (func && PyCallable_Check(func)) {
		//PyObject * args = 
		PyObject_CallObject(func, nullptr);
	}
	else { // function not found or not callable
		if (PyErr_Occurred())
			PyErr_Print();
		std::fprintf(stderr, "Failed to find callable named {%s}.\n", funcName);
	}
	Py_XDECREF(func);
	Py_DECREF(module);

	return true;
}


//====================================================
int main (int argc, const char ** argv) {
#ifdef PYTHON3
	// Py_DecodeLocale doesn't exist until 3.5
	//wchar_t * programName = Py_DecodeLocale(argv[0], nullptr);
	wchar_t * programName = const_cast<wchar_t*>(L"a.out");
	Py_SetProgramName(programName); // "optional but recommended"
#else
	Py_SetProgramName(const_cast<char*>(argv[0]));
#endif
	Py_Initialize();

	// test executing Python passed from program
	PyRun_SimpleString("print('test {}'.format(2 + 8))");

	runFile("test.py");

	callFunction("test", "test_func");

	Py_Finalize();
#ifdef PYTHON3
	PyMem_RawFree(programName);
#endif
	return 0;
}

