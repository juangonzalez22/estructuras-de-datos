#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * @struct NodoV
 * @brief Define la estructura de un nodo de la lista de vértices.
 *
 * Campos:
 *   @var dato
 *     Valor entero que identifica al vértice.
 *   @var sig
 *     Puntero al siguiente NodoV en la lista.
 *   @var marcado
 *     Entero que indica si el vértice ha sido visitado (1) o no (0) en un recorrido.
 */

typedef struct NodoV
{
    int dato;
    struct NodoV *sig;
    int marcado;
} *ListaVertice;


/**
 * @struct NodoA
 * @brief Define la estructura de un nodo de la lista de arcos (aristas).
 *
 * Campos:
 *   @var origen
 *     Valor entero que identifica al vértice de origen del arco.
 *   @var destino
 *     Valor entero que identifica al vértice de destino del arco.
 *   @var costo
 *     Valor entero que representa el peso o costo del arco.
 *   @var sig
 *     Puntero al siguiente NodoA en la lista.
 */
typedef struct NodoA
{
    int origen;
    int destino;
    int costo;
    struct NodoA *sig;
} *ListaArco;


/**
 * @struct nodoGrafo
 * @brief Define la estructura principal del grafo.
 *
 * Campos:
 *   @var v
 *     Puntero a la lista de vértices (ListaVertice).
 *   @var a
 *     Puntero a la lista de arcos (ListaArco).
 */
typedef struct nodoGrafo
{
    ListaVertice v;
    ListaArco a;
} Grafo;


/**
 * @brief Inicializa un grafo vacío sin vértices ni arcos.
 * @return Grafo Un grafo con listas vacías de vértices y arcos.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * @endcode
 */
Grafo crearGrafo()
{
    Grafo g;
    g.v = NULL;
    g.a = NULL;
    return g;
}


/**
 * @brief Imprime por consola todos los arcos de una lista de arcos, mostrando el vértice origen,
 *        el vértice destino y el costo asociado a cada arco.
 * @param a_lista Puntero a la cabeza de la lista de arcos (ListaArco) que se desea imprimir.
 * @return void
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarArco(g, 1, 2, 10);
 * g = insertarArco(g, 2, 1, 5);
 * imprimirArcos(g.a);
 * @endcode
 */
void imprimirArcos(ListaArco a_lista) {
    printf("Arcos en el grafo (origen -> destino (costo)):\n");
    while (a_lista != NULL) {
        printf("%d -> %d (%d)\n", a_lista->origen, a_lista->destino, a_lista->costo);
        a_lista = a_lista->sig;
    }
    printf("\n");
}


/**
 * @brief Agrega un nuevo vértice al grafo. El nuevo vértice se inserta al inicio
 *        de la lista de vértices.
 * @param g El grafo al cual se le agregará el vértice.
 * @param x El valor entero que identificará al nuevo vértice.
 * @return Grafo El grafo actualizado con el nuevo vértice.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 10);
 * g = insertarVertice(g, 20);
 * g = insertarVertice(g, 30);
 * @endcode
 */
Grafo insertarVertice(Grafo g, int x)
{
    ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
    if (nuevo == NULL) {
        perror("Error: No se pudo asignar memoria para nuevo vertice");
        return g;
    }
    nuevo->sig = g.v;
    nuevo->dato = x;
    nuevo->marcado = 0; 
    g.v = nuevo;
    return g;
}


/**
 * @brief Imprime la lista de vértices del grafo con su dato y su marca.
 * @param g El grafo cuya lista de vértices se imprimirá.
 * @return void
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * imprimirListaV(g);
 * @endcode
 */
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


/**
 * @brief Inserta un nuevo arco (dirigido) desde un vértice origen 'x' a un
 *        vértice destino 'y' con un costo 'z' en el grafo. El nuevo arco se
 *        inserta al inicio de la lista de arcos.
 * @param g El grafo al cual se le agregará el arco.
 * @param x El valor del vértice origen.
 * @param y El valor del vértice destino.
 * @param z El costo asociado al arco.
 * @return Grafo El grafo actualizado con el nuevo arco.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 10);
 * g = insertarArco(g, 2, 3, 5);
 * imprimirArcos(g.a);
 * @endcode
 */
