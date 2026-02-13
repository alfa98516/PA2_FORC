#include <iostream>

#ifndef BST
#define BST
enum Color {RED,BLACK};

template<typename T>
void myswap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T, typename U>
struct bstNode{
    T key;
    T originalKey;
    U value;
    bstNode<T,U>* left;
    bstNode<T,U>* right;
    bstNode<T,U>* parent;
    Color color;
    int subtreeSize;

    bstNode(T key_data, U value_data){
        key = key_data;
        originalKey = key_data;
        value = value_data;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = RED;
        subtreeSize = 1;
    }

    bstNode(){
        key = T();
        originalKey = T();
        value = U();
        left = NULL;
        right = NULL;
        parent = NULL;
        color = RED;
        subtreeSize = 1;
    }
};

//Implementing a left-leaning red-black tree
template <typename T, typename U>
class LLRB {
    private:
        bstNode<T,U>* root;
        bstNode<T,U>* lastInserted;
        int treeSize;

        bstNode<T,U>* rotateLeft(bstNode<T,U>*& node) {
            bstNode<T,U>* child = node->right;

            node->right = child->left;
            if (node->right != NULL) node->right->parent = node;
            
            child->left = node;
            child->parent = node->parent;
            node->parent = child;

            child->color = node->color;
            node->color = RED;

            // set subtreeSize for node
            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;
            int rightSize = (node->right != NULL) ? node->right->subtreeSize : 0;
            node->subtreeSize = leftSize + rightSize +1;

            leftSize = (child->left != NULL) ? child->left->subtreeSize : 0;
            rightSize = (child->right != NULL) ? child->right->subtreeSize: 0;
            child->subtreeSize = leftSize + rightSize +1;

            return child;
        }

        bstNode<T,U>* rotateRight(bstNode<T,U>*& node){
            bstNode<T,U>* child = node->left;
            node->left = child->right;
            if (node->left != NULL) node->left->parent = node;
            
            child->right = node;
            child->parent = node->parent;
            node->parent = child;

            child->color = node->color;
            node->color = RED;

            // set subtreeSize for node
            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;
            int rightSize = (node->right != NULL) ? node->right->subtreeSize : 0;
            node->subtreeSize = leftSize + rightSize +1;

            leftSize = (child->left != NULL) ? child->left->subtreeSize : 0;
            rightSize = (child->right != NULL) ? child->right->subtreeSize: 0;
            child->subtreeSize = leftSize + rightSize +1;

            return child;
        }


        bstNode<T,U>* insertHelper(bstNode<T,U>* node, const T& key, const U& value, bstNode<T,U>* parent){
            //standard insert
            if (node == NULL) {
                bstNode<T,U>* newNode = new bstNode<T,U>(key, value);
                newNode->parent = parent;
                newNode->color = RED;
                lastInserted = newNode;
                treeSize++;
                return newNode;
            }

            //Ignore duplicates
            if (key == node->key) {
                lastInserted = node;
                return node;
            }

            // Recursive insertion
            if (key < node->key) {
                node->left = insertHelper(node->left, key, value, node);
            }
            else{
                node->right = insertHelper(node->right, key, value, node);
            }

            // fixup the LLRB (bottom up)
            node = fixup(node);

            // set subtreeSize for node
            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;
            int rightSize = (node->right != NULL) ? node->right->subtreeSize : 0;
            node->subtreeSize = leftSize + rightSize + 1;

            return node;
        }

        // Helper function to check if node is red
        bool isRed(bstNode<T,U>* node){
            if (node == NULL) return false;
            return node->color == RED;
        }

        // Flips color of node and children
        void flipColors(bstNode<T,U>* node) {
            node->color = (node->color == RED) ? BLACK : RED;
            if (node->left != NULL) {
                node->left->color = (node->left->color == RED) ? BLACK : RED;
            }
            if (node->right != NULL) {
                node->right->color = (node->right->color == RED) ? BLACK : RED;
            }
        }


        bstNode<T,U>* fixup(bstNode<T,U>* node){
            // Fix right-leaning red nodes.
            if (isRed(node->right) && !isRed(node->left)){
                node = rotateLeft(node);
            }

            // Fix if two reds in a row to the left.
            if (isRed(node->left) && isRed(node->left->left)){
                node = rotateRight(node);
            }

            // Fix if two childern red
            if (isRed(node->left) && isRed(node->right)){
                flipColors(node);
            }

            return node;
        }

        void swapData(bstNode<T,U>* u, bstNode<T,U>* v){
            myswap(u->key, v->key);
            myswap(u->originalKey, v->originalKey);
            myswap(u->value, v->value);
        }

