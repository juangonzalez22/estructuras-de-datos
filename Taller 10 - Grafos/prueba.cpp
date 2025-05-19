#include "stdio.h"
#include "stdlib.h"
#include "string.h"

using namespace std;

/***************************************************************************************************
 Nombre de la estructura: NodoV
 Objetivo: Definir la estructura de un nodo de la lista de vértices.
 Campos:
    dato    - Valor entero que identifica al vértice.
    sig     - Puntero al siguiente NodoV en la lista.
    marcado - Entero que indica si el vértice ha sido visitado (1) o no (0)
              en un recorrido.
****************************************************************************************************/
typedef struct NodoV
{
    int dato;
    struct NodoV *sig;
    int marcado;
} *ListaVertice;

/***************************************************************************************************
 Nombre de la estructura: NodoA
 Objetivo: Definir la estructura de un nodo de la lista de arcos (aristas).
 Campos:
    origen  - Valor entero que identifica al vértice de origen del arco.
    destino - Valor entero que identifica al vértice de destino del arco.
    costo   - Valor entero que representa el peso o costo del arco.
    sig     - Puntero al siguiente NodoA en la lista.
****************************************************************************************************/
typedef struct NodoA
{
    int origen;
    int destino;
    int costo;
    struct NodoA *sig;
} *ListaArco;

/***************************************************************************************************
 Nombre de la estructura: nodoGrafo
 Objetivo: Definir la estructura principal del grafo.
 Campos:
    v       - Puntero a la lista de vértices (ListaVertice).
    a       - Puntero a la lista de arcos (ListaArco).
****************************************************************************************************/
typedef struct nodoGrafo
{
    ListaVertice v;
    ListaArco a;
} Grafo;

// --- Funciones auxiliares para manejo de listas (usadas en BFS/DFS para construir resultado) ---

/***************************************************************************************************
 Nombre de la subrutina: agregarVerticeAListaResultado
 Objetivo: Agrega un vértice al final de una lista de vértices. Usado para construir
           la lista de resultados de BFS y DFS.
 Parámetros:
    lista   - Puntero a la cabeza de la ListaVertice donde se agregará el nodo.
    dato    - El valor entero del vértice a agregar.
 Retorna:
    ListaVertice - La cabeza de la lista actualizada con el nuevo vértice.
****************************************************************************************************/
ListaVertice agregarVerticeAListaResultado(ListaVertice lista, int dato) {
    ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
    nuevo->dato = dato;
    nuevo->marcado = 0; // El marcado aquí es irrelevante para la lista de resultado
    nuevo->sig = NULL;

    if (lista == NULL) {
        return nuevo;
    }
    ListaVertice temp = lista;
    while (temp->sig != NULL) {
        temp = temp->sig;
    }
    temp->sig = nuevo;
    return lista;
}

/***************************************************************************************************
 Nombre de la subrutina: liberarListaVertice
 Objetivo: Libera la memoria asignada a una lista de vértices.
 Parámetros:
    lista   - La cabeza de la ListaVertice a liberar.
 Retorna:
    void
****************************************************************************************************/
void liberarListaVertice(ListaVertice lista) {
    ListaVertice actual = lista;
    ListaVertice siguiente;
    while (actual != NULL) {
        siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
}

// --- Funciones del Grafo ---

/***************************************************************************************************
 Nombre de la subrutina: crearGrafo
 Objetivo: Inicializar un grafo vacío sin vértices ni arcos.
 Parámetros: Ninguno
 Retorna:
    Grafo - Un grafo con listas vacías de vértices y arcos.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo que las estructuras y la función crearGrafo están definidas arriba

    int main() {
        Grafo miGrafo;
        miGrafo = crearGrafo();
        if (miGrafo.v == NULL && miGrafo.a == NULL) {
            printf("Grafo creado vacio exitosamente.\n");
        } else {
            printf("Error al crear el grafo vacio.\n");
        }
        return 0;
    }
****************************************************************************************************/
Grafo crearGrafo()
{
    Grafo g;
    g.v = NULL;
    g.a = NULL;
    return g;
}


/***************************************************************************************************
 Nombre de la subrutina: imprimirArcos
 Objetivo: Imprimir por consola todos los arcos de una lista de arcos, mostrando el vértice origen,
           el vértice destino y el costo asociado a cada arco.
 Parámetros:
    a_lista - Puntero a la cabeza de la lista de arcos (ListaArco) que se desea imprimir.
 Retorna:
    void
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarArco, imprimirArcos definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarArco(g, 1, 2, 10);
        g = insertarArco(g, 2, 1, 5);

        printf("Lista de arcos en el grafo:\n");
        imprimirArcos(g.a);

        // Liberar memoria (no implementado en este ejemplo simple)
        return 0;
    }
****************************************************************************************************/
void imprimirArcos(ListaArco a_lista) {
    printf("Arcos en el grafo (origen -> destino (costo)):\n");
    while (a_lista != NULL) {
        printf("%d -> %d (%d)\n", a_lista->origen, a_lista->destino, a_lista->costo);
        a_lista = a_lista->sig; // Avanzar al siguiente arco en la lista
    }
    printf("\n");
}


/***************************************************************************************************
 Nombre de la subrutina: insertarVertice
 Objetivo: Agregar un nuevo vértice al grafo. El nuevo vértice se inserta al inicio
           de la lista de vértices.
 Parámetros:
    g       - El grafo al cual se le agregará el vértice.
    x       - El valor entero que identificará al nuevo vértice.
 Retorna:
    Grafo   - El grafo actualizado con el nuevo vértice.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, imprimirListaV definidas

    void imprimirDatosVertices(ListaVertice v_lista) { // Función auxiliar para imprimir
        printf("Vertices en el grafo: ");
        while(v_lista != NULL) {
            printf("%d ", v_lista->dato);
            v_lista = v_lista->sig;
        }
        printf("\n");
    }

    int main() {
        Grafo g = crearGrafo();
        printf("Antes de insertar vertices:\n");
        imprimirDatosVertices(g.v); // Imprime la lista de vértices (debería estar vacía)

        g = insertarVertice(g, 10);
        g = insertarVertice(g, 20);
        g = insertarVertice(g, 30);

        printf("Despues de insertar vertices 10, 20, 30:\n");
        imprimirDatosVertices(g.v); // Imprime la lista de vértices
        return 0;
    }
****************************************************************************************************/
Grafo insertarVertice(Grafo g, int x)
{
    ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
    if (nuevo == NULL) {
        perror("Error: No se pudo asignar memoria para nuevo vertice");
        return g; // Retorna el grafo original si falla malloc
    }
    nuevo->sig = g.v;
    nuevo->dato = x;
    nuevo->marcado = 0; // el vertice no esta marcado por defecto
    g.v = nuevo;
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: imprimirListaV
 Objetivo: Imprimir la lista de vértices del grafo con su dato y su marca.
 Parámetros:
    g       - El grafo cuya lista de vértices se imprimirá.
 Retorna:
    void
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, marcarVertice, imprimirListaV definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);

        printf("Lista de vertices inicial (todos desmarcados):\n");
        imprimirListaV(g);

        g = marcarVertice(g, 2); // Marcar el vértice 2

        printf("\nLista de vertices despues de marcar el vertice 2:\n");
        imprimirListaV(g);

        return 0;
    }
****************************************************************************************************/
void imprimirListaV(Grafo g)
{
    ListaVertice k = g.v;
    printf("\n--- Lista de Vertices (Dato, Marcado) ---");
    if (k == NULL) {
        printf("\nNo hay vertices en el grafo.");
    }
    while (k != NULL)
    {
        printf("\nVertice: %d      Marcado: %d", k->dato, k->marcado);
        k = k->sig;
    }
    printf("\n----------------------------------------\n");
}

