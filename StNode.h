//Header file for StNode
#ifndef STNODE_H
#define STNODE_H

#include <iostream>
#include <cstring>

class StNode {
 public:
  //Constructor and destructor
  StNode(char*);
  ~StNode();

  //Getting and setting next node
  StNode* getNext();
  void setNext(StNode*);

  //Getting and setting stored value (may not need)
  char* getValue();
  void setValue(char*);

 private:
  //Node points to next node and holds a value
  StNode* next;
  char* value;
};
#endif
