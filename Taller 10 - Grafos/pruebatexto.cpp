#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/***************************************************************/
typedef struct NodoV
{
    char *dato;
    struct NodoV *sig;
    int marcado;
} *ListaVertice;

/***************************************************************/
typedef struct NodoA
{
    char *origen;
    char *destino;
    int costo;
    struct NodoA *sig;
} *ListaArco;

/***************************************************************/
typedef struct nodoGrafo
{
    ListaVertice v;
    ListaArco a;
} Grafo;

/***************************************************************/
Grafo crearGrafo()
{
    Grafo g;
    g.v = NULL;
    g.a = NULL;
    return g;
}

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
ListaVertice verticesGrafo(Grafo g)
{
    return g.v;
}

/***************************************************************/
ListaArco arcosGrafo(Grafo g)
{
    return g.a;
}

/***************************************************************/
Grafo cambiarListaV(Grafo g, ListaVertice k)
{
    g.v = k;
    return g;
}

/***************************************************************/
Grafo cambiarListaA(Grafo g, ListaArco k)
{
    g.a = k;
    return g;
}

/***************************************************************/
int vacioGrafo(Grafo g)
{
    if (g.v == NULL)
        return 1;
    else
        return 0;
}

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
ListaArco dijkstra(Grafo g, const char *origen, const char *destino)
{
    if (vacioGrafo(g))
    {
        printf("Dijkstra Error: El grafo está vacío.\n");
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
        printf("Dijkstra Error: El vértice origen o destino no existe en el grafo.\n");
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
