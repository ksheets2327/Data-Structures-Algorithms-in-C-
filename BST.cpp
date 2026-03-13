#include "BST.h"
#include <stack>
#include <iostream>

template <typename T>
BST<T>::BST() : root (nullptr) {}

template <typename T>
BST<T>::~BST() {
    while (!empty()){
        T min_val = get_min();
        delete_node(min_val);
    }
};

//Copy Constructor
template <typename T>
BST<T>::BST(const BST<T>& other) {
    root = copy_tree(other.root);
};

template <typename T>
BTNode<T>* BST<T>::copy_tree(const BTNode<T>* node) const {
    if (node == nullptr)
        return nullptr;
    BTNode<T>* new_node = new BTNode<T>(node->data);
    new_node->left = copy_tree(node->left);
    new_node->right = copy_tree(node->right);
    return new_node;
};

template <typename T>
BTNode<T>* BST<T>::search(const T& val) const {
    BTNode<T>* node = root;

    while (node) {
        if (node->data == val) {
            return node;
        }
        else if (val < node->data) {
            node = node->left;
        }
        else if (val > node->data) {
            node = node->right;
        }
    }

    return nullptr;
}

template <typename T>
bool BST<T>::find_target(const T& val) const {
    //Should return true if there exist two elements in the BST
    //such that their sum is equal to val, otherwise false
    return find_target(root, val);
};

template <typename T>
bool BST<T>::find_target(BTNode<T>* node, const T& target) const {
    if (node == nullptr)
        return false;
    T complement = target - node->data;
    if ((complement != node->data) && (search(complement) != nullptr))
        return true;
    return (find_target(node->left, target) || find_target(node->right, target));
};

template <typename T>
int BST<T>::get_height() const {
    //Returns the height of the Binary Tree
    return (get_height(root));
};

template <typename T>
int BST<T>::get_height(BTNode<T>* node) const {
    if (node == nullptr)
        return 0;
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    // Return the maximum height between the left and right subtrees
    // add 1 for the current node
    return 1 + std::max(left_height, right_height);
};


template <typename T>
bool BST<T>::empty() const {
    return (root == nullptr); 
}

