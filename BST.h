// CSMC 341 - Spring 2020 - Project 3

// A balanced BST using array-based rebalancing and a user-provided
// imbalance function.

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <string>

// ********************************************
// Additional 'using' statements may be added.
// ********************************************

using std::string;
using std::cout;
using std::endl;

// Typedef for a balance function pointer.  A balance function returns
// true if the tree is **imbalanced** at a node.  This allows you to
// try different balance criteria.
typedef bool (*balfn_t)(int leftHeight, int rightHeight, int leftSize, int rightSize);

class BST { // Balanced BST class

public:
  
  class BNode{ // BST Node inner class
  public:
    BNode(string ch = "", int rank = -1, int height = 0, int size = 1);
    string _data;   // holds string data
    int _key;       // integer key value
    int _height;    // height of the node
    int _size;      // size of the subtree rooted at the node
    BNode* _right;  // right child pointer
    BNode* _left;   // left child pointer
  };

  //
  // Constructor, Copy Constructor, Assignment Operator, Destructor
  //

  // Constructor.  Must pass a pointer to a balanced function.
  BST(balfn_t imbalanced);
  
  // Copy constructor
  BST(const BST& rhs);

  // Assignment operator
  BST& operator=(const BST& rhs);

  // Destructor
  ~BST();                   

  //
  // Basic functions
  //
  
  // Insert (key, data) pair in the tree
  bool insert(string data, int key); 

  // Size of the tree (number of nodes)
  int size() const;

  // Height of the tree
  int height() const; 

  // Print the data using an inorder traversal; if verbose is 'true',
  // print the tree structure including sizes, heights, and
  // parentheses.
  void dump(bool verbose = false) const;
  
 private:
  BNode* _root;        // root of the tree
  balfn_t _imbalanced; // function to check for imbalance

  // ********************************************
  // Private function declarations go here!
  // ********************************************
  
  //-------------------------------------------------------------------------------    
  //help function for copy constructor
  void copyHelp(BNode* &copyTo, BNode* copyFrom){
    if (copyFrom == nullptr){
      copyTo = nullptr;
    }
    else{
      copyTo = new BNode();
      copyTo->_data = copyFrom->_data;
      copyTo->_key = copyFrom->_key;
      copyTo->_height = copyFrom->_height;
      copyTo->_size = copyFrom->_size;
      copyHelp(copyTo->_left, copyFrom->_left);
      copyHelp(copyTo->_right, copyFrom->_right);
    }
  }
  //-------------------------------------------------------------------------------
  //help function for destructor
  void destructHelp(BNode* node){
    if (node != nullptr){
      destructHelp(node->_right);
      destructHelp(node->_left);
      delete node;
    }
  }
  //-------------------------------------------------------------------------------
  //help function to determine sizes
  int getSize(BNode* ptr) const{
    int left = 0;
    int right = 0;
    if (ptr->_left != nullptr){
      left = getSize(ptr->_left);
    }
    if (ptr->_right != nullptr){
      right = getSize(ptr->_right);
    }
    return left + right + 1;
  }
  //-------------------------------------------------------------------------------  
  //help function to determine height
  int getHeight(BNode* ptr) const {
    if (!ptr){
      return 0;
    }
    int leftHeight = getHeight(ptr->_left);
    int rightHeight = getHeight(ptr->_right);
    return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
  }
  //-------------------------------------------------------------------------------  
  //heper for getHeight
  int finalHeight(BNode* ptr) const{
    int check = getHeight(ptr);
    return check - 1;
  }
  //-------------------------------------------------------------------------------  
  //help function for insertion
  void insertHelp(BNode* current, BNode* newNode){
    //added if
    if (current == nullptr){
      current = newNode;
      return;
    }
    
    if (newNode->_key < current->_key){
      if (current->_left == nullptr){
        current->_left = newNode;
      }
      else{
        insertHelp(current->_left, newNode);
      }
    }
    else if (newNode->_key > current->_key){
      if (current->_right == nullptr){
        current->_right = newNode;
      }
      else{
        insertHelp(current->_right, newNode);
      }
    }
    else{
      cout << "no duplicates!" << endl;
    }
  }
  //-------------------------------------------------------------------------------  
  //helper function to create sorted array
  int createArray(BNode* add, BNode* arr[], int count){
    if (add == nullptr){
      return count;
    }
    if (add->_left != nullptr){
      count = createArray(add->_left, arr, count);
    }    
    arr[count] = add;
    count++;
    if (add->_right != nullptr){
      count = createArray(add->_right, arr, count);
    }
    
    return count;
  }
  //-------------------------------------------------------------------------------  
  //helper function to create balanced BST using sorted array
  BNode* createBST(BNode* arr[], int start, int end){
    if (start > end){
      return nullptr;
    }
    int mid = ((start + end) / 2);
    BNode* root = arr[mid];
    //_root = arr[mid];
    root->_left = createBST(arr, start, mid - 1);
    root->_right = createBST(arr, mid + 1, end);
    return root;
  }
  //-------------------------------------------------------------------------------  
  //helper to print contents of tree
  void printHelp(BNode* ptr) const{
    if (ptr == nullptr){
      return;
    }
    printHelp(ptr->_left);
    cout << ptr->_data;
    printHelp(ptr->_right);
  }
  //-------------------------------------------------------------------------------  
  //helper to print when verbose == true
  void printVerbose(BNode* ptr) const{
    if (ptr == nullptr){
      return;
    }
    cout << "(";
    printVerbose(ptr->_left);
    cout << ptr->_data << ":" << finalHeight(ptr) << ":" << getSize(ptr);
    printVerbose(ptr->_right);
    cout << ")";
  }
};


#endif