/***************************************************************************************************
 Nombre de la subrutina: insertarArco
 Objetivo: Insertar un nuevo arco (dirigido) desde un vértice origen 'x' a un
           vértice destino 'y' con un costo 'z' en el grafo. El nuevo arco se
           inserta al inicio de la lista de arcos.
 Parámetros:
    g       - El grafo al cual se le agregará el arco.
    x       - El valor del vértice origen.
    y       - El valor del vértice destino.
    z       - El costo asociado al arco.
 Retorna:
    Grafo   - El grafo actualizado con el nuevo arco.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, imprimirListaA definidas

    void imprimirArcos(ListaArco a_lista) { // Función auxiliar
        printf("Arcos en el grafo (origen -> destino (costo)):\n");
        while(a_lista != NULL) {
            printf("%d -> %d (%d)\n", a_lista->origen, a_lista->destino, a_lista->costo);
            a_lista = a_lista->sig;
        }
        printf("\n");
    }

    int main() {
        Grafo g = crearGrafo();
        // Es recomendable que los vértices existan antes de crear arcos entre ellos.
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);

        printf("Antes de insertar arcos:\n");
        imprimirArcos(g.a);

        g = insertarArco(g, 1, 2, 10); // Arco de 1 a 2 con costo 10
        g = insertarArco(g, 2, 3, 5);  // Arco de 2 a 3 con costo 5

        printf("Despues de insertar arcos:\n");
        imprimirArcos(g.a);
        // La función imprimirListaA del código original también puede usarse.
        // imprimirListaA(g);

        return 0;
    }
****************************************************************************************************/
Grafo insertarArco(Grafo g, int x, int y, int z)
{
    ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
    if (nuevo == NULL) {
        perror("Error: No se pudo asignar memoria para nuevo arco");
        return g; // Retorna el grafo original si falla malloc
    }
    nuevo->sig = g.a;
    nuevo->origen = x;
    nuevo->destino = y;
    nuevo->costo = z;
    g.a = nuevo;
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: imprimirListaA
 Objetivo: Imprimir por consola todos los arcos del grafo con su origen, destino y costo.
 Parámetros:
    g       - El grafo cuya lista de arcos se imprimirá.
 Retorna:
    void
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, imprimirListaA definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarArco(g, 1, 2, 100);
        g = insertarArco(g, 2, 1, 50);

        printf("Lista de arcos en el grafo:\n");
        imprimirListaA(g);

        return 0;
    }
****************************************************************************************************/
void imprimirListaA(Grafo g)
{
    ListaArco k = g.a;
    printf("\n--- Lista de Arcos (Origen, Destino, Costo) ---");
    if (k == NULL) {
        printf("\nNo hay arcos en el grafo.");
    }
    while (k != NULL)
    {
        printf("\nArco: %d -> %d      Costo: %d", k->origen, k->destino, k->costo);
        k = k->sig;
    }
    printf("\n---------------------------------------------\n");
}

/***************************************************************************************************
 Nombre de la subrutina: verticesGrafo
 Objetivo: Obtener la lista de vértices del grafo.
 Parámetros:
    g       - La estructura del grafo.
 Retorna:
    ListaVertice - Un puntero a la cabeza de la lista enlazada de vértices.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, verticesGrafo definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);

        ListaVertice lista_v = verticesGrafo(g);

        printf("Vertices obtenidos con verticesGrafo(): ");
        while(lista_v != NULL) {
            printf("%d ", lista_v->dato);
            lista_v = lista_v->sig;
        }
        printf("\n");

        // Liberar memoria (no implementado en este ejemplo simple)
        return 0;
    }
****************************************************************************************************/
ListaVertice verticesGrafo(Grafo g)
{
    return g.v;
}

/***************************************************************************************************
 Nombre de la subrutina: arcosGrafo
 Objetivo: Obtener la lista de arcos del grafo.
 Parámetros:
    g       - La estructura del grafo.
 Retorna:
    ListaArco - Un puntero a la cabeza de la lista enlazada de arcos.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, arcosGrafo definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarArco(g, 1, 2, 10);

        ListaArco lista_a = arcosGrafo(g);

        printf("Arcos obtenidos con arcosGrafo():\n");
        while(lista_a != NULL) {
            printf("Origen: %d, Destino: %d, Costo: %d\n",
                   lista_a->origen, lista_a->destino, lista_a->costo);
            lista_a = lista_a->sig;
        }
        // Liberar memoria (no implementado en este ejemplo simple)
        return 0;
    }
****************************************************************************************************/
ListaArco arcosGrafo(Grafo g)
{
    return g.a;
}