        bstNode<T,U>* eraseHelper(bstNode<T,U>* node, const T& key, bool& deleted){
            if (node == NULL) return NULL;

            if (key < node->key){
                //Going left ensure we're not going into 2-node
                if (!isRed(node->left) && node->left != NULL && !isRed(node->left->left)) {
                    node = moveRedLeft(node);
                }
                node->left = eraseHelper(node->left, key, deleted);
            }

            else {
                // Lean right red links left before going right
                if (isRed(node->left)) {
                    node = rotateRight(node);
                }

                // Found node at bottom (no right child)
                if (key == node->key && node->right == NULL) {
                    // Update parent pointers
                    if (node->left != NULL) {
                        node->left->parent = node->parent;
                    }
                    delete node;
                    deleted = true;
                    return NULL;
                }

                // Going right ensure we're not going into a 2-node
                if (node->right != NULL && !isRed(node->right) && !isRed(node->right->left)) {
                    node = moveRedRight(node);
                }

                // Found node in middle of tree
                if (key == node->key) {
                    // Replace with successor (minimum of right subtree)
                    bstNode<T,U>* succ = findMin(node->right);
                    swapData(node,succ);
                    node->right = eraseHelper(node->right, key, deleted);
                }
                else {
                    node->right = eraseHelper(node->right, key, deleted);
                }
            }

            // Fix up on the way back
            node = fixup(node);

            // Update subtreeSize
            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;
            int rightSize = (node->right != NULL) ? node->right->subtreeSize : 0;
            node->subtreeSize = leftSize + rightSize + 1;

            return node;
        }

        bstNode<T,U>* moveRedLeft(bstNode<T,U>* node){
            // Assuming node is red and
            // node->left and node->left-left are black
            // make node->left or one of its children red

            flipColors(node);

            if (node->right != NULL && isRed(node->right->left)) {
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
                flipColors(node);
            }

            return node;
        }

        bstNode<T,U>* moveRedRight(bstNode<T,U>* node) {
            // Assuming node is red and
            // node->right and node->right-left are black
            // make node->right or one of its children red

            flipColors(node);

            if (node->left != NULL && isRed(node->left->left)) {
                node = rotateRight(node);
                flipColors(node);
            }

            return node;
        }

        // Finds smallest node
        bstNode<T,U>* findMin(bstNode<T,U>* node) const {
            if (node == NULL) return NULL;
            while (node->left != NULL) {
                node = node->left;
            }
            return node;
        }

        // Finds largest node
        bstNode<T,U>* findMax(bstNode<T,U>* node) const {
            if (node == NULL) return NULL;
            while (node->right != NULL) {
                node = node->right;
            }
            return node;
        }

        // erase the smallest node
        bstNode<T,U>* eraseMin(bstNode<T,U>* node, bool& deleted) {
            if (node->left == NULL) {
                if (node->right != NULL) {
                    node->right->parent = node->parent;
                }
                delete node;
                deleted = true;
                return node->right;
            }

            if (!isRed(node->left) && !isRed(node->left->left)) {
                node = moveRedLeft(node);
            }

            node->left = eraseMin(node->left, deleted);

            node = fixup(node);

            // Set subtreeSize
            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;
            int rightSize = (node->right != NULL) ? node->right->subtreeSize : 0;
            node->subtreeSize = leftSize + rightSize + 1;

            return node;
        }

        // destroy the tree recursively
        void destroyTree(bstNode<T,U>* node){
            if (node == NULL) return;

            // destroy left first
            destroyTree(node->left);
            // then right
            destroyTree(node->right);
            delete node;
        }

        // makes a copy of the tree
        bstNode<T,U>* copyTree(bstNode<T,U>* node, bstNode<T,U>* parent) {
            if (node == NULL) return NULL;

            bstNode<T,U>* newNode = new bstNode<T,U>(node->key, node->value);
            newNode->parent = parent;
            newNode->color = node->color;
            newNode->subtreeSize = node->subtreeSize;

            // first copy left
            newNode->left = copyTree(node->left, newNode);
            // then right
            newNode->right = copyTree(node->right, newNode);

            return newNode;
        }

        // Finds node with given key if exists
        bstNode<T,U>* findHelper(bstNode<T,U>* node, const T& key) const{
            if (node == NULL) return NULL;

            
            if (node->key < key) {
                // node must be to the right
                return findHelper(node->right, key);
            }

            else if (node->key > key) {
                // node must be to the left
                return findHelper(node->left, key);
            }

            else {
                // found!
                return node;
            }
        }

        // find the node with the smallest key greater or equal to given key.
        bstNode<T,U>* lowerBoundHelper(bstNode<T,U>* node, const T& key, bstNode<T,U>* candidate) const{
            if (node == NULL) return candidate;

            if (node->key >= key) {
                return lowerBoundHelper(node->left, key, node);
            }
            else {
                return lowerBoundHelper(node->right, key, candidate);
            }
        }

        // find the node with the smallest key strictly greater than the given key.
        bstNode<T,U>* upperBoundHelper(bstNode<T,U>* node, const T& key, bstNode<T,U>* candidate) const{
            if (node == NULL) return candidate;

            if (node->key > key){
                return upperBoundHelper(node->left, key, node);
            }
            else {
                return upperBoundHelper(node->right, key, candidate);
            }
        }

