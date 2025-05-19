#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/***************************************************************/
/**
 * @struct NodoV
 * @brief Representa un nodo de la lista de vértices de un grafo.
 *
 * Cada nodo almacena el dato del vértice, un puntero al siguiente vértice en la lista
 * y un indicador de si el vértice ha sido marcado (útil para algoritmos de recorrido).
 *
 * Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarVertice(g, "A");
 * g = insertarVertice(g, "B");
 * ListaVertice v = g.v;
 * @endcode
 */
/***************************************************************/
typedef struct NodoV
{
    char *dato;
    struct NodoV *sig;
    int marcado;
} *ListaVertice;

/***************************************************************/
/**
 * @struct NodoA
 * @brief Representa un nodo de la lista de arcos de un grafo.
 *
 * Cada nodo almacena el vértice de origen, el vértice de destino, el costo del arco
 * y un puntero al siguiente arco en la lista.
 *
 * Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * g = insertarArco(g, "A", "B", 5);
 * ListaArco a = g.a;
 * @endcode
 */
/***************************************************************/
typedef struct NodoA
{
    char *origen;
    char *destino;
    int costo;
    struct NodoA *sig;
} *ListaArco;

/***************************************************************/
/**
 * @struct nodoGrafo
 * @brief Representa un grafo mediante listas de vértices y arcos.
 *
 * El grafo contiene una lista de vértices y una lista de arcos que conectan dichos vértices.
 *
 * Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * @endcode
 */
/***************************************************************/
typedef struct nodoGrafo
{
    ListaVertice v;
    ListaArco a;
} Grafo;

/***************************************************************/
/**
 * @brief Crea un grafo vacío.
 *
 * Inicializa un grafo con listas de vértices y arcos vacías.
 *
 * Ejemplo de uso:
 * @code
 * Grafo g = crearGrafo();
 * @endcode
 *
 * @return Grafo vacío.
 */
/***************************************************************/
Grafo crearGrafo()
{
    Grafo g;
    g.v = NULL;
    g.a = NULL;
    return g;
}

/***************************************************************/
/**
 * @brief Imprime todos los arcos del grafo.
 *
 * Muestra en consola la lista de arcos en el formato: origen -> destino (costo).
 *
 * Ejemplo de uso:
 * @code
 * imprimirArcos(g.a);
 * @endcode
 *
 * @param a_lista Lista de arcos a imprimir.
 */
/***************************************************************/
void imprimirArcos(ListaArco a_lista)
{
    printf("Arcos en el grafo (origen -> destino (costo)):\n");
    while (a_lista != NULL)
    {
        printf("%s -> %s (%d)\n", a_lista->origen, a_lista->destino, a_lista->costo);
        a_lista = a_lista->sig;
    }
    printf("\n");
}

/***************************************************************/
/**
 * @brief Inserta un nuevo vértice en el grafo.
 *
 * Agrega un vértice con el dato especificado a la lista de vértices del grafo.
 *
 * Ejemplo de uso:
 * @code
 * g = insertarVertice(g, "A");
 * @endcode
 *
 * @param g Grafo en el que se insertará el vértice.
 * @param x Dato del vértice a insertar.
 * @return Grafo con el nuevo vértice agregado.
 */
/***************************************************************/
Grafo insertarVertice(Grafo g, const char *x)
{
    ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
    if (nuevo == NULL)
    {
        perror("Error: No se pudo asignar memoria para nuevo vertice");
        return g;
    }
    nuevo->dato = strdup(x);
    nuevo->sig = g.v;
    nuevo->marcado = 0;
    g.v = nuevo;
    return g;
}

/***************************************************************/
/**
 * @brief Imprime la lista de vértices del grafo.
 *
 * Muestra en consola los vértices y su estado de marcado.
 *
 * Ejemplo de uso:
 * @code
 * imprimirListaV(g);
 * @endcode
 *
 * @param g Grafo del que se imprimirán los vértices.
 */