/***************************************************************************************************
 Nombre de la subrutina: cambiarListaV
 Objetivo: Reemplazar la lista de vértices del grafo con una nueva lista.
 Parámetros:
    g       - La estructura del grafo.
    k       - La nueva lista de vértices que reemplazará la existente.
 Retorna:
    Grafo   - El grafo actualizado con la nueva lista de vértices.
 Precaución: Esta función no libera la memoria de la lista de vértices original.
             El programador debe manejar la memoria adecuadamente para evitar fugas.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, cambiarListaV, imprimirListaV, liberarListaVertice definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        printf("Grafo original:\n");
        imprimirListaV(g);

        // Crear una nueva lista de vértices
        ListaVertice nueva_lista = NULL;
        ListaVertice nodo_a = (ListaVertice)malloc(sizeof(struct NodoV));
        nodo_a->dato = 100; nodo_a->marcado = 0;
        ListaVertice nodo_b = (ListaVertice)malloc(sizeof(struct NodoV));
        nodo_b->dato = 200; nodo_b->marcado = 0;
        nodo_a->sig = nodo_b;
        nodo_b->sig = NULL;
        nueva_lista = nodo_a;

        // Antes de cambiar, es buena práctica liberar la lista antigua si no se va a usar más
        liberarListaVertice(g.v); // Suponiendo que g.v ya no se necesita

        g = cambiarListaV(g, nueva_lista);
        printf("\nGrafo con nueva lista de vertices:\n");
        imprimirListaV(g);

        liberarListaVertice(g.v); // Liberar la nueva lista al final
        return 0;
    }
****************************************************************************************************/
Grafo cambiarListaV(Grafo g, ListaVertice k)
{
    g.v = k;
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: cambiarListaA
 Objetivo: Reemplazar la lista de arcos del grafo con una nueva lista.
 Parámetros:
    g       - La estructura del grafo.
    k       - La nueva lista de arcos que reemplazará la existente.
 Retorna:
    Grafo   - El grafo actualizado con la nueva lista de arcos.
 Precaución: Esta función no libera la memoria de la lista de arcos original.
             El programador debe manejar la memoria adecuadamente para evitar fugas.
 Ejemplo de uso:
    #include "stdio.h"

    int main() {
        Grafo g = crearGrafo();
        g = insertarArco(g, 1, 2, 10);
        printf("Grafo original con arcos:\n");
        imprimirListaA(g);

        // Crear una nueva lista de arcos
        ListaArco nueva_lista_a = NULL;
        ListaArco arco_nuevo = (ListaArco)malloc(sizeof(struct NodoA));
        arco_nuevo->origen = 10; arco_nuevo->destino = 20; arco_nuevo->costo = 100;
        arco_nuevo->sig = NULL;
        nueva_lista_a = arco_nuevo;

        g.a = NULL; 
        g = cambiarListaA(g, nueva_lista_a);
        printf("\nGrafo con nueva lista de arcos:\n");
        imprimirListaA(g);

        return 0;
    }
****************************************************************************************************/
Grafo cambiarListaA(Grafo g, ListaArco k)
{
    g.a = k;
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: vacioGrafo
 Objetivo: Determinar si el grafo está vacío (es decir, si no tiene vértices).
 Parámetros:
    g       - La estructura del grafo a verificar.
 Retorna:
    int     - 1 si el grafo no tiene vértices (g.v es NULL), 0 en caso contrario.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, vacioGrafo definidas

    int main() {
        Grafo g1 = crearGrafo();
        if (vacioGrafo(g1)) {
            printf("El grafo g1 esta vacio.\n");
        } else {
            printf("El grafo g1 no esta vacio.\n");
        }

        g1 = insertarVertice(g1, 1);
        if (vacioGrafo(g1)) {
            printf("El grafo g1 esta vacio despues de insertar.\n");
        } else {
            printf("El grafo g1 no esta vacio despues de insertar.\n");
        }
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
int vacioGrafo(Grafo g)
{
    if (g.v == NULL)
        return 1;
    else
        return 0;
}

/***************************************************************************************************
 Nombre de la subrutina: eliminarVertice
 Objetivo: Eliminar un vértice específico del grafo.
 Parámetros:
    g       - El grafo del cual se eliminará el vértice.
    x       - El valor del vértice a eliminar.
 Retorna:
    Grafo   - El grafo actualizado sin el vértice 'x'. Si el vértice no se encuentra,
              el grafo se retorna sin cambios.
 Nota: Esta función solo elimina el vértice de la lista de vértices. No elimina
       automáticamente los arcos asociados a este vértice. Para una eliminación
       completa, se deberían eliminar también dichos arcos.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, eliminarVertice, imprimirListaV definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2); // Vértice a eliminar
        g = insertarVertice(g, 3);

        printf("Vertices antes de eliminar el 2:\n");
        imprimirListaV(g);

        g = eliminarVertice(g, 2);

        printf("\nVertices despues de eliminar el 2:\n");
        imprimirListaV(g);

        g = eliminarVertice(g, 5); // Intentar eliminar un vértice que no existe
        printf("\nVertices despues de intentar eliminar el 5 (no existente):\n");
        imprimirListaV(g);

        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
Grafo eliminarVertice(Grafo g, int x)
{
    ListaVertice k = g.v, p_anterior = NULL;

    // Caso 1: El grafo está vacío o el vértice a eliminar es el primero
    if (k != NULL && k->dato == x) {
        g.v = k->sig; // La cabeza de la lista de vértices apunta al siguiente
        free(k);      // Libera el nodo eliminado
        return g;
    }

    // Caso 2: El vértice a eliminar está en medio o al final de la lista
    while (k != NULL && k->dato != x) {
        p_anterior = k;
        k = k->sig;
    }

    // Si k es NULL, el vértice no se encontró
    if (k == NULL) return g;

    // Si se encontró (k != NULL), p_anterior apunta al nodo anterior a k
    p_anterior->sig = k->sig; // El anterior ahora apunta al siguiente de k
    free(k);                  // Libera el nodo k
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: eliminarArco
 Objetivo: Eliminar un arco específico del grafo, definido por un vértice origen 'x'
           y un vértice destino 'y'.
 Parámetros:
    g       - El grafo del cual se eliminará el arco.
    x       - El valor del vértice origen del arco a eliminar.
    y       - El valor del vértice destino del arco a eliminar.
 Retorna:
    Grafo   - El grafo actualizado sin el arco (x -> y). Si el arco no se encuentra,
              el grafo se retorna sin cambios.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, eliminarArco, imprimirListaA definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g,1); g = insertarVertice(g,2); g = insertarVertice(g,3);
        g = insertarArco(g, 1, 2, 10); // Arco a eliminar
        g = insertarArco(g, 2, 3, 20);
        g = insertarArco(g, 1, 3, 30);

        printf("Arcos antes de eliminar (1 -> 2):\n");
        imprimirListaA(g);

        g = eliminarArco(g, 1, 2);

        printf("\nArcos despues de eliminar (1 -> 2):\n");
        imprimirListaA(g);

        g = eliminarArco(g, 1, 5); // Intentar eliminar un arco que no existe
        printf("\nArcos despues de intentar eliminar (1 -> 5) (no existente):\n");
        imprimirListaA(g);
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
Grafo eliminarArco(Grafo g, int x, int y)
{
    ListaArco k = g.a, p_anterior = NULL;

    // Caso 1: La lista de arcos está vacía o el arco a eliminar es el primero
    if (k != NULL && k->origen == x && k->destino == y) {
        g.a = k->sig; // La cabeza de la lista de arcos apunta al siguiente
        // printf("\nEl arco a borrar es %d -> %d (era el primero)", k->origen, k->destino); // Debug
        free(k);      // Libera el nodo del arco eliminado
        return g;
    }

    // Caso 2: El arco a eliminar está en medio o al final de la lista
    while (k != NULL && !(k->origen == x && k->destino == y)) {
        p_anterior = k;
        k = k->sig;
    }

    // Si k es NULL, el arco no se encontró
    if (k == NULL) return g;

    // Si se encontró (k != NULL), p_anterior apunta al nodo anterior a k
    // printf("\nEl arco a borrar es %d -> %d", k->origen, k->destino); // Debug
    p_anterior->sig = k->sig; // El anterior ahora apunta al siguiente de k
    free(k);                  // Libera el nodo k
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: costoArco
 Objetivo: Retorna el costo del arco que va desde el vértice origen 'x' hasta el
           vértice destino 'y'.
 Parámetros:
    g       - La estructura del grafo.
    x       - El valor del vértice origen.
    y       - El valor del vértice destino.
 Retorna:
    int     - El costo del arco si existe. Retorna -1 si el arco no se encuentra.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, costoArco definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g,1); g = insertarVertice(g,2);
        g = insertarArco(g, 1, 2, 75);

        int c = costoArco(g, 1, 2);
        if (c != -1) {
            printf("El costo del arco de 1 a 2 es: %d\n", c);
        } else {
            printf("El arco de 1 a 2 no existe.\n");
        }

        c = costoArco(g, 2, 1); // Arco no existente en este ejemplo
        if (c != -1) {
            printf("El costo del arco de 2 a 1 es: %d\n", c);
        } else {
            printf("El arco de 2 a 1 no existe.\n");
        }
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
int costoArco(Grafo g, int x, int y)
{
    ListaArco k = g.a;

    while (k != NULL)
    {
        if ((k->origen == x) && (k->destino == y))
            return k->costo;
        k = k->sig;
    }
    return -1; // no encontró el arco
}

/***************************************************************************************************
 Nombre de la subrutina: ordenGrafo
 Objetivo: Calcular el número total de vértices en el grafo.
 Parámetros:
    g       - La estructura del grafo.
 Retorna:
    int     - El número de vértices en el grafo.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, ordenGrafo definidas

    int main() {
        Grafo g = crearGrafo();
        printf("Orden del grafo vacio: %d\n", ordenGrafo(g));

        g = insertarVertice(g, 10);
        g = insertarVertice(g, 20);
        g = insertarVertice(g, 30);
        printf("Orden del grafo con 3 vertices: %d\n", ordenGrafo(g));
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
int ordenGrafo(Grafo g)
{
    int orden = 0;
    ListaVertice k = g.v;

    while (k != NULL)
    {
        orden++;
        k = k->sig;
    }
    return orden;
}

/***************************************************************************************************
 Nombre de la subrutina: marcarVertice
 Objetivo: Marcar un vértice específico del grafo (establecer su campo 'marcado' a 1).
 Parámetros:
    g       - El grafo que contiene el vértice.
    x       - El valor del vértice que se desea marcar.
 Retorna:
    Grafo   - El grafo actualizado con el vértice 'x' marcado. Si el vértice no se
              encuentra, el grafo se retorna sin cambios.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, marcarVertice, imprimirListaV definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 5);
        g = insertarVertice(g, 10);

        printf("Antes de marcar el vertice 5:\n");
        imprimirListaV(g); // Mostrará el vértice 5 no marcado

        g = marcarVertice(g, 5);

        printf("\nDespues de marcar el vertice 5:\n");
        imprimirListaV(g); // Mostrará el vértice 5 marcado
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
Grafo marcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;

    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 1;
            return g; // Retorna tan pronto como lo encuentra y marca
        }
        k = k->sig;
    }
    return g; // Si no lo encuentra, retorna el grafo original
}

/***************************************************************************************************
 Nombre de la subrutina: desmarcarVertice
 Objetivo: Desmarcar un vértice específico del grafo (establecer su campo 'marcado' a 0).
 Parámetros:
    g       - El grafo que contiene el vértice.
    x       - El valor del vértice que se desea desmarcar.
 Retorna:
    Grafo   - El grafo actualizado con el vértice 'x' desmarcado. Si el vértice no se
              encuentra, el grafo se retorna sin cambios.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, marcarVertice, desmarcarVertice, imprimirListaV definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 7);
        g = marcarVertice(g, 7); // Primero marcamos el vértice

        printf("Antes de desmarcar el vertice 7 (deberia estar marcado):\n");
        imprimirListaV(g);

        g = desmarcarVertice(g, 7);

        printf("\nDespues de desmarcar el vertice 7:\n");
        imprimirListaV(g); // Mostrará el vértice 7 no marcado
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
Grafo desmarcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 0;
            return g; // Retorna tan pronto como lo encuentra y desmarca
        }
        k = k->sig;
    }
    return g; // Si no lo encuentra, retorna el grafo original
}

/***************************************************************************************************
 Nombre de la subrutina: desmarcarGrafo
 Objetivo: Desmarcar todos los vértices del grafo (establecer 'marcado' a 0 para todos).
 Parámetros:
    g       - El grafo cuyos vértices se van a desmarcar.
 Retorna:
    Grafo   - El grafo con todos sus vértices desmarcados.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, marcarVertice, desmarcarGrafo, imprimirListaV definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);

        g = marcarVertice(g, 1); // Marcar algunos vértices
        g = marcarVertice(g, 3);

        printf("Vertices con algunos marcados:\n");
        imprimirListaV(g);

        g = desmarcarGrafo(g);

        printf("\nVertices despues de desmarcar todo el grafo:\n");
        imprimirListaV(g); // Todos deben aparecer como no marcados
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
Grafo desmarcarGrafo(Grafo g)
{
    ListaVertice k = g.v;

    while (k != NULL)
    {
        k->marcado = 0;
        k = k->sig;
    }
    return g;
}

/***************************************************************************************************
 Nombre de la subrutina: marcadoVertice
 Objetivo: Verificar si un vértice específico del grafo está marcado.
 Parámetros:
    g       - La estructura del grafo.
    x       - El valor del vértice a verificar.
 Retorna:
    int     - 1 si el vértice 'x' está marcado, 0 si no está marcado.
              También retorna 0 si el vértice 'x' no se encuentra en el grafo.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, marcarVertice, marcadoVertice definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 10);
        g = insertarVertice(g, 20);

        g = marcarVertice(g, 10); // Marcamos el vértice 10

        if (marcadoVertice(g, 10)) {
            printf("El vertice 10 esta marcado.\n");
        } else {
            printf("El vertice 10 NO esta marcado.\n");
        }

        if (marcadoVertice(g, 20)) {
            printf("El vertice 20 esta marcado.\n");
        } else {
            printf("El vertice 20 NO esta marcado.\n");
        }

        if (marcadoVertice(g, 30)) { // Vértice no existente
            printf("El vertice 30 esta marcado.\n");
        } else {
            printf("El vertice 30 NO esta marcado (o no existe).\n");
        }
        // Liberar memoria
        return 0;
    }
****************************************************************************************************/
int marcadoVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            return k->marcado; // Retorna directamente el estado (0 o 1)
        }
        k = k->sig;
    }
    return 0; // Si no se encuentra el vértice, se considera no marcado
}

