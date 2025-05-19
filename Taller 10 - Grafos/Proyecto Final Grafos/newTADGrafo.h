#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct NodoV
{
    int dato;
    struct NodoV *sig;
    int marcado;
} *ListaVertice;

typedef struct NodoA
{
    int origen;
    int destino;
    int costo;
    struct NodoA *sig;
} *ListaArco;

typedef struct nodoGrafo
{
    ListaVertice v;
    ListaArco a;
} Grafo;

Grafo crearGrafo()
{
    Grafo g;
    g.v = NULL;
    g.a = NULL;
    return g;
}

// Funci�n para adicionar un vertice a la lista de v�rtices
Grafo insertarVertice(Grafo g, int x)
{
    ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
    nuevo->sig = g.v;
    nuevo->dato = x;
    nuevo->marcado = 0; // el vertice no esta marcado
    g.v = nuevo;
    return g;
}

void imprimirListaV(Grafo g)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        printf(" \n%d     %d", k->dato, k->marcado);
        k = k->sig;
    }
}

// Funci�n para adicionar un arco a la lista de arcos
Grafo insertarArco(Grafo g, int x, int y, int z)
{
    ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
    nuevo->sig = g.a;
    nuevo->origen = x;
    nuevo->destino = y;
    nuevo->costo = z;
    g.a = nuevo;
    return g;
}

// imprime la lista de arcos
void imprimirListaA(Grafo g)
{
    ListaArco k = g.a;
    while (k != NULL)
    {
        printf(" \n%d    %d     %d", k->origen, k->destino, k->costo);
        k = k->sig;
    }
}

ListaVertice verticesGrafo(Grafo g)
{
    return g.v;
}

ListaArco arcosGrafo(Grafo g)
{
    return g.a;
}

Grafo cambiarListaV(Grafo g, ListaVertice k)
{
    g.v = k;
    return g;
}

Grafo cambiarListaA(Grafo g, ListaArco k)
{
    g.a = k;
    return g;
}

int vacioGrafo(Grafo g)
// Devuelve verdadero si el grafo es vacio
{
    if (g.v == NULL)
        return 1;
    else
        return 0;
}

// elimina un vertice del grafo
Grafo eliminarVertice(Grafo g, int x)
{
    ListaVertice k = g.v, p;

    if (g.v != NULL)
    {
        if (g.v->dato == x)
        {
            g.v = g.v->sig;
            free(k);
        }
        else
        {
            while ((k->sig != NULL) && (k->sig->dato != x))
                k = k->sig;
            if (k->sig != NULL)
            {
                p = k->sig;
                k->sig = p->sig;
                free(p);
            }
        }
    }
    return g;
}

// Elimina un arco que parta del origen x al destino y
Grafo eliminarArco(Grafo g, int x, int y)
{
    ListaArco k = g.a, p;

    if (g.a != NULL)
    {
        if ((g.a->origen == x) && (g.a->destino == y))
        {
            g.a = g.a->sig;
            free(k);
        }
        else
        {
            while ((k->sig != NULL) && !((k->sig->origen == x) && (k->sig->destino == y)))
                k = k->sig;
            if (k->sig != NULL)
            {
                p = k->sig;
                printf("\n el arco a borrar es %d   %d", p->origen, p->destino);
                k->sig = p->sig;
                free(p);
            }
        }
    }
    return g;
}

// retorna el costo del arco desde x hasta y
int costoArco(Grafo g, int x, int y)
{
    ListaArco k = g.a;

    while (k != NULL)
    {
        if ((k->origen == x) && (k->destino == y))
            return k->costo;
        k = k->sig;
    }
    return -1; // no encontr� el arco
}

// retorna el n�mero de v�rtices asociados al grafo
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

// marca un vertice de grafo
Grafo marcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;

    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 1;
            k = NULL;
        }
        else
            k = k->sig;
    }
    return g;
}

// desmarca un vertice de grafo
Grafo desmarcarVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            k->marcado = 0;
            k = NULL;
        }
        else
            k = k->sig;
    }
    return g;
}

// desmarca todos los vertices del grafo
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

// Indica si un v�rtice est� marcado
int marcadoVertice(Grafo g, int x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (k->dato == x)
        {
            if (k->marcado == 0)
                return 0;
            else
                return 1;
        }
        else
            k = k->sig;
    }
    return 0;
}