/***************************************************************/
void imprimirListaV(Grafo g)
{
    ListaVertice k = g.v;
    printf("\n--- Lista de Vertices (Dato, Marcado) ---");
    if (k == NULL)
    {
        printf("\nNo hay vertices en el grafo.");
    }
    while (k != NULL)
    {
        printf("\nVertice: %s      Marcado: %d", k->dato, k->marcado);
        k = k->sig;
    }
    printf("\n----------------------------------------\n");
}

/***************************************************************/
/**
 * @brief Inserta un nuevo arco en el grafo.
 *
 * Agrega un arco desde el vértice de origen al vértice de destino con el costo especificado.
 *
 * Ejemplo de uso:
 * @code
 * g = insertarArco(g, "A", "B", 5);
 * @endcode
 *
 * @param g Grafo en el que se insertará el arco.
 * @param x Vértice de origen.
 * @param y Vértice de destino.
 * @param z Costo del arco.
 * @return Grafo con el nuevo arco agregado.
 */
/***************************************************************/
Grafo insertarArco(Grafo g, const char *x, const char *y, int z)
{
    ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
    if (nuevo == NULL)
    {
        perror("Error: No se pudo asignar memoria para nuevo arco");
        return g;
    }
    nuevo->origen = strdup(x);
    nuevo->destino = strdup(y);
    nuevo->costo = z;
    nuevo->sig = g.a;
    g.a = nuevo;
    return g;
}

/***************************************************************/
/**
 * @brief Imprime la lista de arcos del grafo.
 *
 * Muestra en consola los arcos del grafo en el formato: Origen -> Destino, Costo.
 *
 * Ejemplo de uso:
 * @code
 * imprimirListaA(g);
 * @endcode
 *
 * @param g Grafo del que se imprimirán los arcos.
 */
/***************************************************************/
void imprimirListaA(Grafo g)
{
    ListaArco k = g.a;
    printf("\n--- Lista de Arcos (Origen, Destino, Costo) ---");
    if (k == NULL)
    {
        printf("\nNo hay arcos en el grafo.");
    }
    while (k != NULL)
    {
        printf("\nArco: %s -> %s      Costo: %d", k->origen, k->destino, k->costo);
        k = k->sig;
    }
    printf("\n---------------------------------------------\n");
}

/***************************************************************/
/**
 * @brief Devuelve la lista de vértices del grafo.
 *
 * Permite acceder directamente a la lista de vértices almacenada en el grafo.
 *
 * Ejemplo de uso:
 * @code
 * ListaVertice v = verticesGrafo(g);
 * @endcode
 *
 * @param g Grafo del que se obtendrán los vértices.
 * @return Lista de vértices del grafo.
 */
/***************************************************************/
ListaVertice verticesGrafo(Grafo g)
{
    return g.v;
}

/***************************************************************/
/**
 * @brief Devuelve la lista de arcos del grafo.
 *
 * Permite acceder directamente a la lista de arcos almacenada en el grafo.
 *
 * Ejemplo de uso:
 * @code
 * ListaArco a = arcosGrafo(g);
 * @endcode
 *
 * @param g Grafo del que se obtendrán los arcos.
 * @return Lista de arcos del grafo.
 */
/***************************************************************/
ListaArco arcosGrafo(Grafo g)
{
    return g.a;
}

/***************************************************************/
/**
 * @brief Cambia la lista de vértices del grafo.
 *
 * Permite reemplazar directamente la lista de vértices almacenada en el grafo.
 *
 * Ejemplo de uso:
 * @code
 * g = cambiarListaV(g, nuevaLista);
 * @endcode
 *
 * @param g Grafo al que se le cambiará la lista de vértices.
 * @param k Nueva lista de vértices.
 * @return Grafo con la lista de vértices actualizada.
 */
/***************************************************************/
Grafo cambiarListaV(Grafo g, ListaVertice k)
{
    g.v = k;
    return g;
}

/***************************************************************/
/**
 * @brief Cambia la lista de arcos del grafo.
 *
 * Permite reemplazar directamente la lista de arcos almacenada en el grafo.
 *
 * Ejemplo de uso:
 * @code
 * g = cambiarListaA(g, nuevaLista);
 * @endcode
 *
 * @param g Grafo al que se le cambiará la lista de arcos.
 * @param k Nueva lista de arcos.
 * @return Grafo con la lista de arcos actualizada.
 */
