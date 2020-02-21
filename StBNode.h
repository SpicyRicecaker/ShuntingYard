#ifndef STBNODE_H
#define STBNODE_H

#include <iostream>
#include <cstring>
#include "BNode.h"

class StBNode{
 public:
  StBNode(BNode*);
  ~StBNode();

  StBNode* getNext();
  void setNext(StBNode*);

  BNode* getValue();
  void setValue(BNode*);
 private:
  StBNode* next;
  BNode* bNode; 
};
#endif
