#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cstring>

class BNode{
public:
  BNode(char*);
  ~BNode();
  char* getValue();
  BNode* getLeft();
  BNode* getRight();
  void setLeft(BNode*);
  void setRight(BNode*);
private:
  BNode* left;
  BNode* right;
  char* value;
};
#endif
