///////////////////////////////////////////////////////////////
// Name: Kassidie Sheets
// Filename: AVL_countGreaterNode.cpp
// Course: Data Structures  COP3415
// Last Modification: 4/11/2024
//////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

// AVL tree node
struct Node {
    int value;
    Node* left, * right;
    int height;
};

//Get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
};

// Get the height of the tree
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
};

// Get the balance factor of the node
int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
};

// Right rotate the subtree 
Node* rightRotate(Node* oldroot) {
    //Store original left and right nodes
    Node* othernode = oldroot->right;
    Node* newroot = oldroot->left;

    //Make the old left node into the new root
    newroot->right = oldroot;
    oldroot->left = othernode;

    //Update Heights
    newroot->height = max(height(newroot->left), height(newroot->right)) + 1;
    oldroot->height = max(height(oldroot->left), height(oldroot->right)) + 1;

    return newroot;
};

// Left rotate the subtree
Node* leftRotate(Node* oldroot) {
    Node* newroot = oldroot->right;
    Node* othernode = oldroot->left;

    newroot->left = oldroot;
    oldroot->right = othernode;

    newroot->height = max(height(newroot->left), height(newroot->right)) + 1;
    oldroot->height = max(height(newroot->left), height(newroot->right)) + 1;


    return newroot;
};

//Utility function to create a new node
Node* newNode(int value) {
    Node* root = new Node();
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    root->height = 1;
    return root;
};

// Insert a node into the AVL tree
Node* insert(Node* root, int value) {
    if (root == NULL)
        return (newNode(value));

    if (value > root->value)
        root->right = insert(root->right, value);
    else if (value < root->value)
        root->left = insert(root->left, value);
    else
        return root;

    //Update height
    root->height = 1 + max(height(root->left), height(root->right));

    //Get Balance Factor
    int balance = getBalance(root);

    if ((balance > 1) && (value < root->left->value)) //LL
        return rightRotate(root);
    if ((balance < -1) && (value > root->right->value)) //RR
        return leftRotate(root);
    if ((balance > 1) && (value > root->left->value)) { //LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if ((balance < -1) && (value < root->right->value)) { //RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
};

// Function to count nodes greater than a given value
int countGreaterNodes(Node* node, int value) {
    if (node == NULL)
        return 0;
    if (node->value > value) {
        return countGreaterNodes(node->right, value) + countGreaterNodes(node->left, value) + 1;
    }
    else if (node->value <= value) {
        return countGreaterNodes(node->right, value);
    }
};

//Driver
int main() {
    Node* root = nullptr;
    Node* node = nullptr;

    // Construct AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 30);

    // Count nodes greater than 15
    int key = 15;
    cout << "nums = [10,20,5,15,30]" << endl;
    cout << "Number of nodes greater than " << key << ":" << countGreaterNodes(root, 15) << endl;
    cout << endl;

    //Construct AVL tree
    node = insert(node, 25);
    node = insert(node, 15);
    node = insert(node, 35);
    node = insert(node, 10);
    node = insert(node, 20);
    node = insert(node, 30);
    node = insert(node, 40);

    cout << "nums = [25,15,35,10,20,30,40]" << endl;
    cout << "Number of nodes greater than " << key << ":" << countGreaterNodes(node, 15) << endl;

    return 0;
};



