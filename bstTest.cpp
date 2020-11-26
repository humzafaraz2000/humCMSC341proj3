//tester file for BST

#include "BST.h"

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
  cout << endl;
  bst.dump(true);
  cout << endl;
  cout << "size = " << bst.size() << endl;
  cout << "height = " << bst.height() << endl;
  
  //test copy constructor
  BST copy(bst);
  cout << "Copy: " << endl;
  copy.dump(true);
  cout << endl;
  cout << "size = " << bst.size() << endl;
  cout << "height = " << bst.height() << endl;  
  
  //test overloaded assignment operator
  BST assign = bst;
  cout << "Assignment operator: " << endl;
  assign.dump(true);
  cout << endl;
  cout << "size = " << bst.size() << endl;
  cout << "height = " << bst.height() << endl;  
  
  return 0;
}