Grafo insertarArco(Grafo g, int x, int y, int z)
{
    ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
    if (nuevo == NULL) {
        perror("Error: No se pudo asignar memoria para nuevo arco");
        return g;
    }
    nuevo->sig = g.a;
    nuevo->origen = x;
    nuevo->destino = y;
    nuevo->costo = z;
    g.a = nuevo;
    return g;
}


/**
 * @brief Imprime por consola todos los arcos del grafo con su origen, destino y costo.
 * @param g El grafo cuya lista de arcos se imprimirá.
 * @return void
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarArco(g, 1, 2, 100);
 * g = insertarArco(g, 2, 1, 50);
 * imprimirListaA(g);
 * @endcode
 */
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


/**
 * @brief Obtiene la lista de vértices del grafo.
 * @param g La estructura del grafo.
 * @return ListaVertice Un puntero a la cabeza de la lista enlazada de vértices.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * ListaVertice lista_v = verticesGrafo(g);
 * @endcode
 */
ListaVertice verticesGrafo(Grafo g)
{
    return g.v;
}

/**
 * @brief Obtiene la lista de arcos del grafo.
 * @param g La estructura del grafo.
 * @return ListaArco Un puntero a la cabeza de la lista enlazada de arcos.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarArco(g, 1, 2, 10);
 * ListaArco lista_a = arcosGrafo(g);
 * @endcode
 */
ListaArco arcosGrafo(Grafo g)
{
    return g.a;
}


/**
 * @brief Reemplaza la lista de vértices del grafo con una nueva lista.
 * @param g La estructura del grafo.
 * @param k La nueva lista de vértices que reemplazará la existente.
 * @return Grafo El grafo actualizado con la nueva lista de vértices.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * printf("Grafo original:\n");
 * imprimirListaV(g);
 * 
 * ListaVertice nueva_lista = NULL;
 * ListaVertice nodo_a = (ListaVertice)malloc(sizeof(struct NodoV));
 * nodo_a->dato = 100; nodo_a->marcado = 0;
 * ListaVertice nodo_b = (ListaVertice)malloc(sizeof(struct NodoV));
 * nodo_b->dato = 200; nodo_b->marcado = 0;
 * nodo_a->sig = nodo_b;
 * nodo_b->sig = NULL;
 * 
 * nueva_lista = nodo_a;
 * g = cambiarListaV(g, nueva_lista);
 * @endcode
 */
Grafo cambiarListaV(Grafo g, ListaVertice k)
{
    g.v = k;
    return g;
}


/**
 * @brief Reemplaza la lista de arcos del grafo con una nueva lista.
 * @param g La estructura del grafo.
 * @param k La nueva lista de arcos que reemplazará la existente.
 * @return Grafo El grafo actualizado con la nueva lista de arcos.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarArco(g, 1, 2, 10);
 * printf("Grafo original con arcos:\n");
 * imprimirListaA(g);
 * 
 * ListaArco nueva_lista_a = NULL;
 * ListaArco arco_nuevo = (ListaArco)malloc(sizeof(struct NodoA));
 * arco_nuevo->origen = 10; arco_nuevo->destino = 20; arco_nuevo->costo = 100;
 * arco_nuevo->sig = NULL;
 * nueva_lista_a = arco_nuevo;
 * 
 * g.a = NULL;
 * g = cambiarListaA(g, nueva_lista_a);
 * @endcode
 */
Grafo cambiarListaA(Grafo g, ListaArco k)
{
    g.a = k;
    return g;
}


/**
 * @brief Verifica si el grafo está vacío (sin vértices).
 * @param g El grafo a verificar.
 * @return int Retorna 1 si el grafo no tiene vértices, 0 en caso contrario.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * if (vacioGrafo(g)) {
 *     printf("El grafo está vacío.\n");
 * } else {
 *     printf("El grafo tiene vértices.\n");
 * }
 * @endcode
 */
int vacioGrafo(Grafo g)
{
    if (g.v == NULL)
        return 1;
    else
        return 0;
}


