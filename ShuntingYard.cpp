//USE DELIMs FOR MODULARITY
//() TO DECLARE VECTORS WITH NULL-TERMINATING CHARACTERS

#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include "StNode.h"
#include "BNode.h"
#include "StBNode.h"

void pushStack(char* value, StNode*& current); //Adds to top of stack
void pushBinaryStack(BNode* bNode, StBNode*& current); //Lazy
char* popStack(StNode* &past, StNode* &current); //Takes from top of stack
BNode* popBinaryStack(StBNode* &past, StBNode* &current); //Lazy
char* peepStack(StNode* current); //Looks at top of stack
void enqueue(char* value, StNode*& current);  //Adds to the rear of queue
char* dequeue(StNode*& head); //Takes from the front of queue
void printQueue(StNode* current);
//void addBi();
//void printBi();
//void promptUser();
void getInput(char* &inptr);
void splitInput (std::vector<char*>*in_split_ptr, char* inptr, char delim);
void convExp2Post(std::vector<char*>*in_split_ptr, StNode* &operatorStack, StNode* &postfixQueue);
void createTree(StNode*& postfixQueue, StBNode*& buffer);//To create a tree, we need the postfix queue, as well as a stack that will hold the binary tree conversion process...
int getPrio(char n); // Get prio should deal with char

