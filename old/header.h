//Estructuras de Funciones

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODO{
  char usuario [21];
  char barrio [21];
  int tel;
  char mail[41];
  char pass [11];
  struct NODO *sig;

};

struct LIBRO{
  char titulo[41];
  struct LIBRO *sig;
};


void crearUsuario(struct NODO **ppio);         //recibe ppio carga datos en una struct y se lo cuelga a la lista 
void baja_usuario(struct NODO **ppio);
void buscar(struct NODO *);
void agregar_libro(char *usuario);         //el usuario agrega un libro
void borrar_libro(char * usuario);         // pasa el nombre del txt a abrir para borrar libro
void listar_mislibros (char *usuario);     // muestra los libros del usuario
void listar_libros(struct LIBRO *);         //muestra todos los libros de todos los usuarios
void validar_usuario(struct NODO *);       //valida usuario y password
void levantarLista(struct NODO** ppio);
void sobreescribirFile(struct NODO** ppio);//le pasas ppio con la lista nueva modificada a guardar y sobreescribe el viejo
int buscaUsuario(struct NODO aux,struct NODO** ppio);     //busca si existe el usuario para que no haya duplicados  
void crearDAT(void);
void guardaruser(struct NODO**ppio);
int validar_UserPass(void);
int buscarUsuario2(char*usuario);
void ins_orden(struct NODO nuevo,struct NODO**ppio);


