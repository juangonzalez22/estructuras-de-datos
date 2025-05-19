#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct NodoV
  {  int dato;
     struct NodoV *sig;
     int marcado;
        } *ListaVertice;


typedef struct NodoA
  {  int origen;
     int destino;
     int costo;
     struct NodoA *sig;
        } *ListaArco;


typedef struct nodoGrafo{
        ListaVertice v;
        ListaArco a;
        } Grafo;


/*
 Nombre Subrutina: crearGrafo
 Objetivo: Inicializar un grafo vacío sin vértices ni arcos.
 Parámetros: Ninguno
 Retorno: Un grafo con listas vacías de vértices y arcos.
 Ejemplo de uso: Grafo g = crearGrafo();
*/
Grafo crearGrafo()
  {
      Grafo g;
      g.v=NULL;
      g.a=NULL;
      return g;
  }
      


/*
 Nombre Subrutina: insertarVertice
 Objetivo: Agregar un nuevo vértice al grafo.
 Parámetros: Grafo g, int x (valor del vértice)
 Retorno: Grafo actualizado con el nuevo vértice.
 Ejemplo de uso: g = insertarVertice(g, 5);
*/
Grafo insertarVertice (Grafo g, int x)
{
   ListaVertice nuevo=(ListaVertice) malloc(sizeof (struct NodoV));
   nuevo->sig=g.v;
   nuevo->dato=x;
   nuevo->marcado=0;   // el vertice no esta marcado
   g.v=nuevo;
   return g;
}


/*
 Nombre Subrutina: imprimirListaV
 Objetivo: Imprimir la lista de vértices del grafo con su marca.
 Parámetros: Grafo g
 Retorno: Ninguno (void)
 Ejemplo de uso: imprimirListaV(g);
*/
void imprimirListaV(Grafo g)
{
     ListaVertice k=g.v;
     while (k!=NULL)
     {
           printf(" \n%d     %d",k->dato, k->marcado);
           k=k->sig;
           }
 }


/*
 Nombre Subrutina: insertarArco
 Objetivo: Insertar un nuevo arco (x ? y) con un costo z en el grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice origen.
   - int y: vértice destino.
   - int z: costo del arco.
 Retorno: 
   - Grafo: grafo actualizado con el nuevo arco.
 Ejemplo de uso: 
   g = insertarArco(g, 1, 3, 10);
*/
Grafo insertarArco (Grafo g, int x, int y, int z)
{
   ListaArco nuevo=(ListaArco) malloc(sizeof (struct NodoA));
   nuevo->sig=g.a;
   nuevo->origen=x;
   nuevo->destino=y;
   nuevo->costo=z;
   g.a=nuevo;
   return g;
}
        
        
/*
 Nombre Subrutina: imprimirListaA
 Objetivo: Imprimir por consola todos los arcos del grafo con su origen, destino y costo.
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - void
 Ejemplo de uso: 
   imprimirListaA(g);
*/
void imprimirListaA(Grafo g)
{
     ListaArco k=g.a;
     while (k!=NULL)
     {
           printf(" \n%d    %d     %d",k->origen, k->destino, k->costo);
           k=k->sig;
           }
 }


/*
 Nombre Subrutina: verticesGrafo
 Objetivo: Obtener la lista de vértices del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - ListaVertice: lista enlazada de vértices.
 Ejemplo de uso: 
   ListaVertice v = verticesGrafo(g);
*/
ListaVertice verticesGrafo (Grafo g)
 {
     return g.v;
 }
    
/*
 Nombre Subrutina: arcosGrafo
 Objetivo: Obtener la lista de arcos del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - ListaArco: lista enlazada de arcos.
 Ejemplo de uso: 
   ListaArco a = arcosGrafo(g);
*/
ListaArco arcosGrafo (Grafo g)
 {
     return g.a;
 }
    
/*
 Nombre Subrutina: cambiarListaV
 Objetivo: Reemplazar la lista de vértices del grafo con una nueva.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - ListaVertice k: nueva lista de vértices.
 Retorno: 
   - Grafo: grafo actualizado.
 Ejemplo de uso: 
   g = cambiarListaV(g, nuevaLista);
*/
Grafo cambiarListaV (Grafo g, ListaVertice k)
{
   g.v = k;
   return g;
}

/*
 Nombre Subrutina: cambiarListaA
 Objetivo: Reemplazar la lista de arcos del grafo con una nueva.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - ListaArco k: nueva lista de arcos.
 Retorno: 
   - Grafo: grafo actualizado.
 Ejemplo de uso: 
   g = cambiarListaA(g, nuevaLista);
*/
Grafo cambiarListaA (Grafo g, ListaArco k)
{
   g.a = k;
   return g;
}

/*
 Nombre Subrutina: vacioGrafo
 Objetivo: Determinar si el grafo está vacío (sin vértices).
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - int: 1 si está vacío, 0 en caso contrario.
 Ejemplo de uso: 
   if (vacioGrafo(g)) { ... }
*/
int vacioGrafo (Grafo g)
       // Devuelve verdadero si el grafo es vacio
    {
      if (g.v==NULL)
         return 1;
      else
         return 0;
    }

/*
 Nombre Subrutina: eliminarVertice
 Objetivo: Eliminar un vértice del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice a eliminar.
 Retorno: 
   - Grafo: grafo actualizado sin el vértice x.
 Ejemplo de uso: 
   g = eliminarVertice(g, 2);
*/
Grafo eliminarVertice (Grafo g, int x)
{
    ListaVertice k=g.v, p;

    if (g.v!=NULL)
        {
           if (g.v->dato == x)
             {
              g.v = g.v->sig;
              free(k);
              }
           else
             {
               while ((k->sig != NULL) && (k->sig->dato != x))
                  k=k->sig;
               if (k->sig!=NULL)
                  {
                     p=k->sig;
                     k->sig=p->sig;
                     free(p);
                  }
             }
        }
     return g;
 }

