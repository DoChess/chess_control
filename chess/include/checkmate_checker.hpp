#ifndef CHECKMATE_CHECKER_H
#define CHECKMATE_CHECKER_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include "motion_validation.hpp"

using namespace std;
using coordinate = pair<int,int>;

static map<int, string> fonetic_words = {
  {0 , "ALPHA"},
  {1 , "BRAVO"},
  {2 , "CHARLIE"},
  {3 , "DELTA"},
  {4 , "ECHO"},
  {5 , "FOXTROT"},
  {6 , "GOLF"},
  {7 , "HOTEL"}
};

static map<int, string> number_words = {
  {0 , "EIGHT"},
  {1 , "SEVEN"},
  {2 , "SIX"},
  {3 , "FIVE"},
  {4 , "FOUR"},
  {5 , "THREE"},
  {6 , "TWO"},
  {7 , "ONE"}
};

vector<coordinate> look_for_threat_pieces(int turn, coordinate , MotionValidation &);
bool try_to_scape_moving_king(coordinate, coordinate, int, MotionValidation &);
bool try_to_capture_threat_piece(coordinate, int, MotionValidation &);
bool try_to_move_piece_to_blocking_position(coordinate, int, MotionValidation &);
bool try_to_put_piece_in_the_way(coordinate, coordinate, int, MotionValidation &);
bool is_a_check_mate(int, MotionValidation &);

#endif
