#ifndef DEQUEUE2_HPP
#define DEQUEUE2_HPP

template <typename T>
class Dequeue {
    private:
        T* data;
        int capacity;
        int head;
        int count;

        // Don't know if needed to implement resize and shrink but did it anyways - örugglega flókanar en þetta þurfti að vera
        void resize() { 
            // TODO:: if queue if gets to large for the capacity, then resize it | O(n)
            int increase = capacity*2;
            T* temp = new T[increase];
            for (int i = 0; i < count; i++) {
                temp[i] = data[(head + i) % capacity];
            }
            delete[] data;
            data = temp;
            capacity = increase;
            head = 0;
        }

        void shrink() {
            // TODO:: Decrease the capacity | O(n)
            int decrease = capacity/2;
            if (decrease < 2) {
                return;
            }
            T* temp = new T[decrease];
            for (int i= 0; i < count; i++) {
                temp[i] = data[(head + i) % capacity];
            }
            delete[] data;
            data = temp;
            capacity = decrease;
            head = 0;
        }

    public:
        Dequeue() : capacity(2), head(0), count(0)  { // constructer.
            data = new T[capacity];
        }

        Dequeue(const Dequeue &other) : capacity(other.capacity), head(other.head), count(other.count) { // copy constructer.
             // copy construction - must properly copy the contents of another instance of the data structure | O(n)
            data = new T[capacity];
            for (int i = 0; i < count; i++) {
                data[i] = other.data[(other.head + i) % other.capacity];
            }
            head = 0;
        }

        Dequeue& operator=(const Dequeue& other) {
            // Assignment constructer | O(n)
            if (this == &other) {
                return *this; // self-assignment
            }
            delete[] data; // free existing memory

            capacity = other.capacity;
            count = other.count;

            // allocate new memory
            data = new T[capacity];
            for (int i = 0; i < count; i++) {
                data[i] = other.data[(other.head + i) % other.capacity];
            }
            head = 0;
            return *this;
        }

        ~Dequeue() {
            delete[] data;
        }

        void push_front(T x) {
            // TODO:: must insert an element to the front of the deque | O(1)
            if (count == capacity) {
                resize();
            }
            if (count == 0) {
                data[head] = x;
            } else {
                head = (head-1 + capacity) % capacity;
                data[head] = x;
            }
            count++;
        }

        void push_back(T x) {
            // TODO:: must insert an element to the back of the deque | O(1)
            if (count == capacity) {
                resize();
            }
            int rear = (head + count) % capacity;
            data[rear] = x;
            count++;
        }

        void pop_front() {
            // TODO:: must remove the front element off of the deque | O(1)
            if (count == 0) {
                return;
            }
            head = (head + 1) % capacity;
            count--;

            if (capacity > 2 && count < capacity/2) {
                shrink();
            }
        }

        void pop_back() {
            // TODO:: must remove the back element off of the deque | O(1)
            if (count == 0) {
                return;
            }
            count--;

            if (capacity > 2 && count < capacity/2) {
                shrink();
            }
        }

        T front() {
            // TODO:: must provide access to the front element of the deque | O(1)
            if (count == 0) {
                return T();
            }
            return data[head];
        }

        T back() {
            // TODO:: must provide access to the back element of the deque | O(1)
            if (count == 0) {
                return T();
            }
            int rear = (head + count-1) % capacity;
            return data[rear];
        }

        int size() {
            // get size | O(1)
            return count;
        }

        // This for debugging 
        void getAll() { // O(n)
            for (int i = 0; i < count; i++) {
                std::cout << data[(head + i) % capacity] << " ";
            }
            std::cout << std::endl;
        }

        void debugging() { // Just a debugging function
            std::cout << "Capacity: " << capacity << std::endl;
            std::cout << "Size: " << count << std::endl;
            std::cout << "Head: " << head << std::endl;
            if (count > 0) {
                std::cout << "Head value: " << data[head] << std::endl;
            } else {
                std::cout << "Deque is empty — no head/rear value" << std::endl;
            }
            getAll();
        }

};

#endif