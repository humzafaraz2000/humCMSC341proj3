// CMSC 341 - Spring 2020 - Project 3

//TOOK OUT 3 LINE FROM weights.txt
//AND 1 LINE FROM scrambled.txt

#include <vector>
#include "Scanner.h"

// Balance function for use with BSTs.  This implements the
// height-balance property for AVL trees.  Returns true if
// height-balance property is violated.
bool Scanner::heightImbalance(int leftHeight, int rightHeight, int leftSize, int rightSize) {
  return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
}

// SNode constructor.  bounds contains the upper and lower bounds on
// the weights for this BST.
Scanner::SNode::SNode(pair<int, int> bounds) {
  _bounds = bounds;
  _root = new BST(heightImbalance);
  _left = _right = nullptr;
}

Scanner::SNode::~SNode() {
  
}


Scanner::Scanner(int lines, int range, vector<string> chars) {
  // TBD
  //CREATE NODE HERE
  _lines = lines;
  for (int i = 0; i < lines; i++){
    //cout << i << endl;
    int bound1 = (i * range) + 1;
    int bound2 = bound1 + range - 1;
    pair <int,int> bounds(bound1, bound2);
    SNode* newNode = new SNode(bounds);
    if (_forest == nullptr){
      _forest = newNode;
    }
    else{
      insertSNode(_forest, newNode);
    }
    /*
    cout <<"before balance" << endl;
    bool notBal = heightImbalance(finalHeight(_forest->_left), finalHeight(_forest->_right), 0, 0);
    cout << "after heightImbalance" << endl;
    if (notBal == true){
      cout << "IN IF" << endl;
      SNode* arr [i];
      createArray(_forest, arr, 0);
      cout << "after createArray" << endl;
      _forest = createBST(arr, 0, i - 1);
      cout << "after create BST" << endl;
    }
    */
  }
  _chars = chars;
}

Scanner::~Scanner() {
  // TBD
  destructor(_forest);
}

Scanner::Scanner(const Scanner& rhs) {
  // TBD 
  copyScanHelp(_forest, rhs._forest);
}

Scanner& Scanner::operator=(const Scanner& rhs) {
  // TBD
  return *this;
}

// Read the data files and insert into the datastructure.  File in
// 'ascii' contains the scrambled character indices; file 'weights'
// contains the corresponding weights.
bool Scanner::loadFiles(string ascii, string weights) {
  vector<int> allWeights;
  vector<int> allChars;
  
  //load in ascii
  std::ifstream asciiFile;
  asciiFile.open(ascii);
  int chars;
  if(asciiFile.is_open()){
    while (!asciiFile.eof()){
      asciiFile >> chars;
      allChars.push_back(chars);
      if (asciiFile.peek() == ','){
        asciiFile.ignore();
      }
    }
  }
  
  //load in weights
  std::ifstream weightsFile;
  weightsFile.open(weights);
  int weight;
  if(weightsFile.is_open()){
    while(!weightsFile.eof()){
      weightsFile >> weight;
      allWeights.push_back(weight);
      if (weightsFile.peek() == ','){
        weightsFile.ignore();
      }
    }
  }
  
  for (int i = 0; i < (int)allWeights.size(); i++){
    insert(allWeights.at(i), allChars.at(i));
  }
  
  asciiFile.close();
  weightsFile.close();
  return true;
}

// Insert a node; splay the node that is inserted.
bool Scanner::insert(int weight, int ch) {
  // TBD
  insertHelp(_forest, weight, ch);
  return true;
}

void Scanner::dump() const {
  // TBD
  //same as dump except verbose
  dumpHelp(_forest);
}

void Scanner::inorder() const {
  // TBD
  //inorder traversal of tree
  //call dump for each tree
  inorderHelp(_forest);
}


