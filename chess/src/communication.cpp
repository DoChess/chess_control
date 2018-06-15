
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

void send_command(string command){
  //printf("O comando foi %s\n",command.c_str());

  int command_confirmed = 0;
  string system_call = "echo -n '"  + command + ".' > /dev/rfcomm2";

  printf("1 - Enviando o comando %s\n", system_call.c_str()); 

  for(i = 0;i < 3;++i){
    //system("echo -n 'G0 X7 Y0.' > /dev/rfcomm2");
    system(system_call.c_str());
  }

  printf("2 - Comando foi enviado\n");

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

      printf("Recebidos %i bytes: %s\n", n, (char *)buf);

      for(i = 0;i < n;++i){
        if(buf[i] == 'S'){
          printf("3 - Sinal de confirmação recebido.\n");
          command_confirmed = 1;
          break;
        }
      }
      if(command_confirmed) break;
      else printf("X - Sinal de confirmação não foi recebido.\n");
    }
  }

}

