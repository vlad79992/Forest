#include <iostream>
#include "Nary_tree.hpp"

Nary_tree::Nary_tree(std::string data) {
    root = GetNewNode(data);
}

Nary_tree::~Nary_tree()
{
    clear(root);
}

Nary_tree::Node* Nary_tree::GetNewNode(std::string data)
{
    Node* newNode = new Node();
    newNode->data = data;
    nodes++;
    return newNode;
}

void Nary_tree::addChild(Node *node, std::string data)
{
    Node* newNode = GetNewNode(data);
    node->children.push_back(newNode);
}

Nary_tree::Node* Nary_tree::find(Node* nowNode, std::string data)
{
    if (nowNode->data == data) {
        return nowNode;
    }
    
    for (int i = 0; i < nowNode->children.size(); i++)
    {
        Node* result = find(nowNode->children[i], data);
        if (result != nullptr) {
            return result;
        }
    }
    
    return nullptr;
}
void Nary_tree::printTree(Node* node, const std::string& prefix, bool isLast)
{
    if (node == nullptr) return;
    
    std::cout << prefix;
    
    if (isLast) {
        std::cout << "└── ";
    } else {
        std::cout << "├── ";
    }
    
    std::cout << node->data << std::endl;
    
    std::string newPrefix = prefix + (isLast ? "    " : "│   ");
    
    for (size_t i = 0; i < node->children.size(); ++i) {
        bool lastChild = (i == node->children.size() - 1);
        printTree(node->children[i], newPrefix, lastChild);
    }
}

void Nary_tree::Print()
{
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    printTree(root);
}

void Nary_tree::clear(Node* node)
{
    if (node == nullptr) return;
    
    for (Node* child : node->children) {
        clear(child);
    }
    
    delete node;
}

void Nary_tree::Remove(Node* parent, int index) {
    if (parent == nullptr || index < 0 || index >= parent->children.size()) return;
    
    Node* childToRemove = parent->children[index];
    parent->children.erase(parent->children.begin() + index);
    clear(childToRemove);
    nodes--; 
}