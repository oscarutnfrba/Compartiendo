 
#include "headers.h"
/*
R abre si no existe da error no lo crea 
W crea si existe sobrescribe se pierde lo anterior  
A abre o crea para aniadir si existe se abre apuntando al final si no existe lo crea  

ab abre en modo escritura binario para aniadir al final si no existe lo crea  
+ se adiciona  
B binario se debe combinar con r w a  
w+ crea p lectura escritura sobreescribe el anterior  
wb crea para escritura en binario si existe sera sobrteescrito  
w+b crea lectura escritura binario si no existe lo crea  

r+ abre existente lectura escritura si no existe produce error  
rb abrir para lectrura en modo binario si no existe da error  
r+b abre binario lectura escritura si no existe da error
strcat
*/
int main (void){
  
  struct nodo* ppio=NULL,*aux; 
  
  char opcion[21];
  char titulo[31];
  int resultado=0;
  char usuario[21];
  char* us; 
  int choice=0;
  printf("desea crear usuario? s/n\n " );
  scanf("%s",opcion);
  
  if (strcmp(opcion,"s")==0){
                             levantarLista(&ppio); 
                             crearUsuario(&ppio); 
                             printf("usuario creado satisfactoriamente\n");
                             }
  
  printf("desea loguearse? s/n\n " );
  scanf("%s",opcion);
  
  if (strcmp(opcion,"s")==0){
                             levantarLista(&ppio);
                             loguearse(&ppio); 
			    
                             } 
  
   printf("usuario %s logueado satisfactoriamente\n",ppio->usuario);
  
   while(1){
    printf("\nQUE DESEA HACER?\n\n1-buscar libros\n2-agregar libros\n3-borrar libros\n4-listar sus libros\n5-listar todos los libros\n6-Salir\n\n");
                                   
                   scanf("%d",&choice);
  if(choice==1){
                printf("ingrese el titulo a buscar\n");
                scanf("%s",titulo);
                buscarLibros(&ppio,titulo);
                }
  
  
   if(choice==2){ 
                 agregar_libro(ppio->usuario); 
                }
   if(choice==3){ 
                 borrar_libro(ppio->usuario);
                }
  if(choice==4){ 
                 listar_mislibros(ppio->usuario);
                }
  if(choice==5){ 
                levantarLista(&ppio);
                listar_libros(&ppio);
                }
  if(choice==6){ 
                printf("\nGRACIAS POR UTILIZAR EL SERVICIO\n");
		return 0;
                }
   }
  
  return 0;
} 
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
  }//de aca se pretende salir con la lista de libros sin repetirse desordenados
  //se podria ordenar 
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
  getchar();
  gets(aborrar);
  //scanf(" %s",aborrar);
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
//   getchar();
//   gets(aborrar);
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
     //fgets(new.titulo,41,stdin);
     //scanf(" %s",new.titulo);
     fwrite(&new,sizeof(struct libro),1,fp);  
     printf("libro %s agregado a su lista\ndesea agregar otro libro? s/n \n",new.titulo); 
     scanf(" %s",opcion);
     }while(strcmp(opcion,"s")==0);
  
  fclose(fp); 
  
  
  return;
}

void buscarLibros(struct nodo**ppio,char* titulo){
  
  struct nodo*aux;
  lenvantarLista(&aux);
  //aux=*ppio;
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
 
     do{  
	if(i>0)
	printf("el nombre de usuario que eligio ya existe ");
	printf("ingrese nuevo nombre de usuario\n");
	scanf("%s",new.usuario);  
	if(*ppio==NULL){
	                guardarUser(new);//para que no le de tiempo a otro a elegir el mismo nombre 
			ok=0;
	                }
	else{
	     ok=buscaUsuario2(new);               //devuelve 0 si no existe o si es feof
	     i++;  
	     }
	if(i>3){
            printf("Supero la cantidad de reintentos se desconectara\n");
            return;}
        }while(ok!=0);
     
   
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