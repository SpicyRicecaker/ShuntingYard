#include <iostream>
#include <cstring>
#include "StNode.h"
#include "BNode.h"

void pushStack(char* value, StNode*& current);
char popStack(StNode* &past, StNode* &current);
char peepStack(StNode* current);
void printStack(StNode* current);
//void addBi();
//void printBi();
//void promptUser();
void getInput(char* &inptr);
void convExp2Post(char* inptr, StNode* &operatorHead, StNode* &postfixHead);
int getPrio(char n);

using namespace std;

//Main function of ShuntingYard
int main(){
  //Setup input
  char in[999];
  char* inptr = &in[0];

  //Stack for postfix operators while converting
  StNode* operatorHead = NULL;
  //Stack for postfix output
  StNode* postfixHead = NULL;
  //Binary tree that we're nont really concerned with rn

  bool running = true;

  //Main program loop, get user input, convert into postfix, ask for desired output, then output
  while(running){
    cout << "Please enter an infix expression..." << endl;
    //First, get expression input
    getInput(inptr);
    //We need someway to split the operands and operators of the input by spaces
    //Then, convert into postfix
    convExp2Post(inptr, operatorHead, postfixHead);//
    //Debug
    printStack(postfixHead);//
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
  //Have a temporary buffer to store operators and operands between spaces
  char buf[999];
  char* buffer = &buf[0];
  //Find the length of the infix expression
  int inlength = strlen(input);
  //For every character in the infix expression
  for(int a = 0; a < inlength; ++a){
    char x = input[a];
    if(x == ' '){
      //Check if it is a digit
      if(isdigit(input[a])){
        //Push to the postfix stack if it is
        pushStack(input[a], postfixHead);
      }else if (input[a] == ' '){
        continue;
      }else if (operatorHead == NULL){ //Otherwise if the operator stack is empty, add the current charater
        pushStack(input[a], operatorHead);
      }else if(input[a] == '('){  //If it is an open  parenthesis, just add it to the operator stack
        pushStack(input[a], operatorHead);
      }else if(input[a] == ')'){
        //Eject until the open parenthesis
      }else { 
        //Otherwise if it is an operator, get its prio and compare it with the operator stack. If the prio is greater, then add it, if it is less, then we need to keep on ejecting operators until a lower prio is found or we reach the end of the stack
        while(getPrio(input[a]) <= getPrio(peepStack(operatorHead))){
          pushStack(popStack(operatorHead, operatorHead), postfixHead);
        }
        pushStack(input[a], operatorHead);
      }
    }
  } else{
      int counter = 0;
      for(int b = a; b <= a; ++b){
        buffer[counter] = input[b];
        ++counter;
      }
    }
  //If we've reached the end of the infix expression || it is empty, output the entire operator stack into the prefix expression
  while(peepStack(operatorHead) != '\0'){
    pushStack(popStack(operatorHead, operatorHead), postfixHead);
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

void pushStack(char* value, StNode* &current){
  if(current == NULL){
    current = new StNode(value);
    return;
  }
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    pushStack(value, n);
  }else{
    current->setNext(new StNode(value));
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
    StNode* n = current->getNext();
    return popStack(current, n);
  }else{
    char t = *(current->getValue());
    past->setNext(NULL);
    delete current;
    current = NULL;
    return t;
  }
}

char peepStack(StNode* current){
  if(current == NULL){
    return '\0';
  }
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    return peepStack(n);
  }else{
    return *(current->getValue());
  }
}

void printStack(StNode* current){
  if(current == NULL){
    cout << "Empty stack" << endl;
    return;
  }
  cout << *(current->getValue()) << " ";
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    printStack(n);
  }
}