ListaVertice sucesores(Grafo g, int x)
{
    ListaArco k = g.a;
    ListaVertice ver = NULL, nuevo;

    while (k != NULL)
    {
        if (k->origen == x)
        { // se agrega a la lista el destino del arco como sucesor de x
            nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
            nuevo->sig = ver;
            nuevo->dato = k->destino;
            nuevo->marcado = 0; // el vertice no esta marcado
            ver = nuevo;
            printf("\nsucesor %d  ", nuevo->dato);
        }
        k = k->sig;
    }
    return ver;
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
ListaVertice recorridoBFS(Grafo g, int inicioVerticeDato)
{
    if (vacioGrafo(g))
    {
        printf("BFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0;
    int max_id = -1;
    while (vActual != NULL)
    {
        if (vActual->dato == inicioVerticeDato)
            encontrado = 1;
        if (vActual->dato > max_id)
            max_id = vActual->dato;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado)
    {
        printf("BFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    int *visitado = (int *)calloc(max_id + 1, sizeof(int));
    int *pendientes = (int *)malloc(n * sizeof(int));
    int frente = 0, fin = 0;

    ListaVertice resultado = NULL;

    pendientes[fin++] = inicioVerticeDato;
    visitado[inicioVerticeDato] = 1;

    while (frente < fin)
    {
        int actual = pendientes[frente++];
        while (frente < fin)
        {
            int actual = pendientes[frente++];
            // Agregar manualmente el vértice a la lista resultado
            ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
            nuevo->dato = actual;
            nuevo->marcado = 0;
            nuevo->sig = resultado;
            resultado = nuevo;

            ListaArco arco = g.a;
            while (arco != NULL)
            {
                if (arco->origen == actual && !visitado[arco->destino])
                {
                    pendientes[fin++] = arco->destino;
                    visitado[arco->destino] = 1;
                }
                arco = arco->sig;
            }
        }

        ListaArco arco = g.a;
        while (arco != NULL)
        {
            if (arco->origen == actual && !visitado[arco->destino])
            {
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
ListaVertice recorridoDFS(Grafo g, int inicioVerticeDato)
{
    if (vacioGrafo(g))
    {
        printf("DFS Error: El grafo esta vacio.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0, max_id = -1;
    while (vActual != NULL)
    {
        if (vActual->dato == inicioVerticeDato)
            encontrado = 1;
        if (vActual->dato > max_id)
            max_id = vActual->dato;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado)
    {
        printf("DFS Error: El vertice de inicio %d no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    int *visitado = (int *)calloc(max_id + 1, sizeof(int));
    int *pila = (int *)malloc(n * sizeof(int));
    int tope = 0;

    ListaVertice resultado = NULL;

    pila[tope++] = inicioVerticeDato;

    while (tope > 0)
    {
        int actual = pila[--tope];
        if (!visitado[actual])
        {
            visitado[actual] = 1;
                        ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
            nuevo->dato = actual;
            nuevo->marcado = 0;
            nuevo->sig = resultado;
            resultado = nuevo;

            int num_sucesores = 0;
            ListaArco arco = g.a;
            while (arco != NULL)
            {
                if (arco->origen == actual && !visitado[arco->destino])
                {
                    num_sucesores++;
                }
                arco = arco->sig;
            }
            int *sucesores = (int *)malloc(num_sucesores * sizeof(int));
            int idx = 0;
            arco = g.a;
            while (arco != NULL)
            {
                if (arco->origen == actual && !visitado[arco->destino])
                {
                    sucesores[idx++] = arco->destino;
                }
                arco = arco->sig;
            }
            for (int i = num_sucesores - 1; i >= 0; i--)
            {
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
ListaArco dijkstra(Grafo g, int origen, int destino)
{
    if (vacioGrafo(g))
    {
        printf("Dijkstra Error: El grafo está vacío.\n");
        return NULL;
    }

    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL)
    {
        if (temp_v->dato > max_id)
        {
            max_id = temp_v->dato;
        }
        temp_v = temp_v->sig;
    }

    if (max_id < 0)
    {
        printf("Dijkstra Error: El grafo no tiene vértices.\n");
        return NULL;
    }

    int num_vertices_total = max_id + 1;
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));

    if (distancia == NULL || predecesor == NULL)
    {
        perror("Error al reservar memoria para Dijkstra");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    for (int i = 0; i < num_vertices_total; i++)
    {
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    temp_v = g.v;
    int origen_existe = 0, destino_existe = 0;
    while (temp_v != NULL)
    {
        if (temp_v->dato == origen)
        {
            origen_existe = 1;
        }
        if (temp_v->dato == destino)
        {
            destino_existe = 1;
        }
        temp_v = temp_v->sig;
    }

    if (!origen_existe || !destino_existe)
    {
        printf("Dijkstra Error: El vértice origen o destino no existe en el grafo.\n");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen] = 0;
    g = desmarcarGrafo(g);

    for (int count = 0; count < num_vertices_total; count++)
    {
        int u = -1;
        int min_dist = INT_MAX;

        temp_v = g.v;
        while (temp_v != NULL)
        {
            int id_actual = temp_v->dato;
            if (!temp_v->marcado && distancia[id_actual] < min_dist)
            {
                min_dist = distancia[id_actual];
                u = id_actual;
            }
            temp_v = temp_v->sig;
        }

        if (u == -1)
            break;

        g = marcarVertice(g, u);

        ListaArco temp_a = g.a;
        while (temp_a != NULL)
        {
            if (temp_a->origen == u)
            {
                int v = temp_a->destino;
                int costo = temp_a->costo;

                if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v])
                {
                    distancia[v] = distancia[u] + costo;
                    predecesor[v] = u;
                }
            }
            temp_a = temp_a->sig;
        }
    }

    ListaArco camino = NULL;
    int actual = destino;
    while (actual != -1 && actual != origen)
    {
        int anterior = predecesor[actual];
        if (anterior == -1)
        {
            printf("No hay camino desde %d hasta %d.\n", origen, destino);
            free(distancia);
            free(predecesor);
            return NULL;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL)
        {
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
ListaArco prim(Grafo g, int inicio)
{
    if (vacioGrafo(g))
    {
        printf("Prim Error: El grafo está vacío.\n");
        return NULL;
    }

    ListaVertice temp_v = g.v;
    int inicio_existe = 0;
    while (temp_v != NULL)
    {
        if (temp_v->dato == inicio)
        {
            inicio_existe = 1;
            break;
        }
        temp_v = temp_v->sig;
    }

    if (!inicio_existe)
    {
        printf("Prim Error: El vértice de inicio %d no existe en el grafo.\n", inicio);
        return NULL;
    }

    g = desmarcarGrafo(g);
    ListaArco mst = NULL;
    g = marcarVertice(g, inicio);
    while (1)
    {
        ListaArco temp_a = g.a;
        ListaArco arco_min = NULL;
        int costo_min = INT_MAX;

        while (temp_a != NULL)
        {
            if (marcadoVertice(g, temp_a->origen) && !marcadoVertice(g, temp_a->destino))
            {
                if (temp_a->costo < costo_min)
                {
                    costo_min = temp_a->costo;
                    arco_min = temp_a;
                }
            }
            else if (marcadoVertice(g, temp_a->destino) && !marcadoVertice(g, temp_a->origen))
            {
                if (temp_a->costo < costo_min)
                {
                    costo_min = temp_a->costo;
                    arco_min = temp_a;
                }
            }
            temp_a = temp_a->sig;
        }

        if (arco_min == NULL)
        {
            break;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL)
        {
            perror("Error al asignar memoria para un arco");
            return NULL;
        }
        nuevo_arco->origen = arco_min->origen;
        nuevo_arco->destino = arco_min->destino;
        nuevo_arco->costo = arco_min->costo;
        nuevo_arco->sig = NULL;

        if (mst == NULL)
        {
            mst = nuevo_arco;
        }
        else
        {
            ListaArco temp = mst;
            while (temp->sig != NULL)
            {
                temp = temp->sig;
            }
            temp->sig = nuevo_arco;
        }

        if (!marcadoVertice(g, arco_min->origen))
        {
            g = marcarVertice(g, arco_min->origen);
        }
        else
        {
            g = marcarVertice(g, arco_min->destino);
        }
    }

    temp_v = g.v;
    while (temp_v != NULL)
    {
        if (!temp_v->marcado)
        {
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
ListaArco bellmanFord(Grafo g, int origen, int destino)
{
    if (vacioGrafo(g))
    {
        printf("Bellman-Ford Error: El grafo está vacío.\n");
        return NULL;
    }

    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL)
    {
        if (temp_v->dato > max_id)
        {
            max_id = temp_v->dato;
        }
        temp_v = temp_v->sig;
    }

    if (max_id < 0)
    {
        printf("Bellman-Ford Error: El grafo no tiene vértices.\n");
        return NULL;
    }

    int num_vertices_total = max_id + 1;
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));

    if (distancia == NULL || predecesor == NULL)
    {
        perror("Error al reservar memoria para Bellman-Ford");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    for (int i = 0; i < num_vertices_total; i++)
    {
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    temp_v = g.v;
    int origen_existe = 0, destino_existe = 0;
    while (temp_v != NULL)
    {
        if (temp_v->dato == origen)
        {
            origen_existe = 1;
        }
        if (temp_v->dato == destino)
        {
            destino_existe = 1;
        }
        temp_v = temp_v->sig;
    }

    if (!origen_existe || !destino_existe)
    {
        printf("Bellman-Ford Error: El vértice origen o destino no existe en el grafo.\n");
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen] = 0;

    int n = num_vertices_total;
    for (int i = 1; i < n; i++)
    {
        ListaArco temp_a = g.a;
        while (temp_a != NULL)
        {
            int u = temp_a->origen;
            int v = temp_a->destino;
            int costo = temp_a->costo;
            if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v])
            {
                distancia[v] = distancia[u] + costo;
                predecesor[v] = u;
            }
            temp_a = temp_a->sig;
        }
    }

    ListaArco temp_a = g.a;
    while (temp_a != NULL)
    {
        int u = temp_a->origen;
        int v = temp_a->destino;
        int costo = temp_a->costo;
        if (distancia[u] != INT_MAX && distancia[u] + costo < distancia[v])
        {
            printf("Bellman-Ford Error: Se detectó un ciclo negativo alcanzable.\n");
            free(distancia);
            free(predecesor);
            return NULL;
        }
        temp_a = temp_a->sig;
    }

    ListaArco camino = NULL;
    int actual = destino;
    while (actual != -1 && actual != origen)
    {
        int anterior = predecesor[actual];
        if (anterior == -1)
        {
            printf("No hay camino desde %d hasta %d.\n", origen, destino);
            free(distancia);
            free(predecesor);
            return NULL;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL)
        {
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
ListaArco kruskal(Grafo g)
{
    if (vacioGrafo(g))
    {
        printf("Kruskal Error: El grafo está vacío.\n");
        return NULL;
    }

    int n = ordenGrafo(g);
    if (n == 0)
        return NULL;

    int max_id = -1;
    ListaVertice temp_v = g.v;
    while (temp_v != NULL)
    {
        if (temp_v->dato > max_id)
            max_id = temp_v->dato;
        temp_v = temp_v->sig;
    }
    int *dato_a_indice = (int *)malloc((max_id + 1) * sizeof(int));
    int *indice_a_dato = (int *)malloc(n * sizeof(int));
    for (int i = 0; i <= max_id; i++)
        dato_a_indice[i] = -1;
    temp_v = g.v;
    int idx = 0;
    while (temp_v != NULL)
    {
        dato_a_indice[temp_v->dato] = idx;
        indice_a_dato[idx] = temp_v->dato;
        idx++;
        temp_v = temp_v->sig;
    }

    int *padre = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        padre[i] = i;

#define FIND(padre, x) ({ int _x = (x); while (padre[_x] != _x) _x = padre[_x]; _x; })

    int m = 0;
    ListaArco temp_a = g.a;
    while (temp_a != NULL)
    {
        m++;
        temp_a = temp_a->sig;
    }
    ListaArco *arcos = (ListaArco *)malloc(m * sizeof(ListaArco));
    temp_a = g.a;
    for (int i = 0; i < m; i++)
    {
        arcos[i] = temp_a;
        temp_a = temp_a->sig;
    }
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - 1 - i; j++)
        {
            if (arcos[j]->costo > arcos[j + 1]->costo)
            {
                ListaArco tmp = arcos[j];
                arcos[j] = arcos[j + 1];
                arcos[j + 1] = tmp;
            }
        }
    }

    ListaArco mst = NULL, mst_last = NULL;
    int arcos_mst = 0;
    for (int i = 0; i < m && arcos_mst < n - 1; i++)
    {
        int u = arcos[i]->origen;
        int v = arcos[i]->destino;
        int idx_u = dato_a_indice[u];
        int idx_v = dato_a_indice[v];
        int ru = FIND(padre, idx_u);
        int rv = FIND(padre, idx_v);
        if (ru != rv)
        {
            ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
            nuevo->origen = u;
            nuevo->destino = v;
            nuevo->costo = arcos[i]->costo;
            nuevo->sig = NULL;
            if (mst == NULL)
            {
                mst = nuevo;
                mst_last = nuevo;
            }
            else
            {
                mst_last->sig = nuevo;
                mst_last = nuevo;
            }
            padre[rv] = ru;
            arcos_mst++;
        }
    }

    int raiz = FIND(padre, 0);
    int conexo = 1;
    for (int i = 1; i < n; i++)
    {
        if (FIND(padre, i) != raiz)
        {
            conexo = 0;
            break;
        }
    }

    free(padre);
    free(dato_a_indice);
    free(indice_a_dato);
    free(arcos);

#undef FIND

    if (!conexo)
    {
        printf("Kruskal Error: El grafo no es conexo.\n");
        while (mst != NULL)
        {
            ListaArco tmp = mst;
            mst = mst->sig;
            free(tmp);
        }
        return NULL;
    }

    return mst;
}