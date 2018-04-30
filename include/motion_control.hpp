#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include <string>
#include <iostream>
#include <queue>

using namespace std;

class MotionControl {
  public:
    MotionControl(int (&p_chess_board)[8][8],
                  int(&p_points_chess_board[17][17])
                 ):chess_board(p_chess_board),
                   points_chess_board(p_points_chess_board){};
    ~MotionControl(){};

    queue<string> get_path(int, int, int, int);

  private:
    int (&chess_board)[8][8];
    int (&points_chess_board)[17][17];
};

#endif
