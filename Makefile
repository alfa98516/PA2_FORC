warnings = pedantic
std = c++98

# Test files
HEAP_TEST = heapTest.cpp
DEQUEUE_TEST = dequeTest.cpp

# Executable filenames
HEAP_EXE = heap2
DEQUEUE_EXE = dequeue

# Default target - build all tests
all: $(HEAP_EXE) $(DEQUEUE_EXE)

# Compile rules
$(HEAP_EXE): $(HEAP_TEST) heap.hpp
	g++ -Wall -Wextra -pedantic -g -std=c++98 $(HEAP_TEST) -o $(HEAP_EXE)
$(DEQUEUE_EXE): $(DEQUEUE_TEST) dequeue.hpp
	g++ -Wall -Wextra -pedantic -g -std=c++98 $(DEQUEUE_TEST) -o $(DEQUEUE_EXE)


clean:
	rm -f $(HEAP_EXE) $(DEQUEUE_EXE)
# RUN
# g++ -std=c++98 heapTest.cpp -o heap
# ./heap2
# */