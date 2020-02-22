//Header file for Binary Tree Node Class 
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cstring>

class BNode{
public:
  BNode(char*);
  ~BNode();
  //Getters and setters for left and right node, as well as value
  char* getValue();
  BNode* getLeft();
  BNode* getRight();
  void setLeft(BNode*);
  void setRight(BNode*);
private:
  //A binary tree node class holds
  //A left pointer
  BNode* left;
  //A right pointer
  BNode* right;
  //Root node value
  char* value;
};
#endif