/*
 Nombre Subrutina: eliminarArco
 Objetivo: Eliminar un arco específico del grafo (de x a y).
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice origen.
   - int y: vértice destino.
 Retorno: 
   - Grafo: grafo actualizado sin el arco.
 Ejemplo de uso: 
   g = eliminarArco(g, 1, 4);
*/
Grafo eliminarArco (Grafo g, int x, int y)
{
    ListaArco k=g.a, p;

    if (g.a!=NULL)
        {
           if ((g.a->origen == x) && (g.a->destino == y))
             {
              g.a = g.a->sig;
              free(k);
              }
           else
             {
               while ((k->sig != NULL) && !((k->sig->origen == x) && (k->sig->destino == y)))
                  k=k->sig;
               if (k->sig!=NULL)
                  {
                     p=k->sig;
                     printf("\n el arco a borrar es %d   %d",p->origen,p->destino);
                     k->sig=p->sig;
                     free(p);
                  }
             }
        }
     return g;
 }
 
 
 /*
 Nombre Subrutina: costoArco
 Objetivo: Retorna el costo del arco que va desde el vértice x hasta el vértice y.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice origen.
   - int y: vértice destino.
 Retorno: 
   - int: costo del arco si existe, -1 si no se encuentra.
 Ejemplo de uso: 
   int c = costoArco(g, 2, 5);
*/
 int costoArco (Grafo g, int x, int y)
  {
    ListaArco k=g.a;

    while (k != NULL)
      {
       if ((k->origen == x) && (k->destino == y))
          return k->costo;
       k=k->sig;
      }
    return -1;       // no encontr? el arco
  }


/*
 Nombre Subrutina: ordenGrafo
 Objetivo: Calcular el número total de vértices en el grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - int: número de vértices.
 Ejemplo de uso: 
   int n = ordenGrafo(g);
*/
int ordenGrafo(Grafo g)
  {
    int orden=0;
    ListaVertice k=g.v;

    while (k != NULL)
      {
        orden++;
        k=k->sig;
      }
    return orden;
  }


/*
 Nombre Subrutina: marcarVertice
 Objetivo: Marcar un vértice del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice que se desea marcar.
 Retorno: 
   - Grafo: grafo actualizado con el vértice marcado.
 Ejemplo de uso: 
   g = marcarVertice(g, 3);
*/
Grafo marcarVertice (Grafo g, int x)
{
    ListaVertice k=g.v;

    while (k!=NULL)
        {
           if (k->dato == x)
             {
              k->marcado = 1;
              k=NULL;
             }
           else
             k=k->sig;
        }
     return g;
 }


/*
 Nombre Subrutina: desmarcarVertice
 Objetivo: Desmarcar un vértice del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice que se desea desmarcar.
 Retorno: 
   - Grafo: grafo actualizado con el vértice desmarcado.
 Ejemplo de uso: 
   g = desmarcarVertice(g, 3);
*/
Grafo desmarcarVertice (Grafo g, int x)
{
    ListaVertice k=g.v;
    while (k!=NULL)
        {
           if (k->dato == x)
             {
              k->marcado = 0;
              k=NULL;
             }
           else
             k=k->sig;
        }
     return g;
 }

/*
 Nombre Subrutina: desmarcarGrafo
 Objetivo: Desmarcar todos los vértices del grafo.
 Parámetros: 
   - Grafo g: estructura del grafo.
 Retorno: 
   - Grafo: grafo con todos los vértices desmarcados.
 Ejemplo de uso: 
   g = desmarcarGrafo(g);
*/
Grafo desmarcarGrafo (Grafo g)
{
    ListaVertice k=g.v;

    while (k!=NULL)
        {
           k->marcado = 0;
           k=k->sig;
        }
     return g;
 }


/*
 Nombre Subrutina: marcadoVertice
 Objetivo: Verificar si un vértice está marcado.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice a verificar.
 Retorno: 
   - int: 1 si está marcado, 0 si no está marcado o no existe.
 Ejemplo de uso: 
   if (marcadoVertice(g, 4)) { ... }
*/
int marcadoVertice (Grafo g, int x)
{
    ListaVertice k=g.v;
    while (k!=NULL)
        {
           if (k->dato == x)
             {  
              if (k->marcado == 0)
                  return 0;
              else 
                  return 1;
             }
           else
             k=k->sig;
        }
     return 0;
 }    
    
    
/*
 Nombre Subrutina: sucesores
 Objetivo: Obtener la lista de vértices sucesores de un vértice dado.
 Parámetros: 
   - Grafo g: estructura del grafo.
   - int x: vértice del cual se desean los sucesores.
 Retorno: 
   - ListaVertice: lista enlazada de vértices sucesores de x.
 Ejemplo de uso: 
   ListaVertice s = sucesores(g, 2);
*/

ListaVertice sucesores(Grafo g, int x)
{
   ListaArco k=g.a;
   ListaVertice ver=NULL, nuevo;

    while (k != NULL)
      {
       if (k->origen == x)
          {  // se agrega a la lista el destino del arco como sucesor de x
            nuevo=(ListaVertice) malloc(sizeof (struct NodoV));
            nuevo->sig=ver;
            nuevo->dato=k->destino;
            nuevo->marcado=0;   // el vertice no esta marcado
            ver=nuevo;
            printf("\nsucesor %d  ",nuevo->dato);
          }
       k=k->sig;
      }
   return ver;
}