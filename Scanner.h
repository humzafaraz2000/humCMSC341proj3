// CMSC 341 - Spring 2020 - Project 3

#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BST.h"

// ********************************************
// Additional 'using' statements may be added.
// ********************************************

using std::string;
using std::pair;
using std::vector;

class Scanner { // tree of trees class

public:

  class SNode{
    friend Scanner;
  public:
    SNode(pair<int, int> bounds);
    ~SNode();
  private:
    pair<int, int> _bounds;
    BST* _root;
    SNode* _left;
    SNode* _right;
  };
/*
SNode:
- bounds (lower/upper)
- BST
- left/right nodes

BST:
- character
- weight
on an insert:
- find the node which bounds can contain the weight
- insert into that BST
- splay it
*/
  // Scanner constructor.  Pass in the number of lines in the image
  // (lines), the number of characers per line (range), and a vector
  // of strings containing the ASCII characters corresponding to the
  // indices in the scrambled image; e.g., chars[0] is the character
  // corresponding to "1", chars[1] corresponds to "2", etc.
  Scanner(int lines, int range, vector<string> chars);

  // Scanner destructor.  Must delete the splay tree and all of the
  // BSTs.
  ~Scanner();

  // Copy constructor.  Must make a deep copy and should function
  // correctly when the right-hand side is empty.
  Scanner(const Scanner& rhs);

  // Assignment operator.  Must make a deep copy, function correctly
  // when the right-hand side is empty, and protect against
  // self-assignment.
  Scanner& operator=(const Scanner& rhs);

  // Insert (character, weight) pair; splay the node in which the pair
  // is inserted.  Return 'false' if insertion fails, e.g. if the
  // weight is out-of-bounds; return 'true' otherwise.
  bool insert(int weight, int ch);
  
  // Load the data files (ASCII file and weights file) and insert data
  // into the data structure.  Returns 'false' if either file fails to
  // open; returns 'true' otherwise.
  bool loadFiles( string ascii, string weights );

  // Prints the unscrambled ASCII art.  Does an inorder traversal of
  // the splay tree, calling the BST dump() method for each BST.
  void dump() const;

  // Prints an inorder traversal of the splay tree, printing the
  // bounds (upper:lower) for each node in the splay tree.  Prints
  // parentheses to show the structure of the tree.
  void inorder() const;

private:
  SNode* _forest;         // pointer to splay tree root
  int _lines;             // number of lines in the image
  vector<string> _chars;  // characters used in the ascii art.
			  // _chars[0] corresponds to charcter "1",
			  // _chars[1] to character "2", etc.

  // Balance function.  Implements the height-balance propery of AVL
  // trees.  Returns true if the property is violated. The leftSize
  // and rightSize arguments are not used.  Passed to the BST
  // constructor.
  static bool heightImbalance(int leftHeight, int rightHeight, int leftSize, int rightSize);

  // *************************************************
  // Additional private function declarations go here!
  // *************************************************
  
