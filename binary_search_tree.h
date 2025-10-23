#include <vector>

using namespace std;



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
    void inorder_traversal(TreeNode* root, vector<int>& output);
    void preorder_traversal(TreeNode* root, vector<int>& output);
    void postorder_traversal(TreeNode* root, vector<int>& output);
    TreeNode* maximum_node(TreeNode* root);
    TreeNode* minimum_node(TreeNode* root);
    bool isFound(TreeNode* root, int value);
    TreeNode* delete_node_by_value(TreeNode* root, int value);
    vector<int> get_tree_data(TreeNode* root);
};

inline void BinarySearchTree::delete_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
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

inline BinarySearchTree::TreeNode* BinarySearchTree::delete_node_by_value(TreeNode* root, int value) {
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

inline void BinarySearchTree::inorder_traversal(TreeNode* root, vector<int>& output) {
    if (!root) {
        return;
    }
    inorder_traversal(root->left, output);
    output.push_back(root->value);
    inorder_traversal(root->right, output);
}

inline void BinarySearchTree::preorder_traversal(TreeNode* root, vector<int>& output) {
    if (!root) {
        return;
    }
    output.push_back(root->value);
    preorder_traversal(root->left, output);
    preorder_traversal(root->right, output);
}

inline void BinarySearchTree::postorder_traversal(TreeNode* root, vector<int>& output) {
    if (!root) {
        return;
    }
    postorder_traversal(root->left, output);
    postorder_traversal(root->right, output);
    output.push_back(root->value);
}

inline vector<int> BinarySearchTree::get_tree_data(TreeNode* root) {
    vector<int> output;
    inorder_traversal(root, output);
    return output;
}