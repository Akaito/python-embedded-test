#include <Python.h>

int main (int argc, const char ** argv) {
	Py_Initialize();

	// test executing Python passed from program
	PyRun_SimpleString("print('test {}'.format(2 + 8))");

	return 0;
}

