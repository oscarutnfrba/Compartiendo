//Estructuras de Funciones

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



