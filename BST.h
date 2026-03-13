#ifndef BST_H
#define BST_H

#include "BTNode.h"
#include <string>

template <typename T>
class BST {
public:
    BST();

    //Implement these functions
    ~BST();
    BST(const BST<T>& other);
    bool find_target(const T& val) const;
    int get_height() const;
   
    bool empty() const;
    void insert(const T& val);
    void preorder() const;
    void inorder() const;
    void postorder() const;
    void print() const;
    const T& get_min() const; //returns the minimum value in BST
    BTNode<T>* search(const T& val) const; //Searches for a value
    BTNode<T>* search_parent(const T& val); //Searches for a parent of value
    void delete_node(const T& val);
private:
    BTNode<T>* root;
    void preorder(BTNode<T>* node) const;
    void inorder(BTNode<T>* node) const;
    void postorder(BTNode<T>* node) const;
    void print(const std::string& prefix, const BTNode<T>* node, bool isRight) const;

    void delete_leaf(BTNode<T>* child, BTNode<T>* parent);
    void delete_one_child(BTNode<T>* child, BTNode<T>* parent);
    void delete_two_children(BTNode<T>* node);

    const T& get_min(BTNode<T>* node) const;
    int get_height(BTNode<T>* node) const;
    bool find_target(BTNode<T>* node, const T& target) const;
    BTNode<T>* copy_tree(const BTNode<T>* node) const;

};

#endif