/***************************************************************/
Grafo cambiarListaA(Grafo g, ListaArco k)
{
    g.a = k;
    return g;
}

/***************************************************************/
/**
 * @brief Verifica si el grafo está vacío.
 *
 * Retorna 1 si el grafo no tiene vértices, 0 en caso contrario.
 *
 * Ejemplo de uso:
 * @code
 * if (vacioGrafo(g)) { printf("El grafo está vacío.\n"); }
 * @endcode
 *
 * @param g Grafo a verificar.
 * @return 1 si el grafo está vacío, 0 si contiene al menos un vértice.
 */
/***************************************************************/
int vacioGrafo(Grafo g)
{
    if (g.v == NULL)
        return 1;
    else
        return 0;
}

/***************************************************************/
/**
 * @brief Elimina un vértice del grafo.
 *
 * Elimina el vértice cuyo dato coincide con el especificado, liberando la memoria asociada.
 *
 * Ejemplo de uso:
 * @code
 * g = eliminarVertice(g, "A");
 * @endcode
 *
 * @param g Grafo del que se eliminará el vértice.
 * @param x Dato del vértice a eliminar.
 * @return Grafo con el vértice eliminado.
 */
/***************************************************************/
Grafo eliminarVertice(Grafo g, const char *x)
{
    ListaVertice k = g.v, p_anterior = NULL;

    if (k != NULL && strcmp(k->dato, x) == 0)
    {
        g.v = k->sig;
        free(k->dato);
        free(k);
        return g;
    }

    while (k != NULL && strcmp(k->dato, x) != 0)
    {
        p_anterior = k;
        k = k->sig;
    }

    if (k == NULL)
        return g;

    p_anterior->sig = k->sig;
    free(k->dato);
    free(k);
    return g;
}

/***************************************************************/
/**
 * @brief Elimina un arco del grafo.
 *
 * Elimina el arco que conecta el vértice de origen con el vértice de destino, liberando la memoria asociada.
 *
 * Ejemplo de uso:
 * @code
 * g = eliminarArco(g, "A", "B");
 * @endcode
 *
 * @param g Grafo del que se eliminará el arco.
 * @param x Vértice de origen.
 * @param y Vértice de destino.
 * @return Grafo con el arco eliminado.
 */
/***************************************************************/
Grafo eliminarArco(Grafo g, const char *x, const char *y)
{
    ListaArco k = g.a, p_anterior = NULL;

    if (k != NULL && strcmp(k->origen, x) == 0 && strcmp(k->destino, y) == 0)
    {
        g.a = k->sig;
        free(k);
        return g;
    }

    while (k != NULL && !(k->origen == x && k->destino == y))
    {
        p_anterior = k;
        k = k->sig;
    }

    if (k == NULL)
        return g;

    p_anterior->sig = k->sig;
    free(k);
    return g;
}

/***************************************************************/
/**
 * @brief Obtiene el costo de un arco entre dos vértices.
 *
 * Busca el arco que conecta el vértice de origen con el vértice de destino y retorna su costo.
 * Si no existe dicho arco, retorna -1.
 *
 * Ejemplo de uso:
 * @code
 * int costo = costoArco(g, "A", "B");
 * @endcode
 *
 * @param g Grafo en el que se buscará el arco.
 * @param x Vértice de origen.
 * @param y Vértice de destino.
 * @return Costo del arco si existe, -1 en caso contrario.
 */
/***************************************************************/
int costoArco(Grafo g, const char *x, const char *y)
{
    ListaArco k = g.a;

    while (k != NULL)
    {
        if ((strcmp(k->origen, x) == 0) && (strcmp(k->destino, y) == 0))
            return k->costo;
        k = k->sig;
    }
    return -1;
}

/***************************************************************/
/**
 * @brief Retorna el número de vértices del grafo.
 *
 * Calcula y retorna el orden del grafo, es decir, la cantidad de vértices que contiene.
 *
 * Ejemplo de uso:
 * @code
 * int n = ordenGrafo(g);
 * @endcode
 *
 * @param g Grafo del que se obtendrá el número de vértices.
 * @return Número de vértices del grafo.
 */
