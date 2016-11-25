 
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
 
struct nodo{
            char usuario [TAMANIO];
            char barrio [TAMANIO];
            int tel;
            char mail[TAMANIO];
            char pass [TAMANIO];
            struct nodo *sig;
            };

struct libro{
             char titulo[TAMANIO];
             struct libro *sig;
             };

void agregar_libro(char *);                       //el usuario agrega un libro mandas el nombre de usuario 

void baja_usuario(struct nodo**);
void buscar(struct nodo *);
void borrar_libro(char *);                         // pasa el nombre del txt a abrir para borrar libro
int  buscaUsuario(struct nodo,struct nodo**);      //busca si existe el usuario para que no haya duplicados 
int  buscaUsuario2(struct nodo); 
void buscarLibros(struct nodo**,char*);            //le paso el ppio y un libro a buscar


void crearUsuario(struct nodo**);                  //recibe ppio carga datos en una struct y se lo cuelga a la lista  
void crearDatLibro(char* string);                  //se le pasa el nombre del usuario para crear la sublista

void guardarUser(struct nodo);
void guardarLista(struct nodo**);
void guardarlibro(struct libro*,char *);

void ins_orden(struct nodo ,struct nodo**);

void listar_mislibros (char *usuario);             // muestra los libros del usuario
void listar_libros(struct nodo**);                 //muestra todos los libros de todos los usuarios sin repetir en orden alfabetico 
void levantarLista(struct nodo**);
void loguearse(struct nodo**);                     // mando * para que quede el nombre y poder mandar a abrir el fp de libros

void ordenarUser(struct nodo**);
void ordenarLibro(struct libro**);

void validar_usuario(struct nodo *);               //valida usuario y password

//#include "headers.h"
//#include "a.c"
char buffer[TAMANIO];
int descServer, descCliente, size, bytes;
int main (void)
{ 
int i =0; 
//***********************************************************************************************************************  
 
  struct nodo* ppio;
  struct libro* libro;
  struct sockaddr_in miaddr, cliente; 
  size = sizeof(struct sockaddr); 
  descServer = socket(AF_INET, SOCK_STREAM, 0);
  if (descServer == -1)   { perror("Socket: ");  return (1); }
  miaddr.sin_family = AF_INET;
  miaddr.sin_port = htons(PUERTO);
  miaddr.sin_addr.s_addr = INADDR_ANY;
  memset(&(miaddr.sin_zero),'\0',8);
  if(bind(descServer, (struct sockaddr *)&miaddr, sizeof(struct sockaddr)) == -1){  perror("Bind: "); return(1); } 
  if(listen (descServer, BACKLOG) == -1) { perror("Listen: "); return(1); }
//*************************************************************************************************************************
printf ("servidor en marcha\n");
  
   
while(1){
         descCliente = accept(descServer, (struct sockaddr *)&cliente, &size);
         if(descCliente == -1) { perror("Accept: "); return(1); }
         printf("Se conectó el cliente %s\r\n", inet_ntoa(cliente.sin_addr));
    
//**************************************************************************************************************************    
do{
    strcpy(buffer,"hola bienvenido\ndesea crear o loguear?\n"); 
    if(write(descCliente,buffer, strlen(buffer)+1)== -1) { perror("Write: ");  return(0); }
    
    bytes = read(descCliente,buffer, TAMANIO);  
    if(strcmp(buffer,"crear usuario")==0){
                                          levantarLista(&ppio);
                                          crearUsuario(&ppio);
                                         }
    printf("Recibí: %s\r\n", buffer); 
    
  
    }while (strcmp(buffer,"salir")!=0);
    
    close (descCliente); 
   }
 return(0);
  }
  
  
 //************************************************************************************************************************
 
 
 
 
 
 //*************************************************************************************************************************
  
  
  
  
  
