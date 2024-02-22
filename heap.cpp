//Arjun Vinsel
//21/FEB/2024
//This program will take ints and sort them into a max heap

#include<iostream>
#include<cstring>
#include<cmath>
#include<fstream>

using namespace std;

void addInput(int (&ary)[], int &counter);// Will add inputs from the line
void addFile(int (&ary)[], int &counter);//will add inputs from a file
void sort(int (&ary)[], int index);//will add the inputs
void print(int ary[], int counter, int level, int index);//will print the inputs
int remove(int (&ary)[], int index, int &counter);//will remove the root and print it
void removeAll(int (&ary)[], int index, int &counter);//will remove all values
void arrayNuller(int (&ary)[], int &size);//Makes all elements in an array null
void reverseSort(int (&ary)[], int index);//called during remove which must go through tree in reverse

int main() {//main funtion
  char input[20];
  bool stillRunning = true;
  int ary[100];
  int counter = 0;
  int index = 0;
  int size = sizeof(ary)/sizeof(ary[0]);
  arrayNuller(ary, size);
  while(stillRunning == true) {
  cout << "please enter addFile, addInput, print, remove, removeAll, or quit " << endl;
    cin >> input;
    cin.ignore(256, '\n');
      if (strcmp(input, "addInput") == 0) {
	addInput(ary, counter);
      }
      if (strcmp(input, "addFile") == 0) {
        addFile(ary, counter);
      }
    if(strcmp(input, "print") == 0) {
      print(ary, counter, 0, 0);
    }
     if(strcmp(input, "removeAll") == 0) {
       removeAll(ary, index, counter);
      counter = 0;
    }
     if(strcmp(input, "remove") == 0) {
       cout << remove(ary, index, counter) << endl;
    }

    if(strcmp(input, "quit") == 0) {
      stillRunning = false;
    }
  }
  return 0;
}

void arrayNuller(int (&ary)[], int &size) {//Makes all elemnts in an array NULL
  for(int i = 0; i < size; i++) {
    ary[i] = NULL;
  }
}

void addInput(int (&ary)[], int &counter) { // Will add inputs from the line
  cout << "enter how many numbers you wish to input up too 100 " << endl;
  int inputL = 0;
  int i = 0;
  cin >> inputL;
  int input = 0;
  cout << "enter your numbers" << endl;
  while(i < inputL) {
    cin >> input;
    cin.ignore(256, '\n');
    ary[counter] = input;
    sort(ary, counter);
    counter++;
    i++;
  }
}

void addFile(int (&ary)[], int &counter) {//Will add ints from a file
  cout << "enter file name " << endl;
  char input[20];
  cin >> input;
  ifstream fin(input);
  int temp;
  while(fin >> temp) {
    ary[counter] = temp;
    counter++;
    sort(ary, counter); 
  }
  fin.close();
}


void sort(int (&ary)[], int index) {//Will sort the ints
  int parent = (floor(index / 2));
   if(ary[index] > ary[parent]) {
     swap(ary[index], ary[parent]);
     int newParrent = (floor(parent / 2));
      if (ary[parent] > ary[newParrent]) {
	sort(ary,parent);
      }
   }
}




void print(int ary[], int counter, int level, int index) {//will print the tree
  if (index >= counter) {
    return;
  }
  print(ary, counter, level + 1, 2 * index + 1);

  for(int i = 0; i < level; i++) {
    cout << "\t";
  }
  cout << ary[index] << endl;
  print(ary, counter, level + 1, 2 * index + 2);
}

int remove(int (&ary)[], int index, int &counter) {//removes the root
  int temp = ary[0];
  ary[0] = ary[counter];
  ary[counter] = 0;
  counter = counter - 1;
  reverseSort(ary, index);
  return temp;
}

void removeAll(int (&ary)[], int index,int &counter) {//will remove all elements in the heap
  int i = 0;
  while(i < counter) {
    remove(ary,index,counter);
    i++;
  }
}

void reverseSort(int (&ary)[], int index) {//called during remove. Will sort through the list top to bottom.
  int rChild = (index * 2 + 1);
  int lChild = (index * 2 + 2);
  int largest = 0;
  if (ary[rChild] < ary[lChild]) {
    largest = lChild;
  }
  else {
    largest = rChild;
  }
  if(ary[largest] > ary[index] ) {
    swap(ary[index], ary[largest]);
    reverseSort(ary, largest);
  }
}
