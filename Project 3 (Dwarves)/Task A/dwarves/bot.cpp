/*
Author: Chen Stanilovsky
Course: CSCI 135
Instructor: Genady Maryash
Assignment:  Project 3 Task A
Description: A program that controls a bot to collect lumber more efficiently
*/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

/*
FUNCTIONALITY TO ADD
BASED ON THE LOCATION OF THE DWARF, IF THE DWARF IS TO THE UP AND RIGHT OF A TREE
CHECK THE UP AND RIGHT OF THE RIGHT FOR EMPTY SPACE FIRST, SAME FOR IF DWARF IS
DOWN LEFT OF A TREE, CHECK THE DOWN AND LEFT OF THE TREE FOR EMPTY SPACES FIRST
(optimize distance traveled)
*/
/*
Given the coordinate of a location on the map, it finds an empty space either
up down left or right from the given location. This is used to find empty spaces
around trees so the dwarf can move there and chop it
*/
vector<int> findEmpty(Dwarf &dwarf, int r, int c){
  vector<int> out;
  int d_row = dwarf.row();
  int d_col = dwarf.col();
  if(d_row > r){
	  if(dwarf.look(r + 1, c) == EMPTY){
		 out.push_back(r + 1);
		 out.push_back(c);
	  }else if(dwarf.look(r, c - 1) == EMPTY){
		 out.push_back(r);
		 out.push_back(c - 1);
	  }else if(dwarf.look(r - 1, c) == EMPTY){
		 out.push_back(r - 1);
		 out.push_back(c);
	  }else if(dwarf.look(r, c + 1) == EMPTY){
		 out.push_back(r);
		 out.push_back(c + 1);
	  }else{
		 out.push_back(-1);
	  }
	}else{
		if(dwarf.look(r - 1, c) == EMPTY){
			out.push_back(r + 1);
			out.push_back(c);
		}else if(dwarf.look(r, c - 1) == EMPTY){
			out.push_back(r);
			out.push_back(c - 1);
		}else if(dwarf.look(r + 1, c) == EMPTY){
			out.push_back(r - 1);
			out.push_back(c);
		}else if(dwarf.look(r, c + 1) == EMPTY){
			out.push_back(r);
			out.push_back(c + 1);
		}else{
			out.push_back(-1);
		}
	}
  return out;
}
/*
This function loops through a border around the dwarf, starting at the 3x3 border
that direfctly surrounds the dwarf, then the 5x5 border that surrounds the 3x3
border etc... When it find a tree in the border, it check for an empty space at
locations were the tree could be chopped. If the location is found the function
returns a vector with the location of the empty space where the tree can be chopped
*/
vector<int> coordToMove(Dwarf &dwarf, int r, int c){
  vector<int> out;
  int offset = 1;
  while(true){
    for(int i = r - offset; i <= r + offset; i++){
      for(int j = c - offset; j <= c + offset; j++){
        if(dwarf.look(i, j) == PINE_TREE || dwarf.look(i, j) == APPLE_TREE){
          out = findEmpty(dwarf, i,j);
          if(out[0] == -1){
            continue;
          }else{
            return out;
          }
        }
      }
    }
    offset++;
  }
}

/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */
void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message
  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}


/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */
/*
This method first checks if there is a tree in a location where the dwarf could
chop it without having to move. If there is no such tree the method looks for a
location where to dwarf could stand with a chopable tree either up down left or
right
*/
void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
  // Look if there is a tree on the right from the dwarf
  if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
  }else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
  }
  else {
    vector<int> coords = coordToMove(dwarf, r, c);
    r = coords[0];
    c = coords[1];
    log << "Walk to " << r << " " << c << endl;
    dwarf.start_walk(r, c);
    return;
  }
}
