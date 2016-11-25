#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <error.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define BACKLOG 500 
#define PUERTO 3090
#define TAMANIO 100
#include <unistd.h>
#include "funcionesListas.h"

int buscar (char *buffer); //funcion a la cual yo le mando un puntero a puntero al string con el repuesto a buscar

int main (void)
{
  NODO *aux = NULL;
  NODO *ppio_res= NULL;
  int descServer, descCliente, size, bytes;
  int i =0;
  int ok = 1;
  int resultado = 0;
  int opcion =0;
  int contador = 0;
  struct sockaddr_in miaddr, cliente;
  char vaciar[]="vacio";
  char buffer[TAMANIO];
  char oklogueo[]="usted se ha logueado correctamente\n";
  char nohay[]= "no hubo coincidencias, quiere buscar, listar o salir?\n";
  char sihay[]= "felicidades, se encontro algo, queres verlo? s/n\n";
  char repuesto[]= "escriba el repuesto a buscar\n";
  char usrexist[]= "existeusr";
  char inpass[]="ingrese pass\r\n";
  char usrnew[]= "ingrese nuevo usuario\n";
  char msginicial []= " bienvenido, ingrese''crear'' para nuevo, o cualquier tecla para loguear\n";
  char msg[]= "elija ''buscar'', ''listar'', ''agregar'', ''borrar'', ''salir''\n\n ";
  char ingreserep []= "Indique nombre del repuesto\n";
  char login[]= "ingrese su usario\n";
  char loginpass[] = " muy bien, ingrese pass\r\n";
  char usrerror[] ="usrnoexiste";
  char passerror[] = "pass invalida, intentede nuevo\n";
  char useraceptado[] = "su cuenta se ha creado satisfactoriamente\n";
  size = sizeof(struct sockaddr);
  
  descServer = socket(AF_INET, SOCK_STREAM, 0);
  if (descServer == -1)
  {
    perror("Socket: ");
    return (1);
  }
  
  miaddr.sin_family = AF_INET;
  miaddr.sin_port = htons(PUERTO);
  miaddr.sin_addr.s_addr = INADDR_ANY;
  memset(&(miaddr.sin_zero),'\0',8);
  
  if(bind(descServer, (struct sockaddr *)&miaddr, sizeof(struct sockaddr)) == -1)
  {
    perror("Bind: ");
    return(1);
  }
  
  if(listen (descServer, BACKLOG) == -1)
  {
    perror("Listen: ");
    return(1);
  }
  printf ("servidor en marcha\n");
  while(1)
  {
    descCliente = accept(descServer, (struct sockaddr *)&cliente, &size);
    if(descCliente == -1)
    {
      perror("Accept: ");
      return(1);
    }
 //********************************************************************************************************************************   
    printf("Se conectó el cliente %s\r\n", inet_ntoa(cliente.sin_addr));
//*********************************************************************************************************************************  
    //        					MENSAJE INICIAL
    if(write(descCliente, msginicial, strlen(msginicial)+1)== -1)//   (1)       -----
    {//                                                               
      perror("Write: ");
      return(0);//                                              
    }
        bytes = read(descCliente,buffer, TAMANIO); // [1]pregunta si crear
  
  printf("Recibí: %s\r\n", buffer);//                                         -----
  
  
  //*********************************************************************************************************************************
  //                                   CREA CUENTA
  opcion= strcmp(buffer,"crear");                               
  if (opcion == 0)
  {
      if(write(descCliente, usrnew, strlen(usrnew)+1)== -1)// dice  "ingrese nuevo usuario " (2)
      {//                                                               
	perror("Write: ");
	return(0);//                                              
      }
	if(!(aux=(NODO*)malloc(sizeof(NODO))))
	{
	  perror ( "malloc");
	  return 0;
	}
	
	
        bytes = read(descCliente,buffer, TAMANIO);//[2] recibe nombre del nuevo usuario
	printf ("recibi: %s\n",buffer);
	ok=crearUsuario(buffer,&aux);
	printf ("VALOR DE OK: %d\n", ok);
	
	while (ok==1)
	{
	    if(write(descCliente, usrexist, strlen(usrexist)+1)== -1)// dice  "ingrese nuevo usuario " (3)
	    {//                                                               
	      perror("Write: ");
	      return(0);//                                              
	    }
	    bytes = read(descCliente,buffer, TAMANIO); //  (3) recibo el usuario corregido
	    printf ("recibi %s\n", buffer);
	    ok = crearUsuario (buffer, &aux);
	    
	}
	
	printf ("se creo el usuario %s\n",buffer);
	
	 if(write(descCliente, inpass, strlen(inpass)+1)== -1)// envio mensaje "ingrese pass(4)
	  {//                                                               
	    perror("Write: ");
	    return(0);//                                              
	   }
      
	bytes = read(descCliente,buffer, TAMANIO);// [4]recibe contraseña  
	nuevoPass (buffer,&aux);
        printf("Recibí: %s\r\n", buffer);
 
        printf (" linea 140 se creo satisfactoriamente la cuenta\n");         
  
        if(write(descCliente, useraceptado, strlen(useraceptado)+1)== -1)// cuenta creada satisfactoriamente"  
	{                                                            
	  perror("Write: ");
	  return(0);//                                              
	}
  }
  //**************************************************************************************** 
  //                                 		 LOGIN
  
  if(write(descCliente, login, strlen(login)+1)== -1)//   (6) envio "ingrese su usuario"
    {//                                                               
      perror("Write: ");
      return(0);//                                              
    }
        bytes = read(descCliente,buffer, TAMANIO);//   [5]    recibe nombre de usuario a loguear
	printf ("recibi: %s \r\n", buffer);
	ok=loginUsuario (buffer, &aux);
	while (ok==1)
	{
	  if(write(descCliente, usrerror, strlen(usrerror)+1)== -1) // (7)envia " error, el usuario que ingresaste para logear no existe"
	  {                                                               
	    perror("Write: ");
	    return(0);                                            
	   }
	   bytes = read(descCliente,buffer, TAMANIO);//[6] recibe reingreso de user bien puesto
	   ok = loginUsuario (buffer, &aux);
	}
	
	  if(write(descCliente, loginpass, strlen(loginpass)+1)== -1)//   (8) envio mensaje "  ingrese contraseña"
    {//                                                               
      perror("Write: ");
      return(0);//                                              
    }

	
	bytes = read(descCliente,buffer, TAMANIO);// [7]recibe ingreso de contraseña
	ok= loginPassword (buffer, &aux);
  
  while ((ok ==1) &&(i<3))
  {
    
	  if(write(descCliente, usrerror, strlen(usrerror)+1)== -1)//    (9) // le envia al cliente aviso de que la contraseña no es esa
	  {                                                               
	    perror("Write: ");
	    return(0);                                            
	   }
	   bytes = read(descCliente,buffer, TAMANIO);// [8] recibe el reingreso de la contraseña
	    ok = loginPassword (buffer, &aux);
	   i++;
  }
  
  if ( i==2)
  {
	   close (descCliente);
  }
    
  if(write(descCliente, oklogueo, strlen(oklogueo)+1)== -1)
    {
      perror("Write: ");
      return(0);//                                          
    }

 //*****************************************************************************************************************************   
    do
    {
    
    if(write(descCliente, msg, strlen(msg)+1)== -1)//   (11)// bienvenido al menu princial elija opcion       ----
    {
      perror("Write: ");
      return(0);//                                          
    }
    
    bytes = read(descCliente,buffer, TAMANIO);// [9] recibe opcion de menu principal "buscar listar agregar y borrar"
  
  printf("Recibí: %s\r\n", buffer);//   
  //****************************************************************************************************************************************************************************************
    
      
  
    }
    while (!(strcmp(buffer,"salir")));
    
    
    
//**************************************************************************************************************************************************************************************
    //                   BUSCAR
  if(!(strcmp(buffer,"buscar")))// si buffer dice buscar, se mete
  {
    if(write(descCliente, repuesto, strlen(repuesto)+1)== -1)//   (12)// que repuesto queres buscar?      ----
    {
      perror("Write: ");
      return(0);//                                          
    }
     bytes = read(descCliente,buffer, TAMANIO); // [10] recibo el nombre del repuesto a buscar
     
     //resultado= buscarArticulo(buffer, &ppio_res);
     
     if(ppio_res == NULL)
     {
       if(write(descCliente, nohay, strlen(nohay)+1)== -1)//   (13)// le digo "el repuesto no existe"      ----
	{
	  perror("Write: ");
	  return(0);//                                          
	}
     }
     else
     {
      if(write(descCliente,sihay , strlen(sihay)+1)== -1)//   (14)// le mando " se encontro repuesto"      ----
      {
	perror("Write: ");
	return(0);//                                          
      }
      
      for (resultado; resultado >0; resultado--)
      {
	strcpy (buffer,ppio_res-> nombre);
      }
     
     if(write(descCliente,buffer , strlen(buffer)+1)== -1)//   (15)// le mando el nombre al cliente      ----
      {
	perror("Write: ");
	return(0);//                                          
      }
      strcpy(buffer, ppio_res->telefono);
     
     if(write(descCliente,buffer , strlen(buffer)+1)== -1)//   (16)// le mando el telefono      ----
      {
	perror("Write: ");
	return(0);//                                          
      }
      
      ppio_res=ppio_res->siguiente;
      
     
     
   //buffer[]={""}; // para que no pueda entrar en otro              ME TIRA ERROR
   
       
 //   }
 // }//************************************************************************************************************************************************************************************
  //                           AGREGAR
  
 /* if (!(strcmp(buffer,"agregar")))
  {}
  
  if (!strcmp(buffer, "listar")))
  {}
  
  if(!(strcmp(buffer, "borrar")))
  {}
  */ 
    
   
    
    
    
    
    
    
    
     
    
                                              
    
/*    
    if(resultado > 0 && contador < resultado)
    {
      if(write(descCliente, buffer, strlen(buffer)+1)== -1)//  (13) le mando al cliente los vendedores
    {
      perror("Write: ");
      return(0);//                                          
    }
     bytes = read(descCliente,buffer, TAMANIO); //[] espera que el cliente me de el ok, para mandar el segundo articulo
     //imprimir (buffer)
      
      contador++;
    }
    
    
  }
  
  
  }
 */ 
    close (descCliente);
  
  return(0);
  }

  }
  }    
  }
/*int buscar (char *buffer)
{
  buffer = "pude cargar el buffer\n";
  return 5;
}
*/