//Estructuras de Funciones

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODO{
  char usuario [21];
  char barrio [41];
  int tel;
  char mail[41];
  char password [11];
  struct NODO *next;

};

struct LIBRO{
  char titulo[41];
  struct LIBRO *next;
};


void alta_usuario();
void baja_usuario();
// void buscar(struct NODO *);
// void agregar_libro(char *usuario);//el usuario agrega un libro
// void borrar_libro(char * usuario);// pasa el nombre del txt a abrir para borrar libro
// void listar_mislibros (char *usuario);// muestra los libros del usuario
// void listar_libros(struct NODO *);//muestra todos los libros de todos los usuarios
int validar_usuario(char *us,char *pass);//valida usuario y password
void ordenar_usuario(struct NODO **);
void ordenar_libros();

void alta_usuario(){
  struct NODO *aux;                                                         //aca esta al pedo por ahora. si no recibiera nada funcionaria igual
                                                                  //aca tambien esta al pedo
  char a[41],b[41];                                                         //estas variables las voy a utilizar para comparar el mail y la contraseña aunque la contraseña tenga un tamaño menor
  
  aux=(struct NODO *)malloc(sizeof(struct NODO));                           //reservo memoria del tamaño de la estructura
		if(aux==NULL){
            		  printf("Error de memoria al cargar usuario\n"); 
            		  return;                                                      //en caso de que no me pueda reservar el espacio
            		  }else{
                    		    aux->next=NULL;
                    		    printf("Nombre de usuario:\n");                     //carga de usuario, barrio, telfono
                    		      scanf("%s",aux->usuario);                         //puse algun getchar() porque me tomaba un enter sin dejarme cargar el dato siguiente
                    		    getchar();
                    		    printf("Barrio:\n");
                    		        fgets(aux->barrio, 41, stdin);                  //use el fgets como para poder cargar un string con espacios y de un tamaño determinado
                    		    printf("telefono:\n");
                    		        scanf("%d",&aux->tel);
                    		    getchar();
                    		    	    
                    		     while(1){                                          //pide el mail y repetir el mail hasta que lo ingrese correctamente
                    		       
                            			      printf("Ingrese E-Mail:\n");
                            			      fgets(a, 41, stdin);                  //use el fgets como para poder cargar un string con espacios y de un tamaño determinado
                            			      
                            			      printf("Repetir E-Mail:\n");
                            			      fgets(b, 41, stdin);
                            			      
                            			      if(strcmp(a,b)==0){                           //compara lo ingresado
                                                				strcpy(aux->mail,a);        //copia en el espacio reservado
                                                				break;                      //una vez que lo ingreso correctamente 2 veces continua
                                                			    }else{
                                                        				printf("Error al ingresar E-Mail\n");
                                                        				printf("primero %s \nsegundo %s \n",a,b);
                                                				    }
                    			        }
                    		    while(1){                                                   //pide la contraseña y repetir la misma hasta que la ingrese correctamente
                            			      printf("Contraseña hasta 10 caracteres:\n");
                            			      scanf("%s",a);
                            			      
                            			      printf("Repetir contraseña:\n");
                            			      scanf("%s",b);
                            			      
                            			      if(strcmp(a,b)==0){
                                                				strcpy(aux->password,a);
                                                				break;                      //una vez que lo ingreso correctamente 2 veces continua
                                                			    }else{
                                                				        printf("Error al ingresar contraseña\n");
                                                				     }
                            			    }
                		  }
		
strcpy(b,aux->usuario);     //Copia el nombre que ingreso el usuario en la variable b para concatenar con un ".txt"
strcat(b,".txt");           //Concatena el nombre ingresado con un ".txt"

FILE *user;
user=fopen(b,"wb");         //abro el archivo en modo escritura, lo crea. Aca deberia validar su existencia o en todo caso cuando recien ingresa el nombre del usuario, hay un error
printf("\n\nUsuario:%s\nBarrio:%s\nTelefono:%d\n\nMail:%s\nContraseña:%s\n\n",aux->usuario,aux->barrio,aux->tel,aux->mail,aux->password); //te muestra todo lo que ingresaste para chequear, debería preguntar                                                                                                                                          si estas de acuerdo o no 
fwrite(aux,sizeof(struct NODO),1,user);     //escribe el archivo del tamaño de la estructura
fclose(user);                               //cierra el archivo
free(aux);                                  //libero el espacio antes tomado por la estructura
return;
}

void baja_usuario(){                                        //aca por ahora es al pedo que me pase el puntero
char usuario[21],password[11];                                                  
  
  printf("Ingrese usuario a eliminar:\n");
      scanf("%s",usuario);
        getchar();	
	strcat(usuario,".txt");                                                     //le concateno el ".txt" para para comparar con la existencia del archivo
	  printf("Ingrese contraseña:\n");
      scanf("%s",password);
	//getchar();
  if(validar_usuario(usuario,password)==1){                                     //esta funcion va adevolver 1 si existe y es correcto el password para ser eliminado o 0 cero en caso contrario
					    remove(usuario);                    //funcion del sistema para borrar el archivo, como ya validé que existe lo puedo borrar
					    printf("El usuario fue eliminado\n");
					    return;
                                    	  }else{
printf("La contraseña ' %s ' es incorrecta vuelva a intentar \n",password); //le indico que lo que puso es incorrecto mostrandoselo, esto se puede obviar, falta                                                                         poner el loop para que vuelva a intentarlo
                                        	                                         	    
                                    	        }
return;
}

int validar_usuario(char *us,char *pass){                                       //chequea que exista el archivo del usuario y que su contraseña sea la correcta
struct NODO *aux2;                                                               //genero puntero del tamaño de struct
int ok=1,err=0;                                                                 // valores a devolver, solo para que sea mas claro en el resto de la funcion
FILE *user2;
user2=fopen(us,"r"); //abre el archivo en modo lectura
	if(user2==NULL){                                                            //comprueba la existencia del archivo y por ende el usuario
			printf("no existe\n");
			return err; //no existe el archivo retorna 0 para que no elimine nada
		      }else{
			printf("existe archivo\n");
			    fread(aux2,sizeof(struct NODO),1,user2);      //lee una porcion del archivo
			    printf("su contraseña es %s\n",aux2->password);  //muestra la contraseña que tiene realmente, es solo para chequeo, se debe quitar luego

			    if(strcmp(pass,aux2->password)==0){              //compara la contraseña ingresada por el usuario y la leida del archivo
							      printf("Coincide la contraseña\n");
							      fclose(user2);                     //coincide y cierra el archivo
							      return ok; //contraseña correcta retorna 1
							      }else{
								    printf("No coincide la contraseña\n");
								    fclose(user2);
								    return err; //contraseña incorrecta retorna 0
								    }
			    }
return err;
  
}