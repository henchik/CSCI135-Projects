/*
Author: Chen Stanilovsky
Course: CSCI-136
Instructor: Professor Maryash
Assignment: Project 2 Task A
A program that reads a text file called dna.txt that contains one DNA strand per
line, and outputs to the console (terminal) the corresponding mRNA strands.
*/
#include <iostream>
#include <fstream>

using namespace std;

int main(){
  ifstream fin("dna.txt");
  if(fin.fail()) {
    cerr << "File cannot be read, opened, or does not exist.\n";
    exit(1);
  }
  string strand;
  while(getline(fin, strand)) {
    for(int i = 0; i < strand.length(); i++){
      switch(strand[i]){
        case 'A':
          strand[i] = 'U';
          break;
        case 'T':
          strand[i] = 'A';
          break;
        case 'C':
          strand[i] = 'G';
          break;
        case 'G':
          strand[i] = 'C';
          break;
      }
    }
    cout << strand << endl;
  }
  fin.close();
}
