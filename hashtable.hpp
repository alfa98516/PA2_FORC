#ifndef HASHMAP
#define HASHMAP
#include "dynamic_array.hpp"
template <typename K, typename V>
class HashMap {

    class Node {
      public: // everything is just nicer public, the user wont ever see a node anyway
        V val;
        K key;
        Node* next;

        Node() { next = NULL; }

        Node(V _val, K _key) : val(_val), key(_key) {}

        Node(V _val, K _key, Node* _next) : val(_val), key(_key), next(_next) {}
    };

    class Bucket {
      public: // again, user wont be able to touch this, so just nicer to keep it public
        Node* tail;
        Node* head;

        Bucket() : tail(NULL), head(NULL) {}

        Bucket(Node* _tail, Node* _head) : tail(_tail), head(_head) {}

        /**
         * @brief this is NOT a user friendly insert function, but I AM the user and i DONT CARE.
         * @param key: the key im inserting
         * @param val: the value im inserting
         */
        void insert(K key, V val) {
            Node* newNode = Node(key, val);
            newNode->next = head; // opted for doing insert at front, as this is a very basic linked list.
            head = newNode;
            if (tail == NULL)
                tail = newNode;
        }

        size_t size() {
            Node* node = head;
            size_t length = 0;
            while (node != NULL) {
                length++;
                node = node->next;
            }
            return length;
        }

        bool contains(K key) {
            Node* node = head;
            while (node != NULL) {

                if (node->key == key) return true;
                node = node->next;
            }
            return false;
        }

        V find(K key) {
            Node* node = head;
            while (node != NULL) {
                if (node->key == key) {
                    return node->val;
                }
                node = node->next;
            }
            return NULL;
        }

      private:
        Node* findNode(K key) {
            Node* node = head;
            while (node != NULL) {
                if (node->key == key) return node;
                node = node->next;
            }
            return NULL;
        }
    };

    Dynamic_Vector<Bucket> bucket; // yyaaayy
    int capacity;

  public:
    HashMap<K, V>() : capacity(32) { // i dont really know what a smart starting size is for a HashMap is.
    }
};
#endif
