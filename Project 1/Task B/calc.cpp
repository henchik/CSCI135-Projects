/*
Author: Chen Stanilovsky
Course: CSCI-135
Instructor: Katherine Howitt
Assignment: Project 1 Task B
A program that reads from the cin a sequence of one or more non-negative integers
written in a file, formula.txt, to be added or subtracted. After the input ends
(end-of-file is reached), the program will compute and print the result of the
input summation.
*/

#include <iostream>
#include <string.h>
using namespace std;

int main(){
  int int_read_from_file;
  char operator_read_from_file;
  //Reads the first value which is always an int (operators come after nums)
  cin >> int_read_from_file;
  //Sets sum to the first value
  int sum = int_read_from_file;
  //Loop untill end of file is reached
  while(cin >> operator_read_from_file >> int_read_from_file){
    //If operator is +, add the following number to the sum
    if(operator_read_from_file == '+'){
      sum += int_read_from_file;
    //If operator is -, subtract the following number from the sum
    }else if(operator_read_from_file == '-'){
      sum -= int_read_from_file;
    }
  }
  //Print sum
  cout << sum << endl;
}
