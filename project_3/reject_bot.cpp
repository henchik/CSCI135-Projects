
#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

vector<vector<Action> > rb_dirs;
vector<int> broken_bots;
/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
  for(int i = 0; i < NUM; i++){
    vector<Action> rb_dir;
    rb_dirs.push_back(rb_dir);
  }
	log << "Start!" << endl;
}
Loc scan(Loc loc, Area &area){
  vector<vector<int> > scanning_order =
  {
    //{row, col}
    {-1, 0}, // UP
    {0, 1}, // RIGHT
    {1, 0}, // DOWN
    {0, -1}, // LEFT
    {-1, -1}, // UP-LEFT
    {-1, 1}, //UP-RIGHT
    {1, 1}, //DOWN-RIGHT
    {1, -1} //DOWN-LEFT
  };
  int debris_r = -2;
  int debris_c = -2;
  int offset = 1;
  int loc_r = loc.r;
  int loc_c = loc.c;
  //Loop until scanning out of range
  while(offset < ROWS && offset < COLS){
    for(int i = 0; i < scanning_order.size(); i++){
      if(area.inspect((loc_r + (offset * scanning_order[i][0])), (loc_c + (offset * scanning_order[i][1]))) == DEBRIS){
        debris_r = loc_r + offset * scanning_order[i][0];
        debris_c = loc_c + offset * scanning_order[i][1];
        Loc output = {debris_r, debris_c};
        return output;
      }
      if(i > 3){
        int corner_size = offset - 1;
        for(int j = 1; j <= corner_size; j++){
          if(area.inspect((loc_r + ((offset * scanning_order[i][0]) - (j * scanning_order[i][0]))), (loc_c + (offset * scanning_order[i][1]))) == DEBRIS){
            debris_r = loc_r + ((offset * scanning_order[i][0]) - (j * scanning_order[i][0]));
            debris_c = loc_c + (offset * scanning_order[i][1]);
            Loc output = {debris_r, debris_c};
            return output;
          }
          if(area.inspect((loc_r + (offset * scanning_order[i][0])), (loc_c + ((offset * scanning_order[i][1]) - (j * scanning_order[i][1])))) == DEBRIS){
            debris_r = loc_r + (offset * scanning_order[i][0]);
            debris_c = loc_c + ((offset * scanning_order[i][1]) - (j * scanning_order[i][1]));
            Loc output = {debris_r, debris_c};
            return output;
          }
        }
      }
    }
    offset++;
  }
  debris_r = -1;
  debris_c = -1;
  Loc output = {debris_r, debris_c};
  return output;
}
Action randomMove(){
  switch(rand() % 4) {
  case 0:
    return LEFT;
  case 1:
    return RIGHT;
  case 2:
    return UP;
  default:
    return DOWN;
  }
}
void removeDirection(int id, int idx){
  rb_dirs[id].erase(rb_dirs[id].begin() + idx);
}
void addDirection(int id, Action dir){
  rb_dirs[id].insert(rb_dirs[id].begin(), dir);
}
bool validMove(int id, Action dir, Area &area){
  Loc loc = area.locate(id);
  for(int i = 0; i < NUM; i++){
    Loc loc2 = area.locate(i);
    if(dir == UP && loc.r - 1 == loc2.r && loc.c == loc2.c){
        removeDirection(id, 0);
        addDirection(id, RIGHT);
        addDirection(id, UP);
        addDirection(id, UP);
        addDirection(id, LEFT);
        return false;
    }else if(dir == DOWN && loc.r + 1 == loc2.r && loc.c == loc2.c){
        removeDirection(id, 0);
        addDirection(id, LEFT);
        addDirection(id, DOWN);
        addDirection(id, DOWN);
        addDirection(id, RIGHT);
        return false;
    }else if(dir == LEFT && loc.r == loc2.r && loc.c - 1 == loc2.c){
        removeDirection(id, 0);
        addDirection(id, UP);
        addDirection(id, LEFT);
        addDirection(id, LEFT);
        addDirection(id, DOWN);
        return false;
    }else if(dir == RIGHT && loc.r == loc2.r && loc.c + 1 == loc2.c){
        removeDirection(id, 0);
        addDirection(id, DOWN);
        addDirection(id, RIGHT);
        addDirection(id, RIGHT);
        addDirection(id, UP);
        return false;
    }
  }
  return true;
}
void setDirections(int id, Loc current_loc, Loc intended_loc ,bool repairing){
  vector<Action> directions;
  //if diff_r is positive must move up, if negative must move down
  int diff_r = current_loc.r - intended_loc.r;
  //if diff_c is positive go left, if negative
  int diff_c = current_loc.c - intended_loc.c;
  while(diff_r != 0 || diff_c != 0){
    if(diff_r > 0){
      directions.push_back(UP);
      diff_r--;
    }else if(diff_r < 0){
      directions.push_back(DOWN);
      diff_r++;
    }else if(diff_c > 0){
      directions.push_back(LEFT);
      diff_c--;
    }else if(diff_c < 0){
      directions.push_back(RIGHT);
      diff_c++;
    }
  }
  if(repairing){
    if(current_loc.c >= intended_loc.c){
      directions.push_back(REPAIR_RIGHT);
    }else{
      directions.push_back(REPAIR_LEFT);
    }
  }
  rb_dirs[id] = directions;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
  if(area.inspect(row, col) == DEBRIS){
    return COLLECT;
  }
  if(rb_dirs[id].size() == 0){
    Loc intended_loc = scan(loc, area);
    log << "Robot " << id << " cleaning debris at " << intended_loc.r << " " << intended_loc.c << endl;
    setDirections(id, loc, intended_loc, false);
  }
  Action dir = rb_dirs[id][0];
  if(validMove(id, dir, area)){
    rb_dirs[id].erase(rb_dirs[id].begin());
  }else{
    Action dir = rb_dirs[id][0];
  }
  return dir;
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;

}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
