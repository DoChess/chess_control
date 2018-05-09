# Chess module folder.
CHESS:= @cd ./chess/

# Voice recognition folder.
#VOICE:= @cd ./voice_recognition/

# Compile each project.
build_chess:
	$(CHESS) && make

#build_voice:
#	$(VOICE) && make

run_chess:
	$(CHESS) && ./bin/chess

#run_voice:
#	$(VOICE) && ./bin/voice

# Compile project. 
all: build_chess #build_voice

clean:
	@rm -rf */obj/* */bin/*
