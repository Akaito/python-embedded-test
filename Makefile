PYTHON3_LDFLAGS := $(shell python3-config --ldflags)
PYTHON3_CFLAGS := $(shell python3-config --cflags)

CC := clang
CXX := clang++

CC += $(PYTHON3_LDFLAGS) $(PYTHON3_CFLAGS)
CXX += $(PYTHON3_LDFLAGS) $(PYTHON3_CFLAGS)

a.out:
	$(CXX) main.cpp
