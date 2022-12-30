#include <iostream>

#include "src/BinarySearchTree.h"

template<typename T>
void print_tree(const BinarySearchTree<T>& bst) {

    std::cout
            << "\n6: " << bst.contains(6)
            << "\n5: " << bst.contains(5)
            << "\n4: " << bst.contains(4)
            << "\n3: " << bst.contains(3)
            << "\n2: " << bst.contains(2)
            << "\n1: " << bst.contains(1)
            << "\n\n"
            ;
}

int main() {
    auto bst = BinarySearchTree<int>{};

    bst.add(4, 6, 2, 5, 3);

    print_tree(bst);

    bst.remove(4);

    print_tree(bst);

    return 0;
}
