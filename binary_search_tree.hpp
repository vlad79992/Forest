#pragma once

#include <vector>
#include <stack>
#include <unordered_set>

//using namespace std; // нельзя писать using в заголовочных файлах!!!

class BinarySearchTree {
public:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int node_value) {
            value = node_value;
            left = nullptr;
            right = nullptr;
        }
    };
    void delete_tree(TreeNode* root);
    TreeNode* insert_node(TreeNode* root, int value);
    void inorder_traversal(TreeNode* root, std::vector<int>& output);
    void preorder_traversal(TreeNode* root, std::vector<int>& output);
    void postorder_traversal(TreeNode* root, std::vector<int>& output);
    TreeNode* maximum_node(TreeNode* root);
    TreeNode* minimum_node(TreeNode* root);
    bool isFound(TreeNode* root, int value);
    TreeNode* delete_node_by_value(TreeNode* root, int value);
    std::vector<int> get_tree_data(TreeNode* root);
};

inline void BinarySearchTree::delete_tree(TreeNode* root) {
    if (!root) return;

    std::stack<TreeNode*> stack;
    std::unordered_set<TreeNode*> visited;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* current = stack.top();
        bool is_leaf_or_children_visited =
            (!current->left || visited.count(current->left)) &&
            (!current->right || visited.count(current->right));

        if (is_leaf_or_children_visited) {
            stack.pop();
            delete current;
            visited.insert(current);
        }
        else {
            if (current->right && !visited.count(current->right)) {
                stack.push(current->right);
            }
            if (current->left && !visited.count(current->left)) {
                stack.push(current->left);
            }
        }
    }
}

inline BinarySearchTree::TreeNode* BinarySearchTree::insert_node(TreeNode* root, int value) {
    TreeNode* node = new TreeNode(value);
    if (!root) {
        return node;
    }
    TreeNode* current = root;
    TreeNode* parent = nullptr;
    while (current) {
        parent = current;
        if (value > current->value) {
            current = current->right;
        }
        else if (value < current->value) {
            current = current->left;
        }
        else {
            delete node;
            return root;
        }
    }
    if (value > parent->value) {
        parent->right = node;
    }
    else {
        parent->left = node;
    }
    return node;
}

inline BinarySearchTree::TreeNode* BinarySearchTree::maximum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->right) {
        current = current->right;
    }
    return current;
}

inline BinarySearchTree::TreeNode* BinarySearchTree::minimum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->left) {
        current = current->left;
    }
    return current;
}

inline bool BinarySearchTree::isFound(TreeNode* root, int value) {
    TreeNode* current = root;
    while (current) {
        if (value == current->value) {
            return true;
        }
        else if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

inline BinarySearchTree::TreeNode* BinarySearchTree::delete_node_by_value(TreeNode* root, int value) {
    if (!root) return nullptr;

    TreeNode* current = root;
    TreeNode* parent = nullptr;

    while (current && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!current) return root;

    if (!current->left) {
        TreeNode* new_child = current->right;
        if (!parent) {
            delete current;
            return new_child;
        }
        if (parent->left == current) {
            parent->left = new_child;
        }
        else {
            parent->right = new_child;
        }
        delete current;
        return root;
    }

    TreeNode* predecessor = current->left;
    TreeNode* pred_parent = current;

    while (predecessor->right) {
        pred_parent = predecessor;
        predecessor = predecessor->right;
    }

    current->value = predecessor->value;

    if (pred_parent == current) {
        pred_parent->left = predecessor->left;
    }
    else {
        pred_parent->right = predecessor->left;
    }
    delete predecessor;

    return root;
}

inline void BinarySearchTree::inorder_traversal(TreeNode* root, std::vector<int>& output) {
    std::stack<TreeNode*> stack;
    TreeNode* current = root;

    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        output.push_back(current->value);
        current = current->right;
    }
}

inline void BinarySearchTree::preorder_traversal(TreeNode* root, std::vector<int>& output) {
    if (!root) return;
    std::stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* current = stack.top();
        stack.pop();
        output.push_back(current->value);
        if (current->right) stack.push(current->right);
        if (current->left) stack.push(current->left);
    }
}

inline void BinarySearchTree::postorder_traversal(TreeNode* root, std::vector<int>& output) {
    if (!root) return;
    std::stack<TreeNode*> stack1, stack2;
    stack1.push(root);

    while (!stack1.empty()) {
        TreeNode* current = stack1.top();
        stack1.pop();
        stack2.push(current);

        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
    }

    while (!stack2.empty()) {
        output.push_back(stack2.top()->value);
        stack2.pop();
    }
}

inline std::vector<int> BinarySearchTree::get_tree_data(TreeNode* root) {
    std::vector<int> output;
    inorder_traversal(root, output);
    return output;
}