
#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

vector<vector<int> > mf_bots;

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;

	log << "Start!" << endl;
}

Action dirToMove(Loc loc, Area &area, bool is_helping, int id){
  int r = loc.r;
  int c = loc.c;
  if(is_helping){
    int mf_r = -1;
    int mf_c = -1;
    for(int i = 0; i < mf_bots.size(); i++){
      if(mf_bots[i][3] == id){
        mf_r = mf_bots[i][0];
        mf_c = mf_bots[i][1];
        break;
      }
    }
    if(r < mf_r - 1){
      return DOWN;
    }else if(r > mf_r + 1){
      return UP;
    }else if(c < mf_c - 1){
      return RIGHT;
    }else if(c > mf_c + 1){
      return LEFT;
    }
  }else{
    int offset = 1;
    while(true){
      for(int i = r - offset; i <= r + offset; i++){
        for(int j = c - offset; j <= c + offset; j++){
          if(i == r && j == c){
            continue;
          }
          if(area.inspect(i,j) == DEBRIS){
            if(i > r){
              return DOWN;
            }else if(i < r){
              return UP;
            }else if(j > c){
              return RIGHT;
            }else if(j < c){
              return LEFT;
            }
          }
        }
      }
      offset++;
      if(offset > ROWS && offset > COLS){
        break;
      }
    }
  }
  //Default movement
  return UP;
}

//MAKE ONLY THE FIRST BOT ID 0 AS A REPAIR BOT IT WILL LOOK AT THE MF_BOTS ARRAY AND SEE IFA NY BOTS ARE MALFUNCTIONING, IT WILL ONLY MOVE TOWARDS THE BOT AT INDEX 0 AND FIX IT, THE ERASE THE FIRST INDEX AND CONTINUE CHECKING IF A BOT IS MALFUNCTIONING, KEEP REPAITING UNTILL THE ARRAY IS EMPTY, THEN COLLECT
/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
  if()
  //Check if bot is malfunctioning
  if(id == 0){
    if(row - 1 == mf_r && col == mf_c){
      mf_bots.erase(mf_bots.begin() + mf_idx, mf_bots.begin() + mf_idx + 1);
      log << id << " Is repairing up at " << mf_r << mf_c << endl;
      return REPAIR_UP;
    }else if(row + 1 == mf_r && col == mf_c){
      mf_bots.erase(mf_bots.begin() + mf_idx, mf_bots.begin() + mf_idx + 1);
      log << id << " Is repairing down at " << mf_r << mf_c << endl;
      return REPAIR_DOWN;
    }else if(row == mf_r && col - 1 == mf_c){
      mf_bots.erase(mf_bots.begin() + mf_idx, mf_bots.begin() + mf_idx + 1);
      log << id << " Is repairing left at " << mf_r << mf_c << endl;
      return REPAIR_LEFT;
    }else if(row == mf_r && col + 1 == mf_c){
      mf_bots.erase(mf_bots.begin() + mf_idx, mf_bots.begin() + mf_idx + 1);
      log << id << " Is repairing right at " << mf_r << mf_c << endl;

      return REPAIR_RIGHT;
    }else{
      return dirToMove(loc, area, id);
    }
  }else{
    if (area.inspect(row, col) == DEBRIS)
  		return COLLECT;
  	else {
      return dirToMove(loc, area, id);
  	}
  }
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
  //send coordinate location to vector (2d vector with row, col, id of malfunctionging bot, id of bot to fix malfunction)
  //assign a specfific bot to move towards this robot
  //when it fixes it, remove location from vector
	log << "Robot " << id << " is damaged." << endl;
  vector<int> mf_info;
  mf_info.push_back(loc.r);
  mf_info.push_back(loc.c);
  mf_info.push_back(id);
  mf_bots.push_back(mf_info);
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
