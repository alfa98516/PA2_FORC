# Test files
MAIN = main.cpp
HEAP_TEST = heapTest.cpp
DEQUEUE_TEST = dequeTest.cpp
DLL_TEST = dllTest.cpp
ARRAY_TEST = test_dynamic_array.cpp
BST_TEST = bst_test.cpp

# Header files
ARRAY = dynamic_array.hpp
HEAP = heap.hpp 
DLL = dll.hpp 
DEQUEUE = dequeue.hpp
BST = self_balancing_bst.hpp
WATCH = $(DLL)

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
DLL_BIN = dll
BST_BIN = bst

a.out: $(MAIN) $(WATCH)
	$(CC) $(CXXFLAGS) $(MAIN) -o a.out

$(ARRAY_BIN): $(ARRAY) 
	$(CC) $(CXXFLAGS) $(ARRAY_TEST) -o $(ARRAY_BIN)

$(HEAP_BIN): $(HEAP)
	$(CC) $(CXXFLAGS) $(HEAP_TEST) -o $(HEAP_BIN)

$(DEQUEUE_BIN): $(DEQUEUE)
	$(CC) $(CXXFLAGS) $(DEQUEUE_TEST) -o $(DEQUEUE_BIN)

$(DLL_BIN): $(DLL)
	$(CC) $(CXXFLAGS) $(DLL_TEST) -o $(DLL_BIN)

$(BST_BIN): $(DLL)
	$(CC) $(CXXFLAGS) $(BST_TEST) -o $(BST_BIN)


clean:
	rm -f $(HEAP_BIN) $(DEQUEUE_BIN) $(ARRAY_BIN) $(DLL_BIN) $(BST_BIN) *.out
