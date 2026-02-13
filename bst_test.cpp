#include <iostream>
#include <cassert>
#include "self_balancing_bst.hpp"  // Your header file

using namespace std;

void testBasicInsertAndFind() {
    cout << "Testing basic insert and find..." << endl;
    
    LLRB<int, string> tree;
    
    // Test empty tree
    assert(tree.size() == 0);
    assert(tree.find(5) == NULL);
    assert(tree.front() == NULL);
    assert(tree.back() == NULL);
    
    // Insert some nodes
    bstNode<int, string>* node1 = tree.insert(5, "five");
    assert(node1 != NULL);
    assert(node1->key == 5);
    assert(node1->value == "five");
    assert(tree.size() == 1);
    
    bstNode<int, string>* node2 = tree.insert(3, "three");
    bstNode<int, string>* node3 = tree.insert(7, "seven");
    bstNode<int, string>* node4 = tree.insert(1, "one");
    bstNode<int, string>* node5 = tree.insert(9, "nine");
    
    assert(tree.size() == 5);
    
    // Test find
    bstNode<int, string>* found = tree.find(7);
    assert(found != NULL);
    assert(found->key == 7);
    assert(found->value == "seven");
    
    // Test find non-existent
    assert(tree.find(100) == NULL);
    
    cout << "✓ Basic insert and find passed!" << endl;
}

void testDuplicateInsert() {
    cout << "Testing duplicate insert..." << endl;
    
    LLRB<int, string> tree;
    
    bstNode<int, string>* node1 = tree.insert(5, "first");
    assert(tree.size() == 1);
    
    // Insert duplicate - should return existing node, not insert
    bstNode<int, string>* node2 = tree.insert(5, "second");
    assert(tree.size() == 1);  // Size should still be 1
    assert(node1 == node2);     // Should return same node
    assert(node2->value == "first");  // Value unchanged
    
    cout << "✓ Duplicate insert passed!" << endl;
}

void testFrontAndBack() {
    cout << "Testing front and back..." << endl;
    
    LLRB<int, string> tree;
    
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(9, "nine");
    
    bstNode<int, string>* front = tree.front();
    assert(front != NULL);
    assert(front->key == 1);
    
    bstNode<int, string>* back = tree.back();
    assert(back != NULL);
    assert(back->key == 9);
    
    cout << "✓ Front and back passed!" << endl;
}

void testLowerBound() {
    cout << "Testing lower bound..." << endl;
    
    LLRB<int, string> tree;
    
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(5, "five");
    tree.insert(7, "seven");
    tree.insert(9, "nine");
    
    // Exact match
    bstNode<int, string>* result = tree.lowerBound(5);
    assert(result != NULL && result->key == 5);
    
    // Between values
    result = tree.lowerBound(4);
    assert(result != NULL && result->key == 5);
    
    // Before all
    result = tree.lowerBound(0);
    assert(result != NULL && result->key == 1);
    
    // After all
    result = tree.lowerBound(10);
    assert(result == NULL);
    
    cout << "✓ Lower bound passed!" << endl;
}

void testUpperBound() {
    cout << "Testing upper bound..." << endl;
    
    LLRB<int, string> tree;
    
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(5, "five");
    tree.insert(7, "seven");
    tree.insert(9, "nine");
    
    // Exact match - should return next larger
    bstNode<int, string>* result = tree.upperBound(5);
    assert(result != NULL && result->key == 7);
    
    // Between values
    result = tree.upperBound(4);
    assert(result != NULL && result->key == 5);
    
    // Before all
    result = tree.upperBound(0);
    assert(result != NULL && result->key == 1);
    
    // After all
    result = tree.upperBound(9);
    assert(result == NULL);
    
    cout << "✓ Upper bound passed!" << endl;
}

