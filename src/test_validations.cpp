#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include "../include/motion_validation.hpp"

using namespace std;

vector<string> false_negatives;
vector<string> false_positives;

void run_piece_test_case(string x_origin, string y_origin, string x_destiny,
  string y_destiny, int turn, bool expected, MotionValidation motion_validator
  ){
    bool test_result = motion_validator.validate_command(x_origin,
                                                         y_origin,
                                                         x_destiny,
                                                         y_destiny,
                                                         turn);

    if(test_result == false && expected == true){
      string failure_message = "the validation failed moving piece from " +
                                x_origin + " " + y_origin + " to " +
                                x_destiny + " " + y_destiny;
      false_negatives.push_back(failure_message);
    }else if(test_result == true && expected == false){
      string failure_message = "the validation passed moving piece from " +
                                x_origin + " " + y_origin + " to " +
                                x_destiny + " " + y_destiny;
      false_positives.push_back(failure_message);
    }
}

void test_pawn_movements(){
  // Normal movement
  int chess_board_1[8][8] = 
   {{1,2,3,4,5,3,2,1},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {12,12,12,12,12,12,12,12},
    {7,8,9,10,11,9,8,7}};

  MotionValidation motion_validator_1 = MotionValidation(chess_board_1);
  motion_validator_1.initialize_dictionaries();

  run_piece_test_case("SEVEN","ALPHA","SIX","ALPHA",0, true, motion_validator_1);

  run_piece_test_case("SEVEN","ALPHA","FIVE","ALPHA",0, true, motion_validator_1);

  run_piece_test_case("SEVEN","BRAVO","SIX","BRAVO",0, true, motion_validator_1);

  run_piece_test_case("SEVEN","BRAVO","FIVE","BRAVO",0, true, motion_validator_1);

  run_piece_test_case("SEVEN","CHARLIE","SIX","CHARLIE",0, true, motion_validator_1);

  run_piece_test_case("SEVEN","CHARLIE","FIVE","CHARLIE",0, true, motion_validator_1);

  run_piece_test_case("TWO","ALPHA","THREE","ALPHA",1, true, motion_validator_1);

  run_piece_test_case("TWO","ALPHA","FOUR","ALPHA",1, true, motion_validator_1);

  run_piece_test_case("TWO","BRAVO","THREE","BRAVO",1, true, motion_validator_1);

  run_piece_test_case("TWO","BRAVO","FOUR","BRAVO",1, true, motion_validator_1);

  run_piece_test_case("TWO","CHARLIE","THREE","CHARLIE",1, true, motion_validator_1);

  run_piece_test_case("TWO","CHARLIE","FOUR","CHARLIE",1, true, motion_validator_1);

  //Capture movement
  int chess_board_2[8][8] = 
   {{1,2,3,4,5,3,2,1},
    {6,6,6,6,6,6,0,6},
    {0,0,12,0,0,0,0,0},
    {12,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,6,0},
    {0,12,0,12,12,12,12,12},
    {7,8,9,10,11,9,8,7}};

  MotionValidation motion_validator_2 = MotionValidation(chess_board_2);
  motion_validator_2.initialize_dictionaries();

  run_piece_test_case("SEVEN","CHARLIE","SIX","CHARLIE",0, true, motion_validator_2);

  run_piece_test_case("SEVEN","ALPHA","FIVE","ALPHA",0, true, motion_validator_2);

  run_piece_test_case("TWO","GOLF","THREE","GOLF",1, true, motion_validator_2);

  //Normal movement
  int chess_board_3[8][8] = 
   {{1,2,3,4,5,3,2,1},
    {6,6,6,6,6,6,0,6},
    {0,0,12,0,0,0,0,0},
    {12,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,6,0},
    {0,12,0,12,12,12,12,12},
    {7,8,9,10,11,9,8,7}};

  MotionValidation motion_validator_3 = MotionValidation(chess_board_3);
  motion_validator_3.initialize_dictionaries();

  run_piece_test_case("SIX","ALPHA","SEVEN","ALPHA",0, false, motion_validator_3);

  run_piece_test_case("FIVE","ALPHA","SEVEN","ALPHA",0, false, motion_validator_3);

  run_piece_test_case("SIX","BRAVO","SEVEN","BRAVO",0, false, motion_validator_3);

  run_piece_test_case("FIVE","BRAVO","SEVEN","BRAVO",0, false, motion_validator_3);

  run_piece_test_case("SIX","CHARLIE","SEVEN","CHARLIE",0, false, motion_validator_3);

  run_piece_test_case("FIVE","CHARLIE","SEVEN","CHARLIE",0, false, motion_validator_3);

  run_piece_test_case("THREE","ALPHA","TWO","ALPHA",1, false, motion_validator_3);

  run_piece_test_case("FOUR","ALPHA","TWO","ALPHA",1, false, motion_validator_3);

  run_piece_test_case("THREE","BRAVO","TWO","BRAVO",1, false, motion_validator_3);

  run_piece_test_case("FOUR","BRAVO","TWO","BRAVO",1, false, motion_validator_3);

  run_piece_test_case("THREE","CHARLIE","TWO","CHARLIE",1, false, motion_validator_3);

  run_piece_test_case("FOUR","CHARLIE","TWO","CHARLIE",1, false, motion_validator_3);

  run_piece_test_case("SEVEN","ALPHA","SIX","BRAVO",0, false, motion_validator_3);

  run_piece_test_case("SEVEN","CHARLIE","FIVE","ALPHA",0, false, motion_validator_3);

  run_piece_test_case("SEVEN","GOLF","SIX","BRAVO",0, false, motion_validator_3);

  run_piece_test_case("SEVEN","GOLF","FIVE","BRAVO",0, false, motion_validator_3);

  run_piece_test_case("SEVEN","DELTA","SIX","CHARLIE",0, false, motion_validator_3);

  run_piece_test_case("SEVEN","ALPHA","FIVE","CHARLIE",0, false, motion_validator_3);

  run_piece_test_case("TWO","BRAVO","THREE","ALPHA",1, false, motion_validator_3);

  run_piece_test_case("TWO","DELTA","FOUR","ALPHA",1, false, motion_validator_3);

  run_piece_test_case("TWO","ALPHA","THREE","BRAVO",1, false, motion_validator_3);

  run_piece_test_case("TWO","CHARLIE","FOUR","BRAVO",1, false, motion_validator_3);

  run_piece_test_case("TWO","BRAVO","THREE","CHARLIE",1, false, motion_validator_3);

  run_piece_test_case("TWO","DELTA","FOUR","CHARLIE",1, false, motion_validator_3);
}