/***************************************************************/
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

/***************************************************************/
/**
 * @brief Marca un vértice del grafo.
 *
 * Cambia el estado de marcado del vértice cuyo dato coincide con el especificado.
 *
 * Ejemplo de uso:
 * @code
 * g = marcarVertice(g, "A");
 * @endcode
 *
 * @param g Grafo en el que se marcará el vértice.
 * @param x Dato del vértice a marcar.
 * @return Grafo con el vértice marcado.
 */
/***************************************************************/
Grafo marcarVertice(Grafo g, const char *x)
{
    ListaVertice k = g.v;

    while (k != NULL)
    {
        if (strcmp(k->dato, x) == 0)
        {
            k->marcado = 1;
            return g;
        }
        k = k->sig;
    }
    return g;
}

/***************************************************************/
/**
 * @brief Desmarca todos los vértices del grafo.
 *
 * Cambia el estado de marcado de todos los vértices a 0 (no marcado).
 *
 * Ejemplo de uso:
 * @code
 * g = desmarcarGrafo(g);
 * @endcode
 *
 * @param g Grafo cuyos vértices serán desmarcados.
 * @return Grafo con todos los vértices desmarcados.
 */
/***************************************************************/
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

/***************************************************************/
/**
 * @brief Consulta el estado de marcado de un vértice.
 *
 * Retorna 1 si el vértice cuyo dato coincide con el especificado está marcado, 0 en caso contrario.
 *
 * Ejemplo de uso:
 * @code
 * if (marcadoVertice(g, "A")) { printf("El vértice A está marcado.\n"); }
 * @endcode
 *
 * @param g Grafo en el que se buscará el vértice.
 * @param x Dato del vértice a consultar.
 * @return 1 si el vértice está marcado, 0 en caso contrario.
 */
/***************************************************************/
int marcadoVertice(Grafo g, const char *x)
{
    ListaVertice k = g.v;
    while (k != NULL)
    {
        if (strcmp(k->dato, x) == 0)
        {
            return k->marcado;
        }
        k = k->sig;
    }
    return 0;
}

/***************************************************************/
/**
 * @brief Calcula el camino más corto entre dos vértices usando el algoritmo de Dijkstra.
 *
 * Encuentra el camino de costo mínimo desde el vértice de origen hasta el vértice de destino en el grafo.
 * Retorna una lista de arcos que representan el camino más corto encontrado.
 * Si no existe camino, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaArco camino = dijkstra(g, "A", "B");
 * @endcode
 *
 * @param g Grafo en el que se buscará el camino.
 * @param origen Vértice de origen.
 * @param destino Vértice de destino.
 * @return Lista de arcos que conforman el camino más corto, o NULL si no existe.
 */
