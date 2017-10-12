# python-embedded-test

Just a quick test to see what embedding Python in C++ is like.

Problems:
- Python expects there to be only one interpreter.
	To sandbox as desired, may need one *process* per interpreter.
	Or, maybe Py_NewInterpreter() will do?  Is there a global "main thread" statefullness with the Python C API?


## TODO

- [ ] Try using "fromlist" when importing a module to maintain its contents.  Returned dict doesn't have anything custom in it.


## Sources

- https://docs.python.org/2/extending/embedding.html
- https://docs.python.org/3/extending/embedding.html


## Reminders
- [Py_NewInterpreter](https://docs.python.org/3/c-api/init.html#c.Py_NewInterpreter)

