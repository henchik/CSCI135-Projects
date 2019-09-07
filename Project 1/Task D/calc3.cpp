/*
Author: Chen Stanilovsky
Course: CSCI-135
Instructor: Katherine Howitt
Assignment: Project 1 Task D
A program that reads from the cin a sequence of one or more non-negative integers
written in a file, formulas.txt, to be added or subtracted. After the input ends
(end-of-file is reached), the program will compute and print the result of the
input summation. Multiple squences can be incliuded in the text file separated
by semi-colons (;). The formulas can include squared numbers indicated with ^
*/

#include <iostream>
#include <string>
using namespace std;

int main(){
  string read_from_file, previous_operator;
  int sum = 0;
  int i = 0;
  int int_converted_from_string;
  while(cin >> read_from_file){
    //Put the number read from the file's length into a variable
    int length_string_read_from_file = read_from_file.length();
    //Check if the number read's length is > 1, if it is it might end with ^ or ;
    if(length_string_read_from_file > 1){
      //check if the number read is the end of a formula
      if(read_from_file.substr(length_string_read_from_file - 1, 1) == ";"){
        //check for ^
        if(read_from_file.substr(length_string_read_from_file - 2, 1) == "^"){
          //if the number is followed by ^ add the square of the number to the sum
          sum += stoi(read_from_file) * stoi(read_from_file);
        //If the number isn't followed by ^
        }else{
          //just add the number to the sum
          sum += stoi(read_from_file);
        }
      //Since the number is the end of the formula, print sum and reset sum to 0
      //and reset previous_operator to emply string
      cout << sum << endl;
      sum = 0;
      previous_operator = "";
    //If the number isn't the end of a formula
      }else{
      //Put the number read into a placeholder variable
      string num_read_holder = read_from_file;
      string operator_read_from_file;
      //Read the next string in the file which must be an operator
      cin >> operator_read_from_file;
      //If the operator is addition
      if(previous_operator == "+" || previous_operator == ""){
        //Check for ^
        if(num_read_holder.substr(length_string_read_from_file - 1, 1) == "^"){
          //If ^ is found add the number squared to the sum
          sum += stoi(num_read_holder) * stoi(num_read_holder);
        }else{
          //if ^ isn't found just add the number to the sum
          sum += stoi(num_read_holder);
        }
      //If the operator is subtraction
    }else if(previous_operator == "-"){
        //check for ^
        if(num_read_holder.substr(length_string_read_from_file - 1, 1) == "^"){
          //If ^ is found subtract the number squared from the sum
          sum -= stoi(num_read_holder) * stoi(num_read_holder);
        }else{
          //if ^ isn't found subtract just the number from the sum
          sum -= stoi(num_read_holder);
        }
      }
      previous_operator = operator_read_from_file;
    }
    //If the number's length is 1
    }else{
      //Put the number read into a placeholder variable
      string num_read_holder = read_from_file;
      string operator_read_from_file;
      //Read the next string in the file which must be an operator
      cin >> operator_read_from_file;
      //If the operator is addition
      if(previous_operator == "+" || previous_operator == ""){
        //Add the number to the sum
        sum += stoi(num_read_holder);
      //If the operator is subtraction
    }else if(previous_operator == "-"){
        //subtract the number from the sum
        sum -= stoi(num_read_holder);
      }
      previous_operator = operator_read_from_file;
    }
  }
}
