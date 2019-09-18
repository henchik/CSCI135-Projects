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
using namespace std;

bool isEndOfFormula(string str){
  if(str[str.length() - 1] == ';'){
    return true;
  }
  return false;
}
bool isSquared(string str){
  if(isEndOfFormula(str)){
    if(str[str.length() - 2] == '^'){
      return true;
    }
  }else{
    if(str[str.length() - 1] == '^'){
      return true;
    }
  }
  return false;
}
bool isAddition(string oper){
  if(oper == "+" || oper == ""){
    return true;
  }
  return false;
}
int main(){
  string reader, previous_operator;
  int total = 0;
  int int_from_string;
  while(cin >> reader){
    bool squared = isSquared(reader);
    bool endOfFormula = isEndOfFormula(reader);
    bool adding = isAddition(previous_operator);
    if(endOfFormula){
      if(reader.length() > 1){
        if(squared){
          if(adding){
            total += stoi(reader) * stoi(reader);
          }else{
            total -= stoi(reader) * stoi(reader);
          }
        }else{
          if(adding){
            total += stoi(reader);
          }else{
            total -= stoi(reader);
          }
        }
      }
      cout << total << endl;
      total = 0;
      previous_operator = "";
    }else{

      string operator_read;
      cin >> operator_read;
      if(squared){
        if(adding){
          total += stoi(reader) * stoi(reader);
        }else{
          total -= stoi(reader) * stoi(reader);
        }
      }else{
        if(adding){
          total += stoi(reader);
        }else{
          total -= stoi(reader);
        }
      }
      if(isEndOfFormula(operator_read)){
        cout << total << endl;
        total = 0;
        previous_operator = "";
      }else{
        previous_operator = operator_read;
      }
    }

  }
}