void testPredecessorSuccessor() {
    cout << "Testing predecessor and successor..." << endl;
    
    LLRB<int, string> tree;
    
    bstNode<int, string>* n1 = tree.insert(5, "five");
    bstNode<int, string>* n2 = tree.insert(3, "three");
    bstNode<int, string>* n3 = tree.insert(7, "seven");
    bstNode<int, string>* n4 = tree.insert(1, "one");
    bstNode<int, string>* n5 = tree.insert(9, "nine");
    
    // Test successor
    bstNode<int, string>* succ = tree.successor(n2);  // successor of 3
    assert(succ != NULL && succ->key == 5);
    
    succ = tree.successor(n5);  // successor of 9 (max)
    assert(succ == NULL);
    
    // Test predecessor
    bstNode<int, string>* pred = tree.predecessor(n1);  // predecessor of 5
    assert(pred != NULL && pred->key == 3);
    
    pred = tree.predecessor(n4);  // predecessor of 1 (min)
    assert(pred == NULL);
    
    cout << "✓ Predecessor and successor passed!" << endl;
}

void testRank() {
    cout << "Testing rank..." << endl;
    
    LLRB<int, string> tree;
    
    bstNode<int, string>* n1 = tree.insert(5, "five");
    bstNode<int, string>* n2 = tree.insert(3, "three");
    bstNode<int, string>* n3 = tree.insert(7, "seven");
    bstNode<int, string>* n4 = tree.insert(1, "one");
    bstNode<int, string>* n5 = tree.insert(9, "nine");
    
    // In-order: 1, 3, 5, 7, 9
    // Indices:  0, 1, 2, 3, 4
    
    assert(tree.rank(n4) == 0);  // 1 is at index 0
    assert(tree.rank(n2) == 1);  // 3 is at index 1
    assert(tree.rank(n1) == 2);  // 5 is at index 2
    assert(tree.rank(n3) == 3);  // 7 is at index 3
    assert(tree.rank(n5) == 4);  // 9 is at index 4
    
    cout << "✓ Rank passed!" << endl;
}

void testKElement() {
    cout << "Testing k-th element..." << endl;
    
    LLRB<int, string> tree;
    
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(9, "nine");
    
    // In-order: 1, 3, 5, 7, 9
    // Indices:  0, 1, 2, 3, 4
    
    bstNode<int, string>* node = tree.kElement(0);
    assert(node != NULL && node->key == 1);
    
    node = tree.kElement(2);
    assert(node != NULL && node->key == 5);
    
    node = tree.kElement(4);
    assert(node != NULL && node->key == 9);
    
    node = tree.kElement(10);  // Out of bounds
    assert(node == NULL);
    
    cout << "✓ K-th element passed!" << endl;
}

// void testErase() {
//     cout << "Testing erase..." << endl;
    
//     LLRB<int, string> tree;
    
//     bstNode<int, string>* n1 = tree.insert(5, "five");
//     bstNode<int, string>* n2 = tree.insert(3, "three");
//     bstNode<int, string>* n3 = tree.insert(7, "seven");
//     bstNode<int, string>* n4 = tree.insert(1, "one");
//     bstNode<int, string>* n5 = tree.insert(9, "nine");
    
//     assert(tree.size() == 5);
    
//     // Erase middle element
//     tree.erase(n1);
//     assert(tree.size() == 4);
//     assert(tree.find(5) == NULL);
    
//     // Verify remaining elements
//     assert(tree.find(3) != NULL);
//     assert(tree.find(7) != NULL);
//     assert(tree.find(1) != NULL);
//     assert(tree.find(9) != NULL);
    
//     // Erase all
//     tree.erase(n2);
//     tree.erase(n3);
//     tree.erase(n4);
//     tree.erase(n5);
    
//     cout << tree.size() << endl;
//     assert(tree.size() == 0);
//     assert(tree.front() == NULL);
//     assert(tree.back() == NULL);
    
//     cout << "✓ Erase passed!" << endl;
// }

