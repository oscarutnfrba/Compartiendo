 //Estructuras de Funciones headers.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct nodo{
  char usuario [21];
  char barrio [21];
  int tel;
  char mail[41];
  char pass [11];
  struct nodo *sig;

};

struct libro{
  char titulo[41];
  struct libro *sig;
};

void agregar_libro(char *usuario);                         //el usuario agrega un libro 

void baja_usuario(struct nodo**);
void buscar(struct nodo *);
void borrar_libro(char * usuario);                         // pasa el nombre del txt a abrir para borrar libro
int  buscaUsuario(struct nodo aux,struct nodo** ppio);     //busca si existe el usuario para que no haya duplicados 
int  buscaUsuario2(struct nodo new); 

void crearUsuario(struct nodo**);                          //recibe ppio carga datos en una struct y se lo cuelga a la lista 
void crearDAT(void);

void guardaruser(struct nodo**ppio);
void guardarlibro(struct libro*,char *);

void ins_orden(struct nodo ,struct nodo**);

void listar_mislibros (char *usuario);                     // muestra los libros del usuario
void listar_libros(struct nodo *);                         //muestra todos los libros de todos los usuarios 
void levantarLista(struct nodo** ppio);
void loguearse(void); 

void validar_usuario(struct nodo *);                       //valida usuario y password

