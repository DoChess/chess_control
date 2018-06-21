#include "../include/checkmate_checker.hpp"

vector<coordinate> displacements {coordinate(1,0), coordinate(0,1),
                                  coordinate(1,1), coordinate(-1,0),
                                  coordinate(0,-1), coordinate(-1,1),
                                  coordinate(1,-1), coordinate(-1,-1)};

vector<coordinate> look_for_threat_pieces(int turn, 
                                          coordinate enemy_king_position,
                                          MotionValidation &motion_validator){
  vector<coordinate> threat_pieces;

  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
    // Dah pra otimizar aqui, colocando a verificação se a peça que existe lá é minha
      if(motion_validator.validate_command(number_words[i], fonetic_words[j],
                                           number_words[enemy_king_position.first],
                                           fonetic_words[ enemy_king_position.second],
                                           turn)){
        threat_pieces.push_back(coordinate(i,j));
      }
    }
  }

  return threat_pieces;
}

bool try_to_scape_moving_king(coordinate king_position,
                              coordinate displacement, int turn,
                              MotionValidation &motion_validator){
  //motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second] =
  //  motion_validator.chess_board[king_position.first][king_position.second];
  //motion_validator[king_position.first][king_position.second] = 0;

  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(number_words[i], fonetic_words[j],
                                           number_words[king_position.first + displacement.first],
                                           fonetic_words[ king_position.second + displacement.second ],
                                           turn)){
        return false;
      }
    }
  }
  
  //motion_validator[king_position.first][king_position.second] = motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second];
  //motion_validator.chess_board[king_position.first + displacement.first][king_position.second + displacement.second] = 0;

  return true;
}

bool try_to_capture_threat_piece(coordinate threat_piece, int turn,
                                 MotionValidation &motion_validator){
  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(number_words[i], fonetic_words[j],
                                           number_words[threat_piece.first],
                                           fonetic_words[ threat_piece.second],
                                           turn)){
        return true;
      }
    }
  }
  return false;
}

bool try_to_move_piece_to_blocking_position(coordinate blocking_position,
                                            int turn,
                                            MotionValidation &motion_validator){
  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      if(motion_validator.validate_command(number_words[i], fonetic_words[ j],
                                           number_words[ blocking_position.first],
                                           fonetic_words[ blocking_position.second],
                                           turn)){
        return true;
      }
    }
  }
  return false;
}

bool try_to_put_piece_in_the_way(coordinate threat_piece,
                                 coordinate king_position, int turn,
                                 MotionValidation &motion_validator){
  int aux;
  for(int i = 0;i < 8;++i){
    for(int j = 0;j < 8;++j){
      aux = motion_validator.chess_board[i][j];
      motion_validator.chess_board[i][j] = ((not turn)? 12 : 6);
      if(!motion_validator.validate_command(number_words[threat_piece.first],
                                            fonetic_words[threat_piece.second],
                                            number_words[ king_position.first],
                                            fonetic_words[ king_position.second],
                                            turn)){
        if(try_to_move_piece_to_blocking_position(coordinate(i,j), 1 - turn, motion_validator)){
          return true;
        }
      }
      motion_validator.chess_board[i][j] = aux;
    }
  }

  return false;
}

bool is_a_check_mate(int turn, MotionValidation &motion_validator){
  vector<coordinate> threat_pieces;
  coordinate white_king_position = motion_validator.white_king_position;
  coordinate black_king_position = motion_validator.black_king_position;

  if(!turn){
    threat_pieces = look_for_threat_pieces(turn, black_king_position, motion_validator);
  }else{
    threat_pieces = look_for_threat_pieces(turn, white_king_position, motion_validator);
  }

  if(threat_pieces.size() == 0){
    if(!turn) motion_validator.is_in_check.second = 0;
    else motion_validator.is_in_check.first = 0;
    return false;
  }
  else{
    if(!turn) motion_validator.is_in_check.second = 1;
    else motion_validator.is_in_check.first = 1;

    // Try to scape moving
    bool scape_try = false;
    for(auto displacement : displacements){
      if(!turn) scape_try = try_to_scape_moving_king(black_king_position, displacement, turn, motion_validator);
      else scape_try = try_to_scape_moving_king(white_king_position, displacement, turn, motion_validator);
      if(scape_try){
        return false;
      }
    }

    if(threat_pieces.size() >= 2){
      return true;
    }

    // Try to capture enemy piece
    scape_try = false;
    scape_try = try_to_capture_threat_piece(threat_pieces[0], 1 - turn, motion_validator); 
    if(scape_try){
      return false;
    }

    // Try to put a piece in the way
    if(!turn) scape_try =  try_to_put_piece_in_the_way(threat_pieces[0], black_king_position, turn, motion_validator);
    else scape_try =  try_to_put_piece_in_the_way(threat_pieces[0], white_king_position, turn, motion_validator);
    if(scape_try == true){
      return false;
    }
  }

  return true;
}

