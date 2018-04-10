#ifndef MOTION_VALIDATION_H
#define MOTION_VALIDATION_H

#include <map>
#include <string>

using namespace std;

class MotionValidation {
  public:
    bool validate_command(string, string, string, string, int);
    MotionValidation(int (&p_chess_board)[8][8]):chess_board(p_chess_board){};
    ~MotionValidation(){};

  private:
    map<string,int> fonetic_alphabet_coordinates;
    map<string,int> number_coordinates;
    map<int,string> piece_types;
    int (&chess_board)[8][8];

    void initialize_dictionaries();
    bool validate_fonetic_words(string, string);
    bool validate_numbers(string, string);
    bool is_there_a_piece_at_origin(int, int);
    bool the_piece_is_mine(int, int, int);
    bool the_piece_can_do_it(int, int, int, int);
};

#endif