void test_king_movements(){
  // Normal movement
  int chess_board_1[8][8] = 
   {{1 ,2 ,3 ,4 ,0 ,3 ,2 ,1 },
    {6 ,6 ,6 ,6 ,0 ,6 ,6 ,6 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,11,0 ,0 ,5 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,6 ,0 ,0 ,0 },
    {12,12,12,0 ,12,12,12,12},
    {7 ,8 ,9 ,10,0 ,9 ,8 ,7 }};

  MotionValidation motion_validator_1 = MotionValidation(chess_board_1);
  motion_validator_1.initialize_dictionaries();

  run_piece_test_case("FIVE","ECHO","SIX","ECHO",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","SIX","FOXTROT",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","FIVE","FOXTROT",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","FOUR","FOXTROT",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","FOUR","ECHO",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","FOUR","DELTA",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","FIVE","DELTA",0, true, motion_validator_1);

  run_piece_test_case("FIVE","ECHO","SIX","DELTA",0, true, motion_validator_1);


  run_piece_test_case("FIVE","BRAVO","SIX","BRAVO",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","SIX","CHARLIE",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","FIVE","CHARLIE",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","FOUR","CHARLIE",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","FOUR","BRAVO",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","FOUR","ALPHA",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","FIVE","ALPHA",1, true, motion_validator_1);

  run_piece_test_case("FIVE","BRAVO","SIX","ALPHA",1, true, motion_validator_1);

  //Capture movement
  int chess_board_2[8][8] = 
   {{1 ,2 ,3 ,4 ,0 ,3 ,2 ,1 },
    {6 ,6 ,6 ,6 ,0 ,6 ,6 ,6 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,11,5 ,12,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,6 ,0 ,0 ,0 },
    {12,12,12,0 ,12,12,12,12},
    {7 ,8 ,9 ,10,0 ,9 ,8 ,7 }};

  MotionValidation motion_validator_2 = MotionValidation(chess_board_2);
  motion_validator_2.initialize_dictionaries();

  run_piece_test_case("FIVE","CHARLIE","FIVE","BRAVO",0, true, motion_validator_2);

  run_piece_test_case("FIVE","CHARLIE","FIVE","DELTA",0, true, motion_validator_2);

  run_piece_test_case("FIVE","BRAVO","FIVE","CHARLIE",1, true, motion_validator_2);

  //Normal movement  
  int chess_board_3[8][8] = 
   {{1 ,2 ,3 ,4 ,5 ,3 ,2 ,1 },
    {6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,6 ,0 ,0 ,0 },
    {12,12,12,0 ,12,12,12,12},
    {7 ,8 ,9 ,10,11 ,9 ,8 ,7 }};

  MotionValidation motion_validator_3 = MotionValidation(chess_board_3);
  motion_validator_3.initialize_dictionaries();
  
  run_piece_test_case("EIGHT","ECHO","SEVEN","ECHO",0, false, motion_validator_3);

  run_piece_test_case("ONE","ECHO","TWO","ECHO",1, false, motion_validator_3);
}

