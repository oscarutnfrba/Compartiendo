#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define INTENTOS 5

typedef struct datos{
  char articulo[32];
  int cantidad;
}DATOS;

typedef struct nodoSec{
  DATOS informacion;  
  struct nodoSec *siguiente;
}NODOSEC;

typedef struct usuarios {
  char user[32];
  char pass[32];
}USUARIOS;

typedef struct nodo {
  USUARIOS usuario;
  struct nodo *siguiente;
  NODOSEC* articulo;
}NODO;

int recuperarLista (NODO**);
int validarUsuario(NODO**);
int buscoUsuario(USUARIOS*, NODO**);
int verificarNoExistente(NODO*, NODO*);
void agregarNodo (NODO**, NODO*);
void guardarLista (NODO**);
void ordenarLista(NODO**);
void crearArchivoUsuario(NODO*);
void agregarNodoSecundario(NODOSEC**, NODOSEC*);
void mostrarListaSecundaria(NODOSEC*);
void recuperarListaSecundaria(char*, NODOSEC**);
int crearUsuario(char*);
void guardarListaSecundaria(char*, NODOSEC*);
void agregoArticulos(NODOSEC*);
void nuevoPass(char*);