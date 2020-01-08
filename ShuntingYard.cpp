#include <iostream>
#include <cstring>
#include "StNode.h"
#include "BNode.h"

void pushStack(char value, StNode* &current);
char popStack(StNode* &past, StNode* &current);
char peepStack(StNode* &current);
void printStack(StNode* current, StNode* head);
void addBi();
void printBi();
//void promptUser();
void getInput(char* &inptr);
void convExp2Post(char* inptr, StNode* &operatorHead, StNode* &postfixHead);
int getPrio(char n);

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
    cout << "Please enter an infix expression..." << endl;
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

void convExp2Post(char* input, StNode* &operatorHead, StNode* &postfixHead){
  int inlength = strlen(input);
  //For every character in the infix expression
  for(int a = 0; inlength; ++a){
    //Check if it is a digit OR OPEN PARETHESIS
    if(isdigit(input[a]) || input[a] == '('){
      //Push to the postfix stack if it is
      pushStack(input[a], postfixHead);
    }else{ //Otherwise if the operator stack is empty, add it
      if(operatorHead == NULL){
        pushStack(input[a], postfixHead);
      }
      //If it is a close parenthesis, keep adding operator stack to postfix until open parenthesis
      if(input[a] == ')'){
        
      }
      //Otherwise if it is an operator, get its prio and compare it with the operator stack. If the prio is greater, then add it, if it is less, then we need to keep on ejecting operators until a lower prio is found or we reach the end of the stack
      while(getPrio(input[a]) <= peepStack(operatorHead)){
        pushStack(popStack(operatorHead, operatorHead), postfixHead);
      }
      pushStack(input[a], operatorHead);
    }
    
    //If we've reached the end of the infix expression || it is empty, output the entire operator stack into the prefix expression
    while(peepStack(operatorHead) != '\0'){
      pushStack(popStack(operatorHead, operatorHead), postfixHead);
    }
  }
}

int getPrio(char n){
  if(n == '+' || n == '-'){
    return 2;
  }else if(n == '*' || n == '/'){
    return 3;
  }else if(n == '^'){
    return 4;
  }
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

//To popStack EFFICIENTLY
//We need to go through out entire stack from the head, or the beginning
//We pass in the one before as a temp node, to avoid the overhead of having to scan forward every time
char popStack(StNode* &past, StNode* &current){
  if(current == NULL){
    return '\0';
  }
  if(current->getNext() != NULL){
    StNode* nn = current->getNext();
    return popStack(current, nn);
  }else{
    char t = *(current->getValue());
    delete current;
    current = NULL;
    past->setNext(NULL);
    return t;
  }
}

char peepStack(StNode* &current){
  if(current == NULL){

    return '\0';
  }
  if(current->getNext() != NULL){
    StNode* temp = current->getNext();
    return peepStack(temp);
  }else{
    return *(current->getValue());
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
