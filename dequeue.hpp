#ifndef DEQUEUE2_HPP
#define DEQUEUE2_HPP

template <typename T>
class Dequeue {
    private:
        T* data;
        int capacity;
        int head;
        int rear;
        int count;

        // Don't know if needed to implement resize and shrink but did it anyways
        void resize() { 
            // TODO:: if queue if gets to large for the capacity, then resize it.
            int increase = capacity*2;
            T* temp = new T[increase];
            for (int i = 0; i < count; i++) {
                temp[i] = data[(head + i) % capacity];
            }
            delete[] data;
            data = temp;
            capacity = increase;
            head = 0;
            rear = count - 1;
        }

        void shrink() {
            // TODO:: Decrease the capacity
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
            rear = count - 1;
        }

    public:
        Dequeue() : capacity(2), head(0), rear(0), count(0)  { // constructer.
            data = new T[capacity];
        }

        Dequeue(const Dequeue &copy) : capacity(copy.capacity), head(copy.head), rear(copy.rear), count(copy.count) { // copy constructer.
             // Assignment and copy construction - must properly copy the contents of another instance of the data structure.
            data = new T[capacity];
            for (int i = 0; i < capacity; i++) {
                data[i] = copy.data[i];
            }
        }

        ~Dequeue() {
            delete[] data;
        }

        void push_front(T x) {
            // TODO:: must insert an element to the front of the deque.
            if (count == capacity) {
                resize();
            }
            head = (head-1 + capacity) % capacity;
            data[head] = x;
            count++;
        }

        void push_back(T x) {
            // TODO:: must insert an element to the back of the deque.
            if (count == capacity) {
                resize();
            }
            rear = (head + count) % capacity;
            data[rear] = x;
            count++;
        }

        void pop_front() {
            // TODO:: must remove the front element off of the deque.
            if (count == 0) {
                std::cout << "Deque is empty" << std::endl;
                return;
            }
            head = (head + 1) % capacity;
            count--;

            if (capacity > 2 && count < capacity/2) {
                shrink();
            }
        }

        void pop_back() {
            // TODO:: must remove the back element off of the deque.
            if (count == 0) {
                std::cout << "Deque is empty" << std::endl;
                return;
            }
            count--;
            rear = (head + count -1) % capacity;

            if (capacity > 2 && count < capacity/2) {
                shrink();
            }
        }

        T front() {
            // TODO:: must provide access to the front element of the deque.
            if (count == 0) {
                std::cout << "Deque is empty" << std::endl;
                return -1;
            }
            return data[head];
        }

        T back() {
            // TODO:: must provide access to the back element of the deque.
            if (count == 0) {
                std::cout << "Deque is empty" << std::endl;
                return -1;
            }
            return data[rear];
        }

        int size() {
            return count;
        }

        // This for debugging 
        void getAll() {
            for (int i = 0; i < count; i++) {
                std::cout << data[(head + i) % capacity] << " ";
            }
            std::cout << std::endl;
        }

        void debugging() { // Just a debugging function
            std::cout << "Capacity: " << capacity << std::endl;
            std::cout << "Size: " << count << std::endl;
            std::cout << "Head: " << head << std::endl;
            std::cout << "Head value: " << data[head] << std::endl;
            std::cout << "Rear: " << rear << std::endl;
            std::cout << "Rear value: " << data[rear] << std::endl;
            getAll();
        }

};

#endif