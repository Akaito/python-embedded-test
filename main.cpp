// References:
// - https://docs.python.org/3/extending/embedding.html

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

#ifdef PYTHON3
	// Py_DecodeLocale doesn't exist until 3.5
	//wchar_t * programName = Py_DecodeLocale(argv[0], nullptr);
	wchar_t * programName = const_cast<wchar_t*>(L"a.out");
	Py_SetProgramName(programName); // "optional but recommended"
#else
	Py_SetProgramName(const_cast<char*>(argv[0]));
#endif

	// test executing Python passed from program
	PyRun_SimpleString("print('test {}'.format(2 + 8))");

	runfile("test.py");

	Py_Finalize();
#ifdef PYTHON3
	PyMem_RawFree(programName);
#endif
	return 0;
}

