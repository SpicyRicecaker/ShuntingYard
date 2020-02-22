#include <iostream>
#include <cstring>
#include "BNode.h"

//Takes in char*
BNode::BNode(char* newValue){
  value = new char[strlen(newValue)];
  strcpy(value, newValue);
  left = NULL;
  right = NULL;
}

//Deletes char* 
BNode::~BNode(){
  delete[] value;
  value = NULL;
}

//Getters and setters for left and right nodes
char* BNode::getValue(){
  return value;
}

BNode* BNode::getLeft(){
  return left;
}

BNode* BNode::getRight(){
  return right;
}

void BNode::setLeft(BNode* newLeft){
  left = newLeft;
}

void BNode::setRight(BNode* newRight){
  right = newRight;
}
