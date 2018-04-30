#ifndef MOTION_VALIDATION_H
#define MOTION_VALIDATION_H

#include <map>
#include <string>
#include <iostream>
#include "pieces_checker.hpp"

using namespace std;
using par = pair<int,int>;

class MotionValidation {
  public:
    void initialize_dictionaries();
    bool validate_command(string, string, string, string, int);
    par is_in_check;
    par white_king_position;
    par black_king_position;
    MotionValidation(int (&p_chess_board)[8][8]):chess_board(p_chess_board){};
    ~MotionValidation(){};

  private:
    int (&chess_board)[8][8];
    map<string,int> fonetic_alphabet_coordinates;
    map<string,int> number_coordinates;
    map<int,string> piece_types;
    PiecesChecker pieces_checker = PiecesChecker(chess_board);

    bool validate_fonetic_words(string, string);
    bool validate_numbers(string, string);
    bool is_there_a_piece_at_origin(int, int);
    bool the_piece_is_mine(int, int, int);
    bool the_piece_can_do_it(int, int, int, int, int);
    void verify_check_for_all_pieces(int);
    bool verify_if_king_is_in_check(int, int, int, int);
    void its_possible_to_defend_king(int, int, int, int, int);
};

#endif