/***************************************************************************************************
 Nombre de la subrutina: sucesores
 Objetivo: Obtener una lista de los vértices sucesores (adyacentes directos a los que
           se puede llegar) de un vértice dado 'x'.
 Parámetros:
    g       - La estructura del grafo.
    x       - El valor del vértice del cual se desean obtener los sucesores.
 Retorna:
    ListaVertice - Una nueva lista enlazada (ListaVertice) que contiene los datos de
                   los vértices sucesores de 'x'. Los nodos en esta lista de sucesores
                   tienen su campo 'marcado' inicializado a 0 por defecto.
                   Retorna NULL si no hay sucesores o si el vértice 'x' no tiene arcos
                   de salida.
 Nota: El llamador es responsable de liberar la memoria de la lista de sucesores
       devuelta usando `liberarListaVertice` cuando ya no se necesite.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructuras, crearGrafo, insertarVertice, insertarArco, sucesores, liberarListaVertice definidas

    void imprimirSucesores(int vertice, ListaVertice s_lista) {
        printf("Sucesores de %d: ", vertice);
        if (s_lista == NULL) {
            printf("Ninguno.");
        }
        while(s_lista != NULL) {
            printf("%d ", s_lista->dato);
            s_lista = s_lista->sig;
        }
        printf("\n");
    }

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);
        g = insertarVertice(g, 4);

        g = insertarArco(g, 1, 2, 0);
        g = insertarArco(g, 1, 3, 0);
        g = insertarArco(g, 2, 4, 0);

        ListaVertice suc_de_1 = sucesores(g, 1);
        imprimirSucesores(1, suc_de_1);
        liberarListaVertice(suc_de_1);

        ListaVertice suc_de_2 = sucesores(g, 2);
        imprimirSucesores(2, suc_de_2);
        liberarListaVertice(suc_de_2);

        ListaVertice suc_de_3 = sucesores(g, 3); // No tiene sucesores en este ejemplo
        imprimirSucesores(3, suc_de_3);
        liberarListaVertice(suc_de_3);

        // Liberar memoria del grafo
        return 0;
    }
****************************************************************************************************/
ListaVertice sucesores(Grafo g, int x)
{
    ListaArco k_arco = g.a;
    ListaVertice lista_sucesores = NULL;

    while (k_arco != NULL)
    {
        if (k_arco->origen == x)
        { // Se agrega el destino del arco como sucesor de x
            lista_sucesores = agregarVerticeAListaResultado(lista_sucesores, k_arco->destino);
            // La línea original 'printf("\nsucesor %d  ",nuevo->dato);' se ha eliminado
            // para que la función solo retorne la lista.
        }
        k_arco = k_arco->sig;
    }
    return lista_sucesores;
}

// --- Implementación de una Cola simple para BFS ---
typedef struct NodoCola {
    int dato;
    struct NodoCola *sig;
} *ColaNodo;

typedef struct {
    ColaNodo frente;
    ColaNodo final_cola; // Renombrado para evitar confusión con 'final' de C++
} Cola;

