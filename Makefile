# Test files
MAIN = main.cpp
HEAP_TEST = heapTest.cpp
DEQUEUE_TEST = dequeTest.cpp
DLL_TEST = dllTest.cpp
ARRAY_TEST = test_dynamic_array.cpp

# Header files
ARRAY = dynamic_array.hpp
HEAP = heap.hpp 
DLL = dll.hpp 
DEQUEUE = dequeue.hpp

# Cflags
STD = -std=c++98
WARNINGS = -Wpedantic
SYMBOLS = -g
CC = g++
CXXFLAGS = $(SYMBOLS) $(WARNINGS) $(STD)

# Binary files
HEAP_BIN = heap2
DEQUEUE_BIN = dequeue
ARRAY_BIN = array
DLL = dll

a.out: $(MAIN)
	$(CC) $(CXXFLAGS) $(MAIN) -o a.out

$(ARRAY_BIN): $(ARRAY) 
	$(CC) $(CXXFLAGS) $(ARRAY_TEST) -o $(ARRAY_BIN)

$(HEAP_BIN): $(HEAP)
	$(CC) $(CXXFLAGS) $(HEAP_TEST) -o $(HEAP_BIN)

$(DEQUEUE_BIN): $(DEQUEUE)
	$(CC) $(CXXFLAGS) $(DEQUEUE_TEST) -o $(DEQUEUE_BIN)




clean:
	rm -f $(HEAP_BIN) $(DEQUEUE_EXE) $(ARRAY_EXE) *.out

