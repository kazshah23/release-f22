/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirrorHelper(root);

    
}

    template <typename T>
void BinaryTree<T>::mirrorHelper(Node* node)
{
    if (node == nullptr) {
        return;
    }
    mirrorHelper(node -> left);
    mirrorHelper(node -> right);

    std::swap(node -> left, node -> right);

    
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    std::stack<Node*> s;
    Node * curr = root;
    std::vector<T> elem;
    while (curr != nullptr || !(s.empty())) {
        while (curr) {
            s.push(curr);
            curr = curr -> left;
        }
        curr = s.top();
        s.pop();
        elem.push_back(curr -> elem);
        curr = curr -> right;
    }

    for (unsigned i = 0; i < elem.size() - 1; i++) {
        if (elem[i] > elem[i + 1]) {
            return false;
        }
    }
    return true;
}
template <typename T>
bool BinaryTree<T>::orderHelper(Node* node) const
{ 
    if (node == nullptr) {
        return true;
    }

    orderHelper(node -> left);
    if (node -> left < node && node < node -> right) {
        return true;
    }
    orderHelper(node -> right);

    return false;

}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const{
  if (root->left == nullptr && root-> right == nullptr) {
        return true;
    }
    std::vector<T> curr;
    inorderTraversal(root, curr);
  for (unsigned i = 0; i < curr.size(); ++i) {

    for (unsigned i = 0; i < curr.size() - 1; ++i) {
        if (curr[i] > curr[i+1]) {
            return false;
        }
    }
    }
        return true;
}  


template <typename T>
    std::vector<T> BinaryTree<T>::inorderTraversal(Node* r, std::vector<T>& vect) const {
        //std::vector<T>  ans;
        if(r == nullptr) { return vect;}
       
        inorderTraversal(r->left, vect);
        vect.push_back(r->elem);
        inorderTraversal(r->right, vect);
        return vect; 
    }