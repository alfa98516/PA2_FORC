#include <iostream>
#include "node.hpp"
#include "dll.hpp"

int main() {
    Dll<int> lists[10];
    Node<int>* cursors[10];
    
    // Initialize
    for (int i = 0; i < 10; i++) {
        cursors[i] = lists[i].back();
    }
    
    // Build list 0
    cursors[0] = lists[0].insert(cursors[0], 10);
    cursors[0] = lists[0].insert(cursors[0], 20);
    cursors[0] = lists[0].insert(cursors[0], 30);
    
    std::cout << "List 0 size: " << lists[0].size() << std::endl;
    
    // Copy to list 1
    lists[1] = lists[0];
    cursors[1] = lists[1].back();
    std::cout << "List 1 size after copy: " << lists[1].size() << std::endl;
    
    // Erase from list 1
    cursors[1] = lists[1].predecessor(cursors[1]);
    std::cout << "Erasing node with data: " << cursors[1]->data << std::endl;
    cursors[1] = lists[1].erase(cursors[1]);
    std::cout << "List 1 size after erase: " << lists[1].size() << std::endl;
    
    // Copy list 1 (modified) back to list 0
    lists[0] = lists[1];
    std::cout << "List 0 size after reassignment: " << lists[0].size() << std::endl;
    
    // Try using list 2
    lists[2] = lists[0];
    cursors[2] = lists[2].front();
    if (cursors[2]) {
        std::cout << "List 2 front data: " << cursors[2]->data << std::endl;
        cursors[2] = lists[2].successor(cursors[2]);
        if (cursors[2]) {
            std::cout << "List 2 next data: " << cursors[2]->data << std::endl;
        }
    }
    
    std::cout << "Program ending" << std::endl;
    return 0;
}