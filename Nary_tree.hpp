#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

class Nary_tree
{
private:
    struct Node
    {
        std::string data;
        std::vector<Node*> children;
    };
    
    void printTree(Node* node, const std::string& prefix = "", bool isLast = true);
    
public:
    Nary_tree(std::string data);
    int nodes = 0;
    Node* root;
    Node* GetNewNode(std::string data);
    Node* find(Node* nowNode, std::string data);
    void addChild(Node *node, std::string data);
    void Print();
    void Remove(Node *parent, int index);
    void clear(Node* node); // Добавим функцию для очистки памяти
    ~Nary_tree(); // Деструктор
};