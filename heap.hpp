#ifndef HEAP
#define HEAP

template <typename T>
class MinHeap {
    private:
        T* heap;
        int capacity;
        int count;

        /*
        parent(i) = (i - 1) / 2
        left(i)   = 2*i + 1
        right(i)  = 2*i + 2
        */

        void resize() {
            // o(n)
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < count; i++) {
                temp[i] = heap[i];
            }
            delete[] heap;
            heap = temp;
        }

        void shrink() {
            // O(n)
            capacity = capacity/2;
            T* temp = new T[capacity];
            for (int i = 0; i < count; i++) {
                temp[i] = heap[i];
            }
            delete[] heap;
            heap = temp;
        }

        void swap(T *a, T *b) {
            T temp = *a;
            *a = *b;
            *b = temp;
        }

        void heapify(int idx) {
            // Heapify the heap to be correct from for Min heap
            int left = 2*idx + 1;
            int right = 2*idx + 2;
            int target = idx;

            if (left < count && heap[left] < heap[idx]) {
                target = left;
            }  
            if (right < count && heap[right] < heap[target]) {
                target = right;
            } 
            if (target !=  idx) {
                swap(&heap[idx], &heap[target]);
                heapify(target);
            } 

        }

    public:
        MinHeap() : capacity(10), count(0) { 
            // constructer - initializes an empty heap
            heap = new T[capacity];
        }

        MinHeap(const MinHeap &other) : capacity(other.capacity), count(other.count) {
            // copy constructer - must properly copy the contents of another instance of the data structure | O(n)
            heap = new T[capacity];
            for (int i = 0; i < count; i++) {
                heap[i] = other.heap[i];
            }
        }

        MinHeap& operator=(const MinHeap& other) { 
            // Assignment operator - must properly copy the contents of another instance of the data structure
            if (this != &other) {
                delete[] heap;
                capacity  = other.capacity;
                count = other.count;

                heap = new T[capacity];
                for (int i = 0; i < count; i++) {
                    heap[i] = other.heap[i];
                }
            }
            return *this;
        }

        ~MinHeap() { // For destructor to free memory.
            delete[] heap;
        }

        void push(T data) {
            // TODO:: must insert an element to the heap.
            if (count == capacity) {
                resize();
            }
            heap[count] = data;
            int idx = count;
            count++;
            
            while (idx > 0 && heap[(idx-1)/2] > heap[idx]) {
                swap(&heap[idx], &heap[(idx-1)/2]);
                idx = (idx-1)/2;
            }
        }

        void pop() { // if the function only pops it (not return also)
            // TODO:: must remove the smallest element from the heap.
            if (count == 0) {
                return;
            }
            heap[0] = heap[count - 1];
            count--;

            // Heapify
            heapify(0);

            // If data has gotten too small compared to how big the capacity is
            if (capacity > 10 && count < capacity/2) {
                shrink();
            }
        }

        T peek() {
            // TODO:: must provide access to the smallest element in the heap | O(1)
            if (count == 0) {
                return T();
            }
            return heap[0];
        }

        int size() {
            // TODO:: must provide the size of the heap | O(1)
            return count;
        }

        // For debugging
        void getAll() { 
            // TODO:: print out all data to see | O(n)
            for (int i = 0; i < count; i++) {
                std::cout << heap[i] << " ";
            }
            std::cout << std::endl;
        }

        void debugging() {
            std::cout << "Capacity: " << capacity << std::endl;
            std::cout << "Size: " << count << std::endl;
            getAll(); 
        }

};

#endif

