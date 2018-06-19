
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

 **************************************************/
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include "../include/communication.hpp"
#include "../include/rs232.hpp"

int i, n,
    cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
    bdrate=9600;       /* 9600 baud */

unsigned char buf[100];

char mode[]={'8','N','1',0};

using namespace std;

void open_comport(){
  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");
  }
}

string get_displacement(string text_piece){
  string number = "";

  if(text_piece[1] == '-'){
    if(text_piece.size() == 4){
      number += text_piece[2]; number += text_piece[3];
    }else if(text_piece.size() == 3){
      number += text_piece[2];
    }
  }else{
    if(text_piece.size() == 3){
      number += text_piece[1]; number += text_piece[2];
    }else if(text_piece.size() == 2){
      number += text_piece[1];
    }
  }

  return number;
}

string translate_to_cartesian_coordinates(string command){
  stringstream ss(command);

  string translated_command = "", text_piece;
  string x_displacement = "", y_displacement = "";
  string number;

  while(ss >> text_piece){

    if(text_piece[0] == 'G') translated_command += (text_piece + ' ');
    else if(text_piece[0] == 'X'){
      number = get_displacement(text_piece);
      if(text_piece[1] != '-')  y_displacement = (number != "0"?("Y-" + number):("Y0"));
      else y_displacement = "Y" + number;
    }else if(text_piece[0] == 'Y'){
      number = get_displacement(text_piece);
      if(text_piece[1] == '-') x_displacement = (number != "0"?("X-" + number + " "):("X0 "));
      else x_displacement = "X" + number + " ";
    }
  }

  return translated_command + x_displacement + y_displacement;
}

void send_command(string command){
  if(command.size() > 3){
    command = translate_to_cartesian_coordinates(command);
  }

  printf("Enviando comando %s\n", command.c_str());

  return;

  int command_confirmed = 0;
  string system_call = "echo -n '"  + command + ".' > /dev/rfcomm2";

  printf("Sending command: %s.\n", system_call.c_str());

  for(i = 0;i < 3;++i){
    //system("echo -n 'G0 X7 Y0.' > /dev/rfcomm2");
    system(system_call.c_str());
  }

  printf("Command sent.\n");

  while(1){
    n = RS232_PollComport(cport_nr, buf, 100); // Number of read bytes

    if(n > 0)
    {
      buf[n] = 0;   /* always put a "null" at the end of a string! */

      for(i=0; i < n; i++)
      {
        if(buf[i] < 32)  /* replace unreadable control-codes by dots */
        {
          buf[i] = '.';
        }
      }

      printf("%i bytes received: %s\n", n, (char *)buf);

      for(i = 0;i < n;++i){
        if(buf[i] == 'S'){
          printf("Confirmation signal received.\n");
          command_confirmed = 1;
          break;
        }
      }
      if(command_confirmed) break;
      else printf("Confirmation signal not received.\n");
    }
  }
}

