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
void convExp2Post(char* inptr, StNode* &operatorHead, StNode* &postfixHead);
int getPrio(char n); // Get prio should deal with char

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
  //Vector that will be used to buffer input
  vector<char> buf;
  //Find the length of the infix expression
  int inlength = strlen(input);
  //For every character in the infix expression
  for(int a = 0; a < inlength; ++a){
    if(a == inlength -1){
      i
        asd
        f
        asdf
        asdf


        
    }
    if(input[a] == ' '){
      //If it does, then convert to a number, push to postfix, and clear the buffer
      vector<char>::iterator it;
      char temp[buf.size()+1];
      int counter = 0;
      for(it = buf.begin(); it != buf.end(); ++it){
        temp[counter] = *(it);
        ++counter;
      }
      temp[buf.size()] = '\0';
      buf.clear();
      if(isdigit(temp[0])){ //Check if the buffer currently holds a number
        pushStack(temp, postfixHead);
      }else if (operatorHead == NULL){ //Otherwise if the operator stack is empty, add the current charater
        pushStack(temp, operatorHead);
      }else if(input[a] == '('){  //If it is an open  parenthesis, just add it to the operator stack
        pushStack(temp, operatorHead);
      }else if(input[a] == ')'){
        //Eject until the open parenthesis
        while(peepStack(operatorHead)[0] != '('){
          popStack(operatorHead, operatorHead);
        }
        buf.clear();
      }else {
        //Otherwise if it is an operator, get its prio and compare it with the operator stack. If the prio is greater, then add it, if it is less, then we need to keep on ejecting operators until a lower prio is found or we reach the end of the stack
        while(getPrio(input[a]) <= getPrio(peepStack(operatorHead)[0])){
          pushStack(popStack(operatorHead, operatorHead), postfixHead);
        }
        pushStack(temp, operatorHead);
      }
    } else {
      buf.push_back(input[a]);
      cout << "pushing back " << input[a] << endl;
    }
  }
  //If we've reached the end of the infix expression || it is empty, output the entire operator stack into the prefix expression
  while(peepStack(operatorHead) != NULL){
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
char* popStack(StNode* &past, StNode* &current){
  if(current == NULL){
    return NULL;
  }
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    return popStack(current, n);
  }else{
    char* t = current->getValue();
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
