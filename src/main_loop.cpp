#include <utility>

using namespace std;

using coordinate = pair<int,int>;

#define BLACK_ROOK 1
#define BLACK_KNIGHT 2
#define BLACK_BISHOP 3
#define BLACK_QUEEN 4
#define BLACK_KING 5
#define BLACK_PAWN 6
#define WHITE_ROOK 7
#define WHITE_KNIGHT 8
#define WHITE_BISHOP 9
#define WHITE_QUEEN 10
#define WHITE_KING 11
#define WHITE_PAWN 12

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
}
