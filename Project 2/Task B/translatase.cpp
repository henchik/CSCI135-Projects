/*
Author: Chen Stanilovsky
Course: CSCI-136
Instructor: Professor Maryash
Assignment: Project 2 Task B
A program that reads a text file called dna.txt that contains one DNA strand per
line, and outputs to the console (terminal) the corresponding mRNA strands.
*/
#include <iostream>
#include <fstream>

using namespace std;

string dictionary_read(ifstream &dict, string key) {
    string key_reader, value_reader;
    dict.clear(); // reset error state
    dict.seekg(0); // return file pointer to the beginning
    while (dict >> key_reader >> value_reader) {
      if(key == key_reader){
        return value_reader;
      }
    }
    return "Value not found";
}

string dna_to_mrna(string dna){
  string out = "";
  for(int i = 0; i < dna.length(); i++){
      switch(dna[i]){
        case 'A':
          out += 'U';
          break;
        case 'T':
          out += 'A';
          break;
        case 'C':
          out += 'G';
          break;
        case 'G':
          out += 'C';
          break;
      }
    }
    return out;
}
string translate(string dna, ifstream &dict){
  string mrna = dna_to_mrna(dna);
  bool start = false;
  string out = "";
  for(int i = 0; i < mrna.length(); i+= 3){
    string codon = mrna.substr(i,3);
    if(codon == "AUG"){
      start = true;
    }
    if(codon == "UAA" || codon == "UAG" || codon == "UGA"){
      start = false;
      break;
    }
    if(start){
      out += dictionary_read(dict, codon);
      out += "-";
    }
  }
  out = out.substr(0, out.length() - 1);
  return out;
}
int main(){
  ifstream fin("dna2b.txt");
  ifstream codons("codons.tsv");
  if(fin.fail() || codons.fail()){
    cerr << "File cannot be read, opened, or does not exist.\n";
    exit(1);
  }
  string strand;
  while(getline(fin, strand)) {
    cout << translate(strand, codons) << endl << endl;
  }
}
