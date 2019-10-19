/*
Author: Chen Stanilovsky
Course: CSCI 135
Instructor: Gennadiy Maryash
Assignment:  Project 2 Phase I
Description: A program that reports the following:
Pronunciation : the pronunciation of the word W (as given in the dictionary),
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string stringToUpper(string s){
  string out;
  for(int i = 0; i < s.size(); i++){
    out += toupper(s[i]);
  }
  return out;
}
vector<string> splitOnSpace(string s){
  vector<string> output;
  string before, after;
  bool reached_space = false;
  //loop through string param: s
  for(int i = 0; i < s.length(); i++){
    //while the first space hasnt been reached
    if(!reached_space){
      //check if the char at index i is a space
      if(isspace(s[i])){
        //if char at index i is space, indicate that first space has been reached
        //do nothing at this index and skip the next index which will also be a space
        reached_space = true;
        i++;
      }else{
        //If char at index i is not a space and the first space havent been reached
        //concatenate char to the before string
        before += s[i];
      }
    //check if the first space has been reached
    }else{
      //if this char comes after the first space concateneate it to the after string
      after += s[i];
    }
  }
  //push before and after strings into output vector
  output.push_back(before);
  output.push_back(after);
  //return vector with 2 strings, before and after
  return output;
}
string getPronunciation(string s){
  ifstream dict;
  //open file stream
  dict.open("dict.txt");
  //If file is successfully opened
  if(dict.is_open()){
    //loop until end of file is reached
    while(!dict.eof()){
      string line;
      //read one line of file
      getline(dict, line);
      //split line into before and after variables stored in a vector
      vector<string> split_string = splitOnSpace(line);
      //check if the before variable in the split_string vector matches the string we
      //are looking for
      if(split_string[0] == s){
        //close file stream and return the after variable which contains the
        //pronunciation
        dict.close();
        return split_string[1];
      }
    }
  }
  //If end of file is reached and a matching string wasn't found, return not found
  return "Not found";
}
bool validWord(string s){
  //If the string ends with ), this indicates and alternate pronunciation, these
  //are ignored, so return false
  if(s.substr(s.length() - 1, s.length()) == ")"){
    return false;
  }
  //Loop through entire string
  for(int i = 0; i < s.length(); i++){
    //If the char at index i is within the range for capital letters (ASCII 65-90)
    //or the value for apostraphe (ASCII 39), do nothing
    if((s[i] >= 65 && s[i] <= 90) || (s[i] == 39)){
      continue;
    //if char at index i is outside of the proper range of ascii values, return false
    }else{
      return false;
    }
  }
  //if the loop completes the string and no invalid chars are found, return true
  return true;
}
int main(int argc, char const *argv[]) {
  string word;
  cout << "> ";
  cin >> word;
  word = stringToUpper(word);
  if(validWord(word)){
    cout << "\n\nPronunciation    : " << getPronunciation(word) << endl;
  }else{

    cout << "\n\nNot Found" << endl;
  }
  return 0;
}
