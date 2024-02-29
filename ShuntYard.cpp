#include<iostream>
#include <cctype>
#include<cstring>
#include<iomanip>

using namespace std;

class Node {
public:
  char value;
  Node* next;

  Node(char newValue) {
    next = NULL;
    value = newValue;
  }
  char getValue() {
    return value;
  }
  Node* getNext() {
    return next;
  }
  void setNext(Node* nextNode) {
    next = nextNode;
  }
  void printV(Node* node) {
    if(node != NULL) {
    cout << node -> getValue() << endl;
    }
  }
  ~Node() {}
};

class NodeBT {
public:
  char value;
  Node* next;

  NodeBT(char newValue) {
    next = NULL;
    value = newValue;
  }
  char getValueBT() {
    return value;
  }
  Node* getNextBT() {
    return next;
  }
  void setNextBT(Node* nextNode) {
    next = nextNode;
  }
  ~NodeBT() {}
};

int getP(char a);
bool isOp(char a);
void printQ(Node* head);
void arrayNuller(char ary[]);
void pop(Node* &stackFront);//removes the top of the stack
void push(Node* &stackFront, char newValue);//pushs a new value to the top of the stack
char peek(Node* stackFront);//returns the top value of the stack
void enqueue(Node* &qFront, Node* &qTail, char newValue);//Puts an new node at the back of the queue
Node* dequeue(Node* &qFront);//removes the node at the front of the queue
void shunter(char ary[], Node* &stackFront, Node* &qTail, Node* &qFront, int counter);

int main() {
  Node* stackFront = NULL;
  Node* qFront = NULL;
  Node* qTail = NULL;
  char input[20];
  char ary[20];
  arrayNuller(input);
  arrayNuller(ary);
  int counter = 0;
  cout << "please enter the equation" << endl;
  cin.getline(input, 80);
  for(int i = 0; i < 20; i++) {
    if(input[i] != ' ' && input[i] != NULL) {
      ary[counter] = input[i];
      counter++;
    }
  }
  shunter(ary,stackFront,qTail,qFront,counter);
  
  return 0;
}

void arrayNuller(char ary[]) {
  for(int i = 0; i < 20; i++) {
    ary[i] = NULL;
  }
}

void pop(Node* &stackFront) {
  if(stackFront != NULL) {
  Node* temp;
  temp = stackFront;
  stackFront = temp -> getNext();
  delete temp;
  }
}

void push(Node* &stackFront, char newValue) {
  Node* temp = new Node(newValue);
  if(stackFront != NULL) {
  temp -> setNext(stackFront);
  }
  stackFront = temp;
}

char peek(Node* stackFront) {
  if(stackFront != NULL){
  return stackFront -> getValue();
  }
  return NULL;
}

void enqueue(Node* &qFront, Node* &qTail,char newValue) {
  Node* temp = new Node(newValue);
  if(qTail != NULL) {
  qTail -> setNext(temp);
  }
  qTail = temp;
  if(qTail == NULL) {
    qFront = qTail;
  }
}

Node* dequeue(Node* &qFront) {
  Node* temp = qFront;
  qFront = qFront -> getNext();
  delete temp;
  return qFront; 
}

void shunter(char ary[],Node* &stackFront,Node* &qTail,Node* &qFront,int counter) {
  for(int i = 0; i < counter; i++) {
    if(isdigit(ary[i]) == true){//if number put in stack
      enqueue(qFront, qTail, ary[i]);
    }

      if(stackFront == NULL || ary[i] == '(') {
	push(stackFront,ary[i]);
      }
      
      if(ary[i] == ')') {
	while(stackFront != NULL && stackFront -> getValue() != '(') {
	  enqueue(qFront,qTail,(stackFront->getValue()));
	  pop(stackFront);
	}
	pop(stackFront);
      }
      if(isOp(ary[i]) == true) {
	while(stackFront != NULL && getP(ary[i]) <= getP(stackFront->getValue())) {
	  enqueue(qFront,qTail,stackFront -> getValue());
	  pop(stackFront);
	}
	push(stackFront, ary[i]);
      }
  }
  while(stackFront != NULL) {
    enqueue(qFront, qTail, stackFront->getValue());
    pop(stackFront);
  } 
  printQ(qFront);
}

void printQ(Node* head) {
  while(head != NULL) {
    cout << head -> getValue() << ' ';
    Node* temp = head;
    head = head->getNext();
    dequeue(head);
  }
}

int getP(char a) {
  if(a == '+' || a == '-') {
    return 1;
  }
  if(a == '^') {
    return 3;
  }
  if(a == '/' || a== '*') {
    return 2;
  }
  return 0;
}

bool isOp(char a) {
  if(a == '*' ||
     a == '/' ||
     a == '+' ||
     a == '^' ||
     a == '-') {
    return true;
  }
  return false;
}