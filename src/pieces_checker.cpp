#include "../include/pieces_checker.hpp"

bool PiecesChecker::look_for_pieces_in_the_way_rook(int x1, int y1, int x2, int y2){
  if(x1 == x2){
    for(int x = x1;x <= x2;++x){
      for(int y = y1+1;y < y2;++y){
        if(chess_board[x][y] != 0){
          return false;
        }
      }
    }
  }else{
    for(int x = x1+1;x < x2;++x){
      for(int y = y1;y <= y2;++y){
        if(chess_board[x][y] != 0){
          return false;
        }
      }
    }
    return true;
  }
}

bool PiecesChecker::look_for_pieces_in_the_way_bishop(int x1, int x2, int y1, int y2){
  int p1 = x1;
  int p2 = y1;
  for(int k = 0;k < (x1 - x2) - 1;++k){
    if(x1 < x2){
      if(y1 < y2){
        p1++;
        p2++;
      }else{
        p1++;
        p2--;
      }
    }else{
      if(y1 < y2){
        p1--;
        p2++;
      }else{
        p1--;
        p2--;
      }
    }

    if(chess_board[p1][p2] != 0){
      return false;
    }
  }
  return true;
}

bool PiecesChecker::look_for_pieces_at_destiny(int x, int y, int turn){
  if(
      chess_board[x][y] == 0 or
      ( turn and (chess_board[x][y] <= 6 and chess_board[x][y] > 0) ) or
      ((not turn) and chess_board[x][y] >= 7)
    ){
    return true;
  }else{
    return false;
  }
}

bool PiecesChecker::knight_checker(int x1, int y1, int x2, int y2, int turn){
  if(
      ((abs(x1 - x2) == 2 and abs(y1 - y2) == 1) or
       (abs(y1 - y2) == 2 and abs(x1 - x2) == 1)) and
      look_for_pieces_at_destiny(x2,y2, turn)
    ){
    return true;
  }else{
    return false;
  }
}

bool PiecesChecker::king_checker(int x1, int y1, int x2, int y2, int turn){
  if(
      ((abs(x1 - x2) == 1 and abs(y1 - y2) == 1) or
       (abs(x1 - x2) == 1 and abs(y1 - y2) == 0) or
       (abs(y1 - y2) == 1 and abs(x1 - x2) == 0)) and
      look_for_pieces_at_destiny(x2, y2, turn)
    ){
    return true;
  }else{
    return false;
  }
}

bool PiecesChecker::rook_checker(int x1, int y1, int x2, int y2, int turn){
  bool is_a_valid_movement = true;
  if(x1 == x2 or y1 == y2){
    if(y2 < y1){
      int aux;
      aux = y2;
      y2 = y1;
      y1 = aux;
      y1++;
    }
    if(x2 < x1){
      int aux;
      aux = x2;
      x2 = x1;
      x1 = aux;
      x1++;
    }
    is_a_valid_movement = look_for_pieces_in_the_way_rook(x1, y1, x2, y2);
  }else{
    is_a_valid_movement = false;
  }
  return (is_a_valid_movement and look_for_pieces_at_destiny(x2, y2, turn));
}

bool PiecesChecker::pawn_checker(int x1, int y1, int x2, int y2, int turn){
  bool is_a_valid_movement = false;
  //cout << "X1 " << x1 << " Y1 " << y1 << " X2 " << x2 << " Y2 " << y2 << endl;
  if(y1 == y2 and ((abs(x1 - x2) == 2 and (x1 == 1 or x1 == 6)) or 
        (abs(x1 - x2) == 1))){
    if(not turn){
      if(x2 > x1){
        is_a_valid_movement = true;
      }
    }else{
      if(x1 > x2){
        is_a_valid_movement = true;
      }
    }
    if(is_a_valid_movement and abs(x1 -x2) == 2){
      if(not turn){
        if(chess_board[x1+1][y1] != 0) is_a_valid_movement = false;
      }else if(turn){
        if(chess_board[x1-1][y1] != 0) is_a_valid_movement = false;
      }
    }
  }
 
  return (is_a_valid_movement and look_for_pieces_at_destiny(x2, y2, turn));
}

bool PiecesChecker::bishop_checker(int x1, int y1, int x2, int y2, int turn){
  bool is_a_valid_movement = false;
  if(abs(x1 - x2) == abs(y1 - y2) and
      look_for_pieces_in_the_way_bishop(x1, x2, y1, y2) and
      look_for_pieces_at_destiny(x2, y2, turn)
    ){
    is_a_valid_movement = true;
  }
  return is_a_valid_movement;
}

bool PiecesChecker::queen_checker(int x1, int y1, int x2, int y2, int turn){
  bool is_a_valid_movement = false;
  if(rook_checker(x1, y1, x2, y2, turn) or bishop_checker(x1, y1, x2, y2, turn)){
    is_a_valid_movement = true;
  }

  return is_a_valid_movement;
}

