#include "header.h"
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
  
  struct NODO* ppio=NULL;
  struct NODO* aux=NULL;
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
                             if(validar_UserPass()==1){
						      printf("usuario logueado satisfactoriamente\n");
						      }else{
							    printf("error de logueo\n");
							    }
				
                             }
  
 
  return 0;
} 

int validar_UserPass(void){                                       //chequea que exista el archivo del usuario y que su contraseña sea la correcta
struct NODO *aux,*ppio;            
levantarLista(&ppio);
int ok=1,err=0,i=0; 
char usuario[21], usuario2[21];
char contrasena[21];

printf("Ingrese nombre de usuario\n");
scanf("%s",usuario);
strcpy(usuario2,usuario); //para tener el usuario sin concatenar que luego voy a comparar
strcat(usuario,".dat");

FILE *fp;
fp=fopen(usuario,"rb"); //abre el archivo en modo lectura
	if(fp==NULL){                                                            //comprueba la existencia del archivo y por ende el usuario
			printf("no existe\n");
			return err; //no existe el archivo retorna 0 para que no elimine nada
		      }else{
			printf("existe archivo\n");
			levantarLista(&ppio);
			aux=ppio;
			    while(aux!=NULL&&(strcmp(aux->usuario,usuario2)!=0)){
					aux=aux->sig;
				}
					
			printf("Ingrese la contraseña \n");
			scanf("%s",contrasena);
				
			while(i<3){
						if(strcmp(contrasena,aux->pass)==0){              //compara la contraseña ingresada por el usuario y la leida del archivo
															printf("Coincide la contraseña\n");
															fclose(fp);                     //coincide y cierra el archivo
							      return ok; //contraseña correcta retorna 1
							      }else{
										printf("No coincide la contraseña por favor reintente\n");
										}
						i++;
						}	
				printf("Supero la cantidad de reintentos\n");
			    fclose(fp);
				return err; //contraseña incorrecta retorna 0
			    }
return err;
  
}

void crearUsuario(struct NODO**ppio){    //recibe ppio carga el nuevo NODO y se lo aniade a la lista 
   
  int i=0;
  int ok=0;
  char pass[21];
  char usuario[21];
  struct NODO *nuevo;   
 nuevo=(struct NODO*)malloc(sizeof(struct NODO));
     do{  
	if(i<0)
	printf("el nombre de usuario que eligio ya existe ");
	printf("ingrese nuevo nombre de usuario\n");
	scanf("%s",nuevo->usuario);  
	ok=buscaUsuario2(usuario);
	i++; 
        }while(ok!=0&&i<3);
        
	printf("perfecto el nombre de usuario que eligio esta disponible\n");
	i=0;
    do{ 
      if(i>0)
			printf("el pass no coincide intentelo de nuevo\npor su seguridad debe ingresar dos veces el mismo\n");
		  printf("ingrese pass \n");
		  scanf("%s",pass); 
		  printf("re ingrese pass \n"); 
		  scanf("%s",nuevo->pass); 
		  i++;
      }while(strcmp(pass,nuevo->pass)!=0);
	 printf("ingrese su mail \n"); 
	  scanf("%s",nuevo->mail); 
    printf("ingrese su barrio \n"); 
      scanf("%s",nuevo->barrio); 
  	 printf("ingrese su numero de telefono\n"); 
      scanf("%d",&nuevo->tel);
      printf("\n\n%s\n",nuevo->usuario);
     ins_orden(nuevo,&ppio);
    // guardaruser(nuevo); 
  return;
  
}

// void guardaruser(struct NODO *nuevo){
//  struct NODO *aux;
//  aux=nuevo;
//  aux=(struct NODO*)malloc(sizeof(struct NODO));
//  aux=*ppio;
//  FILE *fp;
//  fp=fopen("usuarios.dat","wb");
//   while(aux){
//               fwrite(aux,sizeof(struct NODO),1,fp);
//               (aux)=aux->sig;
//               }
//  fclose(fp);
// }

// void ins_orden(struct NODO nuevo,struct NODO*ppio){
//   struct NODO* act;
//   struct NODO* ant;
//    struct NODO* aux;
//   aux=&nuevo;
//   act=ant=ppio;
//   if (ppio==NULL){
//                    ppio=aux;
//                     aux->sig=NULL;
//   
//   }else{
//     
//     while (act!=NULL&&act->usuario>aux->usuario){
//                     
//        ant=act;
//        act=act->sig;
//                        
//        }
//   	ant->sig=aux;
//     aux->sig=act;
//   
//   }
//   
//   
// return;
// }

void levantarLista(struct NODO ** ppio){ //abre como lectura arma la lista y cierra el archivo si no existe lo crea es el primer paso
   
  struct NODO *aux= NULL;
  
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
  
  aux= (struct NODO *)malloc(sizeof(struct NODO));    
  fread(&aux, sizeof(struct NODO),1,fp);
                
  while(!feof(fp)){                 //si no es feof carga la lista 
    
    
		    if(*ppio== NULL){
				     aux->sig=NULL;
				     *ppio = aux;
				    }
		    else{ 
			aux->sig=*ppio;
			*ppio=aux;
			}
			aux= (struct NODO *)malloc(sizeof(struct NODO)); 
      fread(&aux, sizeof(struct NODO),1,fp); 
                   }     
  
  fclose (fp);
  return;
  
}

int buscaUsuario2(char *usuario){                  //sin levantar en memoria con el uso de lectura y comparacion 
 int ok=0, error=1;
  strcat(usuario,".dat");                      
  FILE* fp;
  struct NODO* aux;
  aux= (struct NODO *)malloc(sizeof(struct NODO));   
  
  if(!(fp=fopen(usuario,"rb"))){
                                       printf("no existe el usuario\n");
				       return ok;
                                      }else{
					   printf("el usuario ya existe\n");
					   return error;
					    }
return error;
}

void crearDAT(void){
   
  FILE* fp; 
  struct NODO aux; 
  if(!(fp=fopen("usuarios.dat","rb"))){       //si no existe no lo puede crear asi que entra y lo crea
	      fp=fopen("usuarios.dat","wb");             //lo crea  
  //strcpy(aux.usuario,"primer user");         //lo carga 
  //fwrite(&aux,sizeof(struct NODO),1,fp);     //lo guarda  
  }
  fclose(fp);                                //cierra el archivo y libera el puntero file si creo o si pudo leer
 
  return;
}
