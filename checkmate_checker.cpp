#include "../include/checkmate_checker.hpp"

using coordinate = pair<int,int>;
vector<coordinate> displacements {coordinate(1,0), coordinate(0,1),
                                  coordinate(1,1), coordinate(-1,0),
                                  coordinate(0,-1), coordinate(-1,1),
                                  coordinate(1,-1), coordinate(-1,-1)};

vector<coordinate> look_for_threat_pieces(int turn, 
                                          coordinate enemy_king_position){
  vector<coordinate> threat_pieces;

  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(i,j,enemy_king_position.first, 
                                           enemy_king_position.second, turn)){
        threat_pieces.push_back(coordinate(i,j));
      }
    }
  }

  return threat_pieces;
}

bool try_to_scape_moving_king(coordinate king_position,
                                      coordinate displacement, int turn){
  motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second] =
    motion_validator.chess_board[king_position.first][king_position.second];
  motion_validator[king_position.first][king_position.second] = 0;

  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(i,j,king_position.first, 
                                           king_position.second, turn)){
        return false;
      }
    }
  }
  
  motion_validator[king_position.first][king_position.second] = motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second];
  motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second] = 0;

  return true;
}

bool try_to_capture_threat_piece(coordinate threat_piece, int turn){
  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(i,j,threat_piece.first, 
                                            threat_piece.second, !turn)){
        return true;
      }
    }
  }
  return false;
}

bool CheckmateChecker::is_a_check_mate(int turn, coordinate white_king_position,
                                       coordinate black_king_position){
  vector<coordinate> threat_pieces;
  bool checkmate_ocurred = true;

  if(!turn){
    threat_pieces = look_for_threat_pieces(turn, black_king_position);
  }else{
    threat_pieces = look_for_threat_pieces(turn, white_king_position);
  }

  if(threat_pieces.size() == 0){
    if(!turn) motion_validator.is_in_check.second = 0;
    else motion_validator.is_in_check.first = 0;
    return false;
  }
  else if(threat_pieces.size() == 1){
    if(!turn) motion_validator.is_in_check.second = 1;
    else motion_validator.is_in_check.first = 1;

    // Try to scape moving
    bool scape_try = false;
    for(auto displacement : displacements){
      if(!turn) scape_try = try_to_scape_moving_king(black_king_position, displacement, turn);
      else scape_try = try_to_scape_moving_king(white_king_position, displacement, turn);
      if(scape_try){
        return false;
      }
    }

    // Try to capture enemy piece
    scape_try = try_to_capture_threat_piece(threat_pieces[0], turn); 
    if(scape_try == true){
      return false;
    }

    
     
    
    // 2 threat pieces
  else if(threat_pieces.size() >= 2){
    return true;
  }

  return true;
}

