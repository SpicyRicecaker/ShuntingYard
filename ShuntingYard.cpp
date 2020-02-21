//USE DELIM + () TO DECLAR VECTORS

#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include "StNode.h"
#include "BNode.h"

void pushStack(char* value, StNode*& current); // Push stack should be char*
char* popStack(StNode* &past, StNode* &current); // Pop stack should be char*
char* peepStack(StNode* current); // Peep stack should be char*
void printStack(StNode* current); // Print stack should be char*
//void addBi();
//void printBi();
//void promptUser();
void getInput(char* &inptr);
void splitInput (std::vector<char*>*in_split_ptr, char* inptr, char delim);
void debugPrintVector(std::vector<char*>*in_split_ptr);
void convExp2Post(std::vector<char*>*in_split_ptr, StNode* &operatorHead, StNode* &postfixHead);
int getPrio(char n); // Get prio should deal with char

using namespace std;

//Main function of ShuntingYard
int main(){
  //Setup input
  char in[999];
  char* inptr = &in[0];

  //Vector used to store the split input
  vector<char*> in_split;
  vector<char*>* in_split_ptr = &in_split;

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
    splitInput(in_split_ptr, inptr, ' ');

    //debug
    debugPrintVector(in_split_ptr);

    //Then, convert into postfix
    convExp2Post(in_split_ptr, operatorHead, postfixHead);
    //Debug
    cout << "Final result: ";
    printStack(postfixHead);
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

void convExp2Post(std::vector<char*>*in_split_ptr, StNode* &operatorHead, StNode* &postfixHead){
  vector<char*>::iterator it;
  for(it = in_split_ptr->begin(); it != in_split_ptr->end(); ++it){
    //First check if it is a digit, and push that
    if(isalnum((*it)[0])){
      pushStack((*it), postfixHead);
    }else if ((*it)[0] == '('){ //Then check if it is a open parenthesis, if so add that to the stack
      pushStack((*it), operatorHead); 
    }else if((*it)[0] == ')'){ //Or if it is a close parenthesis, eject until open parenthesis, including.
      while((peepStack(operatorHead)[0]) != '('){
        pushStack(popStack(operatorHead, operatorHead), postfixHead);
      }
      popStack(operatorHead, operatorHead);
    }else if((peepStack(operatorHead) == NULL)){ //Otherwise if it is an empty stack, add the operator
      pushStack((*it), operatorHead);
    }else { //Then if it is an operator, compare precedence, eject until precedence is greater than or equal. To do this, we use <= because we also need to add it at the end...
      while(getPrio(((*it)[0])) <= getPrio(peepStack(operatorHead)[0])){
        pushStack(popStack(operatorHead, operatorHead), postfixHead);
        if(peepStack(operatorHead) == NULL){
          break;
        }
      }
      pushStack((*it), operatorHead);
    }
  }
  //If we're at the end of the stack, eject everything from the operator stack
  while(peepStack(operatorHead) != NULL){
    pushStack(popStack(operatorHead, operatorHead), postfixHead);
  }
}

void debugPrintVector(vector<char*>*in_split_ptr){
  vector<char*>::iterator it;
  for(it = in_split_ptr->begin(); it != in_split_ptr->end(); ++it){
    cout << (*it) << ", ";
  }
  cout << endl;
}

int getPrio(char n){
  if(n == '('){
    return 1;
  }else if(n == '+' || n == '-'){
    return 2;
  }else if(n == '*' || n == '/'){
    return 3;
  }else if(n == '^'){
    return 4;
  }
  return 0;
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


void splitInput (vector<char*>*in_split_ptr, char* input, char delim){
  char* buf = new char[strlen(input)]();
  int counter = 0;

  int inlen = strlen(input);
  for(int a = 0; a < inlen; ++a){
    if(input[a] != delim){
      buf[counter++] = input[a];
    }
    if(input[a] == delim || a == inlen-1){
      in_split_ptr->push_back(buf);
      buf = new char[strlen(input)+1]();
      counter = 0;
    }
  }
}

//To popStack EFFICIENTLY
//We need to go through out entire stack from the head, or the beginning
//We pass in the one before as a temp node, to avoid the overhead of having to scan forward every time
char* popStack(StNode* &past, StNode* &current){
  if(current == NULL){
    cout << "Current is null" << endl;
    return NULL;
  }
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    return popStack(current, n);
  }else{
    char* t = new char [strlen(current->getValue())];
    strcpy(t, current->getValue());
    past->setNext(NULL);
    delete current;
    current = NULL;
    return t;
  }
}

char* peepStack(StNode* current){
  if(current == NULL){
    return NULL;
  }
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    return peepStack(n);
  }else{
    return current->getValue();
  }
}

void printStack(StNode* current){
  if(current == NULL){
    cout << "Empty stack" << endl;
    return;
  }
  cout << current->getValue() << " ";
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    printStack(n);
  }
}
