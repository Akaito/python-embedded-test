#include <cstdio>

#include <Python.h>

int main (int argc, const char ** argv) {
	Py_Initialize();

	// test executing Python passed from program
	PyRun_SimpleString("print('test {}'.format(2 + 8))");

	// run a .py file
	FILE * pyfile = std::fopen("test.py", "rt");
	PyRun_SimpleFileEx(
		pyfile,
		"test.py", // for debugging
		true // close the file for me
	);
	pyfile = nullptr;

	return 0;
}

