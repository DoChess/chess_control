#include <utility>
#include <iostream>
#include <queue>
#include <sstream>
#include "../include/motion_validation.hpp"
#include "../utils/shared_memory.cpp"
#include "../include/motion_control.hpp"

// Voice recognition include.
#include "../include/recognition.hpp"

using namespace std;

using coordinate = pair<int,int>;

#define WHITE_ROOK 1
#define WHITE_KNIGHT 2
#define WHITE_BISHOP 3
#define WHITE_QUEEN 4
#define WHITE_KING 5
#define WHITE_PAWN 6

#define BLACK_ROOK 7
#define BLACK_KNIGHT 8
#define BLACK_BISHOP 9
#define BLACK_QUEEN 10
#define BLACK_KING 11
#define BLACK_PAWN 12

int chess_board[8][8] = {{1,2,3,4,5,3,2,1},
  {6,6,6,6,6,6,6,6},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {12,12,12,12,12,12,12,12},
  {7,8,9,10,11,9,8,7}};

int points_chess_board[17][17];
coordinate CNC_position;

void initialize_statements(){
  for(int i = 0;i < 18;++i){
    for( int j = 0;j < 18;++j){
      if(i % 2 != 0 and j % 2 != 0) points_chess_board[i][j] = 0;
      else points_chess_board[i][j] = 1;
    }
  }

  CNC_position = make_pair(0, 0);
}

vector<string> split_command(string full_message){
  stringstream ss(full_message);
  string word;
  vector<string> coordinates;
  while(ss >> word){
    coordinates.push_back(word);
  }
  return coordinates;
}

int main(){
  // Investigate why it musts be inside main
  queue<string> commands_queue;

  initialize_statements();
  MotionValidation motion_validator = MotionValidation(chess_board);
  motion_validator.initialize_dictionaries();

  MotionControl motion_control = MotionControl(chess_board, points_chess_board,
      commands_queue);

  char main_state;
  queue<string> front_messages;
  bool fix_on_grammar;
  int turn = 1;

  initialize_statements();
  attach_memory();

  string msg = "";

  // Added to be used on movimentation
  int x_origin;
  int y_origin; 
  int x_destiny;
  int y_destiny;

  bool is_a_capture_movement;
  bool is_a_valid_movement;

  while(1){
    //start listening 
    msg = "11";

    if(msg == "11"){
      string a(data);  
      if(a == "None"){
        strncpy(data, "11", SHM_SIZE);
      }

      while(1){
        msg = "chess";

        if(msg == "chess"){
          //Comando para o front trocar a cor e indicar que está esperando o resto do comando;

          string b(data);
          if(b == "None"){
            strncpy(data, "31", SHM_SIZE);
          }

          msg = "ECHO TWO ECHO FOUR MOVE";

          fix_on_grammar = true;

          if(fix_on_grammar){
            main_state = 2;
            vector<string> coordinates = split_command(msg);
            is_a_valid_movement = motion_validator.validate_command(coordinates[1],coordinates[0], coordinates[3], coordinates[2], turn);

            if(is_a_valid_movement){
              x_origin = (motion_validator.number_coordinates[coordinates[1]] * 2) + 1;
              y_origin = (motion_validator.fonetic_alphabet_coordinates[coordinates[0]] * 2) + 1;
              x_destiny = (motion_validator.number_coordinates[coordinates[3]] * 2) + 1;
              y_destiny = (motion_validator.fonetic_alphabet_coordinates[coordinates[2]] * 2) + 1;

              // Calculating commands to send to microcontroller
              motion_control.generate_commands(x_origin, y_origin, x_destiny,
                y_destiny, CNC_position.first, CNC_position.second);

              while(not commands_queue.empty()){
                string word = commands_queue.front(); commands_queue.pop();
              }
            
              // Update CNC position in memory
              CNC_position.first = x_destiny;
              CNC_position.second = y_destiny;

            }else{
              printf("O Comando foi invalido");
              // Mandar sinal para o front
              continue;
            }

            a = "3";
            a += (is_a_valid_movement?'1':'0');
            a += '2';
            a += msg;

            strncpy(data, a.c_str(), SHM_SIZE);
            break;

          }else{
            a = "322";
            a += msg;
            strncpy(data, a.c_str(), SHM_SIZE);
            printf("Invalid grammar result.\n");
            continue;
          }
        }
      }
    }

  }

  detach_memory();
    
  // VOICE RECOGNITION
  bool hear_flag = false;
  string desired_command = HEAR_ERROR;

  string command = "";
  command = hear_chess(hear_flag, desired_command);
  printf("\n\n\nMAIN: %s\n\n\n", command.c_str());

  command = hear_move(hear_flag, desired_command);
  printf("\n\n\nMAIN: %s\n\n\n", command.c_str());

  return 0;
}
