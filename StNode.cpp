#include <iostream>
#include <cstring>
#include "StNode.h"

StNode::StNode(char* newValue){
  value = new char[strlen(newValue)+1];
  strcpy(value, newValue);
  next = NULL;
}

StNode::~StNode(){
  delete[] value;
  value = NULL;
}

StNode* StNode::getNext(){
  return next;
}

void StNode::setNext(StNode* newNext){
  next = newNext;
}

char* StNode::getValue(){
  return value;
}

void StNode::setValue(char* newValue){
  strcpy(value, newValue);
}


