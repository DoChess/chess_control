# Exe files
BIN := bin/
# .cpp files
SRC := src/
# .o files
#OBJ := obj/

COMPILER := g++

FLAGS := -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`

# Source files.
# Add all files to be used in onde project here. 

# Concatenates all files to the project.
CHESS := $(wildcard src/main.cpp)

# Compile project. 
all: create_folders $(CHESS:src/%.c)
	$(COMPILER) -o bin/voice $(CHESS) $(FLAGS)

create_folders:
	@mkdir -p $(BIN)

# Run the executable files.
run: bin/voice
	bin/voice

.PHONY: clean
clean:
	rm -rf bin/*