void listar_libros(struct nodo**ppio){
  FILE*fp;
  int existe=0; 
  struct nodo*aux;
  struct libro*libro=NULL;
  struct libro*listalibro=NULL;
  struct libro*recorre;
  aux=*ppio;
  //se arma una lista de los libros y se va comparando si ya esta en la lista no se vuelve a colgar y desp se imprime 
while(aux){
  existe=0;         
  fp=fopen(aux->usuario,"rb");
  libro=(struct libro*)malloc(sizeof(struct libro));
  fread(libro,sizeof(struct libro),1,fp);
  while(!feof(fp)){
                    if(listalibro==NULL){                 //si es el primer libro lo cuelgo como unico elemento
			                  listalibro=libro;
					  libro->sig=NULL;
		    }else{                                
			  recorre=listalibro;//igualo a ppio para comparar a ver si ya colgue ese libro
			  while(recorre){
				          if(strcmp(libro->titulo,recorre->titulo)==0) existe=1; 
					   recorre=recorre->sig;  
			                  }
if(existe==0){                               //si no existe en la lista se cuelga 
              libro->sig=listalibro;
	      listalibro=libro; 
             }
				 	     
				   }            
			    libro=(struct libro*)malloc(sizeof(struct libro));
			    fread(libro,sizeof(struct libro),1,fp);
	                   }
    
    fclose(fp);
    aux=aux->sig;
  }//de aca sale con la lista de libros sin repetirse desordenados
  ordenarLibro(&listalibro);
  recorre=listalibro;
  while(recorre){
                  printf("%s\n",recorre->titulo);
		  recorre=recorre->sig;
                 }
  
  return;
}
void borrar_libro(char *usuario){
  char aborrar[41];
  FILE *fp;
fp=fopen(usuario,"rb");
struct libro *aux, *L=NULL,*ant;  
  
aux=(struct libro*)malloc(sizeof(struct libro));
fread(aux,sizeof(struct libro),1,fp);
  while(!feof(fp)){
                   if(L==NULL){
                               L=aux;
                               aux->sig=NULL;
                  }else{
                        aux->sig=L;
                        L=aux;
                       }
                    aux=(struct libro*)malloc(sizeof(struct libro));
                    fread(aux,sizeof(struct libro),1,fp);
                   }
   fclose(fp);
  ordenarLibro(&L);
 do{
   
   
  printf("que libro desea borrar?\n");
  aux=L;
  ant=L;
  while(aux){ 
             printf("%s\n",aux->titulo);
             aux=aux->sig;
             }
  scanf(" %s",aborrar);
  aux=L;
  while(aux){  
             if(strcmp(aborrar,aux->titulo)==0){
	                                        while(ant->sig!=aux)
		                                        ant=ant->sig;
	                                        ant->sig=aux->sig;
	                                        }
             aux=aux->sig;
             }
  system("clear");
  printf("\nel libro %s se ha eliminado de la lista\ndesea borrar otro libro?\n",aborrar);
  scanf(" %s",aborrar);          
 }while(strcmp(aborrar,"s")==0);
 aux=L;
 fp=fopen(usuario,"wb");
 while(aux){
   fwrite(aux,sizeof (struct libro),1,fp);
   aux=aux->sig;
}
fclose(fp);
  return;
}
void listar_mislibros(char* usuario){
 
FILE *fp; 
fp=fopen(usuario,"rb");
struct libro *aux, *L=NULL;  
  
aux=(struct libro*)malloc(sizeof(struct libro));
fread(aux,sizeof(struct libro),1,fp);
  while(!feof(fp)){
                   if(L==NULL){
                               L=aux;
                               aux->sig=NULL;
                  }else{
                        aux->sig=L;
                        L=aux;
                       }
                    aux=(struct libro*)malloc(sizeof(struct libro));
                    fread(aux,sizeof(struct libro),1,fp);
                   }
   
  ordenarLibro(&L);
 
  aux=L;
  while(aux){ 
             printf("%s\n",aux->titulo);
             aux=aux->sig;
             }
             
  fclose(fp);
return;
}
void ordenarLibro(struct libro **ppio){ 
if (*ppio==NULL){
                 printf("lista vacia\n");
                  return;
                 }
   
  struct libro *p,*max,*aux=NULL;
  
  p=*ppio;
  
while(*ppio){
        max=p;
	      while(p){
		      if (strcmp(max->titulo,p->titulo)<0){
								max=p;
							      }
			p=p->sig;
		      } 
    if (*ppio==max){
                    (*ppio)=max->sig;
		    max->sig=aux;
		    aux=max;
                   }
    else{
         p=(*ppio);
	 while(p->sig!=max){ 
	                     p=p->sig;
	                    }
	 p->sig=max->sig; 
	 max->sig=aux;
	 aux=max;
         }             
                
    p=*ppio;
  }

  *ppio=aux;
  return;
}


