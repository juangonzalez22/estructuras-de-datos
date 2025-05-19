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
    int frente = 0, fin = 0;

    ListaVertice resultado = NULL;

    cola[fin++] = strdup(inicioVerticeDato);
    visitados[visitados_count++] = strdup(inicioVerticeDato);

    while (frente < fin)
    {
        char *actual = cola[frente++];

        ListaVertice nuevo = (ListaVertice)malloc(sizeof(struct NodoV));
        nuevo->dato = strdup(actual);
        nuevo->marcado = 0;
        nuevo->sig = resultado;
        resultado = nuevo;

        ListaArco arco = g.a;
        while (arco != NULL)
        {
            if (strcmp(arco->origen, actual) == 0)
            {
                int ya_visitado = 0;
                for (int i = 0; i < visitados_count; i++)
                {
                    if (strcmp(visitados[i], arco->destino) == 0)
                    {
                        ya_visitado = 1;
                        break;
                    }
                }
                if (!ya_visitado)
                {
                    cola[fin++] = strdup(arco->destino);
                    visitados[visitados_count++] = strdup(arco->destino);
                }
            }
            arco = arco->sig;
        }
        free(actual);
    }

    for (int i = 0; i < visitados_count; i++)
        free(visitados[i]);
    free(visitados);
    for (int i = frente; i < fin; i++)
        free(cola[i]);
    free(cola);

    return resultado;
}

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
            nuevo->sig = resultado;
            resultado = nuevo;

            int num_sucesores = 0;
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
                        num_sucesores++;
                }
                arco = arco->sig;
            }
            char **sucesores = (char **)malloc(num_sucesores * sizeof(char *));
            int idx = 0;
            arco = g.a;
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
                        sucesores[idx++] = strdup(arco->destino);
                }
                arco = arco->sig;
            }
            for (int i = num_sucesores - 1; i >= 0; i--)
            {
                pila[tope++] = sucesores[i];
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