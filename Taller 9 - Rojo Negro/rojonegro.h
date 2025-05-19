/**
 * @file rbt.cpp
 * @brief Implementación de un árbol Rojo-Negro con operaciones de inserción, búsqueda y eliminación,
 *        además de utilidades de consola para posicionamiento y coloración de texto.
 *
 * Este archivo contiene la estructura de datos RBT (Red-Black Tree) junto con todas las funciones
 * necesarias para mantener las propiedades de balanceo del árbol, así como funciones para mostrar
 * el árbol por consola y buscar elementos.
 */

 #include <iostream>
 #include <cstdlib>
 #include <cstdio>
 #include <windows.h>
 #include <cmath>
 
 #define ROJO  'r'  /**< @brief Constante que representa el color rojo del nodo. */
 #define NEGRO 'n'  /**< @brief Constante que representa el color negro del nodo. */
 
 using namespace std;
 
 /**
  * @brief Mueve el cursor de la consola a la posición (x, y).
  *
  * @param x Coordenada horizontal (columna) donde se colocará el cursor.
  * @param y Coordenada vertical (fila) donde se colocará el cursor.
  */
 void posicion(int x, int y)
 {
     HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
     SetConsoleCursorPosition(hConsoleOutput, coord);
 }
 
 /**
  * @brief Cambia el color del texto en la consola.
  *
  * @param c Código de color de la consola (valor entero de Windows).
  */
 void color(int c)
 {
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
 }
 
 /**
  * @struct nodoRBT
  * @brief Nodo de un árbol Rojo-Negro.
  *
  * El nodo contiene:
  * - Un valor entero (@c nro).
  * - Un caracter que indica su color (@c color), 'r' para rojo y 'n' para negro.
  * - Punteros a su padre, hijo izquierdo e hijo derecho.
  */
 struct nodoRBT {
     int nro;           /**< @brief Valor almacenado en el nodo. */
     char color;        /**< @brief Color del nodo: ROJO o NEGRO. */
     nodoRBT *padre;    /**< @brief Puntero al nodo padre. */
     nodoRBT *izq;      /**< @brief Puntero al subárbol izquierdo. */
     nodoRBT *der;      /**< @brief Puntero al subárbol derecho. */
 };
 
 /**
  * @typedef RBT
  * @brief Tipo simplificado para punteros a nodoRBT.
  */
 typedef nodoRBT* RBT;
 
 /**
  * @brief Busca un valor en el árbol.
  *
  * Recorre el árbol de manera iterativa hasta encontrar el valor o llegar a un puntero NULL.
  *
  * @param arbol Puntero a la raíz del árbol.
  * @param dato Valor a buscar.
  * @return Puntero al nodo que contiene el valor, o NULL si no se encuentra.
  */
 RBT buscar(RBT arbol, int dato)
 {
     if (!arbol) {
         cout << "\n\t⚠  El árbol está vacío  ⚠" << endl << endl;
         return NULL;
     }
     RBT actual = arbol;
     while (actual) {
         if (dato == actual->nro) {
             cout << "\n\tEl número " << dato << " existe en el árbol\n";
             return actual;
         }
         actual = (dato < actual->nro) ? actual->izq : actual->der;
     }
     cout << "\n\tEl número " << dato << " NO existe en el árbol\n";
     return NULL;
 }
 
 /**
  * @brief Muestra el árbol en consola de forma recursiva.
  *
  * Imprime primero el subárbol derecho, luego el nodo actual (con su color), y finalmente el izquierdo.
  * Esto produce una visualización "rotada" 90° a la izquierda.
  *
  * @param arbol Puntero al nodo actual.
  * @param nivel Entero que indica la profundidad para sangrar el texto.
  */
 void verArbol(RBT arbol, int nivel)
 {
     if (!arbol) return;
     // Mostrar subárbol derecho con sangría aumentada
     verArbol(arbol->der, nivel + 1);
 
     // Sangría según nivel
     for (int i = 0; i < nivel; ++i) cout << "   ";
 
     // Cambiar color según propiedad del nodo
     if (arbol->color == ROJO) color(12);  // Rojo
     else if (arbol->color == NEGRO) color(8);  // Negro
     cout << arbol->nro << endl;
 
     // Restaurar color por defecto
     color(15);
 
     // Mostrar subárbol izquierdo
     verArbol(arbol->izq, nivel + 1);
 }
 
 /**
  * @brief Obtiene el abuelo de un nodo.
  *
  * El abuelo es el padre del padre del nodo.
  *
  * @param n Puntero al nodo cuyo abuelo se busca.
  * @return Puntero al nodo abuelo, o NULL si no existe.
  */
 RBT abuelo(RBT n)
 {
     return (n && n->padre) ? n->padre->padre : NULL;
 }
 
 /**
  * @brief Obtiene el tío de un nodo.
  *
  * El tío es el hermano del padre del nodo.
  *
  * @param n Puntero al nodo cuyo tío se busca.
  * @return Puntero al nodo tío, o NULL si no existe.
  */
 RBT tio(RBT n)
 {
     RBT a = abuelo(n);
     if (!a) return NULL;
     return (n->padre == a->izq) ? a->der : a->izq;
 }
 
 /**
  * @brief Rotación simple a la derecha alrededor de un nodo.
  *
  * Realiza una rotación para preservar las propiedades del árbol.
  *
  * @param raiz Referencia a la raíz del árbol.
  * @param x Puntero al nodo que será rotado hacia abajo.
  */
 void rotar_dcha(RBT &raiz, RBT &x)
 {
     RBT p = x->padre;
     RBT y = x;
     RBT z = y->izq;
     RBT c = z->der;
 
     // Ajuste del padre
     if (p) {
         if (p->der == y) p->der = z;
         else p->izq = z;
     } else {
         raiz = z;
     }
 
     // Rotación
     y->izq = c;
     z->der = y;
     y->padre = z;
     if (c) c->padre = y;
     z->padre = p;
 }
 
 /**
  * @brief Rotación simple a la izquierda alrededor de un nodo.
  *
  * @param raiz Referencia a la raíz del árbol.
  * @param x Puntero al nodo que será rotado hacia abajo.
  */
 void rotar_izda(RBT &raiz, RBT &x)
 {
     RBT p = x->padre;
     RBT y = x;
     RBT z = y->der;
     RBT c = z->izq;
 
     if (p) {
         if (p->der == y) p->der = z;
         else p->izq = z;
     } else {
         raiz = z;
     }
 
     // Rotación
     y->der = c;
     z->izq = y;
     y->padre = z;
     if (c) c->padre = y;
     z->padre = p;
 }
 
 // Declaración de los casos de inserción para restaurar propiedades RBT
 void insercion_caso1(RBT &n, RBT &raiz);
 void insercion_caso2(RBT &n, RBT &raiz);
 void insercion_caso3(RBT &n, RBT &raiz);
 void insercion_caso4(RBT &n, RBT &raiz);
 void insercion_caso5(RBT &n, RBT &raiz);
 
 /**
  * @brief Caso 5 de la inserción: recolorea y rota según posición.
  *
  * @param n Nodo recién insertado (o nodo de trabajo).
  * @param raiz Raíz del árbol.
  */
 void insercion_caso5(RBT &n, RBT &raiz)
 {
     RBT a = abuelo(n);
     n->padre->color = NEGRO;
     a->color = ROJO;
     if (n == n->padre->izq && n->padre == a->izq) {
         rotar_dcha(raiz, a);
     } else {
         rotar_izda(raiz, a);
     }
 }
 
 /**
  * @brief Caso 4 de la inserción: doble rotación necesaria.
  */
 void insercion_caso4(RBT &n, RBT &raiz)
 {
     RBT a = abuelo(n);
     if (n == n->padre->der && n->padre == a->izq) {
         rotar_izda(raiz, n->padre);
         n = n->izq;
     } else if (n == n->padre->izq && n->padre == a->der) {
         rotar_dcha(raiz, n->padre);
         n = n->der;
     }
     insercion_caso5(n, raiz);
 }
 
 /**
  * @brief Caso 3 de la inserción: recolorear si el tío es rojo.
  */
 void insercion_caso3(RBT &n, RBT &raiz)
 {
     RBT t = tio(n);
     if (t && t->color == ROJO) {
         n->padre->color = NEGRO;
         t->color = NEGRO;
         RBT a = abuelo(n);
         a->color = ROJO;
         insercion_caso1(a, raiz);
     } else {
         insercion_caso4(n, raiz);
     }
 }
 
 /**
  * @brief Caso 2 de la inserción: padre es negro o seguir con caso 3.
  */
 void insercion_caso2(RBT &n, RBT &raiz)
 {
     if (n->padre->color == NEGRO) return;
     insercion_caso3(n, raiz);
 }
 
 /**
  * @brief Caso 1 de la inserción: nuevo nodo como raíz debe ser negro.
  */
 void insercion_caso1(RBT &n, RBT &raiz)
 {
     if (!n->padre) n->color = NEGRO;
     else insercion_caso2(n, raiz);
 }
 
 /**
  * @brief Inserta un nuevo valor en el árbol y reequilibra.
  *
  * - Ubica la posición de inserción.
  * - Crea un nuevo nodo rojo.
  * - Restaura las propiedades Rojo-Negro.
  *
  * @param raiz Referencia al puntero de la raíz del árbol.
  * @param dato Valor a insertar.
  */
 void insertar(RBT &raiz, int dato)
 {
     RBT padre = NULL;
     RBT actual = raiz;
     // Búsqueda de la hoja donde insertar
     while (actual && dato != actual->nro) {
         padre = actual;
         actual = (dato < actual->nro) ? actual->izq : actual->der;
     }
     // Si ya existe, no insertar de nuevo
     if (actual) return;
 
     // Crear nodo nuevo
     actual = (RBT)malloc(sizeof(nodoRBT));
     actual->nro = dato;
     actual->izq = actual->der = NULL;
     actual->padre = padre;
     actual->color = ROJO;
 
     if (!padre) {
         raiz = actual;  // Primer nodo: raíz
     } else if (dato < padre->nro) {
         padre->izq = actual;
     } else {
         padre->der = actual;
     }
 
     // Restaurar propiedades Rojo-Negro
     insercion_caso1(actual, raiz);
     cout << "\n\n\tEl número ha sido insertado\n\n";
 }
 
 /**
  * @brief Elimina un valor del árbol de manera básica (sin reequilibrio de RBT).
  *
  * Nota: Esta función no mantiene las propiedades Rojo-Negro después de eliminar.
  *
  * @param arbol Referencia al puntero de la raíz del árbol.
  * @param x Valor a eliminar.
  */
 void eliminar_rbt(RBT &arbol, int x)
 {
     if (!arbol) return;
     if (x < arbol->nro) {
         eliminar_rbt(arbol->izq, x);
     } else if (x > arbol->nro) {
         eliminar_rbt(arbol->der, x);
     } else {
         // Nodo hoja
         if (!arbol->izq && !arbol->der) {
             arbol = NULL;
             return;
         }
         // Un solo hijo
         if (!arbol->izq) {
             arbol = arbol->der;
             return;
         }
         if (!arbol->der) {
             arbol = arbol->izq;
             return;
         }
         // Dos hijos: reemplazar por predecesor
         RBT aux1 = arbol;
         RBT aux2 = arbol->izq;
         while (aux2->der) {
             aux1 = aux2;
             aux2 = aux2->der;
         }
         arbol->nro = aux2->nro;
         if (aux1 == arbol) arbol->izq = aux2->izq;
         else aux1->der = aux2->izq;
     }
 }