/***************************************************************************************************
 Nombre de la subrutina: crearCola
 Objetivo: Inicializar una cola vacía.
 Parámetros: Ninguno
 Retorna:
    Cola    - Una estructura Cola inicializada con frente y final_cola a NULL.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo estructura Cola y crearCola definidas

    int main() {
        Cola miCola = crearCola();
        if (miCola.frente == NULL && miCola.final_cola == NULL) {
            printf("Cola creada vacia exitosamente.\n");
        } else {
            printf("Error al crear la cola vacia.\n");
        }
        return 0;
    }
****************************************************************************************************/
Cola crearCola() {
    Cola q;
    q.frente = NULL;
    q.final_cola = NULL;
    return q;
}

/***************************************************************************************************
 Nombre de la subrutina: colaVacia
 Objetivo: Verificar si la cola está vacía.
 Parámetros:
    q       - La cola a verificar.
 Retorna:
    int     - 1 si la cola está vacía (frente es NULL), 0 en caso contrario.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo Cola, crearCola, encolar, colaVacia definidas

    int main() {
        Cola miCola = crearCola();
        if (colaVacia(miCola)) {
            printf("La cola esta vacia inicialmente.\n");
        }
        encolar(&miCola, 10);
        if (!colaVacia(miCola)) {
            printf("La cola ya no esta vacia despues de encolar.\n");
        }
        return 0;
    }
****************************************************************************************************/
int colaVacia(Cola q) {
    return (q.frente == NULL);
}

/***************************************************************************************************
 Nombre de la subrutina: encolar
 Objetivo: Agregar un elemento (dato entero) al final de la cola.
 Parámetros:
    q       - Puntero a la Cola donde se agregará el elemento.
    dato    - El valor entero a encolar.
 Retorna:
    void
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo Cola, crearCola, encolar, desencolar, colaVacia definidas

    int main() {
        Cola miCola = crearCola();
        printf("Encolando 10, 20, 30...\n");
        encolar(&miCola, 10);
        encolar(&miCola, 20);
        encolar(&miCola, 30);

        printf("Elementos en la cola (desencolando): ");
        while(!colaVacia(miCola)) {
            printf("%d ", desencolar(&miCola));
        }
        printf("\n");
        return 0;
    }
****************************************************************************************************/
void encolar(Cola *q, int dato) {
    ColaNodo nuevo = (ColaNodo)malloc(sizeof(struct NodoCola));
    if (nuevo == NULL) {
        perror("Error: No se pudo asignar memoria para nodo de cola");
        return;
    }
    nuevo->dato = dato;
    nuevo->sig = NULL;
    if (colaVacia(*q)) {
        q->frente = nuevo;
        q->final_cola = nuevo;
    } else {
        q->final_cola->sig = nuevo;
        q->final_cola = nuevo;
    }
}

/***************************************************************************************************
 Nombre de la subrutina: desencolar
 Objetivo: Extraer y retornar el elemento del frente de la cola.
 Parámetros:
    q       - Puntero a la Cola de donde se extraerá el elemento.
 Retorna:
    int     - El valor entero del elemento extraído del frente de la cola.
              Retorna -1 (o un valor de error predefinido) si la cola está vacía.
              El mensaje de error se imprime en consola si se intenta desencolar de
              una cola vacía.
 Ejemplo de uso:
    (Ver ejemplo de uso de 'encolar')
****************************************************************************************************/
int desencolar(Cola *q) {
    if (colaVacia(*q)) {
        printf("Error: Intento de desencolar de una cola vacia.\n");
        return -1; // Valor de error
    }
    ColaNodo temp = q->frente;
    int dato = temp->dato;
    q->frente = q->frente->sig;
    if (q->frente == NULL) { // Si la cola queda vacía
        q->final_cola = NULL;
    }
    free(temp);
    return dato;
}


