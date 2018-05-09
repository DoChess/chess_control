#include "voice.cpp"

using namespace std;

int main() {

	// If true the code start listening.
	bool hear_flag;
	// Desired string used to controll the system, like:
	// hear "chess" -> stop listening -> set hear_flag to true -> hear <anythin>
	string desired_command;

	desired_command = "chess";
	hear_flag = true;
	/*
		The real objective is use the voice like:
		voice();
		voice.start_listening();
		voice.request_command("command");
	*/
  voice(hear_flag, desired_command);
	return 0;
}
