#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>

using namespace std;

void open_comport();
void send_command(string);  
string get_displacement(string);
string transalate_to_cartesian_coordinates(string);

#endif
