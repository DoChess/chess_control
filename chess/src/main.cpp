#include <utility>
#include <iostream>
#include <queue>
#include <sstream>
#include "../include/motion_validation.hpp"
#include "../utils/shared_memory.cpp"
//#include "../utils/microphone_controller.cpp"
#include "../include/motion_control.hpp"
#include "../include/communication.hpp"
#include "../include/checkmate_checker.hpp"

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

  CNC_position = make_pair(16, 0);
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

void print_actual_chess_board(MotionValidation motion_validator){
  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      string piece = motion_validator.piece_types[chess_board[i][j]].c_str();
      if(piece == "") printf("%s","     EMPTY");
      else{
        for(int i = 0;i < 10 - piece.size();++i) printf(" ");
        printf("%s", piece.c_str());
      }
    }
    printf("\n");
  }
}

bool read_and_write_in_shared_memory(string write_data){
  string shared_memory_content = string(data);

  cout << "Este é o valor  do shared_memory_content = " << shared_memory_content << endl;

  if(shared_memory_content == "None")
  {
    strncpy(data, write_data.c_str(), SHM_SIZE);
  }
  else if (shared_memory_content == "15")
  {
    char none[5] = "None";
    strncpy(data, none, SHM_SIZE);
    return false;
  }

  return true;
}

int main(){
  short qtd_matches = 0;
  while (qtd_matches < 2) {
    queue<string> commands_queue;
    string desired_command = HEAR_ERROR;
    bool hear_flag = false;

    initialize_statements();
    MotionValidation motion_validator = MotionValidation(chess_board);
    motion_validator.initialize_dictionaries();

    MotionControl motion_control = MotionControl(chess_board, points_chess_board,
        commands_queue);

    queue<string> front_messages;
    bool fix_on_grammar;
    int turn = 0;
    int sent_commands_counter = 0;

    initialize_statements();
    attach_memory();
    //open_comport();

    string display_msg = "";

    int x_origin_point; int y_origin_point;
    int x_destiny_point; int y_destiny_point;
    int x_origin; int y_origin; int x_destiny;int y_destiny;

    bool is_a_capture_movement;bool is_a_valid_movement;

    string shared_memory_content;

    hear_begin(hear_flag, desired_command);

    display_msg = "11";

    read_and_write_in_shared_memory("11");

    while(1){
      //if(!read_and_write_in_shared_memory("35")){break;}

      hear_chess(hear_flag, desired_command);

      display_msg = "332Listening";

      //Comando para o front trocar a cor e indicar que está esperando o resto do comando;
      if(!read_and_write_in_shared_memory(display_msg)){break;}

      string listened_command = hear_command(hear_flag, desired_command);

      if(!read_and_write_in_shared_memory("342" + listened_command)){break;}
      string feedback = hear_feedback(hear_flag, desired_command);

      if(feedback == "repeat"){
        if(!read_and_write_in_shared_memory("35")){break;}
        continue;      
      }

      vector<string> coordinates = split_command(listened_command);
      is_a_valid_movement = motion_validator.validate_command(coordinates[1],coordinates[0], coordinates[3], coordinates[2], turn);

      if(is_a_valid_movement){
        display_msg = "312" + listened_command;

        if(!read_and_write_in_shared_memory(display_msg)){break;}

        x_origin_point = (motion_validator.number_coordinates[coordinates[1]] * 2) + 1;
        y_origin_point = (motion_validator.fonetic_alphabet_coordinates[coordinates[0]] * 2) + 1;
        x_destiny_point = (motion_validator.number_coordinates[coordinates[3]] * 2) + 1;
        y_destiny_point = (motion_validator.fonetic_alphabet_coordinates[coordinates[2]] * 2) + 1;

        x_origin = motion_validator.number_coordinates[coordinates[1]];
        y_origin = motion_validator.fonetic_alphabet_coordinates[coordinates[0]];
        x_destiny = motion_validator.number_coordinates[coordinates[3]];
        y_destiny = motion_validator.fonetic_alphabet_coordinates[coordinates[2]];

        // Calculating commands to send to microcontroller
        motion_control.generate_commands(x_origin_point, y_origin_point, x_destiny_point,
            y_destiny_point, CNC_position.first, CNC_position.second, turn);

        printf("SENDING COMMANDS TO MICROCONTROLLER:\n\n");
        while(not commands_queue.empty()){
          string word = commands_queue.front(); commands_queue.pop();
          send_command(word);
        }
        printf("\n\nALL COMMANDS SENT TO MICROCONTROLLER.\n\n");

        chess_board[x_destiny][y_destiny] = chess_board[x_origin][y_origin];
        chess_board[x_origin][y_origin] = 0;

        // Update CNC position in memory
        CNC_position.first = x_destiny_point;
        CNC_position.second = y_destiny_point;

        // Verify if Check Mate ocurred
        bool checkmate_occurred = is_a_check_mate(turn, motion_validator);
        if(checkmate_occurred){
          bool status_memory = read_and_write_in_shared_memory("17");
          break;
        }

        sent_commands_counter++;
        // Sending CNC to initial position
        if(sent_commands_counter == 4){
          send_command("G4");

          CNC_position.first = 16;
          CNC_position.second = 0;
          sent_commands_counter = 0;
        }

        display_msg = "14";

        while(1){
          shared_memory_content = string(data);
          if(shared_memory_content == "None"){
            strncpy(data, display_msg.c_str(), SHM_SIZE);
            break;
          }
        }

        // Change player
        turn = 1 - turn;
      } else {
        // Comand is invalid
        display_msg = "302" + listened_command;
        if(!read_and_write_in_shared_memory(display_msg)){break;}
      }
    }

    detach_memory();
    qtd_matches++;
  }

  return 0;
}