// --- Algoritmo BFS ---
/***************************************************************************************************
 Nombre de la subrutina: recorridoBFS
 Objetivo: Realiza el recorrido en amplitud (BFS) de un grafo desde un vértice de inicio.
 Parámetros:
    g               - Es el grafo sobre el cual se realizará el recorrido.
    inicioVerticeDato - Es el valor del vértice desde donde comenzará el recorrido.
 Retorna:
    ListaVertice    - Una nueva lista enlazada (ListaVertice) que contiene los vértices
                      en el orden en que fueron visitados por BFS.
                      Retorna NULL si el grafo está vacío o si el vértice de inicio
                      no se encuentra.
                      El llamador es responsable de liberar esta lista con `liberarListaVertice`.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo todas las definiciones de Grafo, funciones de manipulación,
    // Cola, recorridoBFS, liberarListaVertice, e imprimirSucesores (modificada para ListaVertice)

    void imprimirRecorrido(const char* tipo, int inicio, ListaVertice resultado) {
        printf("Recorrido %s comenzando desde %d: ", tipo, inicio);
        if (resultado == NULL) {
            printf("No se pudo realizar o resultado vacio.");
        }
        ListaVertice temp = resultado;
        while(temp != NULL) {
            printf("%d ", temp->dato);
            temp = temp->sig;
        }
        printf("\n");
    }

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1); g = insertarVertice(g, 2);
        g = insertarVertice(g, 3); g = insertarVertice(g, 4);
        g = insertarVertice(g, 5); g = insertarVertice(g, 6);

        // Grafo de ejemplo:
        // 1 -> 2, 1 -> 3
        // 2 -> 4, 2 -> 5
        // 3 -> 5
        // 4 -> 6
        // 5 -> 6
        g = insertarArco(g, 1, 2, 0); g = insertarArco(g, 1, 3, 0);
        g = insertarArco(g, 2, 4, 0); g = insertarArco(g, 2, 5, 0);
        g = insertarArco(g, 3, 5, 0);
        g = insertarArco(g, 4, 6, 0); g = insertarArco(g, 5, 6, 0);

        printf("Grafo creado para BFS y DFS.\n");
        imprimirListaV(g);
        imprimirListaA(g);

        ListaVertice resultado_bfs = recorridoBFS(g, 1);
        imprimirRecorrido("BFS", 1, resultado_bfs);
        liberarListaVertice(resultado_bfs);

        resultado_bfs = recorridoBFS(g, 4); // Empezar desde otro nodo
        imprimirRecorrido("BFS", 4, resultado_bfs);
        liberarListaVertice(resultado_bfs);

        resultado_bfs = recorridoBFS(g, 7); // Vértice de inicio no existente
        imprimirRecorrido("BFS", 7, resultado_bfs); // Debería ser NULL o mensaje de error
        liberarListaVertice(resultado_bfs);

        // Liberar grafo (funciones no provistas en el original)
        return 0;
    }
****************************************************************************************************/
ListaVertice recorridoBFS(Grafo g, int inicioVerticeDato) {
    if (vacioGrafo(g)) {
        printf("BFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = verticesGrafo(g);
    int encontrado = 0;
    while(vActual != NULL){
        if(vActual->dato == inicioVerticeDato){
            encontrado = 1;
            break;
        }
        vActual = vActual->sig;
    }

    if(!encontrado){
        printf("BFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    g = desmarcarGrafo(g);
    Cola q = crearCola();
    ListaVertice resultado_recorrido = NULL;

    g = marcarVertice(g, inicioVerticeDato);
    encolar(&q, inicioVerticeDato);
    resultado_recorrido = agregarVerticeAListaResultado(resultado_recorrido, inicioVerticeDato);

    while (!colaVacia(q)) {
        int u_dato = desencolar(&q);

        ListaVertice listaSucesores = sucesores(g, u_dato);
        ListaVertice s_actual = listaSucesores;

        while (s_actual != NULL) {
            int v_dato = s_actual->dato;
            if (!marcadoVertice(g, v_dato)) {
                g = marcarVertice(g, v_dato);
                encolar(&q, v_dato);
                resultado_recorrido = agregarVerticeAListaResultado(resultado_recorrido, v_dato);
            }
            s_actual = s_actual->sig;
        }
        liberarListaVertice(listaSucesores);
    }
    return resultado_recorrido;
}


// --- Algoritmo DFS ---
// Función auxiliar recursiva para DFS
void dfsVisit(Grafo g, int u_dato, ListaVertice *resultado_lista) {
    g = marcarVertice(g, u_dato);
    *resultado_lista = agregarVerticeAListaResultado(*resultado_lista, u_dato);

    ListaVertice listaSucesores = sucesores(g, u_dato);
    ListaVertice s_actual = listaSucesores;

    while (s_actual != NULL) {
        int v_dato = s_actual->dato;
        if (!marcadoVertice(g, v_dato)) {
            dfsVisit(g, v_dato, resultado_lista);
        }
        s_actual = s_actual->sig;
    }
    liberarListaVertice(listaSucesores);
}

/***************************************************************************************************
 Nombre de la subrutina: recorridoDFS
 Objetivo: Realiza el recorrido en profundidad (DFS) de un grafo desde un vértice de inicio.
 Parámetros:
    g               - Es el grafo sobre el cual se realizará el recorrido.
    inicioVerticeDato - Es el valor del vértice desde donde comenzará el recorrido.
 Retorna:
    ListaVertice    - Una nueva lista enlazada (ListaVertice) que contiene los vértices
                      en el orden en que fueron visitados por DFS.
                      Retorna NULL si el grafo está vacío o si el vértice de inicio
                      no se encuentra.
                      El llamador es responsable de liberar esta lista con `liberarListaVertice`.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo todas las definiciones de Grafo, funciones de manipulación,
    // recorridoDFS, liberarListaVertice, e imprimirRecorrido (definida en ejemplo de BFS).

    int main() {
        Grafo g = crearGrafo();
        // Usaremos el mismo grafo que para el ejemplo de BFS
        g = insertarVertice(g, 1); g = insertarVertice(g, 2);
        g = insertarVertice(g, 3); g = insertarVertice(g, 4);
        g = insertarVertice(g, 5); g = insertarVertice(g, 6);

        g = insertarArco(g, 1, 2, 0); g = insertarArco(g, 1, 3, 0);
        g = insertarArco(g, 2, 4, 0); g = insertarArco(g, 2, 5, 0); // Modificado para DFS: 2->5
        g = insertarArco(g, 3, 5, 0);
        // Para hacer el DFS más interesante, hagamos que 4 no tenga sucesores directos
        // y que 5 lleve a 6.
        // g = insertarArco(g, 4, 6, 0); // Comentado para variar
        g = insertarArco(g, 5, 6, 0);
        g = insertarArco(g, 6, 1, 0); // Añadir un ciclo para probar DFS
        g = insertarArco(g, 3, 1, 0); // Otro arco


        printf("Grafo creado para DFS.\n");
        // imprimirListaV(g);
        // imprimirListaA(g);

        ListaVertice resultado_dfs = recorridoDFS(g, 1);
        // La función imprimirRecorrido se definió en el ejemplo de BFS
        // void imprimirRecorrido(const char* tipo, int inicio, ListaVertice resultado) { ... }
        imprimirRecorrido("DFS", 1, resultado_dfs);
        liberarListaVertice(resultado_dfs);

        resultado_dfs = recorridoDFS(g, 3); // Empezar desde otro nodo
        imprimirRecorrido("DFS", 3, resultado_dfs);
        liberarListaVertice(resultado_dfs);

        resultado_dfs = recorridoDFS(g, 7); // Vértice de inicio no existente
        imprimirRecorrido("DFS", 7, resultado_dfs); // Debería ser NULL o mensaje de error
        liberarListaVertice(resultado_dfs);

        return 0;
    }
****************************************************************************************************/
ListaVertice recorridoDFS(Grafo g, int inicioVerticeDato) {
    if (vacioGrafo(g)) {
        printf("DFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = verticesGrafo(g);
    int encontrado = 0;
    while(vActual != NULL){
        if(vActual->dato == inicioVerticeDato){
            encontrado = 1;
            break;
        }
        vActual = vActual->sig;
    }

    if(!encontrado){
        printf("DFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    g = desmarcarGrafo(g);
    ListaVertice resultado_recorrido = NULL;

    // La lógica principal de DFS se maneja en la función recursiva dfsVisit
    dfsVisit(g, inicioVerticeDato, &resultado_recorrido);

    return resultado_recorrido;
}


/***************************************************************************************************
 Nombre de la subrutina: dijkstra
 Objetivo: Encuentra el camino más corto entre dos vértices en un grafo utilizando el algoritmo de 
           Dijkstra. El resultado es una lista de arcos que representan el camino más corto desde 
           el vértice origen hasta el vértice destino.
 Parámetros:
    g       - El grafo sobre el cual se ejecutará el algoritmo.
    origen  - El vértice de inicio desde donde se calcularán las distancias.
    destino - El vértice de destino al cual se desea encontrar el camino más corto.
 Retorna:
    ListaArco - Una lista enlazada de arcos que representan el camino más corto desde el vértice 
                origen hasta el vértice destino. Retorna NULL si no hay un camino entre los 
                vértices o si ocurre un error.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo que las estructuras y funciones necesarias están definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);
        g = insertarArco(g, 1, 2, 10);
        g = insertarArco(g, 2, 3, 5);

        ListaArco camino = dijkstra(g, 1, 3);
        if (camino != NULL) {
            printf("Camino más corto encontrado:\n");
            imprimirArcos(camino);
        } else {
            printf("No hay camino entre los vértices especificados.\n");
        }

        return 0;
    }
****************************************************************************************************/
ListaArco dijkstra(Grafo g, int origen, int destino) {
    if (vacioGrafo(g)) {
        printf("Dijkstra Error: El grafo está vacío.\n");
        return NULL;
    }

    // 1. Inicialización
    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL) {
        if (temp_v->dato > max_id) {
            max_id = temp_v->dato;
        }
        temp_v = temp_v->sig;
    }

    if (max_id < 0) {
        printf("Dijkstra Error: El grafo no tiene vértices.\n");
        return NULL;
    }

    int num_vertices_total = max_id + 1;
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));

    if (distancia == NULL || predecesor == NULL) {
        perror("Error al reservar memoria para Dijkstra");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    for (int i = 0; i < num_vertices_total; i++) {
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    // Validar si el vértice origen y destino existen
    temp_v = g.v;
    int origen_existe = 0, destino_existe = 0;
    while (temp_v != NULL) {
        if (temp_v->dato == origen) {
            origen_existe = 1;
        }
        if (temp_v->dato == destino) {
            destino_existe = 1;
        }
        temp_v = temp_v->sig;
    }

    if (!origen_existe || !destino_existe) {
        printf("Dijkstra Error: El vértice origen o destino no existe en el grafo.\n");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen] = 0;
    g = desmarcarGrafo(g); // Desmarcar todos los vértices al inicio

    // 2. Bucle principal
    for (int count = 0; count < num_vertices_total; count++) {
        int u = -1;
        int min_dist = INT_MAX;

        // Encontrar el vértice no marcado con la distancia mínima
        temp_v = g.v;
        while (temp_v != NULL) {
            int id_actual = temp_v->dato;
            if (!temp_v->marcado && distancia[id_actual] < min_dist) {
                min_dist = distancia[id_actual];
                u = id_actual;
            }
            temp_v = temp_v->sig;
        }

        if (u == -1) break; // No hay más vértices alcanzables

        g = marcarVertice(g, u); // Marcar el vértice como visitado

        // Relajar los arcos salientes de u
        ListaArco temp_a = g.a;
        while (temp_a != NULL) {
            if (temp_a->origen == u) {
                int v = temp_a->destino;
                int costo = temp_a->costo;

                if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v]) {
                    distancia[v] = distancia[u] + costo;
                    predecesor[v] = u;
                }
            }
            temp_a = temp_a->sig;
        }
    }

    // 3. Reconstruir el camino desde el origen hasta el destino
    ListaArco camino = NULL;
    int actual = destino;
    while (actual != -1 && actual != origen) {
        int anterior = predecesor[actual];
        if (anterior == -1) {
            printf("No hay camino desde %d hasta %d.\n", origen, destino);
            free(distancia);
            free(predecesor);
            return NULL;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL) {
            perror("Error al asignar memoria para un arco");
            free(distancia);
            free(predecesor);
            return NULL;
        }
        nuevo_arco->origen = anterior;
        nuevo_arco->destino = actual;
        nuevo_arco->costo = costoArco(g, anterior, actual);
        nuevo_arco->sig = camino;
        camino = nuevo_arco;

        actual = anterior;
    }

    // 4. Liberar memoria
    free(distancia);
    free(predecesor);

    return camino;
}

/***************************************************************************************************
 Nombre de la subrutina: prim
 Objetivo: Encuentra el árbol de expansión mínima (MST) de un grafo no dirigido y ponderado
           utilizando el algoritmo de Prim.
 Parámetros:
    g       - El grafo sobre el cual se ejecutará el algoritmo.
    inicio  - El vértice desde donde se comenzará a construir el MST.
 Retorna:
    ListaArco - Una lista enlazada de arcos que representan el árbol de expansión mínima.
                Retorna NULL si el grafo está vacío, si el vértice de inicio no existe,
                o si el grafo no es conexo.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo que las estructuras y funciones necesarias están definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);
        g = insertarVertice(g, 4);
        g = insertarArco(g, 1, 2, 10);
        g = insertarArco(g, 1, 3, 15);
        g = insertarArco(g, 2, 4, 5);
        g = insertarArco(g, 3, 4, 10);

        ListaArco mst = prim(g, 1);
        if (mst != NULL) {
            printf("Árbol de expansión mínima:\n");
            imprimirArcos(mst);
        } else {
            printf("No se pudo construir el árbol de expansión mínima.\n");
        }

        return 0;
    }
****************************************************************************************************/
ListaArco prim(Grafo g, int inicio) {
    if (vacioGrafo(g)) {
        printf("Prim Error: El grafo está vacío.\n");
        return NULL;
    }

    // Validar si el vértice de inicio existe
    ListaVertice temp_v = g.v;
    int inicio_existe = 0;
    while (temp_v != NULL) {
        if (temp_v->dato == inicio) {
            inicio_existe = 1;
            break;
        }
        temp_v = temp_v->sig;
    }

    if (!inicio_existe) {
        printf("Prim Error: El vértice de inicio %d no existe en el grafo.\n", inicio);
        return NULL;
    }

    // Inicialización
    g = desmarcarGrafo(g); // Desmarcar todos los vértices
    ListaArco mst = NULL;  // Lista de arcos del MST
    g = marcarVertice(g, inicio); // Marcar el vértice de inicio

    // Mientras haya vértices no marcados
    while (1) {
        ListaArco temp_a = g.a;
        ListaArco arco_min = NULL;
        int costo_min = INT_MAX;

        // Buscar el arco de menor costo que conecte un vértice marcado con uno no marcado
        while (temp_a != NULL) {
            if (marcadoVertice(g, temp_a->origen) && !marcadoVertice(g, temp_a->destino)) {
                if (temp_a->costo < costo_min) {
                    costo_min = temp_a->costo;
                    arco_min = temp_a;
                }
            } else if (marcadoVertice(g, temp_a->destino) && !marcadoVertice(g, temp_a->origen)) {
                if (temp_a->costo < costo_min) {
                    costo_min = temp_a->costo;
                    arco_min = temp_a;
                }
            }
            temp_a = temp_a->sig;
        }

        // Si no se encontró un arco válido, terminamos
        if (arco_min == NULL) {
            break;
        }

        // Agregar el arco encontrado al MST al final de la lista
        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL) {
            perror("Error al asignar memoria para un arco");
            return NULL;
        }
        nuevo_arco->origen = arco_min->origen;
        nuevo_arco->destino = arco_min->destino;
        nuevo_arco->costo = arco_min->costo;
        nuevo_arco->sig = NULL;

        if (mst == NULL) {
            mst = nuevo_arco; // Si la lista está vacía, el nuevo arco es el primero
        } else {
            ListaArco temp = mst;
            while (temp->sig != NULL) {
                temp = temp->sig; // Avanzar hasta el final de la lista
            }
            temp->sig = nuevo_arco; // Agregar el nuevo arco al final
        }

        // Marcar el vértice que no estaba marcado
        if (!marcadoVertice(g, arco_min->origen)) {
            g = marcarVertice(g, arco_min->origen);
        } else {
            g = marcarVertice(g, arco_min->destino);
        }
    }

    // Verificar si todos los vértices están marcados (grafo conexo)
    temp_v = g.v;
    while (temp_v != NULL) {
        if (!temp_v->marcado) {
            printf("Prim Error: El grafo no es conexo.\n");
           
            return NULL;
        }
        temp_v = temp_v->sig;
    }

    return mst;
}

/***************************************************************************************************
 Nombre de la subrutina: bellmanFord
 Objetivo: Encuentra el camino más corto entre dos vértices en un grafo (permitiendo pesos negativos)
           utilizando el algoritmo de Bellman-Ford. El resultado es una lista de arcos que representan
           el camino más corto desde el vértice origen hasta el vértice destino.
 Parámetros:
    g       - El grafo sobre el cual se ejecutará el algoritmo.
    origen  - El vértice de inicio desde donde se calcularán las distancias.
    destino - El vértice de destino al cual se desea encontrar el camino más corto.
 Retorna:
    ListaArco - Una lista enlazada de arcos que representan el camino más corto desde el vértice 
                origen hasta el vértice destino. Retorna NULL si no hay un camino entre los 
                vértices, si ocurre un error o si se detecta un ciclo negativo alcanzable.
 Ejemplo de uso:
    #include "stdio.h"
    // Asumiendo que las estructuras y funciones necesarias están definidas

    int main() {
        Grafo g = crearGrafo();
        g = insertarVertice(g, 1);
        g = insertarVertice(g, 2);
        g = insertarVertice(g, 3);
        g = insertarArco(g, 1, 2, 4);
        g = insertarArco(g, 2, 3, -2);
        g = insertarArco(g, 1, 3, 5);

        ListaArco camino = bellmanFord(g, 1, 3);
        if (camino != NULL) {
            printf("Camino más corto encontrado (Bellman-Ford):\n");
            imprimirArcos(camino);
        } else {
            printf("No hay camino entre los vértices especificados o hay ciclo negativo.\n");
        }

        return 0;
    }
****************************************************************************************************/
ListaArco bellmanFord(Grafo g, int origen, int destino) {
    if (vacioGrafo(g)) {
        printf("Bellman-Ford Error: El grafo está vacío.\n");
        return NULL;
    }

    // 1. Inicialización
    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL) {
        if (temp_v->dato > max_id) {
            max_id = temp_v->dato;
        }
        temp_v = temp_v->sig;
    }

    if (max_id < 0) {
        printf("Bellman-Ford Error: El grafo no tiene vértices.\n");
        return NULL;
    }

    int num_vertices_total = max_id + 1;
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));

    if (distancia == NULL || predecesor == NULL) {
        perror("Error al reservar memoria para Bellman-Ford");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    for (int i = 0; i < num_vertices_total; i++) {
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    // Validar si el vértice origen y destino existen
    temp_v = g.v;
    int origen_existe = 0, destino_existe = 0;
    while (temp_v != NULL) {
        if (temp_v->dato == origen) {
            origen_existe = 1;
        }
        if (temp_v->dato == destino) {
            destino_existe = 1;
        }
        temp_v = temp_v->sig;
    }

    if (!origen_existe || !destino_existe) {
        printf("Bellman-Ford Error: El vértice origen o destino no existe en el grafo.\n");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen] = 0;

    // 2. Relajación de aristas (n-1) veces
    int n = num_vertices_total;
    for (int i = 1; i < n; i++) {
        ListaArco temp_a = g.a;
        while (temp_a != NULL) {
            int u = temp_a->origen;
            int v = temp_a->destino;
            int costo = temp_a->costo;
            if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v]) {
                distancia[v] = distancia[u] + costo;
                predecesor[v] = u;
            }
            temp_a = temp_a->sig;
        }
    }

    // 3. Detección de ciclos negativos
    ListaArco temp_a = g.a;
    while (temp_a != NULL) {
        int u = temp_a->origen;
        int v = temp_a->destino;
        int costo = temp_a->costo;
        if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v]) {
            printf("Bellman-Ford Error: Se detectó un ciclo negativo alcanzable.\n");
            free(distancia);
            free(predecesor);
            return NULL;
        }
        temp_a = temp_a->sig;
    }

    // 4. Reconstruir el camino desde el origen hasta el destino
    ListaArco camino = NULL;
    int actual = destino;
    while (actual != -1 && actual != origen) {
        int anterior = predecesor[actual];
        if (anterior == -1) {
            printf("No hay camino desde %d hasta %d.\n", origen, destino);
            free(distancia);
            free(predecesor);
            return NULL;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL) {
            perror("Error al asignar memoria para un arco");
            free(distancia);
            free(predecesor);
            return NULL;
        }
        nuevo_arco->origen = anterior;
        nuevo_arco->destino = actual;
        nuevo_arco->costo = costoArco(g, anterior, actual);
        nuevo_arco->sig = camino;
        camino = nuevo_arco;

        actual = anterior;
    }

    // 5. Liberar memoria
    free(distancia);
    free(predecesor);

    return camino;
}