void test_rook_movements(){
  // Normal movement
  int chess_board_1[8][8] = 
   {{1,2,3,4,5,3,2,0},
    {6,6,6,6,6,6,6,6},
    {0,0,0,0,0,0,0,0},
    {0,0,0,7,0,0,0,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {12,12,12,12,12,12,12,12},
    {7,8,9,10,11,9,8,7}};

  MotionValidation motion_validator_1 = MotionValidation(chess_board_1);
  motion_validator_1.initialize_dictionaries();

  run_piece_test_case("FIVE","DELTA","THREE","DELTA",1, true, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","FIVE","ALPHA",1, true, motion_validator_1);

  run_piece_test_case("FIVE","HOTEL","THREE","HOTEL",0, true, motion_validator_1);

  run_piece_test_case("FIVE","HOTEL","FIVE","ECHO",0, true, motion_validator_1);

  run_piece_test_case("FIVE","HOTEL","SIX","HOTEL",0, true, motion_validator_1);

  // Capture movement
  run_piece_test_case("FIVE","HOTEL","TWO","HOTEL",0, true, motion_validator_1);

  run_piece_test_case("FIVE","HOTEL","FIVE","DELTA",0, true, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","SEVEN","DELTA",1, true, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","FIVE","HOTEL",1, true, motion_validator_1);

  // Normal movement
  run_piece_test_case("FIVE","DELTA","THREE","ALPHA",1, false, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","FOUR","ALPHA",1, false, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","THREE","HOTEL",0, false, motion_validator_1);

  run_piece_test_case("TWO","HOTEL","FIVE","ECHO",0, false, motion_validator_1);

  run_piece_test_case("FIVE","DELTA","TWO","DELTA",1, false, motion_validator_1);

  run_piece_test_case("FIVE","HOTEL","SEVEN","HOTEL",0, false, motion_validator_1);
}

void test_queen_movements(){
  //pass
}

void test_knight_movements(){
  //pass
}

void test_bishop_movements(){
  //pass
}

int main(){
  //test_pawn_movements();
  //test_king_movements();
  test_rook_movements();

  if(false_negatives.size() != 0){
      cout << "The following test cases have failed when they should pass:" << endl << endl;
    for(auto failure_message : false_negatives){
      cout << failure_message << endl << endl;
    }
  }
  if(false_positives.size() != 0){
      cout << "The following test cases have passed when they should fail:" << endl << endl;
    for(auto failure_message : false_positives){
      cout << failure_message << endl << endl;
    }
  }
  if(false_negatives.size() == 0 and false_positives.size() == 0){
    cout << "Sucessfully passed all tests!!" << endl;
  }
}
