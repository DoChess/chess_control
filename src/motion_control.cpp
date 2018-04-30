#include <,,/include/motion_control.hpp>

void MotionControl::get_path(int x_origin, int y_origin, 
                                      int x_destiny, int y_destiny){
  queue<string> commands;
  
  if(abs(x_origin - x_destiny == 1) or abs(y_origin - y_destiny) == 1){
  }else{
    if(x_destiny > x_origin){
           
    }else{

    }
    
  }
}

void MotionControl::move_CNC_to_origin_cell(){
  
}

void MotionControl::switch_on_magnet(){
  string switch_on_instruction = "G1";
  queue.push_back(switch_on_instruction);
}

void MotionControl::switch_off_magnet(){
  string switch_off_instruction = "G2";
  queue.push_back(switch_off_instruction);
}

void MotionControl::set_CNC_to_initial_position(){
  string switch_on_instruction = "G3";
  queue.push_back(switch_on_instruction);
}
