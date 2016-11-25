 
//#include "headers.h"
//#include "a.c"  stcmp
 
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
  char nomuser[TAMANIO];
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
   i=0;
    
do{ 
  if(i>0){
          printf("Error de seleccion\n Ingrese: 'crear usuario','loguear' o 'salir' para cerrar el programa\n");
         }
   __fpurge(stdin); 
   gets(buffer);
  if (strcmp(buffer,"salir")==0){
  			printf("GRACIAS POR UTILIZAR 'COMPARTIENDO LIBROS'\n");
    	break;
  			}
    	
    i++;
  }while((strcmp(buffer,"crear usuario")!=0)&&(strcmp(buffer,"loguear")!=0));
    
    
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
          printf( "La contraseña debe tener una minimo de 4 letras.\nIngreselo nuevamente:\n");
         }
         
__fpurge(stdin); 
gets(buffer);  //elijo pass 
printf("Repita su contraseña:\t");
gets(bufferaux);  //reingreso pass 
if (strlen(buffer)<4)
  strcpy(buffer,"menoracuatro");
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
  system("clear");
  bytes = read(descServer,buffer, TAMANIO); //ingrese su nombre de usuario 
  printf("\t%s\r\n", buffer);
    
while(strcmp(buffer,"ok")!=0){
  
    __fpurge(stdin); 
    gets(buffer);  // ingreso nombre de usuario
    strcpy(nomuser,buffer);
    if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); }//envio nombre de usuario
    bytes = read(descServer,buffer, TAMANIO);//recibo ok o error
    system("clear"); 
    
   }//recibe un ok cuando exista el usuario y a continuacion va a pedir el pass 
   
   //salgo con un read que me mando el server con un ok en buffer 
 //**************************      hasta aca comprobacion de nombre  *********************************** 
 
 
 
 //**************************     desde aca comprobacion de pass        *********************************** 
 
    printf("\n\tvv  Hola bienvenido %s ingrese su pasword  vv  =>>>  ",nomuser);
    __fpurge(stdin); 
    gets(buffer);  //  recojo el pass  
    if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); } //envio pass 
    
    bytes = read(descServer,buffer, TAMANIO);//recibo ok o error
   
    printf("recibi respuesta por el pass que mande => %s\n",buffer);
  
   if(strcmp(buffer,"ok")==0){
                             printf("Hola ''%s''podes comenzar !!!\n",nomuser);
                             return;
  } else{
    i=0;
    while(strcmp(buffer,"exit")!=0){
    
           printf("\t\n'''ERROR'''\n\tEl pass no coincide... recuerde bien.\nLe quedan %d intentos =>  ",i);  
	   
	   __fpurge(stdin); 
           gets(buffer);  // re ingreso pass
     
           if(write(descServer, buffer, strlen(buffer)+1)== -1){ perror("Write: "); return(0); }//re envio pass
           bytes = read(descServer,buffer, TAMANIO);//recibo ok o error
           system("clear");
           printf("\n%s\n\n", buffer);
	   if(strcmp(buffer,"ok")==0){
                                      printf("\t\nHola ''%s''podes comenzar !!!\n",nomuser);
                                      return;
                                     }                 
	   
           }
         }
     
     
     
  return;
}
//********************************** fin del loguear ********************************************
 
 
 
 
     
  
}while(strcmp(buffer,"salir")!=0);
     break;
  }
  return(0);
}  