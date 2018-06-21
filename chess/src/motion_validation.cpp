#include "../include/motion_validation.hpp"
#include <iostream>

using namespace std;

void MotionValidation::initialize_dictionaries(){
  is_in_check = make_pair(0,0);
  white_king_position = make_pair(0,4);
  black_king_position = make_pair(7,4); 

  fonetic_alphabet_coordinates = {
   {"ALPHA" , 0},
   {"BRAVO" , 1},
   {"CHARLIE" , 2},
   {"DELTA" , 3},
   {"ECHO" , 4},
   {"FOXTROT" , 5},
   {"GOLF" , 6},
   {"HOTEL" , 7}
  };

  number_coordinates = {
   {"EIGHT" , 0},
   {"SEVEN" , 1},
   {"SIX" , 2},
   {"FIVE" ,  3},
   {"FOUR" , 4},
   {"THREE" , 5},
   {"TWO" , 6},
   {"ONE" , 7}
  };

  piece_types = {
   {1 , "ROOK"},
   {2 , "KNIGHT"},
   {3 , "BISHOP"},
   {4 , "QUEEN"},
   {5 , "KING"},
   {6 , "PAWN"},
   {7 , "ROOK"},
   {8 , "KNIGHT"},
   {9 , "BISHOP"},
   {10 , "QUEEN"},
   {11 , "KING"},
   {12 , "PAWN"}
  };
}

bool MotionValidation::validate_fonetic_words(string y_origin, string y_destiny){
  if(fonetic_alphabet_coordinates[y_origin] and 
    fonetic_alphabet_coordinates[y_destiny]){
      return true;
    }
  else return false;
}

bool MotionValidation::validate_numbers(string x_origin, string x_destiny){
  if(number_coordinates[x_origin] and number_coordinates[x_destiny]){
    return true;
  }
  else return false;
}

bool MotionValidation::is_there_a_piece_at_origin(int x, int y){
  if(chess_board[x][y] != 0){
    return true;
  }
  else return false;
}

bool MotionValidation::the_piece_is_mine(int x, int y, int turn){
  if(((not turn) and (chess_board[x][y] <= 6 and chess_board[x][y] > 0)) or
     (turn and chess_board[x][y] >= 7)){
    return true;
  }else return false;
}

bool MotionValidation::the_piece_can_do_it(int x, int y,int z, int k, int turn){
  bool can_do_it;
  string piece_type = piece_types[chess_board[x][y]];

  // moving to same position
  if(x == z and y == k) return false;

  if(piece_type == "ROOK"){
    can_do_it = pieces_checker.rook_checker(x, y, z, k, turn);
  }
  else if(piece_type == "KNIGHT"){
    can_do_it = pieces_checker.knight_checker(x, y, z, k, turn);  
  }
  else if(piece_type == "BISHOP"){
    can_do_it = pieces_checker.bishop_checker(x, y, z, k, turn);
  }
  else if(piece_type == "QUEEN"){
    can_do_it = pieces_checker.queen_checker(x, y, z, k, turn);
  }
  else if(piece_type == "KING"){
    can_do_it = pieces_checker.king_checker(x, y, z, k, turn);
  }
  else if(piece_type == "PAWN"){
    can_do_it = pieces_checker.pawn_checker(x, y, z, k, turn);
  }

  return can_do_it;
}

void MotionValidation::verify_check_for_all_pieces(int turn){
  bool has_check = false;
  for(int i = 0;i < 8;++i){
    if(has_check) break;
    for(int j = 0;j < 8;++j){
      if(turn == 0 and chess_board[i][j] > 6 and 
        the_piece_can_do_it(i, j, black_king_position.first, black_king_position.second, 0)){
        has_check = true;
        is_in_check.second = 1;
        break;
      }else if(turn == 1 and chess_board[i][j] <= 6 and
               chess_board[i][j] > 0 and
        the_piece_can_do_it(i, j, white_king_position.first, white_king_position.second, 1)){
        has_check = true;
        is_in_check.first = 1;
        break;
      }
    }
  }
}

void MotionValidation::its_possible_to_defend_king(int x_origin,
                                       int y_origin,
                                       int x_destiny,
                                       int y_destiny,
                                       int turn){
  chess_board[x_destiny][y_destiny] = chess_board[x_origin][y_origin];
  chess_board[x_origin][y_origin] = 0;
  verify_check_for_all_pieces(turn);
  chess_board[x_origin][y_origin] = chess_board[x_destiny][y_destiny];
  chess_board[x_destiny][y_destiny] = 0;
}

bool MotionValidation::verify_if_king_continues_in_check(int x_origin,
    int y_origin,
    int x_destiny,
    int y_destiny,
    int turn){

  if(!turn and is_in_check.first){
    is_in_check.first = 0;
    its_possible_to_defend_king(x_origin, y_origin, x_destiny ,y_destiny, 0); 

    return (is_in_check.first == 0);

  }else if(turn and is_in_check.second){
    is_in_check.second = 0;
    its_possible_to_defend_king(x_origin, y_origin, x_destiny ,y_destiny, 1); 

    return (is_in_check.second == 0);
  }
  return true;
}

bool MotionValidation::validate_command(string x_origin, string y_origin,
  string x_destiny, string y_destiny, int turn){
  
  int x = number_coordinates[x_origin];
  int y = fonetic_alphabet_coordinates[y_origin];
  int z = number_coordinates[x_destiny];
  int k = fonetic_alphabet_coordinates[y_destiny];

  if(is_there_a_piece_at_origin(x, y) and
    the_piece_is_mine(x, y, turn) and
    the_piece_can_do_it(x, y, z, k, turn) and
    verify_if_king_continues_in_check(x, y, z, k, turn)){
    return true;
  }else{
    return false;
  }
}
