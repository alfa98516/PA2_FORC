#ifndef DEFAULT_HASHER
#define DEFAULT_HASHER
#include <cstdio>
template <typename K>
struct Default_Hash {
    const size_t operator()(const K& key) const {
        // quite literally the java hash function (it works fine).
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&key);
        size_t hash = 0;
        for (size_t i = 0; i < sizeof(K); ++i)
            hash = hash * 31 + bytes[i];
        return hash;
    }
};
#endif

#ifndef HASHMAP
#define HASHMAP
#include "dynamic_array.hpp"
template <typename K, typename V, typename Hash = Default_Hash<K> >
class HashMap {

    class Node {
      public
          : // everything is just nicer public, the user wont ever see a node anyway
        V val;
        K key;
        Node* next;

        Node() { next = NULL; }

        Node(K _key, V _val) : val(_val), key(_key), next(NULL) {}

        Node(K _key, V _val, Node* _next) : val(_val), key(_key), next(_next) {}
    };

    class Bucket {
      public: // again, user wont be able to touch this, so just nicer to keep it
              // public
        Node* tail;
        Node* head;

        Bucket() : tail(NULL), head(NULL) {}

        Bucket(Node* _tail, Node* _head) : tail(_tail), head(_head) {}

        Bucket(const Bucket& other) : head(NULL), tail(NULL) {
            Node* current = other.head;
            Node* prev = NULL;
            while (current) {
                Node* newNode = new Node(current->key, current->val);
                if (!head) head = newNode;
                if (prev) prev->next = newNode;
                prev = newNode;
                current = current->next;
            }
            tail = prev;
        }

        /**
         * @brief this is NOT a user friendly insert function, but I AM the user and
         * i DONT CARE.
         * @param key: the key im inserting
         * @param val: the value im inserting
         */
        void insert(K key, V val) {
            if (contains(key)) return;
            Node* newNode = new Node(key, val);
            newNode->next = head; // opted for doing insert at front, as this is a
                                  // very basic linked list.
            head = newNode;
            if (tail == NULL)
                tail = newNode;
        }

        const size_t size() const {
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

                if (node->key == key)
                    return true;
                node = node->next;
            }
            return false;
        }

        const V find(K key) const {
            Node* node = head;
            while (node != NULL) {
                if (node->key == key) {
                    return node->val;
                }
                node = node->next;
            }
            return V();
        }

        void remove(K key) {
            // Handle head removal
            if (head && head->key == key) {
                Node* temp = head;
                head = head->next;
                if (!head) tail = NULL;
                delete temp;
                return;
            }
            // Find the node before the one to delete
            Node* prev = head;
            while (prev && prev->next) {
                if (prev->next->key == key) {
                    Node* toDelete = prev->next;
                    prev->next = toDelete->next;
                    if (toDelete == tail) tail = prev;
                    delete toDelete;
                    return;
                }
                prev = prev->next;
            }
        }
        void update(K key, V val) {
            Node* node = findNode(key);
            if (node != NULL)
                node->val = val;
        }

        void delNode(Node* node) {
            if (node == NULL)
                return;
            delNode(node->next);
            delete node;
        }

        ~Bucket() { delNode(head); }

      private:
        Node* findNode(K key) {
            Node* node = head;
            while (node != NULL) {
                if (node->key == key)
                    return node;
                node = node->next;
            }
            return NULL;
        }
    };

    Dynamic_Vector<Bucket> buckets; // yyaaayy
    size_t capacity;
    Hash hasher;

    void initVector(size_t _capacity) {
        for (size_t i = 0; i < _capacity; ++i) {
            buckets.append(Bucket());
        }
    }

    void rebuild() {

        size_t newCapacity = capacity * 2;
        Dynamic_Vector<Bucket> newBucketVector =
            Dynamic_Vector<Bucket>(newCapacity);

        for (size_t i = 0; i < capacity; ++i) {
            Node* node = buckets[i].head;
            while (node != NULL) {
                size_t hashed = hash(node->key) % newCapacity;
                newBucketVector[hashed].insert(node->key, node->val);
                node = node->next;
            }
        }

        capacity = newCapacity; // no need to delete the old one, the dynamic array takes care of it
        buckets = newBucketVector;
    }

    const size_t hash(const K& key) const { return hasher(key); }

  public:
    HashMap()
        : capacity(32) { // i dont really know what a smart starting size for a
                         // HashMap is.
        initVector(capacity);
    }

    HashMap(const HashMap& other) : capacity(other.capacity), hasher(other.hasher) {
        initVector(capacity);
        for (size_t i = 0; i < other.capacity; ++i) {
            Node* node = other.buckets[i].head;
            while (node) {
                insert(node->key, node->val);
                node = node->next;
            }
        }
    }

    HashMap& operator=(const HashMap& other) {
        if (this == &other) return *this;

        // Clear existing data by creating a new hashmap and swapping
        capacity = other.capacity;
        hasher = other.hasher;
        buckets = Dynamic_Vector<Bucket>(); // Reset to empty
        initVector(capacity);

        // Copy all elements
        for (size_t i = 0; i < other.capacity; ++i) {
            Node* node = other.buckets[i].head;
            while (node) {
                insert(node->key, node->val);
                node = node->next;
            }
        }

        return *this;
    }

    void insert(K key, V val) {
        if (size() > capacity * 0.75)
            rebuild();
        size_t idx = hash(key) % capacity;
        buckets[idx].insert(key, val);
    }

    const Dynamic_Vector<Bucket>& getBuckets() const {
        return buckets;
    }

    const size_t size() const {
        size_t length = 0;
        for (size_t i = 0; i < buckets.getCapacity(); ++i) {
            if (buckets[i].head != NULL) {
                length += buckets[i].size();
            }
        }
        return length;
    }

    const size_t len() const { return buckets.len(); }

    void remove(K key) {
        size_t idx = hash(key) % capacity;
        buckets[idx].remove(key);
    }

    void update(K key, V val) {
        size_t idx = hash(key) % capacity;
        buckets[idx].update(key, val);
    }

    const V find(K key) const {
        size_t idx = hash(key) % capacity;
        return buckets[idx].find(key);
    }
    bool contains(K key) {
        size_t idx = hash(key) % capacity;
        return buckets[idx].contains(key);
    }
};
#endif