        // find the node from the given index in lef-to-right order.
        bstNode<T,U>* kElementHelper(bstNode<T,U>* node, int index) const {
            if (node == NULL) return NULL;

            int leftSize = (node->left != NULL) ? node->left->subtreeSize : 0;

            if (index < leftSize) {
                // Answer is to the left
                return kElementHelper(node->left, index);
            }
            else if (index == leftSize) {
                // found it!
                return node;
            }
            else {
                // Answer to the right
                // Subtract out left subtree and current node
                return kElementHelper(node->right, index - leftSize -1);
            }
        }
    public:
        LLRB(){
            root = NULL;
            lastInserted = NULL;
            treeSize = 0;
        }

        ~LLRB(){
            destroyTree(root);
        }

        LLRB(const LLRB<T,U>& other){
            root = NULL;
            lastInserted = NULL;
            treeSize = 0;

            if (other.root != NULL) {
                root = copyTree(other.root, NULL);
                treeSize = other.treeSize;
            }
        }

        LLRB<T,U>& operator=(const LLRB<T,U>&other) {
            if (this == &other) return *this;

            destroyTree(root);

            root = NULL;
            lastInserted = NULL;
            treeSize = 0;

            if (other.root != NULL) {
                root = copyTree(other.root, NULL);
                treeSize = other.treeSize;
            }

            return *this;
        }

        bstNode<T,U>* find(const T& key) const{
            return findHelper(root, key);
        }

        bstNode<T,U>* lowerBound(const T& key) const{
            return lowerBoundHelper(root, key, NULL);
        }

        bstNode<T,U>* upperBound(const T& key) const{
            return upperBoundHelper(root, key, NULL);
        }

        bstNode<T,U>* insert(const T& key, const U& value){
            root = insertHelper(root, key, value, NULL);
            root->color = BLACK; //Root always black
            return lastInserted;
        }

        // Made erase 
        void erase(T key){
            if (find(key) == NULL) return;
            if (root == NULL) return;

            bool deleted = false;

            if (root->left == NULL && root->right == NULL) {
                if (root->key == key) {
                    delete root;
                    root = NULL;
                    treeSize--;
                    return;
                }
            }

            if (!isRed(root->left) && !isRed(root->right)){
                root->color = RED;
            }

            root = eraseHelper(root, key, deleted);

            if (root != NULL) {
                root->color = BLACK;
                root->parent = NULL;
            }

            if (!deleted) {
                std::cout << "Key not deleted: " << key << std::endl;
            }
            if (deleted) treeSize--;
        }


        bstNode<T,U>* front() const{
            return findMin(root);
        }

        bstNode<T,U>* back() const{
            return findMax(root);
        }

        bstNode<T,U>* predecessor(bstNode<T,U>* cursor) const{
            if (cursor == NULL) return NULL;
            if (cursor->left != NULL) {
                return findMax(cursor->left);
            }

            bstNode<T,U>* node = cursor;
            bstNode<T,U>* parent = node->parent;

            while (parent != NULL && node == parent->left) {
                node = parent;
                parent = parent->parent;
            }

            return parent;
        }

        bstNode<T,U>* successor(bstNode<T,U>* cursor) const{
            if (cursor == NULL) return NULL;

            //If right path, find the minimun node in the right path
            if (cursor->right != NULL) {
                return findMin(cursor->right);
            }

            bstNode<T,U>* node = cursor;
            bstNode<T,U>* parent = node->parent;
            //If no right path, bubble up.
            while (parent != NULL && node == parent->right) {
                node = parent;
                parent = parent->parent;
            }

            return parent;
        }

        // Retun index of node in left-to-right order
        int rank(bstNode<T,U>* cursor) const{
            if (cursor == NULL) return 0;

            int rank = 0;

            //Add left subtree (nodes smaller that cursor)
            if (cursor->left != NULL) {
                rank += cursor->left->subtreeSize;
            }

            // Walk up the tree
            bstNode<T,U>* node = cursor;
            bstNode<T,U>* parent = node->parent;

            while (parent != NULL) {
                // If came from right, add the parent and its left subtree
                if (node == parent->right) {
                    rank += 1;
                    if (parent->left != NULL) {
                        rank += parent->left->subtreeSize;
                    }
                }

                // If we came from left, don't do anything
                node = parent;
                parent = parent->parent;
            }

            return rank;
        }

        bstNode<T,U>* kElement(int index) const{
            return kElementHelper(root,index);
        }

        int size() const{
            return treeSize;
        }

        void printInOrder(bstNode<T,U>* node) {
            if (node == NULL) return;
            printInOrder(node->left);
            std::cout << "(" << node->key << ", " << node->value << ") ";
            printInOrder(node->right);
        }

        bstNode<T,U>* getRoot(){
            return root;
        }
};

#endif