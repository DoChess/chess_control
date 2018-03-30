from motion_validation import MotionValidation

chess_board = [[]]
CNC_position = (0,0)
points_chess_board = [[]]

BLACK_ROOK = 1
BLACK_KNIGHT = 2
BLACK_BISHOP = 3
BLACK_QUEEN = 4
BLACK_KING = 5
BLACK_POWN = 6
WHITE_ROOK = 7
WHITE_KNIGHT = 8
WHITE_BISHOP = 9
WHITE_QUEEN = 10
WHITE_KING = 11
WHITE_POWN = 12

def initialize_chess_board:
    chess_board = [[0 for n in range(8)] for m in range(8)]
    chess_board[0] = [1,2,3,4,5,3,2,1]
    chess_board[1] = [6]*8
    chess_board[6] = [12]*8
    chess_board[7] = [7,8,9,10,11,9,8,7]
    
    CNC_position = (0,0)

    points_chess_board = [[0 if (m % 2 != 0 and n % 2 != 0) else 1 for n in range(17)] for m in range(17)]


if __name__ == "__main__":
    initialize_chess_board()
        
    while(1):
        #Nothing
        break         
    
