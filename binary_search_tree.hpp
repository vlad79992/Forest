#pragma once

#include <vector>
#include <stack>

using namespace std;

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

class BinarySearchTree {
public:

};

inline void delete_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

inline TreeNode* insert_node(TreeNode* root, int value) {
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

inline TreeNode* maximum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->right) {
        current = current->right;
    }
    return current;
}

inline TreeNode* minimum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->left) {
        current = current->left;
    }
    return current;
}

inline bool isFound(TreeNode* root, int value) {
    if (!root) {
        return false;
    }
    TreeNode* current = root;
    while (current) {
        if (value > current->value) {
            current = current->right;
        }
        else if (value < current->value) {
            current = current->left;
        }
        else {
            return true;
        }
    }
    return false;
}

inline TreeNode* delete_node_by_value(TreeNode* root, int value) {
    if (!root) {
        return root;
    }
    if (value > root->value) {
        root->right = delete_node_by_value(root->right, value);
    }
    else if (value < root->value) {
        root->left = delete_node_by_value(root->left, value);
    }
    else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* min_node = minimum_node(root->right);
        root->value = min_node->value;
        root->right = delete_node_by_value(root->right, min_node->value);
    }
    return root;
}

inline void inorder_traversal(TreeNode* root, vector<int>& output) {
    stack<TreeNode*> stack;
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

inline void preorder_traversal(TreeNode* root, vector<int>& output) {
    if (!root) {
        return;
    }

    stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        output.push_back(node->value);
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
}

inline void postorder_traversal(TreeNode* root, vector<int>& output) {
    if (!root) {
        return;
    }
    postorder_traversal(root->left, output);
    postorder_traversal(root->right, output);
    output.push_back(root->value);
}

inline vector<int> get_tree_data(TreeNode* root) {
    vector<int> output;
    inorder_traversal(root, output);
    return output;
}