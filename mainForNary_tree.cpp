#include <iostream>
#include "Nary_tree.hpp"

int main() {
    Nary_tree Tree("/3");
    Tree.addChild(Tree.root, "/2");
    Tree.addChild(Tree.root, "/1");
    Tree.addChild(Tree.root->children[0], "/5");
    Tree.addChild(Tree.root->children[0], "/6");
    Tree.addChild(Tree.root->children[0], "/7"); // 
    Tree.addChild(Tree.root->children[1], "/5");
    Tree.addChild(Tree.root->children[1], "/6");
    Tree.addChild(Tree.root->children[1], "/7");
    Tree.Print();
    Tree.Remove(Tree.root->children[0], 2);
    std::cout << std::endl << "\n\n\n\n\n";
    Tree.Print();
    std::cout << std::endl << "\n\n\n\n\n";
    std::string finding = "/5";
    std::cout << Tree.find(Tree.root, finding);
    return 0;
}