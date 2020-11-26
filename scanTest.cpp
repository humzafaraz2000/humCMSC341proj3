//tester file for Scanner
#include "Scanner.h"

int main(){
  
  vector<string> chars = {"█","░"};
  
  // Scanner with 15 lines, 34 characters per line, 2 characters
  Scanner s(15, 34, chars);

  // Read data files
  s.loadFiles("scrambled.txt", "weights.txt");
  s.dump();
  s.inorder();

  //test assignment operator
  Scanner assign = s;
  assign.dump();
  assign.inorder();
  
  //test copy constructor
  Scanner copy(s);
  copy.dump();
  copy.inorder();
  
  return 0;
}