/***************************************************************************************************
 Nombre de la subrutina: kruskal
 Objetivo: Encuentra el árbol de expansión mínima (MST) de un grafo no dirigido y ponderado
           utilizando el algoritmo de Kruskal.
 Parámetros:
    g       - El grafo sobre el cual se ejecutará el algoritmo.
 Retorna:
    ListaArco - Una lista enlazada de arcos que representan el árbol de expansión mínima.
                Retorna NULL si el grafo está vacío o no es conexo.
****************************************************************************************************/
ListaArco kruskal(Grafo g) {
    if (vacioGrafo(g)) {
        printf("Kruskal Error: El grafo está vacío.\n");
        return NULL;
    }

    int n = ordenGrafo(g);
    if (n == 0) return NULL;

    // Mapear dato de vértice a índice
    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL) {
        if (temp_v->dato > max_id) max_id = temp_v->dato;
        temp_v = temp_v->sig;
    }
    int *dato_a_indice = (int*)malloc((max_id+1)*sizeof(int));
    int *indice_a_dato = (int*)malloc(n*sizeof(int));
    for (int i=0; i<=max_id; i++) dato_a_indice[i] = -1;
    temp_v = g.v;
    int idx = 0;
    while (temp_v != NULL) {
        dato_a_indice[temp_v->dato] = idx;
        indice_a_dato[idx] = temp_v->dato;
        idx++;
        temp_v = temp_v->sig;
    }

    // Inicializar conjuntos disjuntos (uno por vértice)
    int *padre = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++) padre[i] = i;

    // Función find (iterativa, como macro)
    #define FIND(padre, x) ({ int _x = (x); while (padre[_x] != _x) _x = padre[_x]; _x; })

    // Copiar arcos a un arreglo y ordenarlos por costo (burbuja)
    int m = 0;
    ListaArco temp_a = g.a;
    while (temp_a != NULL) { m++; temp_a = temp_a->sig; }
    ListaArco *arcos = (ListaArco*)malloc(m*sizeof(ListaArco));
    temp_a = g.a;
    for (int i=0; i<m; i++) {
        arcos[i] = temp_a;
        temp_a = temp_a->sig;
    }
    for (int i=0; i<m-1; i++) {
        for (int j=0; j<m-1-i; j++) {
            if (arcos[j]->costo > arcos[j+1]->costo) {
                ListaArco tmp = arcos[j];
                arcos[j] = arcos[j+1];
                arcos[j+1] = tmp;
            }
        }
    }

    // Recorrer arcos y construir el MST
    ListaArco mst = NULL, mst_last = NULL;
    int arcos_mst = 0;
    for (int i=0; i<m && arcos_mst < n-1; i++) {
        int u = arcos[i]->origen;
        int v = arcos[i]->destino;
        int idx_u = dato_a_indice[u];
        int idx_v = dato_a_indice[v];
        int ru = FIND(padre, idx_u);
        int rv = FIND(padre, idx_v);
        if (ru != rv) {
            // Agregar arco al MST
            ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
            nuevo->origen = u;
            nuevo->destino = v;
            nuevo->costo = arcos[i]->costo;
            nuevo->sig = NULL;
            if (mst == NULL) {
                mst = nuevo;
                mst_last = nuevo;
            } else {
                mst_last->sig = nuevo;
                mst_last = nuevo;
            }
            padre[rv] = ru; // unir conjuntos
            arcos_mst++;
        }
    }

    // Verificar si se conectaron todos los vértices
    int raiz = FIND(padre, 0);
    int conexo = 1;
    for (int i=1; i<n; i++) {
        if (FIND(padre, i) != raiz) {
            conexo = 0;
            break;
        }
    }

    free(padre); free(dato_a_indice); free(indice_a_dato); free(arcos);

    #undef FIND

    if (!conexo) {
        printf("Kruskal Error: El grafo no es conexo.\n");
        while (mst != NULL) {
            ListaArco tmp = mst;
            mst = mst->sig;
            free(tmp);
        }
        return NULL;
    }

    return mst;
}





int main() {
    Grafo g = crearGrafo();

    // Insertar vértices (asegúrate de incluir todos los que aparecen en los arcos)
    g = insertarVertice(g, 1);
    g = insertarVertice(g, 2);
    g = insertarVertice(g, 3);
    g = insertarVertice(g, 4);
    g = insertarVertice(g, 5);
    g = insertarVertice(g, 6);
    g = insertarVertice(g, 7);

    // Insertar arcos (los mismos que diste en tu ejemplo)
    g = insertarArco(g, 4, 3, -2);
    g = insertarArco(g, 3, 2, -2);
    g = insertarArco(g, 4, 6, -1);
    g = insertarArco(g, 2, 5, -1);
    g = insertarArco(g, 6, 7, 3);
    g = insertarArco(g, 1, 4, 5);

    printf("Arcos originales del grafo:\n");
    imprimirArcos(g.a);

    ListaArco mst = kruskal(g);

    if (mst != NULL) {
        printf("Árbol de expansión mínima (Kruskal):\n");
        imprimirArcos(mst);
    } else {
        printf("No se pudo construir el árbol de expansión mínima.\n");
    }

    return 0;
}