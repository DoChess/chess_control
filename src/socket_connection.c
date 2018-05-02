#include <stdio.h>
#include<string.h>
#include<signal.h>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int SD;
int fd;
char send_buff[300];
char rec_buff[300];
int xablau = 15;

void my_isr(int n)
{
  printf("In Isr..\n");
  write(fd,"**************SERVER TERMINATED!!************",50);
  close(SD);
  printf("SOCKET closed\n");
  kill(getpid(),9);///Kill this process now…
}

void init_server(){
  //Declaring Socket as Global for Signalling in my_

  //my_isr is just for changing the behaviour of SIGNAL 2 i.e ctrl+x /////

  int portNumber = 8080;

  //Sending buffer for "sever to client"
  memset(send_buff,0,300);

  //receving buffer for "Client to server"
  memset(rec_buff,0,300);

  //FIll the  family and address..so that we can bind this details with the socket to be created..
  struct sockaddr_in addr;
  memset(&addr,0,sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(portNumber);

  //////////////////////Creating a SOCKET/////////////////////////
  if((SD=socket(AF_INET,SOCK_STREAM,0))==-1)
  {
    printf("ERROR:Socket failed\n");

    return ;
  }
  printf("SUCCESS:Socket opened\n");

  ///////////////////////////binding.//////////////////////////////////////
  if(bind(SD,(struct sockaddr *)&addr,sizeof(addr))==-1)
  {
    printf("ERROR:Binding on server\n");

    close(SD);
    return;
  }

  ///////////////////////////Listening./////////////////////////////////////////
  printf("LIstening\n");
  listen(SD,5);//listen for any client for up to 5 queues

  ///////////////////////////////////Accepting/.///////////////////////////////

  if((fd=accept(SD,NULL, NULL))<0)
  {
    printf("ERROR:ACCEPT by server\n");
    close(SD);
    return;
  }
  printf("SUCCESS:ACCEPT by Server\n");

  signal(2,my_isr);//modifying the behaviour of the signal 2 as defined in my_isr..routine

  //////////////////Creating parallel processes in while execution//////////////////////////

}
