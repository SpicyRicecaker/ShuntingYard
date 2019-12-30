#include <iostream>
#include <cstring>
#include "SNode.h"

SNode::SNode(char* newValue){
  value = new char[strlen(newValue)];
  strcpy(value, newValue);

  next = NULL;
}

SNode::~SNode(){
  delete[] value;
  value = NULL;
}

SNode* SNode::getNext(){
  return next;
}

void SNode::setNext(SNode* newNext){
  next = newNext;
}

char* SNode::getValue(){
  return value;
}

void SNode::setValue(char* newValue){
  value = newValue;
}


