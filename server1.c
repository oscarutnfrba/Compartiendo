 
//#include "headers.h"
//#include "a.c"  
 
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
  
 system("clear");
 
 while(1){
   
  do{ 
  
   bytes = read(descServer,buffer, TAMANIO); //CREAR usuario O LOGUEAR?
   printf(" %s\r\n", buffer);
   __fpurge(stdin); 
   gets(buffer);  
   if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio crear usuario o loguear
   
   
   
//***************************** si elige crear usuario manda a server y entra aca ****************************************
if(strcmp(buffer,"crear usuario")==0){
 
bytes = read(descServer,buffer, TAMANIO); //ingrese nuevo nombre de usuario 
printf(" %s\r\n", buffer);
    
while(strcmp(buffer,"ok")!=0){
  
    __fpurge(stdin); 
    gets(buffer);  //escribe el usuario a crear 
    if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio usuario a crear
    bytes = read(descServer,buffer, TAMANIO); //el usuario ya existe ingrese otro u ok 
    printf(" %s\r\n", buffer);
    
   }//recibe un ok cuando no exista el usuario y pueda crearlo
  
    
  
printf("felicitaciones su usuario ha sido creado con exito.\nIngrese su pass. Debe ser ingresado dos veces:\n");
  
  
  //*********************************hasta aca crear usuario**************************
   
i=0;
do{
  if(i>0){
          printf( "El pass debe coincidir las dos veces por su seguridad.\nReintente escribirlo nuevamente:\n");
         }
         
__fpurge(stdin); 
gets(buffer);  //elijo pass 
printf("Reingrese pass:\t");
gets(bufferaux);  //reingreso pass 

i++;
}while(strcmp(buffer,bufferaux)!=0);

if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio pass confirmado

bytes = read(descServer,buffer, TAMANIO); //muy bien recuerde su pass , ingrese su mail 
printf(" \t%s\t", buffer);
__fpurge(stdin); 
gets(buffer);  //escribo mi mail  
if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio mail

bytes = read(descServer,buffer, TAMANIO); //ingrese su barrio 
printf(" \t%s\t", buffer);
__fpurge(stdin); 
gets(buffer);  //escribo barrio
if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio barrio

bytes = read(descServer,buffer, TAMANIO); //ingrese su num de tel 
printf(" \t%s\t", buffer);
__fpurge(stdin); 
gets(buffer);  //escribo num de tel 
if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio num de tel 


}
//********************** hasta aca crear usuario **********************************************************

//********************** si eligio loguear mando loguear a server y entra aca  ***********************

if(strcmp(buffer,"loguear")==0){ 
   
  bytes = read(descServer,buffer, TAMANIO); //escriba su nombre de usuario para loguearse
  printf(" \t%s\t", buffer);
  __fpurge(stdin); 
  gets(buffer);                             //escribo mi usuario
  if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio mi usuario 
  
  
  
  
  
  
}
 
 
 
 
    bytes = read(descServer,buffer, TAMANIO); //escriba salir para salir 
    printf(" \t%s\t", buffer);
    __fpurge(stdin); 
    gets(buffer);  //escribo salir u otra cosa
    if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio salir u otra cosa
  
}while(strcmp(buffer,"salir")!=0);
     break;
  }
  return(0);
}