void agregar_libro(char *usuario){
  
  struct libro new; 
  char opcion[21]={"s"};
  FILE*fp; 
  fp=fopen(usuario,"ab");
  do{  
     printf("ingrese el titulo desea agregar %s\n",usuario); 
     getchar();
     gets(new.titulo);
     fwrite(&new,sizeof(struct libro),1,fp);  
     printf("libro %s agregado a su lista\ndesea agregar otro libro? s/n \n",new.titulo); 
     scanf("%s",opcion);
     }while(strcmp(opcion,"s")==0);
  
  fclose(fp); 
  
  
  return;
}

void buscarLibros(struct nodo**ppio,char* titulo){
  struct nodo*aux;
  aux=*ppio;
  struct libro*book;
  FILE* fp;
  book=(struct libro*)malloc(sizeof(struct libro));
  
  while(aux){
             fp=fopen(aux->usuario,"rb");
             fread(book,sizeof(struct libro),1,fp);
	     
 while(!feof(fp)){
	          if(strcmp(book->titulo,titulo)==0){
printf("el usuario %s tiene el libro %s\nbarrio %s tel %d mail %s\n",aux->usuario,titulo,aux->barrio,aux->tel,aux->mail);
			                            }
                  fread(book,sizeof(struct libro),1,fp);
	          }
             aux=aux->sig;
            } 
 fclose(fp);
 free(book);
 free(aux);
 return;
}



 void levantarLista(struct nodo ** ppio){ //abre como lectura arma la lista y cierra el archivo si no existe lo crea es el primer paso
  
  *ppio=NULL;
  FILE *fp;
  if(!(fp = fopen("usuarios.dat", "rb"))){ //w+b crea lectura escritura binario si no existe lo crea  
                                          fp = fopen("usuarios.dat", "wb"); 
					  printf("el archivo usuarios.dat no existia se acaba de crear\nno hay usuarios\n");
					  fclose(fp);
					  return;
                                          } 
			  
                             
  struct nodo *aux= NULL;
  aux=((struct nodo*)malloc(sizeof(struct nodo)));    
  fread(aux, sizeof(struct nodo),1,fp);
    
      
            
  while(!feof(fp)){                 //si no es feof carga la lista 
   		    if(*ppio== NULL){
				     aux->sig=NULL;
				     *ppio = aux;
				    }
		    else{ 
			aux->sig=*ppio;
			*ppio=aux;
			}
			
 aux= (struct nodo *)malloc(sizeof(struct nodo)); 
 fread(aux, sizeof(struct nodo),1,fp); 
                   }     
  
  fclose (fp);
  return;
  
}
void crearUsuario(struct nodo**ppio){    //recibe ppio carga el nuevo nodo y se lo aniade a la lista 
   
  int i=0;
  int ok=0;
  char pass[21];
  struct nodo new;   
  char buffer[TAMANIO];
do{  
   if(i<0){
	   //printf("el nombre de usuario que eligio ya existe ");
	   strcpy(buffer,"el nombre de usuario que eligio ya existe \n"); 
           if(write(descCliente,buffer, strlen(buffer)+1)== -1) { perror("Write: ");  return; }  
	  }
	//printf("ingrese nuevo nombre de usuario\n");
  strcpy(buffer,"ingrese nuevo nombre de usuario\n"); 
  if(write(descCliente,buffer, strlen(buffer)+1)== -1) { perror("Write: ");  return ; }
    
  //scanf("%s",new.usuario);
  bytes = read(descCliente,buffer, TAMANIO);  
  strcpy(new.usuario,buffer);
  if(*ppio==NULL){
	          guardarUser(new);//para que no le de tiempo a otro a elegir el mismo nombre 
                  ok=0;
	          }
	else{
	     ok=buscaUsuario2(new);               //devuelve 0 si no existe o si es feof
	     i++;  
	     }
        }while(ok!=0);
     //if(i>3){
       //      printf("intento demasiadas %d veces se desconecta\n");
         //    return;}
   
	printf("Bienvenido usuario %s\nse ha creado su usuario\n",new.usuario);
	guardarUser(new);//para que no le de tiempo a otro a elegir el mismo nombre 
	crearDatLibro(new.usuario);
	i=0;
    do{ 
      if(i>0)
      printf("el pass no coincide intentelo de nuevo\npor su seguridad debe ingresar dos veces el mismo\n");
      printf("ingrese pass \n");
      scanf("%s",pass); 
      printf("re ingrese pass \n"); 
      scanf("%s",new.pass); 
      i++;
      }while(strcmp(pass,new.pass)!=0);
     
      printf("Muy bien se ha establecido su pasword  recuerdelo.\n");
   
     printf("ingrese su mail \n"); 
      scanf("%s",new.mail); 
     printf("ingrese su barrio \n"); 
      scanf("%s",new.barrio); 
     printf("ingrese su numero de telefono\n"); 
      scanf("%d",&new.tel); 
 if(*ppio==NULL){
	         new.sig=NULL;
	         *ppio=&new;}
 else{
      new.sig=*ppio;
      *ppio=&new;
      }
     guardarLista(ppio); 
  return;
  
}
void loguearse(struct nodo**ppio ){//devuelve 1 si sale o si quiere volver al menu anterior 
  
  char string[21];
  char pass[21];
  struct nodo *aux,*user; 
  int i=0 ;   
 do{
    aux=*ppio;
    if(i>0) printf("Error el usuario no existe\ningrese salir para volver al menu anterior o  ");
    printf("ingrese su nombre de usuario\n");
    scanf("%s",string);
   
     while(aux){ 
                if(strcmp(string,aux->usuario)==0)
		   *ppio=aux;
                aux=aux->sig;
		
                }
  i++; 
  }while(strcmp(string,(*ppio)->usuario)!=0) ;
   

    
           printf("Hola!!! Bienvenid@ %s\n",(*ppio)->usuario);
   i=3; 
do{
   if(i<3) printf("\error de password\trecuerde bien e intentelo nuevamente\n");
   printf("ingrese su pass para ingresar\nle quedan %d intentos ->\t",i);
   scanf("%s",pass); 
   if(strcmp(pass,(*ppio)->pass)!=0) 
     
     i--;
   
   }while(strcmp(pass,(*ppio)->pass)!=0&&i>0);
   
   
   if(i==0){
            printf("intento demasiadas veces se desconecta\n"); 
             //desconectar 
	          return;
           }
           
  return  ;
  
}

