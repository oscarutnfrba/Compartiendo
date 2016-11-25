#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <error.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define TAMANIO 32
#define PUERTO 3090

int main (int argc, char* argv[])
{ 
  int  i=2;
  int  ok=0;
  int  res=0;
  char repuesto[20];
  char opcion[10];
  int  descServer, size, bytes;
  char buffer[TAMANIO];
  struct sockaddr_in servaddr;
  struct hostent* host;
  
  size = sizeof(struct sockaddr);
  
  if (argc != 2)
                {
                  printf("Asegurese de pasar la IP\r\n");
                  return(1);
                }
  
  if((host=gethostbyname(argv[1])) == NULL)
                                            {
                                              perror("Gethostbyname: ");
                                              return(1);
                                            }
while(1){
  descServer = socket(AF_INET, SOCK_STREAM, 0);
  if (descServer == -1)
                        {
                          perror("Socket: ");
                          return (1);
                        }
  
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PUERTO);
  servaddr.sin_addr = *((struct in_addr *)host->h_addr);	
  memset(&(servaddr.sin_zero),'\0',8); //Puede usarse bzero()

  if(connect (descServer,(struct sockaddr*) &servaddr, size) == -1)
                                                                    {
                                                                      perror("Connect: ");
                                                                      return(1);
                                                                    }
//****************************************************************************************************

  bytes = read(descServer,buffer, TAMANIO);//ingrese crear u otra para seguir                  1mer read
  
  printf("Recibí: %s\r\n", buffer);
  __fpurge(stdin);
  scanf("%s",opcion);//ingresa crear o continuar
   if(write(descServer, opcion, strlen(opcion)+1)== -1)//envia crear o continuar               1er write
                                                                {
                                                                  perror("Write: ");
                                                                  return(0);
                                                                }
//*****************************************************************************************************

    res=strcmp(buffer,"crear");                                        //compara si acepta crear
    if (res==0){                                                       //si es crear entra 
       bytes = read(descServer,buffer, TAMANIO);//ingrese new user                             2do read
  
  printf("Recibí: %s\r\n", buffer);//ingrese user new
  __fpurge(stdin);
  scanf("%s",buffer);
  if(write(descServer, buffer, strlen(buffer)+1)== -1)//mando user new                         2do write
    {
      perror("Write: ");
      return(0);
    }
    bytes = read(descServer,buffer, TAMANIO); // nuevo nombre si existe                        3er read
    ok=strcmp(buffer,"existeuser");
    
    if (ok==0){
    printf("Este usuario %s ya existe, pruebe con otro:\r\n",buffer);
     __fpurge(stdin);
     scanf("%s",buffer);
     if(write(descServer, buffer, strlen(buffer)+1)== -1)//mando user new                      3er write
    {
      perror("Write: ");
      return(0);
    }
        bytes = read(descServer,buffer, TAMANIO);                                              //4to read
    ok=strcmp(buffer,"existeuser");                         //si elnew user existe da 0
      
    }
    
     bytes = read(descServer,buffer, TAMANIO);//le pide pass new                               //5to read 
     printf("Recibí: %s\r\n", buffer);
     
       __fpurge(stdin);
       scanf("%s",buffer);
       if(write(descServer, buffer, strlen(buffer)+1)== -1)                                    // 4to write
    {
      perror("Write: ");
      return(0);
    }
    system("clear");
    bytes = read(descServer,buffer, TAMANIO);///se creo el user                                 //5to read 
        printf("%s\r\n",buffer);
    }
//**************************************************************************************************************

printf("Puede continuar\r\n");

  bytes = read(descServer,buffer, TAMANIO);//recibe ingrese user                                 6to read
  
  printf(" %s\r\n", buffer);//ingrese usuario
  __fpurge(stdin);
  scanf("%s",buffer);
  
  if(write(descServer, buffer, strlen(buffer)+1)== -1)//manda usuario                            5to write
    {
      perror("Write: ");
      return(0);
    }
     bytes = read(descServer,buffer, TAMANIO);//recibe usernoexiste                              7mo read 
     ok=strcmp(buffer,"usernoexiste");
     if (ok==0){
       printf("El usuario no existe, intentelo de nuevo.\r\n");
       __fpurge(stdin);
       scanf("%s",buffer); 
       if(write(descServer, buffer, strlen(buffer)+1)== -1)//manda usuario                       6to write
    {
      perror("Write: ");
      return(0);
    }
    ok=strcmp(buffer,"usernoexiste"); 
    }
     bytes = read(descServer,buffer, TAMANIO);//recibe ingrese pass                                8vo read
  
  printf(" %s\r\n", buffer);//ingrese pass
  __fpurge(stdin);
  scanf("%s",buffer);
  
  if(write(descServer, buffer, strlen(buffer)+1)== -1)//manda pass                                 7mo write
    {
      perror("Write: ");
      return(0);
    }
    bytes = read(descServer,buffer, TAMANIO);//recibe usernoexiste error de pass                    9no read
    ok=strcmp(buffer,"usernoexiste");
    if(ok==0){
      printf("El pasword proporcionado es erroneo, tiene %d intentos mas...",i);
      i--;
      __fpurge(stdin);
      scanf("%s",buffer);
      if(write(descServer, buffer, strlen(buffer)+1)== -1)//manda pass                               8vo write
    {
      perror("Write: ");
      return(0);
    }
    bytes = read(descServer,buffer, TAMANIO);//recibe user                                           10mo read
     ok=strcmp(buffer,"usernoexiste");
    }
    system ("clear");
    printf(" Ud. se ha logueado exitosamente\r\n");
    system ("cat bienvenida.dat");
//***********************************************************************************************************
    
//***********************************************************************************************************
  close(descServer);
 }
  return(0);
}