/***************************************************************/
ListaArco dijkstra(Grafo g, const char *origen, const char *destino)
{
    if (vacioGrafo(g))
    {
        perror("Dijkstra Error: El grafo está vacío.\n");
        return NULL;
    }

    int num_vertices_total = ordenGrafo(g);
    char **vertices = (char **)malloc(num_vertices_total * sizeof(char *));
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));
    if (vertices == NULL || distancia == NULL || predecesor == NULL)
    {
        perror("Error al reservar memoria para Dijkstra");
        free(vertices);
        free(distancia);
        free(predecesor);
        return NULL;
    }

    ListaVertice temp_v = g.v;
    int idx = 0;
    while (temp_v != NULL)
    {
        vertices[idx++] = temp_v->dato;
        temp_v = temp_v->sig;
    }

    int origen_idx = -1, destino_idx = -1;
    for (int i = 0; i < num_vertices_total; i++)
    {
        if (strcmp(vertices[i], origen) == 0)
            origen_idx = i;
        if (strcmp(vertices[i], destino) == 0)
            destino_idx = i;
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    if (origen_idx == -1 || destino_idx == -1)
    {
        perror("Dijkstra Error: El vértice origen o destino no existe en el grafo.\n");
        free(vertices);
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen_idx] = 0;
    g = desmarcarGrafo(g);

    // Bucle principal
    for (int count = 0; count < num_vertices_total; count++)
    {
        int u_idx = -1, min_dist = INT_MAX;
        for (int i = 0; i < num_vertices_total; i++)
        {
            ListaVertice vtx = g.v;
            while (vtx != NULL)
            {
                if (strcmp(vtx->dato, vertices[i]) == 0 && !vtx->marcado && distancia[i] < min_dist)
                {
                    min_dist = distancia[i];
                    u_idx = i;
                }
                vtx = vtx->sig;
            }
        }
        if (u_idx == -1)
            break;

        g = marcarVertice(g, vertices[u_idx]);

        ListaArco temp_a = g.a;
        while (temp_a != NULL)
        {
            if (strcmp(temp_a->origen, vertices[u_idx]) == 0)
            {
                int v_idx = -1;
                for (int i = 0; i < num_vertices_total; i++)
                {
                    if (strcmp(temp_a->destino, vertices[i]) == 0)
                    {
                        v_idx = i;
                        break;
                    }
                }
                if (v_idx != -1 && distancia[u_idx] != INT_MAX && distancia[u_idx] + temp_a->costo < distancia[v_idx])
                {
                    distancia[v_idx] = distancia[u_idx] + temp_a->costo;
                    predecesor[v_idx] = u_idx;
                }
            }
            temp_a = temp_a->sig;
        }
    }

    ListaArco camino = NULL;
    int actual = destino_idx;
    while (actual != -1 && actual != origen_idx)
    {
        int anterior = predecesor[actual];
        if (anterior == -1)
        {
            printf("No hay camino desde el nodo hasta %s.\n", origen, destino);
            free(vertices);
            free(distancia);
            free(predecesor);
            return NULL;
        }
        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL)
        {
            perror("Error al asignar memoria para un arco");
            free(vertices);
            free(distancia);
            free(predecesor);
            return NULL;
        }
        nuevo_arco->origen = vertices[anterior];
        nuevo_arco->destino = vertices[actual];
        nuevo_arco->costo = costoArco(g, vertices[anterior], vertices[actual]);
        nuevo_arco->sig = camino;
        camino = nuevo_arco;
        actual = anterior;
    }

    free(vertices);
    free(distancia);
    free(predecesor);
    return camino;
}

/***************************************************************/
/**
 * @brief Calcula el árbol de expansión mínima usando el algoritmo de Prim.
 *
 * Genera el árbol de expansión mínima (MST) a partir del vértice de inicio especificado.
 * Retorna una lista de arcos que conforman el MST. Si el grafo no es conexo, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaArco mst = prim(g, "A");
 * @endcode
 *
 * @param g Grafo sobre el que se calculará el MST.
 * @param inicio Vértice de inicio para el algoritmo de Prim.
 * @return Lista de arcos del árbol de expansión mínima, o NULL si el grafo no es conexo.
 */
/***************************************************************/
ListaArco prim(Grafo g, const char *inicio)
{
    if (vacioGrafo(g))
    {
        perror("Prim Error: El grafo está vacío.\n");
        return NULL;
    }

    ListaVertice temp_v = g.v;
    int inicio_existe = 0;
    while (temp_v != NULL)
    {
        if (strcmp(temp_v->dato, inicio) == 0)
        {
            inicio_existe = 1;
            break;
        }
        temp_v = temp_v->sig;
    }

    if (!inicio_existe)
    {
        perror("Prim Error: El vértice de inicio no existe en el grafo.");
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
        nuevo_arco->origen = strdup(arco_min->origen);
        nuevo_arco->destino = strdup(arco_min->destino);
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
            perror("Prim Error: El grafo no es conexo.\n");
            ListaArco temp, next;
            temp = mst;
            while (temp != NULL)
            {
                next = temp->sig;
                free(temp->origen);
                free(temp->destino);
                free(temp);
                temp = next;
            }
            return NULL;
        }
        temp_v = temp_v->sig;
    }

    return mst;
}

