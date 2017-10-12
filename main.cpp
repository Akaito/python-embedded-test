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
	std::printf(" Import {%s}...\n", moduleName);
	//PyObject * module = PyImport_Import(module_name);
	PyObject * module = PyImport_ImportModuleLevel(
		const_cast<char*>(moduleName),
		nullptr, // globals
		nullptr, // locals
		nullptr, // fromlist
		1 // level (-1 default)
	);
	Py_DECREF(module_name);
	module_name = nullptr;

	// did we find a module to import?
	if (!module) {
		PyErr_Print();
		std::fprintf(stderr, "Failed to load Python module {%s}.\n", moduleName);
		return false;
	}
	// was it really a module?
	if (!PyModule_Check(module)) {
		std::fprintf(stderr, "Imported module {%s} isn't a module?\n", moduleName);
		return false;
	}

	// check the module's dictionary
	{
		PyObject * module_dict = PyModule_GetDict(module);
		PyObject * keys = PyDict_Keys(module_dict);
		int keyCount = PyList_Size(keys);

		std::printf("  module keys:\n");
		for (int i = 0; i < keyCount; ++i) {
			PyObject * item = PyList_GetItem(keys, i);
			// assume these are all strings
			const char * key = PyString_AsString(item);
			std::printf("    {%s}\n", key);
			Py_DECREF(item);
		}

		Py_DECREF(keys);
		Py_DECREF(module_dict);
	}

	std::printf("Try running %s.%s()\n", moduleName, funcName);
	PyRun_SimpleString("test.test_func()");

	PyObject * func = PyObject_GetAttrString(module, funcName);
	if (func && PyCallable_Check(func)) {
		//PyObject * args = 
		PyObject_CallObject(func, nullptr);
	}
	else { // function not found or not callable
		if (PyErr_Occurred())
			PyErr_Print();
		std::fprintf(
			stderr,
			"Failed to find callable named {%s}.  Something of that name %s exist.\n",
			funcName,
			PyObject_HasAttrString(module, funcName) ? "does" : "doesn't"
		);
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