void inorderTraversal(BNode* root);
void preorderTraversal(BNode* root);
void postorderTraversal(BNode* root);

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
  StNode* operatorStack = NULL;
  //QUEUE for postfix output
  StNode* postfixQueue = NULL;
  //Stack for binary expression tree that holds binary nodes to be used during conversion
  StBNode* buffer = NULL;
  //Root node for binary expression tree that will be derived from the buffer
  BNode* root = NULL;

  bool running = true;

  //Main program loop, get user input, convert into postfix, ask for desired output, then output
  while(running){
    cout << "Please enter an infix expression..." << endl;
    //First, get expression input
    getInput(inptr);
    //We need someway to split the operands and operators of the input by spaces
    splitInput(in_split_ptr, inptr, ' ');
    //Then, convert into postfix
    convExp2Post(in_split_ptr, operatorStack, postfixQueue);
    //Output postfix expression
    //USING QUEUE
    cout << "The postfix expression is: ";
    printQueue(postfixQueue);
    cout << endl;
    //Make a binary tree using this postfix expression
    createTree(postfixQueue, buffer);
    //Take the root note out of the stack
    root = popBinaryStack(buffer, buffer);
    //Then, get what the user wants to convert the postfix into
    cout << "Please enter a number, (1) for infix, (2) for prefix, or (3) for postfix." << endl;
    int decide = 0;
    cin >> decide;
    cin.clear();
    cin.ignore(999, '\n');
    switch (decide){
    case 1:
      //We must do in-order traversal in this case...
      cout << "Infix Equation: " << endl;
      inorderTraversal(root);
      break;
    case 2:
      //We must do pre-order traversal in this case...
      cout << "Prefix Equation: " << endl;
      preorderTraversal(root);
      break;
    case 3:
      //We must do post-order traversal in this case...
      cout << "Postfix Equation: " << endl;
      postorderTraversal(root);
      break;
    default:
      cout << "Invalid choice. Program will now exit!" << endl;
      break;

    }

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

void convExp2Post(std::vector<char*>*in_split_ptr, StNode* &operatorStack, StNode* &postfixQueue){
  vector<char*>::iterator it;
  for(it = in_split_ptr->begin(); it != in_split_ptr->end(); ++it){
    //First check if it is a digit, and push that
    if(isalnum((*it)[0])){
      enqueue((*it), postfixQueue);
    }else if ((*it)[0] == '('){ //Then check if it is a open parenthesis, if so add that to the stack
      pushStack((*it), operatorStack); 
    }else if((*it)[0] == ')'){ //Or if it is a close parenthesis, eject until open parenthesis, including.
      while((peepStack(operatorStack)[0]) != '('){
        enqueue(popStack(operatorStack, operatorStack), postfixQueue);
      }
      popStack(operatorStack, operatorStack);
    }else if((peepStack(operatorStack) == NULL)){ //Otherwise if it is an empty stack, add the operator
      pushStack((*it), operatorStack);
    }else { //Then if it is an operator, compare precedence, eject until precedence is greater than or equal. To do this, we use <= because we also need to add it at the end...
      while(getPrio(((*it)[0])) <= getPrio(peepStack(operatorStack)[0])){
        enqueue(popStack(operatorStack, operatorStack), postfixQueue);
        if(peepStack(operatorStack) == NULL){
          break;
        }
      }
      pushStack((*it), operatorStack);
    }
  }
  //If we're at the end of the stack, eject everything from the operator stack
  while(peepStack(operatorStack) != NULL){
    enqueue(popStack(operatorStack, operatorStack), postfixQueue);
  }
}

void createTree(StNode*& postfixQueue, StBNode*& buffer){
  //We gotta go through the queue and start to build our tree...
  while(postfixQueue != NULL){
    //First, store the postfixQueue node value as a char*
    char* t = new char [strlen(postfixQueue->getValue())];
    strcpy(t, dequeue(postfixQueue));
    if(isalnum(t[0])){ //If it's an operand
      //Dynamically allocate it to a binary tree node and add that to the buffer stack
      pushBinaryStack(new BNode(t), buffer);
    }else{ 
      //Otherwise, still dynamically allocate it to a binary tree node
      BNode* temp = new BNode(t);
      cout << "Root is: " << t << endl;
      //Pop off the top of the binary stack and add it to the right pointer
      temp->setRight(popBinaryStack(buffer, buffer));
      cout << "Right is: " << temp->getRight()->getValue() << endl;
      //Pop off the next top of the binary stack and add it to the left pointer
      temp->setLeft(popBinaryStack(buffer, buffer));
      cout << "Left is: " << temp->getLeft()->getValue() << endl;
      pushBinaryStack(temp, buffer);
    }
  }
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

void pushBinaryStack(BNode* value, StBNode*& current){
  if(current == NULL){
    current = new StBNode(value);
    return;
  }
  if(current->getNext() != NULL){
    StBNode* n = current->getNext();
    pushBinaryStack(value, n);
  }else{
    current->setNext(new StBNode(value));
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

BNode* popBinaryStack(StBNode* &past, StBNode* &current){
  if(current == NULL){
    cout << "Current is null" << endl;
    return NULL;
  }
  if(current->getNext() != NULL){
    StBNode* n = current->getNext();
    return popBinaryStack(current, n);
  }else{
    BNode* temp = current->getValue();
    past->setNext(NULL);
    delete current;
    current = NULL;
    return temp;
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

//We want to try and add this to the rear of the queue. The implementation for this looks very similar to push stack, but in the end it'll still be First in First out.
void enqueue(char* value, StNode*& current){
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

//We want to try and take from the front of the queue, so we'll be targetting the "head" node.
char* dequeue(StNode*& head){
  //If head is empty, return NULL
  if(head == NULL){
    return NULL;
  }
  //Otherwise, we'll store what Node comes after the head
  StNode* t = head->getNext();
  //Also the value that the head is holding
  char* o = new char [strlen(head->getValue())];
  strcpy(o, head->getValue());
  //Then cutoff the head
  head->setNext(NULL);
  //Delete the head
  delete head;
  //Then make the temp node the new head.
  head = t;
  //Return the value that the head held
  return o;
}


void printQueue(StNode* current){
  if(current == NULL){
    cout << "Empty stack" << endl;
    return;
  }
  cout << current->getValue() << " ";
  if(current->getNext() != NULL){
    StNode* n = current->getNext();
    printQueue(n);
  }
}

//In preorder, we visit root, then the left subtree, then the right subtree.
void preorderTraversal(BNode* root){
  //If the tree is empty, get out!
  if(root == NULL){
    return;
  }
  //Print out the root
  cout << root->getValue() << " ";
  //Recurse through the left
  preorderTraversal(root->getLeft());
  //Recurse through the right
  preorderTraversal(root->getRight());
}

//In postorder, we visit the left subtree, then the right subtree, then the root.
void postorderTraversal(BNode* root){
  //If the tree is empty, get out!
  if(root == NULL){
    return;
  }
  //Recurse through the left
  postorderTraversal(root->getLeft());
  //Recurse through the right
  postorderTraversal(root->getRight());
  //Print out the root
  cout << root->getValue() << " ";
}

//In inorder, we visit the left subtree, then the root, then the right subtree
void inorderTraversal(BNode* root){
  //If the tree is empty, get out!
  if(root == NULL){
    return;
  }
  if (!isalnum(root->getValue()[0])){
    cout << "( ";
  }
  //Recurse through the left
  inorderTraversal(root->getLeft());
  //Print out the root
  cout << root->getValue() << " ";
  //Recurse through the right
  inorderTraversal(root->getRight());
  if (!isalnum(root->getValue()[0])){
    cout << ") ";
  }
}


