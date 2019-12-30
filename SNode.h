#ifndef SNODE_H
#define SNODE_H

#include <iostream>
#include <cstring>

class SNode {
 public:
  //Constructor and destructor
  SNode(char*);
  ~SNode();

  //Getting and setting next node
  SNode* getNext();
  void setNext(SNode*);

  //Getting and setting stored value (may not need)
  char* getValue();
  void setValue(char*);

 private:
  //Node points to next node and holds a value
  SNode* next;
  char* value;
};
#endif
