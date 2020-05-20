#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROBOT_NUM = 50;

vector<Action> generateDirections(Loc current_loc, Loc intended_loc, bool repairing);
bool isValidMove(int id, Action dir);
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions
enum jbs{
  NOT_BUSY,
  BUSY
};

class Robot{
private:
  int id;
  jbs job_status;
  Loc current_loc;
  Loc job_loc;
  vector<Action> directions;
  static Area area;
  bool repairing;
public:
  Robot(Loc loc, int this_id){
    current_loc = loc;
    id = this_id;
    job_status = NOT_BUSY;
    repairing = false;
  }
  void updateArea(Area &_area){
    area = _area;
  }
  jbs getJobStatus(){
    return job_status;
  }
  Loc getLocation(){
    return current_loc;
  }
  void setJob(Loc loc){

    job_loc = loc;
    job_status = BUSY;
  }
  void removeJob(){
    job_status = NOT_BUSY;
  }
  void setDirections(bool repairing){
    directions = generateDirections(current_loc, job_loc, repairing);
  }
  void updateLocation(Action dir){
    if(dir == UP){
      current_loc = {current_loc.r - 1, current_loc.c};
    }else if(dir == DOWN){
      current_loc = {current_loc.r + 1, current_loc.c};
    }else if(dir == LEFT){
      current_loc = {current_loc.r, current_loc.c - 1};
    }else if(dir == RIGHT){
      current_loc = {current_loc.r, current_loc.c + 1};
    }

  }
  Action getNextMove(ostream &log){
    if(id == 0){
      log << "SIZE OF DIRECTIONS: " << directions.size() << endl;
    }
    if(directions.size() == 0){
      if(id == 0){
        log << "SIZE IS 0 REMOVING JOB" << endl;
      }
      removeJob();
      if(repairing){
        repairing = false;
        return UP;
      }else{
        return COLLECT;
      }
    }
    Action dir = directions[0];
    vector<Action> new_directions;
    for(int i = 1; i < directions.size(); i++){
      new_directions.push_back(directions[i]);
    }
    directions = new_directions;
    if(id == 0){
      log << "LENGTH OF DIRECTIONS FOR ROBOT " << id << " " << directions.size() << endl;
    }
    return dir;
  }
};
vector<Robot> robots;
/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
  for(int i = 0; i < NUM; i++){
    Robot rb = Robot(area.locate(i), i);
    robots.push_back(rb);
  }
	log << "Start!" << endl;
}
bool isValidMove(int id, Action dir){
  Robot rb = robots[id];
  Loc loc = rb.getLocation();
  for(int i = 0; i < robots.size(); i++){
    Robot rb2 = robots[i];
    Loc rb2_loc = rb2.getLocation();
    if(dir == UP){
      if(loc.r - 1 == rb2_loc.r && loc.c == rb2_loc.c){
        return false;
      }
    }else if(dir == RIGHT){
      if(loc.r == rb2_loc.r && loc.c + 1 == rb2_loc.c){
        return false;
      }
    }else if(dir == DOWN){
      if(loc.r + 1 == rb2_loc.r && loc.c == rb2_loc.c){
        return false;
      }
    }else if(dir == LEFT){
      if(loc.r == rb2_loc.r && loc.c - 1 == rb2_loc.c){
        return false;
      }
    }
  }
  return true;
}
vector<Action> generateDirections(Loc current_loc, Loc intended_loc ,bool repairing){
  vector<Action> dirs;
  //if diff_r is positive must move up, if negative must move down
  int diff_r = current_loc.r - intended_loc.r;
  //if diff_c is positive go left, if negative
  int diff_c = current_loc.c - intended_loc.c;
  while(diff_r != 0 || diff_c != 0){
    if(diff_r > 0){
      dirs.push_back(UP);
      diff_r--;
    }else if(diff_r < 0){
      dirs.push_back(DOWN);
      diff_r++;
    }else if(diff_c > 0){
      dirs.push_back(LEFT);
      diff_c--;
    }else if(diff_c < 0){
      dirs.push_back(RIGHT);
      diff_c++;
    }
  }
  if(repairing){
    if(current_loc.c >= intended_loc.c){
      dirs.push_back(REPAIR_RIGHT);
    }else{
      dirs.push_back(REPAIR_LEFT);
    }
  }
  return dirs;
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

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
  Robot *rb = &(robots[id]);
  jbs js = rb->getJobStatus();
  if(js == NOT_BUSY){
    Loc job_loc = scan(loc, area);
    rb->setJob(job_loc);
    rb->setDirections(false);
  }
  Action dir = rb->getNextMove(log);
  rb->updateLocation(dir);
  return dir;
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
