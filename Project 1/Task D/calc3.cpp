/*
Author: Chen Stanilovsky
Course: CSCI-135
Instructor: Katherine Howitt
Assignment: Project 1 Task B
A program that reads from the cin a sequence of one or more non-negative integers
written in a file, formulas.txt, to be added or subtracted. After the input ends
(end-of-file is reached), the program will compute and print the result of the
input summation. Multiple squences can be incliuded in the text file separated
by semi-colons (;). The formulas can include squared numbers indicated with ^
*/

#include <iostream>
using namespace std;

int main(){
  int int_read_from_file;
  char char_read_from_file;
  //Reads the first value which is always an int (operators come after nums)
  cin >> int_read_from_file;
  //Sets sum to the first value
  int sum = int_read_from_file;
  //Loop untill end of file is reached
  while(cin >> char_read_from_file >> int_read_from_file){
    cout << char_read_from_file << endl << int_read_from_file;
  }
  //Print sum of last formula because while loop breaks before it can print
  //cout << sum << endl;
}