template <typename T>
void BST<T>::insert(const T& val) {
    if (empty()) {
        root = new BTNode<T>(val);
    }
    else {
        BTNode<T>* cur = root, *prev = root;
        while (cur) {
            prev = cur;
            if (val < cur->data) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        //cur is nullptr, prev is a parent of cur
        if (val < prev->data) {
            prev->left = new BTNode<T>(val);
        }
        else {
            prev->right = new BTNode<T>(val);
        }
    }
}

template <typename T>
void BST<T>::preorder(BTNode<T>* node) const {
    if (!node) {
        return;
    }
    else {
        std::cout << node->data << ' ';
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename T>
void BST<T>::preorder() const {
    std::cout << "Preorder:\t\t[";
    preorder(root);
    std::cout << "]\n";
}

template <typename T>
void BST<T>::inorder(BTNode<T>* node) const {
    if (!node) {
        return;
    }
    else {
        inorder(node->left);
        std::cout << node->data << ' ';
        inorder(node->right);
    }
}

template <typename T>
void BST<T>::inorder() const {
    std::cout << "Inorder:\t\t[";
    inorder(root);
    std::cout << "]\n";
}

template <typename T>
void BST<T>::postorder(BTNode<T>* node) const {
    if (!node) {
        return;
    }
    else {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << ' ';
    }
}

template <typename T>
void BST<T>::postorder() const {
    std::cout << "Postorder:\t\t[";
    postorder(root);
    std::cout << "]\n";
}

template <typename T>
void BST<T>::print() const {
    print("", root, false);
}


template <typename T>
void BST<T>::print(const std::string& prefix, const BTNode<T>* node, bool isRight) const {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isRight ? "R--" : "L--");

        //print the value of the node
        std::cout << node->data << std::endl;

        //enter the next tree level
        print(prefix + "    ", node->right, true);
        print(prefix + "    ", node->left, false);
    }
}


template <typename T>
const T& BST<T>::get_min() const {
    if (empty()) {
        throw std::string("Empty tree\n");
    }
    else {
        BTNode<T>* cur = root;
        while (cur->left) {
            cur = cur->left;
        }
        return cur->data; 
    }
}


template <typename T>
const T& BST<T>::get_min(BTNode<T>* node) const {
    if (empty()) {
        throw std::string("Empty tree\n");
    }
    else {
        BTNode<T>* cur = node;
        while (cur->left) {
            cur = cur->left;
        }
        return cur->data; 
    }
}

template <typename T>
BTNode<T>* BST<T>::search_parent(const T& val) {
    if(root->data == val) { //root doesn't have a parent
        return nullptr;
    }
    
    BTNode<T>* node = root;
    BTNode<T>* prev = root;

    while (node) {
        if (node->data == val) {
            return prev;
        }
        else if (val < node->data) {
            prev = node;
            node = node->left;
        }
        else if (val > node->data) {
            prev = node;
            node = node->right;
        }
    }

    return nullptr;
}

template <typename T>
void BST<T>::delete_node(const T& val) {
    if (empty()) {
        return;
    }
    BTNode<T>* node = search(val);
    if (!node) {
        throw std::string("No node to delete\n");
    }
    BTNode<T>* parent = search_parent(val);

    if (!node->left && !node->right) { //leaf node
        delete_leaf(node, parent);
    }
    else if (!node->left || !node->right) { //one kid
        delete_one_child(node, parent);
    }
    else { //has two children
       delete_two_children(node); 
    }
}

template <typename T>
void BST<T>::delete_leaf(BTNode<T>* child, BTNode<T>* parent) {
    if (!child) {
        throw std::string ("Delete leaf: no node to delete\n");
    }
    if (!parent) {   //root which is a leaf node
        delete root;
        root = nullptr;
        return;
    }
    else if (parent->left == child) { //left kid
        parent->left = nullptr;
    }
    else if (parent->right == child) { //right kid
        parent->right = nullptr;
    }
    else {
        throw std::string("Delete leaf: impossible to delete\n");
    }

    delete child;
}

template <typename T>
void BST<T>::delete_one_child(BTNode<T>* child, BTNode<T>* parent) {
    if (!child) {
        throw std::string("Delete one child: no node to delete");
    }
    else if (child->left && child->right) {
        throw std::string("Delete one child: node has two children");
    }
    if (child == root) {
        BTNode<T>* to_delete = root;
        root = (root->left) ? root->left : root->right;
        delete to_delete;
        return;
    }

    if(child->right && !child->left) { //right kid
        if (parent->right == child) { //right child of a parent
            parent->right = child->right;
        }
        else if (parent->left == child) { //left child of a parent
            parent->left = child->right;
        }
    }
    else if (!child->right && child->left) {
        if (parent->right == child) { //right child of a parent
            parent->right = child->left;
        }
        else if (parent->left == child) { //left child of a parent
            parent->left = child->left;
        }
    }
    else {
        throw std::string("Delete one child: node has no children");
    }

    //release the memory
    delete child;
}

template <typename T>
void  BST<T>::delete_two_children(BTNode<T>* node) {
    if (!node) {
        throw std::string("Delete two children: no node to delete");
    }
    else if (!node->right || !node->left) {
        throw std::string("Delete two children: node has less than two children");
    }
    T min_node_value = get_min(node->right); 
    BTNode<T>* min_node = search(min_node_value);
    if (!min_node->left && !min_node->right) {
        delete_leaf(min_node, search_parent(min_node_value));
    }
    else if (!min_node->left || !min_node->right) {
        delete_one_child(min_node, search_parent(min_node_value));
    }
    node->data = min_node_value;
}