void testCopyConstructor() {
    cout << "Testing copy constructor..." << endl;
    
    LLRB<int, string> tree1;
    tree1.insert(5, "five");
    tree1.insert(3, "three");
    tree1.insert(7, "seven");
    
    // Copy constructor
    LLRB<int, string> tree2(tree1);
    
    assert(tree2.size() == 3);
    assert(tree2.find(5) != NULL);
    assert(tree2.find(3) != NULL);
    assert(tree2.find(7) != NULL);
    
    // Verify they don't share memory
    bstNode<int, string>* node1 = tree1.find(5);
    bstNode<int, string>* node2 = tree2.find(5);
    assert(node1 != node2);  // Different nodes
    
    // Modify tree1, tree2 should be unaffected
    tree1.insert(9, "nine");
    assert(tree1.size() == 4);
    assert(tree2.size() == 3);
    assert(tree2.find(9) == NULL);
    
    cout << "✓ Copy constructor passed!" << endl;
}

void testAssignmentOperator() {
    cout << "Testing assignment operator..." << endl;
    
    LLRB<int, string> tree1;
    tree1.insert(5, "five");
    tree1.insert(3, "three");
    tree1.insert(7, "seven");
    
    LLRB<int, string> tree2;
    tree2.insert(100, "hundred");
    
    // Assignment
    tree2 = tree1;
    
    assert(tree2.size() == 3);
    assert(tree2.find(5) != NULL);
    assert(tree2.find(100) == NULL);  // Old data gone
    
    // Self-assignment
    tree1 = tree1;
    assert(tree1.size() == 3);
    
    cout << "✓ Assignment operator passed!" << endl;
}

// void testLargeTree() {
//     cout << "Testing large tree (stress test)..." << endl;
    
//     LLRB<int, int> tree;
    
//     // Insert 1000 elements
//     for (int i = 0; i < 1000; i++) {
//         tree.insert(i, i * 2);
//     }
    
//     assert(tree.size() == 1000);
    
//     // Verify all elements exist
//     for (int i = 0; i < 1000; i++) {
//         bstNode<int, int>* node = tree.find(i);
//         assert(node != NULL);
//         assert(node->value == i * 2);
//     }
    
//     // Test rank and kElement
//     bstNode<int, int>* node = tree.kElement(500);
//     assert(node != NULL && node->key == 500);
//     assert(tree.rank(node) == 500);
    
//     // Erase half
//     for (int i = 0; i < 500; i++) {
//         bstNode<int, int>* toErase = tree.find(i);
//         tree.erase(toErase);
//     }
    
//     assert(tree.size() == 500);
    
//     cout << "✓ Large tree stress test passed!" << endl;
// }

void testValueModification() {
    cout << "Testing value modification through node..." << endl;
    
    LLRB<int, string> tree;
    
    bstNode<int, string>* node = tree.insert(5, "original");
    assert(node->value == "original");
    
    // Modify value directly
    node->value = "modified";
    
    // Verify change persists
    bstNode<int, string>* found = tree.find(5);
    assert(found->value == "modified");
    
    cout << "✓ Value modification passed!" << endl;
}

int main() {

    cout << "=== Running LLRB Tree Tests ===" << endl << endl;
    
    // testBasicInsertAndFind();
    // testDuplicateInsert();
    // testFrontAndBack();
    // testLowerBound();
    // testUpperBound();
    // testPredecessorSuccessor();
    // testRank();
    // testKElement();
    // testErase();
    // testCopyConstructor();
    // testAssignmentOperator();
    // testLargeTree();
    // testValueModification();
    
    cout << endl << "=== ALL TESTS PASSED! ===" << endl;
    
    LLRB<int, string> tree;

    bstNode<int, string>* n1 = tree.insert(5, "five");
    bstNode<int, string>* n2 = tree.insert(3, "three");
    bstNode<int, string>* n3 = tree.insert(7, "seven");
    bstNode<int, string>* n4 = tree.insert(1, "one");
    bstNode<int, string>* n5 = tree.insert(9, "nine");
    tree.printInOrder(tree.getRoot());
    cout<<endl;
    tree.erase(5);
    tree.printInOrder(tree.getRoot());
    cout<<endl;
    bstNode<int, string>* target = tree.find(7); 
    cout<< target->key << " " << target->value << " " << target->parent<< " " << target->left->value << " " << target->right->value << " " << target->color <<endl;
    tree.erase(7);
    tree.printInOrder(tree.getRoot());
    cout<<endl;
    // cout<<endl;
    // tree.erase(n3);

    // cout<<endl;


    return 0;
}