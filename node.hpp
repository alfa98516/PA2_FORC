#ifndef NODE
#define NODE
template <typename T>
struct Node{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T value) : data(value), next(NULL), prev(NULL){}
    Node() : data(T()), next(NULL), prev(NULL){}
};
#endif