void guardarLista(struct nodo**ppio){
 struct nodo* aux;
 aux=*ppio;
 FILE *fp;
 fp=fopen("usuarios.dat","wb");
  while(aux){
              fwrite(aux,sizeof(struct nodo),1,fp);
              aux=aux->sig;
              }
 
 fclose(fp);
}

void guardarUser(struct nodo new){
  FILE* fp;
   
  fp=fopen("usuarios.dat","ab");
  fwrite(&new,sizeof(struct nodo),1,fp);
  fclose(fp);
  return;
  
}


int buscaUsuario2(struct nodo new){                  //sin levantar en memoria con el uso de lectura y comparacion 
  int ok=1;                        
  FILE* fp;
  struct nodo* aux;
  aux= (struct nodo *)malloc(sizeof(struct nodo));   
  
  if(!(fp=fopen("usuarios.dat","rb"))){
                                       printf("error de fopen en funcion buscarusuario2\n");
                                      }
 fread(aux, sizeof(struct nodo),1,fp);
 
 while(!feof(fp)){
                  if(strcmp(new.usuario,aux->usuario)==0){ 
		                                          return ok;//ok devuelve 1 si existe
		                                          }
		   fread(aux, sizeof(struct nodo),1,fp);
                  }
  ok=0;                                                            // devuelve 0 si no existe o si es feof     
  return ok;
}
void ordenarUser(struct nodo**ppio){
  
    if (*ppio==NULL){
                     printf("lista vacia\n");
                     return;
                    }
   
  struct nodo *p,*max,*aux=NULL;
  
  p=*ppio;
  
while(*ppio){
        max=p;
	      while(p){
		      if (strcmp(max->usuario,p->usuario)<0){
								max=p;
							      }
			p=p->sig;
		      } 
    if (*ppio==max){
                    *ppio=max->sig;
		    max->sig=aux;
		    aux=max;
                   }
    else{
         p=*ppio;
	 while(p->sig!=max){ 
	                     p=p->sig;
	                    }
	 p->sig=max->sig; 
	 max->sig=aux;
	 aux=max;
         }             
                
    p=*ppio;
  }

  *ppio=aux;
  return;
}  

void crearDatLibro(char* string){
  
  FILE* fp; 
  fp=fopen(string,"wb");
  fclose(fp);
  return;
}