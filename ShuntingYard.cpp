#include <iostream>
#include <cstring>
#include "StNode.h"
#include "BNode.h"

void pushStack(char value, StNode* &current);
char popStack(StNode* &current);
void printStack(StNode* current, StNode* head);
void addBi();
void printBi();
void getInput(char* &inptr);
void convExp2Post(char* inptr, StNode* &operatorHead, StNode* &postfixHead);
int findPrio(char n);

using namespace std;

//Main function of ShuntingYard
int main(){
  char in[999];
  char* inptr = &in[0];

  bool running = true;

  //Stack for postfix operators while converting
  StNode* operatorHead;
  //Stack for postfix output
  StNode* postfixHead;
  //Binary tree that we're nont really concerned with rn
  
  //Main program loop, get user input, convert into postfix, ask for desired output, then output
  while(running){
    //First, get expression input
    getInput(inptr);
   //Then, convert into postfix
    convExp2Post(inptr, operatorHead, postfixHead);
    //Debug
    printStack(postfixHead, postfixHead);
    //Then, get what the user wants to convert it into **l8r
    //getInput(inptr);
    //Then, convert into what ever that is **l8r
    //conv2(inptr);
    //Print the post fix expression for now
    //printSt(poHead);
    break;
  }
  return 0;
}

void getInput(char* &inptr){
  while(true){
    cin.getline(inptr, 999);
    if(strcmp(inptr, "") != 0){
      break;
    }
    cout << "No input detected." << endl;
  }
}

void convExp2Post(char* input, StNode* &opHeadptr, StNode* &poHeadptr){
  for(int a = 0; a < strlen(input); ++a){
    
  }
}

int findPrio(char n){
  return 1;
}

void pushStack(char value, StNode* &current){
  if(current == NULL){
    current->setValue(value);
    return;
  }
  if(current->getNext() == NULL){
    current->setNext(new StNode(value));
  }else{
    StNode* nn = current->getNext();
    pushStack(value, nn);
  }
}

char popStack(StNode* &current){
  if(current == NULL){
    return '\0';
  }
  if(current->getNext() != NULL){
    StNode* nn = current->getNext();
    popStack(nn);
  }else{
    
  }
}

void printStack(StNode* current, StNode* head){
  if(current == head){
    cout << "Stack: ";
  }
  if(current == NULL){
    return;
  }
  cout << current->getValue() << " ";
  if(current->getNext() != NULL){
    printStack(head, current->getNext());
  }
}
