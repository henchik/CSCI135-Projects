/*
Author: Chen Stanilovsky
Course: CSCI 135
Instructor: Gennadiy Maryash
Assignment:  Project 2
Description: A program that reports the following:
Pronunciation : the pronunciation of the word W (as given in the dictionary),
Identical : other words from the dictionary with the same pronunciation as W,
Replace phoneme : words that can be obtained from W by replacing one phoneme.
Add phoneme : words that can be obtained from W by adding one phoneme,
Remove phoneme : words that can be obtained from W by removing one phoneme,
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

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
string getPronunciation(string s, ifstream& dict){
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
string getIdentical(string word, string pronunciation, ifstream& dict){
  string out = "";
  dict.open("dict.txt");
  if(dict.is_open()){
    while(!dict.eof()){
      string line;
      getline(dict, line);
      vector<string> split_string = splitOnSpace(line);
      if((split_string[1] == pronunciation) && split_string[0] != word) {
        if(validWord(split_string[0])){
          out += split_string[0] + " ";
        }
      }
    }
  }
  dict.close();
  return out;
}
vector<string> splitPronunciation(string pronunciation){
  vector<string> output;
  string syllable = "";
  for(int i = 0; i < pronunciation.length(); i++){
    if(pronunciation[i] == ' '){
      output.push_back(syllable);
      syllable = "";
    }else{
      syllable += pronunciation[i];
    }
  }
  output.push_back(syllable);
  return output;
}
int pronunciationDifference(vector<string> pro_1, vector<string> pro_2){
  //The initial differenc count is set to the differnece in length of phonemes
  //int diff = pro_1.size() - pro_2.size();
  int count = 0;//abs(diff);
  //if the length of 1 is less than 2 loop untill end of 1
  if(pro_1.size() == pro_2.size()){
    for(int i = 0; i < pro_1.size(); i++){
      if(pro_1[i] != pro_2[i]){
        count++;
      }
    }
  }
  else if(pro_1.size() < pro_2.size()){
    for(int i = 0, j = 0; j < pro_2.size(); i++, j++){
      //each time a phoneme is not the same increment count
      if(i >= pro_1.size()){
        count++;
      }else if(pro_1[i] != pro_2[j]){
        count++;
        i--;
      }
    }
  //if the loength of 2 is less than 1 loop untill end of 2
  }else if(pro_2.size() < pro_1.size()){
    for(int i = 0, j = 0; i < pro_1.size(); i++, j++){
      //each time a phoneme is not the same increment count
      if(j >= pro_2.size()){
        count++;
      }else if(pro_1[i] != pro_2[j]){
        count++;
        j--;
      }
    }
  }
  return count;
}
string replacePhoneme(string word, string pronunciation, ifstream& dict){
  string output = "";
  //get the split pronunciation of the input word
  vector<string> given_split_pro = splitPronunciation(pronunciation);
  dict.open("dict.txt");
  if(dict.is_open()){
    while(!dict.eof()){
      string line;
      getline(dict, line);
      //split dictionary entry into word and pronunciaton
      vector<string> split_string = splitOnSpace(line);
      //Split pronunciation of read word into vector of strings
      vector<string> read_split_pro = splitPronunciation(split_string[1]);
      //If the length of pronunciations are the same, it is possible that one
      //was replaced and it guarantees that one wasnt added or removed
      if(given_split_pro.size() == read_split_pro.size()){
        //If the difference in pronunciations is only by 1 phoneme, add the read
        //word to the output;
        //THE PRONUNCIATIONDIFFERENCE METHOD IS PROBABLY THE PROBLEM
        if(pronunciationDifference(given_split_pro, read_split_pro) == 1){
          if(validWord(split_string[0])){
            output += split_string[0] + " ";
          }
        }
      }
    }
    dict.close();
  }
  return output;
}
string addPhoneme(string word, string pronunciation, ifstream& dict){
  string out = "";
  vector<string> given_split_pro = splitPronunciation(pronunciation);
  dict.open("dict.txt");
  if(dict.is_open()){
    while(!dict.eof()){
      string line;
      getline(dict, line);
      vector<string> split_string = splitOnSpace(line);
      vector<string> read_split_pro = splitPronunciation(split_string[1]);
      if(given_split_pro.size() + 1 == read_split_pro.size()){
        if(pronunciationDifference(given_split_pro, read_split_pro) == 1){
          if(validWord(split_string[0])){
            out += split_string[0] + " ";
          }
        }
      }
    }
  }
  dict.close();
  return out;
}
string removePhoneme(string word, string pronunciation, ifstream& dict){
  string output = "";
  //get the split pronunciation of the input word
  vector<string> given_split_pro = splitPronunciation(pronunciation);
  dict.open("dict.txt");
  if(dict.is_open()){
    while(!dict.eof()){
      string line;
      getline(dict, line);
      //split dictionary entry into word and pronunciaton
      vector<string> split_string = splitOnSpace(line);
      //Split pronunciation of read word into vector of strings
      vector<string> read_split_pro = splitPronunciation(split_string[1]);
      //If the length of pronunciations are the same, it is possible that one
      //was replaced and it guarantees that one wasnt added or removed
      if((given_split_pro.size() - 1) == read_split_pro.size()){
        //If the difference in pronunciations is only by 1 phoneme, add the read
        //word to the output;
        //THE PRONUNCIATIONDIFFERENCE METHOD IS PROBABLY THE PROBLEM
        if(pronunciationDifference(given_split_pro, read_split_pro) == 1){
          if(validWord(split_string[0])){
            output += split_string[0] + " ";
          }
        }
      }
    }
    dict.close();
  }
  return output;

}
int main(int argc, char const *argv[]) {
  /*cout << (splitPronunciation("D IH0 F ER1").size() + 1 == splitPronunciation("D IH0 F ER1 D").size()) << endl;
  cout << validWord("DEFERRED") << endl;
  cout << pronunciationDifference(splitPronunciation("D IH0 F ER1"), splitPronunciation("D IH0 F D D D ER1"));*/
  string word;
  cout << "> ";
  cin >> word;
  for(int i = 0; i < word.length(); i++){
    word[i] = toupper(word[i]);
  }
  if(validWord(word)){
    ifstream dict;
    string pronunciation = getPronunciation(word, dict);
    string identical = getIdentical(word, pronunciation, dict);
    string replace = replacePhoneme(word, pronunciation, dict);
    string add = addPhoneme(word, pronunciation, dict);
    string remove = removePhoneme(word, pronunciation, dict);
    if (!(pronunciation == "Not found")) {
      cout << endl << "Pronunciation    : " + pronunciation << endl << endl;
      cout << "Identical        : " + identical << endl;
      cout << "Replace phoneme  : " + replace << endl;
      cout << "Add phoneme      : " + add << endl;
      cout << "Remove phoneme   : " + remove << endl;
    }else{
      cout << endl << pronunciation << endl;
    }
  }else{
    cout << endl << "Not found" << endl;
  }
  return 0;
}