/**
 * @brief Elimina un vértice específico del grafo.
 * @param g El grafo del cual se eliminará el vértice.
 * @param x El valor del vértice a eliminar.
 * @return Grafo El grafo actualizado sin el vértice 'x'. Si el vértice no se encuentra,
 *         el grafo se retorna sin cambios.
 * @note Esta función solo elimina el vértice de la lista de vértices. No elimina
 *       automáticamente los arcos asociados a este vértice. Para una eliminación
 *       completa, se deberían eliminar también dichos arcos.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2); // Vértice a eliminar
 * g = insertarVertice(g, 3);
 * printf("Vertices antes de eliminar el 2:\n");
 * imprimirListaV(g);
 * g = eliminarVertice(g, 2);
 * printf("\nVertices despues de eliminar el 2:\n");
 * imprimirListaV(g);
 * g = eliminarVertice(g, 5); // Intentar eliminar un vértice que no existe
 * printf("\nVertices despues de intentar eliminar el 5 (no existente):\n");
 * imprimirListaV(g);
 * @endcode
 */
Grafo eliminarVertice(Grafo g, int x)
{
    ListaVertice k = g.v, p_anterior = NULL;

    if (k != NULL && k->dato == x) {
        g.v = k->sig; 
        free(k);  
        return g;
    }

    while (k != NULL && k->dato != x) {
        p_anterior = k;
        k = k->sig;
    }

    if (k == NULL) return g;

    p_anterior->sig = k->sig;
    free(k);                
    return g;
}


/**
 * @brief Elimina un arco específico del grafo, definido por un vértice origen 'x'
 *        y un vértice destino 'y'.
 * @param g El grafo del cual se eliminará el arco.
 * @param x El valor del vértice origen del arco a eliminar.
 * @param y El valor del vértice destino del arco a eliminar.
 * @return Grafo El grafo actualizado sin el arco (x -> y). Si el arco no se encuentra,
 *         el grafo se retorna sin cambios.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 10); // Arco a eliminar
 * g = insertarArco(g, 2, 3, 20);
 * g = insertarArco(g, 1, 3, 30);
 * printf("Arcos antes de eliminar (1 -> 2):\n");
 * imprimirListaA(g);
 * g = eliminarArco(g, 1, 2);
 * printf("\nArcos despues de eliminar (1 -> 2):\n");
 * imprimirListaA(g);
 * g = eliminarArco(g, 1, 5); // Intentar eliminar un arco que no existe
 * printf("\nArcos despues de intentar eliminar (1 -> 5) (no existente):\n");
 * imprimirListaA(g);
 * @endcode
 */
Grafo eliminarArco(Grafo g, int x, int y)
{
    ListaArco k = g.a, p_anterior = NULL;

    if (k != NULL && k->origen == x && k->destino == y) {
        g.a = k->sig; 
        free(k);
        return g;
    }

    while (k != NULL && !(k->origen == x && k->destino == y)) {
        p_anterior = k;
        k = k->sig;
    }

    if (k == NULL) return g;

    p_anterior->sig = k->sig; 
    free(k);                 
    return g;
}


/**
 * @brief Retorna el costo del arco que va desde el vértice origen 'x' hasta el
 *        vértice destino 'y'.
 * @param g La estructura del grafo.
 * @param x El valor del vértice origen.
 * @param y El valor del vértice destino.
 * @return int El costo del arco si existe. Retorna -1 si el arco no se encuentra.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g,1); g = insertarVertice(g,2);
 * g = insertarArco(g, 1, 2, 75);
 * int c = costoArco(g, 1, 2);
 * if (c != -1) {
 *     printf("El costo del arco de 1 a 2 es: %d\n", c);
 * } else {
 *     printf("El arco de 1 a 2 no existe.\n");
 * }
 * c = costoArco(g, 2, 1); // Arco no existente en este ejemplo
 * if (c != -1) {
 *     printf("El costo del arco de 2 a 1 es: %d\n", c);
 * } else {
 *     printf("El arco de 2 a 1 no existe.\n");
 * }
 * @endcode
 */
