# Exe files
BIN := bin/
# .hpp files
#INC := include/
# .cpp files
SRC := src/
# .o files
OBJ := obj/

COMPILER := g++

VOICE_FLAGS := -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`

FLAGS := -std=c++11 $(VOICE_FLAGS)

# Source files.
# Add all files to be used in onde project here. 

# Concatenates all files to the project.
CHESS := $(wildcard src/*.cpp)

# Compile project. 
all: create_folders $(CHESS:src/%.c=obj/%.o)
	$(COMPILER) -o bin/chess $(CHESS) $(FLAGS)
	touch /tmp/chess_shared_memory.txt

create_folders:
	@mkdir -p $(OBJ) $(BIN)

# Generate .o files.
obj/%.o: src/%.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@ -I./include
	$(COMPILER) $(FLAGS) -c ../utils/utils.c -o obj/utils.o -I../utils

# Run the executable files.
run: bin/chess
	bin/chess

.PHONY: clean
clean:
	rm -rf bin/*
	rm -rf obj/*
