#include <iostream>

#include "DSWTree.h"


// ========================= //
//           MAIN            //
// ========================= //
int main() {
        // You can test using this main.

    std::cout << "=========Default constructor/Print=========" << std::endl;

    std::cout << "-> Creating a DSW tree with default constructor." << std::endl;

    DSWTree<int> tree;
    

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);
    tree.printPretty();






    return 0;
}