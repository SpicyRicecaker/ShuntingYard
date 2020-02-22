#include <iostream>
#include <cstring>
#include "StNode.h"

//Takes in char*
StNode::StNode(char* newValue){
  value = new char[strlen(newValue)+1];
  strcpy(value, newValue);
  next = NULL;
}

//Deletes char*
StNode::~StNode(){
  delete[] value;
  value = NULL;
}

//Getters and setters for next node
StNode* StNode::getNext(){
  return next;
}

void StNode::setNext(StNode* newNext){
  next = newNext;
}

//Getters and setters for char*
char* StNode::getValue(){
  return value;
}

void StNode::setValue(char* newValue){
  strcpy(value, newValue);
}


