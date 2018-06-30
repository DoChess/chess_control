#include "../include/communication.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
  string a = "G1 X0 Y17";
  open_comport();
  send_command(a);

  return 0;
}