  //helper for copy constructor
  void copyScanHelp(SNode* &copyTo, SNode* copyFrom){
    if (copyFrom == nullptr){
      copyTo == nullptr;
    }
    else{
      int bound1 = copyFrom->_bounds.first;
      int bound2 = copyFrom->_bounds.second;
      pair<int,int> bounds(bound1, bound2);
      copyTo = new SNode(bounds);
      BST* ptr(copyFrom->_root);
      copyTo->_root = ptr;
      //attach to tree
      copyScanHelp(copyTo->_left, copyFrom->_left);
      copyScanHelp(copyTo->_right, copyFrom->_right);
    }
  }
  //-------------------------------------------------------------------------------   
  void SNodedestructor(SNode* node){
    node = nullptr;
  }
  //-------------------------------------------------------------------------------     
  //helper for destructor
  void destructor(SNode* node){
    if (node != nullptr){
      delete node->_root;
      destructor(node->_left);
      destructor(node->_right);
      delete node;
    }
  }
  //------------------------------------------------------------------------------- 
  //insert SNode - same as insert for BST except SNode
  void insertSNode(SNode* current, SNode* newNode){
    if (newNode->_bounds.first < current->_bounds.first){
      if (current->_left == nullptr){
        current->_left = newNode;
      }
      else{
        insertSNode(current->_left, newNode);
      }
    }
    else if (newNode->_bounds.first > current->_bounds.first){
      if (current->_right == nullptr){
        current->_right = newNode;
      }
      else{
        insertSNode(current->_right, newNode);
      }
    }
    else{
      cout << "no duplicates!" << endl;
    }    
  }
  //-------------------------------------------------------------------------------   
  //help function to determine height
  int getHeight(SNode* ptr) const {
    if (!ptr){
      return 0;
    } 
    int leftHeight = getHeight(ptr->_left);
    int rightHeight = getHeight(ptr->_right);
    return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
  }
  //-------------------------------------------------------------------------------  
  //helper for getHeight
  int finalHeight(SNode* ptr) const{
    int check = getHeight(ptr);
    return check - 1;
  }
  //------------------------------------------------------------------------------- 
  //helper to create array of SNodes
  int createArray(SNode* add, SNode* arr[], int count){
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
  //helper to recreate BST of SNodes that's balances
  SNode* createBST(SNode* arr[], int start, int end){
    if (start > end){
      return nullptr;
    }
    int mid = ((start + end) / 2); 
    SNode* root = arr[mid];
    //_root = arr[mid];
    root->_left = createBST(arr, start, mid - 1);
    root->_right = createBST(arr, mid + 1, end);
    return root;
  }  
  //-------------------------------------------------------------------------------      
  //helper to insert into correct BST
  void insertHelp(SNode* ptr, int weight, int ch){
    //cout << "weight " << weight << endl; 
    //cout << "firstBound " << ptr->_bounds.first << " secondBound " << ptr->_bounds.second << endl;
    //changed forest to ptr
    if (weight >= ptr->_bounds.first and weight <= ptr->_bounds.second){
      ptr->_root->insert(_chars.at(ch-1), weight);
      return;
    }
    if (weight <= ptr->_bounds.second and ptr->_bounds.second == 13){
      ptr->_root->insert(_chars.at(ch-1), weight);
    }
    else if (weight > _forest->_bounds.second){
      insertHelp(ptr->_right, weight, ch);
    }
    else if (weight < _forest->_bounds.first){
      insertHelp(ptr->_left, weight, ch);
    }
    else{
      cout << "Invalid #" << endl;
    }
  }
  //-------------------------------------------------------------------------------  
  //helper to print out all BSTs
  void dumpHelp(SNode* ptr) const{
    if (ptr == nullptr){
      return;
    }
    dumpHelp(ptr->_left);
    //took out true
    ptr->_root->dump();
    cout << endl;
    dumpHelp(ptr->_right);
  }
  //-------------------------------------------------------------------------------  
  //helper to print out all BSTs (verbose)
  void inorderHelp(SNode* ptr) const{
    if (ptr == nullptr){
      return;
    }
    cout << "(";
    inorderHelp(ptr->_left);
    cout << ptr->_bounds.first << ":" << ptr->_bounds.second;
    inorderHelp(ptr->_right);
    cout << ")";
  }
  //-------------------------------------------------------------------------------
  void zigzig(SNode* current, SNode* parent, SNode* gp){
	  SNode* X = current;
	  SNode* Y = parent; 
	  SNode* Z = gp;
	  SNode* T0 = X->_left;
	  SNode* T1 = X->_right;
	  SNode* T2 = Y->_right;
	  SNode* T3 = Z->_right;
	  SNode* A = X;
	  SNode* B = Y;
	  SNode* C = Z;
	  A->_left = T0;
	  A->_right = T1;
	  B->_left = T2;
	  B->_right = C;
	  C->_left = T2;
	  C->_right = T3;
  }
  //-------------------------------------------------------------------------------
  void zagzag(SNode* current, SNode* parent, SNode* gp){
	  SNode* X = current;
	  SNode* Y = parent; 
	  SNode* Z = gp;
	  SNode* T0 = Z->_left;
	  SNode* T1 = Y->_left;
	  SNode* T2 = X->_left;
	  SNode *T3 = X->_right;
	  SNode *A = X;
	  SNode *B = Y;
	  SNode *C = Z;
	  A->_left = B;
	  A->_right = T3;
	  B->_left = C;
	  B->_right = T2;
	  C->_left = T0;
	  C->_right = T1;
	  gp = current;
  }  
  //-------------------------------------------------------------------------------
  void zigzag(SNode* current, SNode* parent, SNode* gp){
	  SNode*  X = current;
	  SNode *Y = parent; 
	  SNode* Z = gp;
	  SNode* T0 = Y->_left;
	  SNode* T1 = X->_left;
	  SNode* T2 = X->_right;
	  SNode *T3 = Z->_right;
	  X->_left = Y;
	  X->_right = Z;
	  Y->_left = T0;
	  Y->_right = T1;
	  Z->_left = T2;
	  Z->_right = T3;
	  gp = current;
  }    
};

#endif