int costoArco(Grafo g, int x, int y)
{
    ListaArco k = g.a;

    while (k != NULL)
    {
        if ((k->origen == x) && (k->destino == y))
            return k->costo;
        k = k->sig;
    }
    return -1; 
}


/**
 * @brief Calcula el número total de vértices en el grafo.
 * @param g La estructura del grafo.
 * @return int El número de vértices en el grafo.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * printf("Orden del grafo vacio: %d\n", ordenGrafo(g));
 * g = insertarVertice(g, 10);
 * g = insertarVertice(g, 20);
 * g = insertarVertice(g, 30);
 * printf("Orden del grafo con 3 vertices: %d\n", ordenGrafo(g));
 * @endcode
 */
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


/**
 * @brief Marca un vértice específico del grafo (establece su campo 'marcado' a 1).
 * @param g El grafo que contiene el vértice.
 * @param x El valor del vértice que se desea marcar.
 * @return Grafo El grafo actualizado con el vértice 'x' marcado. Si el vértice no se
 *         encuentra, el grafo se retorna sin cambios.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 5);
 * g = insertarVertice(g, 10);
 * printf("Antes de marcar el vertice 5:\n");
 * imprimirListaV(g); // Mostrará el vértice 5 no marcado
 * g = marcarVertice(g, 5);
 * printf("\nDespues de marcar el vertice 5:\n");
 * imprimirListaV(g); // Mostrará el vértice 5 marcado
 * @endcode
 */
Grafo marcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;

    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 1;
            return g; 
        }
        k = k->sig;
    }
    return g;
}


/**
 * @brief Desmarca un vértice específico del grafo (establece su campo 'marcado' a 0).
 * @param g El grafo que contiene el vértice.
 * @param x El valor del vértice que se desea desmarcar.
 * @return Grafo El grafo actualizado con el vértice 'x' desmarcado. Si el vértice no se
 *         encuentra, el grafo se retorna sin cambios.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 7);
 * g = marcarVertice(g, 7); // Primero marcamos el vértice
 * printf("Antes de desmarcar el vertice 7 (deberia estar marcado):\n");
 * imprimirListaV(g);
 * g = desmarcarVertice(g, 7);
 * printf("\nDespues de desmarcar el vertice 7:\n");
 * imprimirListaV(g); // Mostrará el vértice 7 no marcado
 * @endcode
 */
Grafo desmarcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 0;
            return g;
        }
        k = k->sig;
    }
    return g;
}


/**
 * @brief Desmarca todos los vértices del grafo (establece 'marcado' a 0 para todos).
 * @param g El grafo cuyos vértices se van a desmarcar.
 * @return Grafo El grafo con todos sus vértices desmarcados.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = marcarVertice(g, 1);
 * g = marcarVertice(g, 3);
 * printf("Vertices con algunos marcados:\n");
 * imprimirListaV(g);
 * g = desmarcarGrafo(g);
 * printf("\nVertices despues de desmarcar todo el grafo:\n");
 * imprimirListaV(g); 
 * @endcode
 */
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


/**
 * @brief Verifica si un vértice específico del grafo está marcado.
 * @param g La estructura del grafo.
 * @param x El valor del vértice a verificar.
 * @return int 1 si el vértice 'x' está marcado, 0 si no está marcado o no existe en el grafo.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 10);
 * g = insertarVertice(g, 20);
 * g = marcarVertice(g, 10); // Marcamos el vértice 10
 * if (marcadoVertice(g, 10)) {
 *     printf("El vertice 10 esta marcado.\n");
 * } else {
 *     printf("El vertice 10 NO esta marcado.\n");
 * }
 * if (marcadoVertice(g, 20)) {
 *     printf("El vertice 20 esta marcado.\n");
 * } else {
 *     printf("El vertice 20 NO esta marcado.\n");
 * }
 * if (marcadoVertice(g, 30)) { // Vértice no existente
 *     printf("El vertice 30 esta marcado.\n");
 * } else {
 *     printf("El vertice 30 NO esta marcado (o no existe).\n");
 * }
 * @endcode
 */
int marcadoVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            return k->marcado;
        }
        k = k->sig;
    }
    return 0;
}


