/*
Author: Chen Stanilovsky
Course: CSCI-135
Instructor: Katherine Howitt
Assignment: Project 1 Task D
A program that reads from the cin a sequence of one or more non-negative integers
written in a file, formulas.txt, to be added or subtracted. After the input ends
(end-of-file is reached), the program will compute and print the result of the
input totalmation. Multiple squences can be incliuded in the text file separated
by semi-colons (;). The formulas can include squared numbers indicated with ^
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
  string reader, previous_operator;
  int previous_num;
  int total = 0;
  int int_read;
  string num = "";
  bool num_squared = false;
  while(cin >> reader){
    //Loops through each index of read string
    for(int i = 0; i < reader.length(); i++){
      //get character at indeex i
      char c = reader[i];
      //If the character is + or -
      if(c == '+' || c == '-'){
        //If num is not empty, check previous operator and the num_squared bool
        //Add/Subtract/Square accordingly
        if(num.length() > 0){
          if(previous_operator == "+" || previous_operator == ""){
            if(num_squared){
              total += stoi(num) * stoi(num);
            }else{
              total += stoi(num);
            }
          }else{
            if(num_squared){
              total -= stoi(num) * stoi(num);
            }else{
              total -= stoi(num);
            }
          }
        }
        //After total is updated, reset num and set previous operator to the one
        //at index i
        previous_operator = c;
        num = "";
        num_squared = false;
      //If end of formula is reached
      }else if(c == ';'){
        //If num is not empty
        if(num.length() > 0){
          //check previous operator and num_squared, add/subtract/square accordingly
          if(previous_operator == "+" || previous_operator == ""){
            if(num_squared){
              total += stoi(num) * stoi(num);
            }else{
              total += stoi(num);
            }
          }else{
            if(num_squared){
              total -= stoi(num) * stoi(num);
            }else{
              total -= stoi(num);
            }
          }
        }
        //Since end of formula is reached, print total, and reset
        cout << total << endl;
        total = 0;
        previous_operator = "";
        num = "";
        num_squared = false;
      }else if(c == '^'){
        //If ^ is found, set num_squared bool to true to indicate that the number is squared
        num_squared = true;
      }
      else{
        //If the character read is a number, concatenate it to num
        num += c;
      }

    }
  }
}
