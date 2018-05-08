#ifndef PIECES_CHECKER
#define PIECES_CHECKER

#include <stdlib.h>
#include <iostream>

using namespace std;

class PiecesChecker {
  public:
    PiecesChecker(int (&p_chess_board)[8][8]):chess_board(p_chess_board){};
    ~PiecesChecker(){};

    bool knight_checker(int x1, int y1, int x2, int y2, int turn);
    bool king_checker(int x1, int y1, int x2, int y2, int turn);
    bool rook_checker(int x1, int y1, int x2, int y2, int turn);
    bool pawn_checker(int x1, int y1, int x2, int y2, int turn);
    bool bishop_checker(int x1, int y1, int x2, int y2, int turn);
    bool queen_checker(int x1, int y1, int x2, int y2, int turn);
  private:
    int (&chess_board)[8][8];

    bool look_for_pieces_in_the_way_rook(int x1, int y1, int x2, int y2);
    bool look_for_pieces_in_the_way_bishop(int x1, int x2, int y1, int y2);
    bool look_for_pieces_at_destiny(int x, int y, int turn);
};

#endif