/**
 * @brief Obtiene una lista de los vértices sucesores (adyacentes directos a los que
 *        se puede llegar) de un vértice dado 'x'.
 * @param g La estructura del grafo.
 * @param x El valor del vértice del cual se desean obtener los sucesores.
 * @return ListaVertice Una nueva lista enlazada que contiene los datos de los vértices sucesores de 'x'.
 *         Los nodos en esta lista de sucesores tienen su campo 'marcado' inicializado a 0 por defecto.
 *         Retorna NULL si no hay sucesores o si el vértice 'x' no tiene arcos de salida.
 * @note El llamador es responsable de liberar la memoria de la lista de sucesores devuelta usando
 *       `liberarListaVertice` cuando ya no se necesite.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarVertice(g, 4);
 * g = insertarArco(g, 1, 2, 0);
 * g = insertarArco(g, 1, 3, 0);
 * g = insertarArco(g, 2, 4, 0);
 * ListaVertice suc_de_1 = sucesores(g, 1);
 * @endcode
 */
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


/**
 * @brief Realiza un recorrido en anchura (BFS) sobre el grafo desde un vértice de inicio,
 *        sin usar una cola ni funciones auxiliares externas. Retorna una lista de vértices
 *        en el orden en que fueron visitados.
 * @param g El grafo sobre el cual se realizará el recorrido.
 * @param inicioVerticeDato El valor del vértice desde donde comenzará el recorrido.
 * @return ListaVertice Una lista enlazada con los vértices en el orden visitado.
 *         Retorna NULL si el grafo está vacío o si el vértice de inicio no existe.
 * @note El llamador es responsable de liberar la memoria de la lista devuelta si es necesario.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 0);
 * g = insertarArco(g, 1, 3, 0);
 * ListaVertice recorrido = recorridoBFS(g, 1);
 * @endcode
 */