/***************************************************************/
/**
 * @brief Calcula el camino más corto entre dos vértices usando el algoritmo de Bellman-Ford.
 *
 * Encuentra el camino de costo mínimo desde el vértice de origen hasta el vértice de destino en el grafo.
 * Retorna una lista de arcos que representan el camino más corto encontrado.
 * Si no existe camino o hay un ciclo negativo, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaArco camino = bellmanFord(g, "A", "B");
 * @endcode
 *
 * @param g Grafo en el que se buscará el camino.
 * @param origen Vértice de origen.
 * @param destino Vértice de destino.
 * @return Lista de arcos que conforman el camino más corto, o NULL si no existe.
 */
/***************************************************************/
ListaArco bellmanFord(Grafo g, const char *origen, const char *destino)
{
    if (vacioGrafo(g))
    {
        printf("Bellman-Ford Error: El grafo está vacío.\n");
        return NULL;
    }

    int num_vertices_total = ordenGrafo(g);
    char **vertices = (char **)malloc(num_vertices_total * sizeof(char *));
    int *distancia = (int *)malloc(num_vertices_total * sizeof(int));
    int *predecesor = (int *)malloc(num_vertices_total * sizeof(int));

    if (vertices == NULL || distancia == NULL || predecesor == NULL)
    {
        perror("Error al reservar memoria para Bellman-Ford");
        free(vertices);
        free(distancia);
        free(predecesor);
        return NULL;
    }

    ListaVertice temp_v = g.v;
    int idx = 0;
    while (temp_v != NULL)
    {
        vertices[idx++] = temp_v->dato;
        temp_v = temp_v->sig;
    }

    int origen_idx = -1, destino_idx = -1;
    for (int i = 0; i < num_vertices_total; i++)
    {
        if (strcmp(vertices[i], origen) == 0)
            origen_idx = i;
        if (strcmp(vertices[i], destino) == 0)
            destino_idx = i;
        distancia[i] = INT_MAX;
        predecesor[i] = -1;
    }

    if (origen_idx == -1 || destino_idx == -1)
    {
        printf("Bellman-Ford Error: El vértice origen o destino no existe en el grafo.\n");
        free(vertices);
        free(distancia);
        free(predecesor);
        return NULL;
    }

    distancia[origen_idx] = 0;

    int n = num_vertices_total;
    for (int i = 1; i < n; i++)
    {
        ListaArco temp_a = g.a;
        while (temp_a != NULL)
        {
            int u = -1, v = -1;
            for (int j = 0; j < num_vertices_total; j++)
            {
                if (strcmp(temp_a->origen, vertices[j]) == 0)
                    u = j;
                if (strcmp(temp_a->destino, vertices[j]) == 0)
                    v = j;
            }
            int costo = temp_a->costo;
            if (u != -1 && v != -1 && distancia[u] != INT_MAX && distancia[u] + costo < distancia[v])
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
        int u = -1, v = -1;
        for (int j = 0; j < num_vertices_total; j++)
        {
            if (strcmp(temp_a->origen, vertices[j]) == 0)
                u = j;
            if (strcmp(temp_a->destino, vertices[j]) == 0)
                v = j;
        }
        int costo = temp_a->costo;
        if (u != -1 && v != -1 && distancia[u] != INT_MAX && distancia[u] + costo < distancia[v])
        {
            printf("Bellman-Ford Error: Se detectó un ciclo negativo alcanzable.\n");
            free(vertices);
            free(distancia);
            free(predecesor);
            return NULL;
        }
        temp_a = temp_a->sig;
    }

    ListaArco camino = NULL;
    int actual = destino_idx;
    while (actual != -1 && actual != origen_idx)
    {
        int anterior = predecesor[actual];
        if (anterior == -1)
        {
            printf("No hay camino desde %s hasta %s.\n", origen, destino);
            free(vertices);
            free(distancia);
            free(predecesor);
            return NULL;
        }

        ListaArco nuevo_arco = (ListaArco)malloc(sizeof(struct NodoA));
        if (nuevo_arco == NULL)
        {
            perror("Error al asignar memoria para un arco");
            free(vertices);
            free(distancia);
            free(predecesor);
            return NULL;
        }
        nuevo_arco->origen = strdup(vertices[anterior]);
        nuevo_arco->destino = strdup(vertices[actual]);
        nuevo_arco->costo = costoArco(g, vertices[anterior], vertices[actual]);
        nuevo_arco->sig = camino;
        camino = nuevo_arco;

        actual = anterior;
    }

    free(vertices);
    free(distancia);
    free(predecesor);

    return camino;
}

/***************************************************************/
/**
 * @brief Calcula el árbol de expansión mínima usando el algoritmo de Kruskal.
 *
 * Genera el árbol de expansión mínima (MST) del grafo utilizando el algoritmo de Kruskal.
 * Retorna una lista de arcos que conforman el MST. Si el grafo no es conexo, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaArco mst = kruskal(g);
 * @endcode
 *
 * @param g Grafo sobre el que se calculará el MST.
 * @return Lista de arcos del árbol de expansión mínima, o NULL si el grafo no es conexo.
 */
/***************************************************************/
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

    ListaVertice temp_v = g.v;
    int idx = 0;
    char **vertices = (char **)malloc(n * sizeof(char *));
    while (temp_v != NULL)
    {
        vertices[idx++] = temp_v->dato;
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
        int u = -1, v = -1;
        for (int j = 0; j < n; j++)
        {
            if (strcmp(arcos[i]->origen, vertices[j]) == 0)
                u = j;
            if (strcmp(arcos[i]->destino, vertices[j]) == 0)
                v = j;
        }
        if (u == -1 || v == -1)
            continue;
        int ru = FIND(padre, u);
        int rv = FIND(padre, v);
        if (ru != rv)
        {
            ListaArco nuevo = (ListaArco)malloc(sizeof(struct NodoA));
            nuevo->origen = strdup(arcos[i]->origen);
            nuevo->destino = strdup(arcos[i]->destino);
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
    free(vertices);
    free(arcos);

#undef FIND

    if (!conexo)
    {
        printf("Kruskal Error: El grafo no es conexo.\n");
        while (mst != NULL)
        {
            ListaArco tmp = mst;
            mst = mst->sig;
            free(tmp->origen);
            free(tmp->destino);
            free(tmp);
        }
        return NULL;
    }

    return mst;
}

/***************************************************************/
/**
 * @brief Realiza un recorrido en anchura (BFS) sobre el grafo desde un vértice dado.
 *
 * Genera una lista enlazada de los vértices visitados en orden de recorrido BFS.
 * Si el vértice de inicio no existe o el grafo está vacío, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaVertice recorrido = recorridoBFS(g, "A");
 * @endcode
 *
 * @param g Grafo sobre el que se realizará el recorrido.
 * @param inicioVerticeDato Dato del vértice de inicio.
 * @return Lista de vértices visitados en orden BFS, o NULL si no es posible.
 */
/***************************************************************/
ListaVertice recorridoBFS(Grafo g, const char *inicioVerticeDato)
{
    if (vacioGrafo(g))
    {
        printf("BFS Error: El grafo está vacío.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0;
    while (vActual != NULL)
    {
        if (strcmp(vActual->dato, inicioVerticeDato) == 0)
            encontrado = 1;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado)
    {
        printf("BFS Error: El vértice de inicio %s no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    char **visitados = (char **)malloc(n * sizeof(char *));
    int visitados_count = 0;
    char **cola = (char **)malloc(n * sizeof(char *));
    int frente = 0, final = 0;

    ListaVertice resultado = NULL;
    ListaVertice ultimo = NULL;

    cola[final++] = strdup(inicioVerticeDato);

    while (frente < final)
    {
        char *actual = cola[frente++];
        int ya_visitado = 0;
        for (int i = 0; i < visitados_count; i++)
        {
            if (strcmp(visitados[i], actual) == 0)
            {
                ya_visitado = 1;
                break;
            }
        }
        if (!ya_visitado)
        {
            visitados[visitados_count++] = strdup(actual);
            ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
            nuevo->dato = strdup(actual);
            nuevo->marcado = 0;
            nuevo->sig = NULL;
            if (resultado == NULL) {
                resultado = nuevo;
                ultimo = nuevo;
            } else {
                ultimo->sig = nuevo;
                ultimo = nuevo;
            }

            ListaArco arco = g.a;
            while (arco != NULL)
            {
                if (strcmp(arco->origen, actual) == 0)
                {
                    int ya_sucesor = 0;
                    for (int i = 0; i < visitados_count; i++)
                    {
                        if (strcmp(visitados[i], arco->destino) == 0)
                        {
                            ya_sucesor = 1;
                            break;
                        }
                    }
                    if (!ya_sucesor)
                        cola[final++] = strdup(arco->destino);
                }
                arco = arco->sig;
            }
        }
        free(actual);
    }

    for (int i = 0; i < visitados_count; i++)
        free(visitados[i]);
    free(visitados);
    for (int i = frente; i < final; i++)
        free(cola[i]);
    free(cola);

    return resultado;
}

/***************************************************************/
/**
 * @brief Realiza un recorrido en profundidad (DFS) sobre el grafo desde un vértice dado.
 *
 * Genera una lista enlazada de los vértices visitados en orden de recorrido DFS.
 * Si el vértice de inicio no existe o el grafo está vacío, retorna NULL.
 *
 * Ejemplo de uso:
 * @code
 * ListaVertice recorrido = recorridoDFS(g, "A");
 * @endcode
 *
 * @param g Grafo sobre el que se realizará el recorrido.
 * @param inicioVerticeDato Dato del vértice de inicio.
 * @return Lista de vértices visitados en orden DFS, o NULL si no es posible.
 */
/***************************************************************/
ListaVertice recorridoDFS(Grafo g, const char *inicioVerticeDato)
{
    if (vacioGrafo(g))
    {
        printf("DFS Error: El grafo está vacío.\n");
        return NULL;
    }

    ListaVertice vActual = g.v;
    int encontrado = 0, n = 0;
    while (vActual != NULL)
    {
        if (strcmp(vActual->dato, inicioVerticeDato) == 0)
            encontrado = 1;
        n++;
        vActual = vActual->sig;
    }
    if (!encontrado)
    {
        printf("DFS Error: El vértice de inicio %s no existe en el grafo.\n", inicioVerticeDato);
        return NULL;
    }

    char **visitados = (char **)malloc(n * sizeof(char *));
    int visitados_count = 0;
    char **pila = (char **)malloc(n * sizeof(char *));
    int tope = 0;

    ListaVertice resultado = NULL;
    ListaVertice ultimo = NULL;

    pila[tope++] = strdup(inicioVerticeDato);

    while (tope > 0)
    {
        char *actual = pila[--tope];
        int ya_visitado = 0;
        for (int i = 0; i < visitados_count; i++)
        {
            if (strcmp(visitados[i], actual) == 0)
            {
                ya_visitado = 1;
                break;
            }
        }
        if (!ya_visitado)
        {
            visitados[visitados_count++] = strdup(actual);
            ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
            nuevo->dato = strdup(actual);
            nuevo->marcado = 0;
            nuevo->sig = NULL;
            if (resultado == NULL) {
                resultado = nuevo;
                ultimo = nuevo;
            } else {
                ultimo->sig = nuevo;
                ultimo = nuevo;
            }

            int num_sucesores = 0;
            ListaArco arco = g.a;
            while (arco != NULL)
            {
                if (strcmp(arco->origen, actual) == 0)
                    num_sucesores++;
                arco = arco->sig;
            }
            char **sucesores = (char **)malloc(num_sucesores * sizeof(char *));
            int idx = 0;
            arco = g.a;
            while (arco != NULL)
            {
                if (strcmp(arco->origen, actual) == 0)
                    sucesores[idx++] = strdup(arco->destino);
                arco = arco->sig;
            }
            for (int i = num_sucesores - 1; i >= 0; i--)
            {
                int ya_sucesor = 0;
                for (int j = 0; j < visitados_count; j++)
                {
                    if (strcmp(visitados[j], sucesores[i]) == 0)
                    {
                        ya_sucesor = 1;
                        break;
                    }
                }
                if (!ya_sucesor)
                    pila[tope++] = sucesores[i];
                else
                    free(sucesores[i]);
            }
            free(sucesores);
        }
        free(actual);
    }

    for (int i = 0; i < visitados_count; i++)
        free(visitados[i]);
    free(visitados);
    for (int i = 0; i < tope; i++)
        free(pila[i]);
    free(pila);

    return resultado;
}
