#include "funcionesListas.h"
void agregarNodo (NODO** primero, NODO* datos)
{
  //Agrego siempre al principio.
/*  if(primero == NULL)
    *primero = datos;
  else
  {*/
    datos->siguiente = *primero;
    *primero = datos;
  //}
 return;
}

void guardarLista(NODO ** datos)
{
  NODO *aux;
  FILE *descriptor;
  
  //Abro el archivo de los usuarios
  descriptor = fopen("usuarios.dat", "w+b");
  if (descriptor == NULL)
  {
    perror("fopen: ");
    return;
  }
  //Igualo el puntero auxiliar a la dirección contenida por el puntero datos.
  aux = *datos;
 
  //Escribo en datos byte a byte hasta llegar al NULL
  while(aux != NULL)
  {
    fwrite(&(aux->usuario),sizeof(USUARIOS),1,descriptor);
    *datos = aux;
    aux = aux->siguiente;
    free(*datos);
  }  
  //Cierro el archivo.
  fclose (descriptor);
  return;
}

int recuperarLista(NODO ** primero)
{
   FILE *descriptor;
   USUARIOS aux;
   NODO *cargar = NULL;
   descriptor = fopen("usuarios.dat", "rb");
   
   // Me fijo que no devuelva NULL, sino muestra un mensaje de error.
   if ((descriptor == NULL) && (errno == 2))
   {
     return(1);
   }
   
   //Lee byte a byte y copia en la lista hasta llegar al end of file.
   fread(&aux, sizeof(USUARIOS),1,descriptor);
   
   while(!feof(descriptor))
   {
     cargar = (NODO *)malloc(sizeof(NODO));
     strcpy(cargar->usuario.user, aux.user);
     strcpy(cargar->usuario.pass, aux.pass);
     cargar->siguiente = NULL;
     cargar->articulo = NULL;
     
     agregarNodo(primero, cargar);
     fread(&aux, sizeof(USUARIOS),1,descriptor);
   }
   fclose (descriptor);
   return(0);
}

void mostrarLista(NODO *mostrar)
{
  NODO *aux;
  aux = mostrar;
  //Muestra en pantalla todos los usuarios. 
  while(aux)
  {
    printf("Usuario: %s\t\t Clave: %s\r\n",aux->usuario.user, aux->usuario.pass);
    aux = aux->siguiente;
  }
  return;
}

void ordenarLista(NODO **principio)
{
  NODO *nodoAct, *nodoSig;
  NODO *auxiliar = NULL;
  int compara;
  
  while(*principio)
  {
    nodoAct = *principio;
    nodoSig = nodoAct->siguiente;
    while (nodoSig)
    {
      compara = strcmp(nodoAct->usuario.user, nodoSig->usuario.user);
      if(compara < 0)
      {
	nodoAct = nodoSig;
      }
      nodoSig = nodoSig->siguiente;
    }
    if (*principio == nodoAct)
    {
      *principio = nodoAct->siguiente;
    }
    else
    {
      for(nodoSig = *principio; nodoSig->siguiente != nodoAct; nodoSig = nodoSig->siguiente);
      nodoSig->siguiente = nodoAct->siguiente;
    }
    nodoAct->siguiente = auxiliar;
    auxiliar = nodoAct;
  }
  *principio = auxiliar;
  return;
}