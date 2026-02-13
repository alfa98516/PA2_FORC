#include "node.hpp"

#ifndef DLL
#define DLL
template <typename T>
class Dll{
    private:
        Node<T>* head;
        Node<T>* tail;
        int list_size;

    public:
        //base constructor for initializing an empty dll
        Dll(){
            head = new Node<T>();
            tail = new Node<T>();
            head->next = tail;
            tail->prev = head;
            list_size = 0;
        }

        //deconstructor to avoid memory leaks
        ~Dll(){
            Node<T>* temp = head;
            while (temp != NULL) {
                Node<T>* next = temp->next;
                delete temp;
                temp = next;
            }
        }
        //deep copy constructror
        Dll(const Dll& other){
            head = new Node<T>();
            tail = new Node<T>();
            head->next = tail;
            tail->prev = head;
            list_size = 0;

            Node<T>* otherNode = other.head->next;
            Node<T>* last = head;
            while (otherNode != other.tail) {
                //make new node with data of dll being copied
                Node<T>* newNode = new Node<T>(otherNode->data);

                last->next = newNode;
                newNode->prev = last;

                last = newNode;
                otherNode = otherNode->next;
                list_size++;
            }

            last->next = tail;
            tail->prev = last;
        }

        //assignment operator
        Dll<T>& operator=(const Dll<T>& other) {
            if (this == &other) return*this;

            Node<T>* temp = head;
            while (temp != NULL) {
                Node<T>* next = temp->next;
                delete temp;
                temp = next;
            }

            head = new Node<T>();
            tail = new Node<T>();
            head->next = tail;
            tail->prev = head;
            list_size = 0;

            Node<T>* otherNode = other.head->next;
            Node<T>* last = head;
            while (otherNode != other.tail) {
                Node<T>* newNode = new Node<T>(otherNode->data);

                last->next = newNode;
                newNode->prev = last;

                last = newNode;
                otherNode = otherNode->next;
                list_size++;
            }

            last->next = tail;
            tail->prev = last;

            return *this;
        }

        //Gets first node (not a sentinel node)
        Node<T>* front() const{
            if(head->next != tail){
                return head->next;
            }
            return NULL;
        }

        //Gets the last node (tail)
        Node<T>* back() const{
            return tail;
        }

        //Insert new node at provided cursor node, return the new node.
        Node<T>* insert(Node<T>* cursor, const T& data){
            if (cursor == NULL) return NULL;
            //Don't allow inserting at the head
            if (cursor == head) return NULL;

            Node<T>* newNode = new Node<T>(data);
            Node<T>* prevNode = cursor->prev;

            newNode->next = cursor;
            newNode->prev = prevNode;
            prevNode->next = newNode;
            cursor->prev = newNode;

            list_size++;

            return newNode;
        }

        //Remove the provided cursor node, return the node after provided cursor.
        Node<T>* erase(Node<T>* cursor){
            if (cursor == NULL) return NULL;
            if (cursor == head) return NULL;
            if (cursor == tail) return NULL;

            Node<T>* prevNode = cursor->prev;
            Node<T>* nextNode = cursor->next;

            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            delete cursor;

            list_size--;

            return nextNode;
        }

        //Gets the next node of the provided cursor node
        Node<T>* successor(Node<T>* cursor){
            if (cursor == NULL) return NULL;
            if (cursor == tail) return NULL;
            return cursor->next;
        }

        //Gets the previous node of the provided cursor node
        Node<T>* predecessor(Node<T>* cursor){
            if (cursor == NULL) return NULL;
            if (cursor == head) return NULL;
            if (cursor->prev == head) return NULL;
            return cursor->prev;
        }

        //Gets the amount of elements in the dll
        int size() const{
            return list_size;
        }
};

#endif