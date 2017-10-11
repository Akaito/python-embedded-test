PYTHON2_CFLAGS := -DPYTHON2 $(shell python-config --cflags)
PYTHON3_CFLAGS := -DPYTHON3 $(shell python3-config --cflags)
PYTHON2_LDFLAGS := $(shell python2-config --ldflags)
PYTHON3_LDFLAGS := $(shell python3-config --ldflags)

CXX := clang++ --std=c++14
CXX += $(PYTHON2_LDFLAGS) $(PYTHON2_CFLAGS)

a.out: main.cpp
	$(CXX) main.cpp
