// CMSC 341 - Spring 2020 - Project 3

#include "BST.h"

// Constructor for the BNode nested class
BST::BNode::BNode(string ch, int rank, int height, int size) {
  _data = ch;
  _key = rank;
  _height = height;
  _size = size;
  _right = nullptr;
  _left = nullptr;
}

// Constructor for the BST class; requires a balance function
BST::BST(balfn_t imbalanced) {
  _root = nullptr;
  _imbalanced = imbalanced;
}

BST::~BST(){
  destructHelp(_root);
}

BST::BST(const BST& rhs) {
  copyHelp(_root, rhs._root);
}

BST& BST::operator=(const BST& rhs){
  destructHelp(_root);
  copyHelp(_root, rhs._root);
  return *this;
}

bool imbalfn(int leftHeight, int rightHeight, int leftSize, int rightSize) {
   return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
}

// Insert a (character, rank) pair
bool BST::insert(string ch, int rank) {
  BNode* newNode = new BNode();
  newNode->_data = ch;
  newNode->_key = rank;
  if (_root == nullptr){
    _root = newNode;
  }
  else{
    insertHelp(_root, newNode);
    _root->_size++;
  }
  //array based rebalancing
  bool isntBal = imbalfn(finalHeight(_root->_right), finalHeight(_root->_left), 0, 0);
  if (isntBal == true){
    BNode* arr [size()];
    createArray(_root, arr, 0);
    int sizePtr = size();
    _root = createBST(arr, 0, size() - 1);
    _root->_size = sizePtr;
  }
  return true;
}

int BST::size() const {
  return ( _root == nullptr ? 0 : _root->_size );
}

int BST::height() const {
  BNode* ptr = _root;
  int height = finalHeight(ptr);
  return height;
}

void BST::dump(bool verbose) const {
  if (!verbose){
    printHelp(_root);
  }
  else{
    printVerbose(_root);
  }
}

// A sample balance function.  This implements the height-balanced
// property from AVL trees.
/*
bool imbalfn(int leftHeight, int rightHeight, int leftSize, int rightSize) {
   return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
}
*/
//HERE
// A sample main to exercise BST separately.  This is *NOT* a thorough
// test program
/*
int main() {
  
  BST bst( imbalfn );
  bst.insert("A", 5);
  bst.insert("B", 10);
  bst.insert("C", 15);
  bst.insert("D", 20);
  bst.insert("E", 30);
  bst.insert("F", 40);
  bst.insert("G", 55);
  bst.insert("H", 60);
  bst.insert("I", 65);
  bst.insert("J", 70);
  bst.insert("K", 75);
  bst.insert("L", 80);
  bst.dump();
  //added endl
  cout << endl;
  bst.dump(true);
  cout << endl;
  cout << "size = " << bst.size() << endl;
  cout << "height = " << bst.height() << endl;
  return 0;
}
*/