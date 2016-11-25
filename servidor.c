 
//#include "headers.h"
//#include "a.c"  
//http://ssalanitri.blogspot.com.ar/2010/03/buenas-practicas-de-programacion-en-c_10.html
#include<stdio.h>
#include <stdio.h>
#include <error.h>
#include <netdb.h>
#include<stdlib.h>
#include<string.h>
#include <string.h>
#include <unistd.h>  
#include <stdlib.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG 500 
#define PUERTO 3090
#define TAMANIO 100

char buffer[TAMANIO];
int descServer, descCliente, size, bytes;

int main (int argc, char* argv[])
{ 
  int  i=0; 
  //char buffer[TAMANIO];
  char bufferaux[TAMANIO];
  struct  hostent* host;
  struct sockaddr_in servaddr;
  int  descServer, size, bytes;
  
  size = sizeof(struct sockaddr);
  
  if (argc != 2){
                  printf("Asegurese de pasar la IP\r\n");
                  return(1);
                }
  
  if((host=gethostbyname(argv[1])) == NULL) { perror("Gethostbyname: "); return(1);  }
  descServer = socket(AF_INET, SOCK_STREAM, 0); 
  if (descServer == -1) { perror("Socket: "); return (1);  } 
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PUERTO);
  servaddr.sin_addr = *((struct in_addr *)host->h_addr);	
  memset(&(servaddr.sin_zero),'\0',8); //Puede usarse bzero() 
  if(connect (descServer,(struct sockaddr*) &servaddr, size) == -1){ perror("Connect: "); return(1); }
  
 
 
 while(1){
   
  
do{
  
   bytes = read(descServer,buffer, TAMANIO); //CREAR O LOGUEAR?
   printf(" %s\r\n", buffer);
   do{
      __fpurge(stdin);
      printf("ingrese crear usuario o loguear");
      gets(buffer);  
      }while((strcmp(buffer,"loguear")!=0&&buffer,"crear usuario")!=0);
   
   if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio crear o loguear
   
   }while (strcmp(buffer,"salir")!=0);
    
  return(0);
  }
}