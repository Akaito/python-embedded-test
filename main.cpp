#include <cstdio>

#include <Python.h>


void runfile(const char * filename) {
	FILE * pyfile = std::fopen(filename, "rt");
	PyRun_SimpleFileEx(
		pyfile,
		filename, // for debugging
		true // close the file for me
	);
}


int main (int argc, const char ** argv) {
	Py_Initialize();

	// test executing Python passed from program
	PyRun_SimpleString("print('test {}'.format(2 + 8))");

	runfile("test.py");

	return 0;
}

