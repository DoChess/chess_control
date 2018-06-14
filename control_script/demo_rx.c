
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

 **************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

char teste[10] = {"G0 X7 Y8."};

int main()
{
  int i, n,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  unsigned char buf[4096];

  char mode[]={'8','N','1',0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
  }

  for(int j = 0;j < 10;++j){

    int deu_bom = 0;

    printf("1 - Enviando o comando %d\n",j); 

    //RS232_cputs(cport_nr, teste); 
    for(i = 0;i < 3;++i){
      system("echo -n 'G0 X7 Y0.' > /dev/rfcomm2");
    }

    printf("2 - Comando %d foi enviado\n",j);

    while(1){
      n = RS232_PollComport(cport_nr, buf, 4095); // Numero de bytes

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
            printf("3 - Sinal de confirmação recebido\n.");
            deu_bom = 1;
            break;
          }
        }
        if(deu_bom) break;
      }
    }
  }

  return(0);
}

