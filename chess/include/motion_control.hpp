#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;
using par = pair<int,int>;

class MotionControl {
  public:
    MotionControl(int (&p_chess_board)[8][8],
                  int (&p_points_chess_board)[17][17],
                  queue<string> &p_commands_queue
                 ):chess_board(p_chess_board),
                   points_chess_board(p_points_chess_board),
                   commands_queue(p_commands_queue),
                   magnet_is_on(true){};

    ~MotionControl(){};
    
    bool magnet_is_on;
    queue<string> &commands_queue;
    void get_path(int, int, int, int);
    void switch_on_magnet();
    void switch_off_magnet();
    void move_CNC_to_origin_cell(int, int); 
    void generate_commands(int, int, int, int, int, int, int);
    par get_white_free_cemetery();
    par get_black_free_cemetery();
    
  private:
    bool is_it_a_capture_movement(int, int);
    int (&chess_board)[8][8];
    int (&points_chess_board)[17][17];
    par white_cemetery = make_pair(1, -3);
    par black_cemetery = make_pair(1, 19);
};

#endif
