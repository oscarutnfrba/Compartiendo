#include "header1.h"
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

*/
int main (void){
  
  struct nodo* ppio=NULL;
  struct nodo* aux=NULL;
  char opcion[21];
  
  crearDAT();
  
  printf("desea crear usuario? s/n\n " );
  scanf("%s",opcion);
  
  if (strcmp(opcion,"s")==0){
                             crearUsuario(&ppio);
                             printf("usuario creado satisfactoriamente\n");
                             }
  
  printf("desea loguearse? s/n\n " );
  scanf("%s",opcion);
  
  if (strcmp(opcion,"s")==0){
                             loguearse();
                             printf("usuario logueado satisfactoriamente\n");
                             }
  
 
  return 0;
} 
void loguearse(void){
  char nombre[21];
  struct nodo* aux;
  aux=(struct nodo*)malloc(sizeof (struct nodo));
  FILE* fp;
  fp=fopen("usuarios.dat","r");
  fread(aux,sizeof(struct nodo),1,fp);
  printf("ingrese su nombre de usuario\n");
  scanf("%s",nombre);
  //printf("%s\n",aux->usuario);
        
  while((!feof(fp))&&(strcmp(nombre,aux->usuario)!=0)){
	     printf("%s\n",aux->usuario);
                                                        fread(aux,sizeof(struct nodo),1,fp);
                                                      }
 printf("%s\n",aux->usuario);
  return;
}



void crearUsuario(struct nodo**ppio){    //recibe ppio carga el nuevo nodo y se lo aniade a la lista 
   
  int i=0;
  int ok=0;
  char pass[21];
  struct nodo new;   
 
     do{  
	if(i<0)
	printf("el nombre de usuario que eligio ya existe ");
	printf("ingrese nuevo nombre de usuario\n");
	scanf("%s",new.usuario);  
	ok=buscaUsuario2(new);
	i++; 
        }while(ok!=0&&i<3);
     //if(i>3){
       //      printf("intento demasiadas %d veces se desconecta\n");
         //    return;}
   
	printf("perfecto el nombre de usuario que eligio esta disponible\n");
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
     
     //if(i>3){
       //      printf("intento demasiadas %d veces se desconecta\n");
         //    return;}
  //aca el resto de la carga de datos 
     printf("ingrese su mail \n"); 
      scanf("%s",new.mail); 
    printf("ingrese su barrio \n"); 
      scanf("%s",new.barrio); 
  	 printf("ingrese su numero de telefono\n"); 
      scanf("%d",&new.tel);
     ins_orden(new,ppio);
     guardaruser(ppio); 
  return;
  
}
void guardarlibro(struct libro *ppio, char *usuario){
	
  FILE *fp;
  fp=fopen(usuario,"wb");
  while(ppio){
  		fwrite(ppio,sizeof(struct libro),1,fp);
    	ppio=ppio->sig;
  
  }
  fclose(fp);
  return;
}
void guardaruser(struct nodo**ppio){
 
 FILE *fp;
 fp=fopen("usuarios.dat","wb");
  while(*ppio){
              fwrite((*ppio),sizeof(struct nodo),1,fp);
              (*ppio)=(*ppio)->sig;
              }
 fclose(fp);
}

void ins_orden(struct nodo new,struct nodo**ppio){
struct nodo* act;
  struct nodo* ant;
   struct nodo* aux;
  aux=&new;
  act=ant=*ppio;
  if (*ppio==NULL){
                   *ppio=aux;
                    aux->sig=NULL;
  
  }else{
    
    while (act!=NULL&&act->usuario>aux->usuario){
                    
       ant=act;
       act=act->sig;
                       
       }
  	ant->sig=aux;
    aux->sig=act;
  
  }
  
  
return;
}

void levantarLista(struct nodo ** ppio){ //abre como lectura arma la lista y cierra el archivo si no existe lo crea es el primer paso
   
  struct nodo *aux= NULL;
  
  FILE *fp;
  if(!(fp = fopen("usuarios.dat", "rb"))){ //w+b crea lectura escritura binario si no existe lo crea  
                                          fp = fopen("usuarios.dat", "wb");
    																			printf("el archivo usuarios.dat no existia se acaba de crear\n");
                                          } 
  
  
  if(feof(fp)){                    //si el archivo esta vacio devuelve ppio = NULL 
               *ppio=NULL; 
               fclose (fp);
               return;
               }
  
  aux= (struct nodo *)malloc(sizeof(struct nodo));    
  fread(&aux, sizeof(struct nodo),1,fp);
                
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
      fread(&aux, sizeof(struct nodo),1,fp); 
                   }     
  
  fclose (fp);
  return;
  
}

int buscaUsuario(struct nodo new,struct nodo** ppio){//devuelve 0 si no existe devuelve 1 si existe 
                                                      //comprobar antes de enviar que no sea NULL ppio
  int ok=1; 
  struct nodo* aux;
  aux=*ppio;
        
   while(aux){
              if(strcmp(aux->usuario,new.usuario)==0)
              return ok;                                 //ok devuelve 1 
              aux=aux->sig;
              }
  
  
  ok=0;
  return ok;
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
  ok=0;                                                            // devuelve 0 si no existe          
  return ok;
}

void crearDAT(void){
   
  FILE* fp; 
  struct nodo aux; 
  if(!(fp=fopen("usuarios.dat","r"))){       //si no existe no lo puede crear asi que entra y lo crea
  fp=fopen("usuarios.dat","wb");             //lo crea  
  strcpy(aux.usuario,"primer user");         //lo carga 
  fwrite(&aux,sizeof(struct nodo),1,fp);     //lo guarda  
  }
  fclose(fp);                                //cierra el archivo y libera el puntero file si creo o si pudo leer
 
  return;
}