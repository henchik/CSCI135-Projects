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

bool moveUp;
bool moveLeft;
vector<vector<int> > checkedPos;

enum Movement{UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NONE};
/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */
Movement directionToMove(Dwarf &dwarf, int r, int c, int offset){
  //check up
  if (dwarf.look(r+(offset*-1), c) == PINE_TREE || dwarf.look(r+(offset*-1), c) == APPLE_TREE) {
    return Movement::UP;
  }
  //Check down
  else if (dwarf.look(r+offset, c) == PINE_TREE || dwarf.look(r+offset, c) == APPLE_TREE) {
    return Movement::DOWN;
  }
  //check left
  else if (dwarf.look(r, c+(offset*-1)) == PINE_TREE || dwarf.look(r, c+(offset*-1)) == APPLE_TREE) {
    return Movement::LEFT;
  }
  //check right
  else if (dwarf.look(r, c+offset) == PINE_TREE || dwarf.look(r, c+offset) == APPLE_TREE) {
    return Movement::RIGHT;
  }
  //check up-left diagonal
  else if (dwarf.look(r+(offset*-1), c+(offset*-1)) == PINE_TREE || dwarf.look(r+(offset*-1), c+(offset*-1)) == APPLE_TREE) {
    return Movement::UPLEFT;
  }
  //check up-right diagonal
  else if (dwarf.look(r+(offset*-1), c+(offset)) == PINE_TREE || dwarf.look(r+(offset*-1), c+(offset)) == APPLE_TREE) {
    return Movement::UPRIGHT;
  }
  //check down-left diagonal
  else if (dwarf.look(r+(offset), c+(offset*-1)) == PINE_TREE || dwarf.look(r+(offset), c+(offset*-1)) == APPLE_TREE) {
    return Movement::DOWNLEFT;
  }
  //check down-right diagonal
  else if (dwarf.look(r+offset, c+offset) == PINE_TREE || dwarf.look(r+offset, c+offset) == APPLE_TREE) {
    return Movement::DOWNRIGHT;
  }else{
    return Movement::NONE;
  }

}

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message
  moveUp = true;
  moveLeft = false;
  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

bool hasBeenChecked(vector<int> pos){
  for(int i = 0; i < checkedPos.size(); i++){
    for(int j = 0; j < checkedPos[i].size(); j++){

    }
  }
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

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
  // Look if there is a tree on the right from the dwarf
  if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
  }else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
  }
  else {
    /*
    FUNCTIONALITY TO ADD
    loop through closest positions near the dwarfs, r+1 c, then r-1 c, then r c+1
    etc..., you can use and offset for checking (r or c + offset), multiply offset
    by -1 each time to check +1 and -1
    */

    int offset = 1;
    while(true){
      Movement direction = directionToMove(dwarf, r, c, offset);
      if (direction == Movement::UP) {
        dwarf.start_walk(r + (offset*-1) + 1, c);
        log << "Walk to " << r + (offset*-1) + 1<< " " << c << endl;
        return;
      }else if (direction == Movement::DOWN) {
        dwarf.start_walk(r + offset - 1, c);
        log << "Walk to " << r + offset - 1<< " " << c << endl;
        return;
      }else if (direction == Movement::LEFT) {
        dwarf.start_walk(r, c+(offset*-1) + 1);
        log << "Walk to " << r << " " << c+(offset*-1) + 1 << endl;
        return;
      }else if (direction == Movement::RIGHT) {
        dwarf.start_walk(r, c + offset - 1);
        log << "Walk to " << r << " " << c + offset - 1<< endl;
        return;
      }else if (direction == Movement::UPLEFT) {
        dwarf.start_walk(r + (offset*-1) + 1, c + (offset*-1));
        log << "Walk to " << r + (offset*-1) + 1 << " " << c + (offset*-1) << endl;
        return;
      }else if (direction == Movement::UPRIGHT) {
        dwarf.start_walk(r +(offset*-1) + 1, c + offset);
        log << "Walk to " << r  +(offset*-1) + 1 << " " << c+ offset << endl;
        return;
      }else if (direction == Movement::DOWNLEFT) {
        dwarf.start_walk(r + offset - 1, c + (offset*-1));
        log << "Walk to " << r  + offset - 1<< " " << c + (offset*-1) << endl;
        return;
      }else if (direction == Movement::DOWNRIGHT) {
        dwarf.start_walk(r + offset - 1, c+offset);
        log << "Walk to " << r+ offset - 1 << " " << c+offset << endl;
        return;
      }
      offset++;
    }
    /*if(r == 0){
      moveUp = false;
      log << "TOUCHED EDGE" << endl;

    }else if(r >= ROWS - 1){
      moveUp = true;
      log << "TOUCHED EDGE" << endl;

    }
    if(c == 0){
      moveLeft = false;
      log << "TOUCHED EDGE" << endl;
    }else if (c >= COLS - 1) {
      log << "TOUCHED EDGE" << endl;
      moveLeft = true;
    }

    int vertOrHori = rand() % 2;
    if(vertOrHori){
      if(moveUp){
        r = r - 1;
      }else{
        r = r + 1;
      }
    }else{
      if(moveLeft){
        c = c - 1;
      }else{
        c = c + 1;
      }
    }*/
    log << "MOVING LEFT?: " << moveLeft << endl << "MOVING UP?: " << moveUp << endl;
    dwarf.start_walk(r, c);
    return;
  }
}
