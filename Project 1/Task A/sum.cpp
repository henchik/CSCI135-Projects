/*
Author: Chen Stanilovsky
Course: CSCI-136
Instructor: Professor Maryash
Assignment: Project 1 Task A
A program that reads a sequence of integers from cin, and reports their sum.
*/
#include <iostream>
using namespace std;

int main(){
  int int_read_from_file;
  int sum = 0;
  //The following while loop makes the inner statement happen each time
  //the int_read_from_file variable gets a new values from the cin
  while(cin >> int_read_from_file){
    //Adds each value to the sum
    sum += int_read_from_file;
  }
  //Prints sum
  cout << sum << endl;
}
