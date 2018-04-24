#include <utility>
#include <iostream>
#include "../include/motion_validation.hpp"

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

int main(){
    initialize_statements();
    MotionValidation motion_validator = MotionValidation(chess_board);
    motion_validator.initialize_dictionaries();

    bool resp = motion_validator.validate_command("SEVEN","CHARLIE","SIX","CHARLIE",0);
    cout << "O resultado foi " << resp << endl;

    bool resp2 = motion_validator.validate_command("SEVEN","CHARLIE","FIVE","CHARLIE",0);
    cout << "O resultado foi " << resp2 << endl;
}
