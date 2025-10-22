#pragma once

#include <iostream>

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

void delete_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

TreeNode* insert_node(TreeNode* root, int value) {
    TreeNode* new_node = new TreeNode(value);
    if (!root) {
        root = new_node;
        return root;
    }
    if (value > root->value) {
        root->right = insert_node(root->right, value);
    }
    else {
        root->left = insert_node(root->left, value);
    }
    return root;
}

void print_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    print_tree(root->left);
    std::cout << root->value << ' ';
    print_tree(root->right);
}

TreeNode* maximum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->right) {
        current = current->right;
    }
    return current;
}

TreeNode* minimum_node(TreeNode* root) {
    TreeNode* current = root;
    while (current->left && current->left) {
        current = current->left;
    }
    return current;
}

bool isFound(TreeNode* root, int value) {
    if (!root) {
        return false;
    }
    if (value > root->value) {
        return isFound(root->right, value);
    }
    if (value < root->value) {
        return isFound(root->left, value);
    }
    return true;
}

TreeNode* delete_node_by_value(TreeNode* root, int value) {
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