ListaVertice recorridoBFS(Grafo g, int inicioVerticeDato) {
    if (vacioGrafo(g)) {
        printf("BFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0;
    int max_id = -1;
    while (vActual != NULL) {
        if (vActual->dato == inicioVerticeDato) encontrado = 1;
        if (vActual->dato > max_id) max_id = vActual->dato;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado) {
        printf("BFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    int *visitado = (int*)calloc(max_id + 1, sizeof(int));
    int *pendientes = (int*)malloc(n * sizeof(int));
    int frente = 0, fin = 0;

    ListaVertice resultado = NULL;

    pendientes[fin++] = inicioVerticeDato;
    visitado[inicioVerticeDato] = 1;

    while (frente < fin) {
        int actual = pendientes[frente++];
        resultado = agregarVerticeAListaResultado(resultado, actual);

        ListaArco arco = g.a;
        while (arco != NULL) {
            if (arco->origen == actual && !visitado[arco->destino]) {
                pendientes[fin++] = arco->destino;
                visitado[arco->destino] = 1;
            }
            arco = arco->sig;
        }
    }

    free(visitado);
    free(pendientes);
    return resultado;
}


/**
 * @brief Realiza un recorrido en profundidad (DFS) sobre el grafo desde un vértice de inicio,
 *        sin usar recursión ni funciones auxiliares externas. Retorna una lista de vértices
 *        en el orden en que fueron visitados.
 * @param g El grafo sobre el cual se realizará el recorrido.
 * @param inicioVerticeDato El valor del vértice desde donde comenzará el recorrido.
 * @return ListaVertice Una lista enlazada con los vértices en el orden visitado.
 *         Retorna NULL si el grafo está vacío o si el vértice de inicio no existe.
 * @note El llamador es responsable de liberar la memoria de la lista devuelta si es necesario.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 0);
 * g = insertarArco(g, 1, 3, 0);
 * ListaVertice recorrido = recorridoDFS(g, 1);
 * @endcode
 */
ListaVertice recorridoDFS(Grafo g, int inicioVerticeDato) {
    if (vacioGrafo(g)) {
        printf("DFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0, max_id = -1;
    while (vActual != NULL) {
        if (vActual->dato == inicioVerticeDato) encontrado = 1;
        if (vActual->dato > max_id) max_id = vActual->dato;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado) {
        printf("DFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    int *visitado = (int*)calloc(max_id + 1, sizeof(int));
    int *pila = (int*)malloc(n * sizeof(int));
    int tope = 0;

    ListaVertice resultado = NULL;

    pila[tope++] = inicioVerticeDato;

    while (tope > 0) {
        int actual = pila[--tope];
        if (!visitado[actual]) {
            visitado[actual] = 1;
            resultado = agregarVerticeAListaResultado(resultado, actual);

            int num_sucesores = 0;
            ListaArco arco = g.a;
            while (arco != NULL) {
                if (arco->origen == actual && !visitado[arco->destino]) {
                    num_sucesores++;
                }
                arco = arco->sig;
            }
            int *sucesores = (int*)malloc(num_sucesores * sizeof(int));
            int idx = 0;
            arco = g.a;
            while (arco != NULL) {
                if (arco->origen == actual && !visitado[arco->destino]) {
                    sucesores[idx++] = arco->destino;
                }
                arco = arco->sig;
            }
            for (int i = num_sucesores - 1; i >= 0; i--) {
                pila[tope++] = sucesores[i];
            }
            free(sucesores);
        }
    }

    free(visitado);
    free(pila);
    return resultado;
}


/**
 * @brief Encuentra el camino más corto entre dos vértices en un grafo utilizando el algoritmo de 
 *        Dijkstra. El resultado es una lista de arcos que representan el camino más corto desde 
 *        el vértice origen hasta el vértice destino.
 * @param g El grafo sobre el cual se ejecutará el algoritmo.
 * @param origen El vértice de inicio desde donde se calcularán las distancias.
 * @param destino El vértice de destino al cual se desea encontrar el camino más corto.
 * @return ListaArco Una lista enlazada de arcos que representan el camino más corto desde el vértice 
 *         origen hasta el vértice destino. Retorna NULL si no hay un camino entre los 
 *         vértices o si ocurre un error.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 10);
 * g = insertarArco(g, 2, 3, 5);
 * ListaArco camino = dijkstra(g, 1, 3);
 * if (camino != NULL) {
 *     printf("Camino más corto encontrado:\n");
 *     imprimirArcos(camino);
 * } else {
 *     printf("No hay camino entre los vértices especificados.\n");
 * }
 * @endcode
 */
ListaArco dijkstra(Grafo g, int origen, int destino) {
    if (vacioGrafo(g)) {
        printf("Dijkstra Error: El grafo está vacío.\n");
        return NULL;
    }

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
    g = desmarcarGrafo(g); 

    for (int count = 0; count < num_vertices_total; count++) {
        int u = -1;
        int min_dist = INT_MAX;

        temp_v = g.v;
        while (temp_v != NULL) {
            int id_actual = temp_v->dato;
            if (!temp_v->marcado && distancia[id_actual] < min_dist) {
                min_dist = distancia[id_actual];
                u = id_actual;
            }
            temp_v = temp_v->sig;
        }

        if (u == -1) break; 

        g = marcarVertice(g, u); 

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

    free(distancia);
    free(predecesor);

    return camino;
}


/**
 * @brief Encuentra el árbol de expansión mínima (MST) de un grafo no dirigido y ponderado
 *        utilizando el algoritmo de Prim.
 * @param g El grafo sobre el cual se ejecutará el algoritmo.
 * @param inicio El vértice desde donde se comenzará a construir el MST.
 * @return ListaArco Una lista enlazada de arcos que representan el árbol de expansión mínima.
 *         Retorna NULL si el grafo está vacío, si el vértice de inicio no existe,
 *         o si el grafo no es conexo.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarVertice(g, 4);
 * g = insertarArco(g, 1, 2, 10);
 * g = insertarArco(g, 1, 3, 15);
 * g = insertarArco(g, 2, 4, 5);
 * g = insertarArco(g, 3, 4, 10);
 * ListaArco mst = prim(g, 1);
 * if (mst != NULL) {
 *     printf("Árbol de expansión mínima:\n");
 *     imprimirArcos(mst);
 * } else {
 *     printf("No se pudo construir el árbol de expansión mínima.\n");
 * }
 * @endcode
 */
ListaArco prim(Grafo g, int inicio) {
    if (vacioGrafo(g)) {
        printf("Prim Error: El grafo está vacío.\n");
        return NULL;
    }


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

    g = desmarcarGrafo(g);
    ListaArco mst = NULL;  
    g = marcarVertice(g, inicio); 
    while (1) {
        ListaArco temp_a = g.a;
        ListaArco arco_min = NULL;
        int costo_min = INT_MAX;


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

        if (arco_min == NULL) {
            break;
        }

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
            mst = nuevo_arco; 
        } else {
            ListaArco temp = mst;
            while (temp->sig != NULL) {
                temp = temp->sig; 
            }
            temp->sig = nuevo_arco;
        }

        if (!marcadoVertice(g, arco_min->origen)) {
            g = marcarVertice(g, arco_min->origen);
        } else {
            g = marcarVertice(g, arco_min->destino);
        }
    }

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


/**
 * @brief Encuentra el camino más corto entre dos vértices en un grafo (permitiendo pesos negativos)
 *        utilizando el algoritmo de Bellman-Ford. El resultado es una lista de arcos que representan
 *        el camino más corto desde el vértice origen hasta el vértice destino.
 * @param g El grafo sobre el cual se ejecutará el algoritmo.
 * @param origen El vértice de inicio desde donde se calcularán las distancias.
 * @param destino El vértice de destino al cual se desea encontrar el camino más corto.
 * @return ListaArco Una lista enlazada de arcos que representan el camino más corto desde el vértice 
 *         origen hasta el vértice destino. Retorna NULL si no hay un camino entre los 
 *         vértices, si ocurre un error o si se detecta un ciclo negativo alcanzable.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarArco(g, 1, 2, 4);
 * g = insertarArco(g, 2, 3, -2);
 * g = insertarArco(g, 1, 3, 5);
 * ListaArco camino = bellmanFord(g, 1, 3);
 * if (camino != NULL) {
 *     printf("Camino más corto encontrado (Bellman-Ford):\n");
 *     imprimirArcos(camino);
 * } else {
 *     printf("No hay camino entre los vértices especificados o hay ciclo negativo.\n");
 * }
 * @endcode
 */
ListaArco bellmanFord(Grafo g, int origen, int destino) {
    if (vacioGrafo(g)) {
        printf("Bellman-Ford Error: El grafo está vacío.\n");
        return NULL;
    }

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

    free(distancia);
    free(predecesor);

    return camino;
}

/**
 * @brief Encuentra el árbol de expansión mínima (MST) de un grafo no dirigido y ponderado
 *        utilizando el algoritmo de Kruskal.
 * @param g El grafo sobre el cual se ejecutará el algoritmo.
 * @return ListaArco Una lista enlazada de arcos que representan el árbol de expansión mínima.
 *         Retorna NULL si el grafo está vacío, no es conexo o si ocurre un error.
 * @note El grafo debe ser no dirigido y ponderado para que el resultado sea válido.
 * @par Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, 1);
 * g = insertarVertice(g, 2);
 * g = insertarVertice(g, 3);
 * g = insertarVertice(g, 4);
 * g = insertarArco(g, 1, 2, 10);
 * g = insertarArco(g, 1, 3, 15);
 * g = insertarArco(g, 2, 4, 5);
 * g = insertarArco(g, 3, 4, 10);
 * ListaArco mst = kruskal(g);
 * if (mst != NULL) {
 *     printf("Árbol de expansión mínima (Kruskal):\n");
 *     imprimirArcos(mst);
 * } else {
 *     printf("No se pudo construir el árbol de expansión mínima.\n");
 * }
 * @endcode
 */
ListaArco kruskal(Grafo g) {
    if (vacioGrafo(g)) {
        printf("Kruskal Error: El grafo está vacío.\n");
        return NULL;
    }

    int n = ordenGrafo(g);
    if (n == 0) return NULL;

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

    int *padre = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++) padre[i] = i;

    #define FIND(padre, x) ({ int _x = (x); while (padre[_x] != _x) _x = padre[_x]; _x; })

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
            padre[rv] = ru; 
            arcos_mst++;
        }
    }

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