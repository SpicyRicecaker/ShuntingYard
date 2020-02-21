#include <iostream>
#include <cstring>
#include "BNode.h"
#include "StBNode.h"

StBNode::StBNode(BNode* newBNode){
  bNode = newBNode;

  next = NULL;
}

StBNode::~StBNode(){
  //delete bNode;
  //bNode = NULL;
}

StBNode* StBNode::getNext(){
  return next;
}

void StBNode::setNext(StBNode* newNext){
  next = newNext;
}

BNode* StBNode::getValue(){
  return bNode;
}

void StBNode::setValue(BNode* newBNode){
  bNode = newBNode;
}


