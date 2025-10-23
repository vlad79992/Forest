#pragma once
#include <iostream>
#include <stack>
#include <utility>

template<typename Key>
class Binary_tree {
private:
    struct Node {
        Key key;
        Node* left;
        Node* right;
        explicit Node(const Key& k) : key(k), left(nullptr), right(nullptr) {}
        explicit Node(Key&& k) : key(std::move(k)), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

public:
    Binary_tree() = default;
    ~Binary_tree() { clear(); }

    void insert(const Key& key);
    void insert(Key&& key);
    void erase(const Key& key);
    bool contains(const Key& key) const;
    void clear();
    void print_prefix(std::ostream& os = std::cout) const;
    void print_infix(std::ostream& os = std::cout) const;
    void print_postfix(std::ostream& os = std::cout) const;
};

template<typename Key>
void Binary_tree<Key>::insert(const Key& key) {
    if (!root) {
        root = new Node(key);
        return;
    }

    Node* current = root;
    while (true) {
        if (key < current->key) {
            if (!current->left) {
                current->left = new Node(key);
                return;
            }
            current = current->left;
        }
        else if (key > current->key) {
            if (!current->right) {
                current->right = new Node(key);
                return;
            }
            current = current->right;
        }
        else {
            return;
        }
    }
}

template<typename Key>
void Binary_tree<Key>::insert(Key&& key) {
    if (!root) {
        root = new Node(std::move(key));
        return;
    }

    Node* current = root;
    while (true) {
        if (key < current->key) {
            if (!current->left) {
                current->left = new Node(std::move(key));
                return;
            }
            current = current->left;
        }
        else if (key > current->key) {
            if (!current->right) {
                current->right = new Node(std::move(key));
                return;
            }
            current = current->right;
        }
        else {
            return;
        }
    }
}

template<typename Key>
void Binary_tree<Key>::erase(const Key& key) {
    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if (!current) return;

    if (current->left == nullptr && current->right == nullptr) {
        if (!parent) {
            root = nullptr;
        }
        else if (parent->left == current) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete current;
        return;
    }

    if (current->left == nullptr || current->right == nullptr) {
        Node* child = (current->left != nullptr) ? current->left : current->right;
        if (!parent) {
            root = child;
        }
        else if (parent->left == current) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        delete current;
        return;
    }

    Node* successor = current->right;
    Node* successor_parent = current;
    while (successor->left) {
        successor_parent = successor;
        successor = successor->left;
    }
    current->key = successor->key;

    if (successor_parent->left == successor) {
        successor_parent->left = successor->right;
    }
    else {
        successor_parent->right = successor->right;
    }
    delete successor;
}

template<typename Key>
bool Binary_tree<Key>::contains(const Key& key) const {
    Node* current = root;
    while (current) {
        if (key == current->key) return true;
        current = (key < current->key) ? current->left : current->right;
    }
    return false;
}

template<typename Key>
void Binary_tree<Key>::clear() {
    if (!root) return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        if (node->left) stack.push(node->left);
        if (node->right) stack.push(node->right);
        delete node;
    }
    root = nullptr;
}

template<typename Key>
void Binary_tree<Key>::print_prefix(std::ostream& os) const {
    if (!root) return;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        os << node->key << ' ';
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
}

template<typename Key>
void Binary_tree<Key>::print_infix(std::ostream& os) const {
    if (!root) return;
    std::stack<Node*> stack;
    Node* current = root;
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        os << current->key << ' ';
        current = current->right;
    }
}

template<typename Key>
void Binary_tree<Key>::print_postfix(std::ostream& os) const {
    if (!root) return;
    std::stack<Node*> stack1;
    std::stack<Node*> stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        Node* node = stack1.top();
        stack1.pop();
        stack2.push(node);
        if (node->left) stack1.push(node->left);
        if (node->right) stack1.push(node->right);
    }
    while (!stack2.empty()) {
        Node* node = stack2.top();
        stack2.pop();
        os << node->key << ' ';
    }
}