class MotionValidation:
    def __init__(self):
        ## Phonetic Alphabet
        self.fonetic_alphabet_coordinates = { 
            "ALPHA" : 0,
            "BRAVO" : 1,
            "CHARLIE" : 2,
            "DELTA" : 3,
            "ECHO" : 4,
            "FOXTROT" : 5,
            "GOLF" : 6,
            "HOTEL" : 7
        }
        self.number_coordinates = {
            "EIGHT" : 0,
            "SEVEN" : 1,
            "SIX" : 2,
            "FIVE" :  3,
            "FOUR" : 4,
            "THREE" : 5,
            "TWO" : 6,
            "ONE" : 7
        }
        self.piece_types = {
            1 : "ROOK",
            2 : "KNIGHT",
            3 : "BISHOP",
            4 : "QUEEN",
            5 : "KING",
            6 : "POWN",
            7 : "ROOK",
            8 : "KNIGHT",
            9 : "BISHOP",
            10 : "QUEEN",
            11 : "KING",
            12 : "POWN"
        }

    def validate_fonetic_words(self, y_origin, y_destiny):
        if not y_origin in self.fonetic_alphabet_coordinate:
            print("The word " + y_origin + " is an invalid origin column coordinate!")
            return False
        elif not y_destiny in self.fonetic_alphabet_coordinate:
            print("The word " + y_destiny + " is an invalid destiny column coordinate!")
            return False
        else:
            return True 

    def validate_numbers(self, x_origin, x_destiny):
        if not x_origin in self.number_coordinates:
            print("The word " + x_origin + " is an invalid origin line coordinate!")
            return False
        elif not y_destiny in self.number_coordinates:
            print("The word " + x_destiny + " is an invalida destiny line coordinate!")
            return False
        else:
            return True

    def is_there_a_piece_at_origin(self, x_origin, y_origin):
        x = self.number_coordinates[x_origin]
        y = self.fonetic_alphabet_coordinates[y_origin]

        if chess_board[x][y] != 0:
            return true
        else:
            return False

    def the_piece_is_mine(self. x_origin, y_origin, turn):
        x = self.number_coordinates[x_origin]
        y = self.fonetic_alphabet_coordinates[y_origin]

        if turn:
            if chess_board[x][y] <= 6:
                return True
        else:
            if chess_board[x][y] >= 7:
                return True
            
        return False

    def the_piece_can_do_it(self, x_origin, y_origin):
        x = self.number_coordinates[x_origin]
        y = self.fonetic_alphabet_coordinates[y_origin]
        
        piece_type = piece_types[chess_board[x][y]]
        
    def validate_command(y_origin, x_origin, y_destiny, x_destiny, turn):
        if validate_fonetic_words(y_origin, y_destiny and
           validate_numbers(x_origin, x_destiny) and
           is_there_a_piece_at_origin(x_origin, x_destiny) and
           the_piece_is_mine(x_origin, x_destiny, turn) and
           the_piece_can_do_it(x_origin, x_destiny):
            return True
        else:
            print("Invalid command!!")
            return False
