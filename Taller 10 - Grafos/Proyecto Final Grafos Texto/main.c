/***************************************************************/
/**
 * @defgroup ColoresTerminal Colores y estilos ANSI para la terminal
 * @brief Macros para imprimir texto con colores y estilos en la consola.
 *
 * Estas macros definen códigos de escape ANSI para mostrar texto en diferentes colores y estilos
 * (como negrita o subrayado) en la terminal. Son útiles para resaltar mensajes, menús y advertencias
 * en la interfaz de usuario del programa.
 *
 * Ejemplo de uso:
 * @code
 * printf(ANSI_COLOR_RED "Este texto es rojo\n" ANSI_COLOR_RESET);
 * printf(ANSI_BOLD "Texto en negrita\n" ANSI_COLOR_RESET);
 * @endcode
 *
 * @note Funcionan en la mayoría de terminales compatibles con ANSI.
 */
/***************************************************************/
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_COLOR_BRIGHT_GREEN "\x1b[92m"
#define ANSI_COLOR_BRIGHT_RED "\x1b[91m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>No
#include <stdbool.h>
#include "newTADgrafotexto.h"

void menu();
void escenario1();
void escenario2();
void escenario3();
void pausarYLimpiar();


/***************************************************************/
/**
 * @brief Pausa la ejecución hasta que el usuario presione Enter y limpia la pantalla.
 *
 * Esta función muestra un mensaje solicitando al usuario que presione Enter para continuar.
 * Una vez que el usuario lo hace, limpia la consola usando el comando del sistema.
 *
 * @note Utiliza "system(\"cls\")", por lo que solo funciona correctamente en sistemas Windows.
 *
 * @code
 * pausarYLimpiar();
 * @endcode
 */
/***************************************************************/
void pausarYLimpiar()
{
    printf("\nPresiona Enter para continuar...");
    getchar(); // Espera el Enter real del usuario
    system("cls");
}

/***************************************************************/
/**
 * @brief Solicita al usuario el nombre de un nuevo vértice y lo inserta en el grafo.
 *
 * Esta función pide al usuario que ingrese el nombre de un vértice por consola,
 * elimina el salto de línea y lo inserta en el grafo usando la función insertarVertice().
 *
 * @param g Puntero al grafo donde se insertará el nuevo vértice.
 *
 * @code
 * Grafo g = crearGrafo();
 * insertarNuevoVertice(&g);
 * @endcode
 */
/***************************************************************/
void insertarNuevoVertice(Grafo *g)
{
    printf("Ingrese el nombre del vertice: ");
    char nombre[50];
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;
    *g = insertarVertice(*g, nombre);
}

/***************************************************************/
/**
 * @brief Solicita al usuario los datos de un nuevo arco y lo inserta en el grafo.
 *
 * Esta función pide al usuario que ingrese el nombre del vértice origen, el vértice destino y el costo del arco.
 * Verifica que ambos vértices existan y que no exista ya un arco entre ellos. Si las validaciones son correctas,
 * inserta el arco en el grafo usando la función insertarArco().
 *
 * Si alguno de los vértices no existe, si el arco ya existe o si el costo es menor o igual a cero, muestra un mensaje de error.
 *
 * @param g Puntero al grafo donde se insertará el nuevo arco.
 *
 * @code
 * Grafo g = crearGrafo();
 * insertarNuevoArco(&g);
 * @endcode
 */
/***************************************************************/
void insertarNuevoArco(Grafo *g)
{
    printf("Ingrese el nombre del vertice origen: ");
    char origen[50];
    fgets(origen, sizeof(origen), stdin);
    origen[strcspn(origen, "\n")] = 0;

    printf("Ingrese el nombre del vertice destino: ");
    char destino[50];
    fgets(destino, sizeof(destino), stdin);
    destino[strcspn(destino, "\n")] = 0;

    printf("Ingrese el costo del arco: ");
    int costo;
    scanf("%d", &costo);
    while (getchar() != '\n')
        ;
    int existe_origen = 0, existe_destino = 0;
    ListaVertice v = (*g).v;
    while (v != NULL)
    {
        if (strcmp(v->dato, origen) == 0)
            existe_origen = 1;
        if (strcmp(v->dato, destino) == 0)
            existe_destino = 1;
        v = v->sig;
    }

    ListaArco a = (*g).a;
    while (a != NULL)
    {
        if (strcmp(a->origen, origen) == 0 && strcmp(a->destino, destino) == 0)
        {
            printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
            printf("Error: Ya existe un arco entre esos dos vertices.\n");
            printf(ANSI_COLOR_RESET);
            return;
        }
        a = a->sig;
    }

    if (!existe_origen || !existe_destino)
    {
        printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
        printf("Error: Uno o ambos vertices no existen en el grafo.\n");
        printf(ANSI_COLOR_RESET);
        return;
    }
    else if (costo <= 0)
    {
        printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
        printf("Error: El costo del arco debe ser mayor que cero.\n");
        printf(ANSI_COLOR_RESET);
        return;
    }
    else
    {
        *g = insertarArco(*g, origen, destino, costo);
        printf(ANSI_COLOR_BRIGHT_GREEN);
        printf("Arco insertado: %s -> %s (Costo: %d)\n", origen, destino, costo);
        printf(ANSI_COLOR_RESET);
    }
}

/***************************************************************/
/**
 * @brief Formatea una lista de vértices recorridos como una cadena de texto.
 *
 * Esta función toma una lista enlazada de vértices (por ejemplo, resultado de un recorrido BFS o DFS)
 * y construye una cadena con los nombres de los vértices separados por " -> ".
 *
 * @param recorrido Lista enlazada de vértices a formatear.
 * @return Cadena de texto con el recorrido formateado. El usuario debe liberar la memoria con free().
 *
 * @code
 * ListaVertice recorrido = recorridoBFS(g, "A");
 * char *texto = formatearRecorrido(recorrido);
 * printf("%s\n", texto);
 * free(texto);
 * @endcode
 */
/***************************************************************/
char *formatearRecorrido(ListaVertice recorrido)
{
    char *resultado = (char *)malloc(1024 * sizeof(char));
    strcpy(resultado, "");

    while (recorrido != NULL)
    {
        strcat(resultado, recorrido->dato);
        if (recorrido->sig != NULL)
            strcat(resultado, " -> ");
        recorrido = recorrido->sig;
    }
    return resultado;
}

/***************************************************************/
/**
 * @brief Genera un archivo de texto con la información del grafo y sus recorridos.
 *
 * Esta función crea un archivo llamado "resultados_escenario1.txt" que contiene:
 * - La lista de ubicaciones (vértices) del grafo.
 * - La lista de caminos (arcos) con sus distancias.
 * - Los recorridos BFS y DFS desde cada vértice, formateados como cadenas.
 *
 * Si ocurre un error al abrir el archivo, muestra un mensaje por consola.
 *
 * @param g Grafo del cual se extraerá la información para el archivo.
 *
 * @code
 * Grafo g = crearGrafo();
 * generarArchivo(g);
 * @endcode
 *
 * @note El archivo generado se llama "resultados_escenario1.txt" y se sobrescribe en cada ejecución.
 */
/***************************************************************/
void generarArchivo(Grafo g)
{

    FILE *archivo = fopen("resultados_escenario1.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Lista de Ubicaciones:\n");
    ListaVertice vertice = g.v;
    while (vertice != NULL)
    {
        fprintf(archivo, "Ubicacion: %s\n", vertice->dato);
        vertice = vertice->sig;
    }

    fprintf(archivo, "\nLista de Caminos:\n");
    ListaArco arco = g.a;
    while (arco != NULL)
    {
        fprintf(archivo, "Camino: %s -> %s (Distancia: %d km)\n", arco->origen, arco->destino, arco->costo);
        arco = arco->sig;
    }

    fprintf(archivo, "\nRecorridos BFS desde cada vertice:\n");
    for (ListaVertice origen = g.v; origen != NULL; origen = origen->sig)
    {
        ListaVertice recorrido = recorridoBFS(g, origen->dato);
        if (recorrido != NULL)
        {
            char *formateado = formatearRecorrido(recorrido);
            fprintf(archivo, "Desde %s: %s\n", origen->dato, formateado);
            free(formateado);
        }
        else
        {
            fprintf(archivo, "Desde %s: No hay recorrido\n", origen->dato);
        }
    }

    fprintf(archivo, "\nRecorridos DFS desde cada vertice:\n");
    for (ListaVertice origen = g.v; origen != NULL; origen = origen->sig)
    {
        ListaVertice recorrido = recorridoDFS(g, origen->dato);
        if (recorrido != NULL)
        {
            char *formateado = formatearRecorrido(recorrido);
            fprintf(archivo, "Desde %s: %s\n", origen->dato, formateado);
            free(formateado);
        }
        else
        {
            fprintf(archivo, "Desde %s: No hay recorrido\n", origen->dato);
        }
    }

    fclose(archivo);
    printf("Resultados guardados en [resultados_escenario1.txt]\n");
}

/***************************************************************/
/**
 * @brief Menú interactivo para el Escenario 1: Grafo de ubicaciones culturales.
 *
 * Permite al usuario gestionar un grafo con ubicaciones culturales, ofreciendo opciones para:
 * - Insertar vértices y arcos.
 * - Realizar recorridos BFS y DFS desde un vértice dado.
 * - Generar un archivo de resultados con la información del grafo y los recorridos.
 *
 * El menú se repite hasta que el usuario elige regresar al menú principal.
 *
 * @code
 * escenario1();
 * @endcode
 */
/***************************************************************/
void escenario1()
{

    Grafo g = crearGrafo();

    g = insertarVertice(g, "Museo del Oro");
    g = insertarVertice(g, "Museo de Arte Moderno");
    g = insertarVertice(g, "Biblioteca Nacional");
    g = insertarVertice(g, "Teatro Principal");
    g = insertarVertice(g, "Casa de la Cultura");

    g = insertarArco(g, "Museo del Oro", "Museo de Arte Moderno", 1);
    g = insertarArco(g, "Museo del Arte Moderno", "Museo del Oro", 1);

    g = insertarArco(g, "Museo del Oro", "Biblioteca Nacional", 1);
    g = insertarArco(g, "Biblioteca Nacional", "Museo del Oro", 1);

    g = insertarArco(g, "Museo de Arte Moderno", "Teatro Principal", 1);
    g = insertarArco(g, "Teatro Principal", "Museo de Arte Moderno", 1);

    g = insertarArco(g, "Teatro Principal", "Casa de la Cultura", 1);
    g = insertarArco(g, "Casa de la Cultura", "Teatro Principal", 1);

    int opcion;
    do
    {
        printf(ANSI_BOLD ANSI_COLOR_GREEN);
        printf("***************************************************\n");
        printf("*************** MENU ESCENARIO 1 ******************\n");
        printf("***************************************************\n\n");
        printf(ANSI_COLOR_RESET);

        printf(ANSI_BOLD ANSI_COLOR_YELLOW);
        printf("\nIngresa una opcion:\n");
        printf(ANSI_COLOR_RESET);

        printf("1. Insertar Vertice\n");
        printf("2. Insertar Arco\n");
        printf("3. Recorrer usando BFS\n");
        printf("4. Recorrer usando DFS\n");
        printf("5. Generar archivo con resultados\n");
        printf("6. Regresar al menu principal\n\n");
        printf(ANSI_BOLD ANSI_COLOR_GREEN);
        printf("***************************************************\n");
        printf(ANSI_COLOR_RESET);
        printf("Opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n')
            ;

        switch (opcion)
        {
        case 1:
            insertarNuevoVertice(&g);
            printf(ANSI_COLOR_BRIGHT_GREEN);
            printf("Vertice insertado.\n");
            printf(ANSI_COLOR_RESET);
            pausarYLimpiar();
            break;
        case 2:
            insertarNuevoArco(&g);

            pausarYLimpiar();
            break;
        case 3:
        {
            char inicio[50];
            printf("Ingrese el vertice de inicio para BFS: ");
            fgets(inicio, sizeof(inicio), stdin);
            inicio[strcspn(inicio, "\n")] = 0;
            ListaVertice recorrido = recorridoBFS(g, inicio);
            if (recorrido)
            {
                char *formateado = formatearRecorrido(recorrido);
                printf("Recorrido BFS: %s\n", formateado);
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay recorrido BFS desde ese vertice.\n");
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;
        }
        case 4:
        {
            char inicio[50];
            printf("Ingrese el vertice de inicio para DFS: ");
            fgets(inicio, sizeof(inicio), stdin);
            inicio[strcspn(inicio, "\n")] = 0;
            ListaVertice recorrido = recorridoDFS(g, inicio);
            if (recorrido)
            {
                char *formateado = formatearRecorrido(recorrido);
                printf("Recorrido DFS: %s\n", formateado);
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay recorrido DFS desde ese vertice.\n");
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;
        }
        case 5:
            generarArchivo(g);
            pausarYLimpiar();
            break;
        case 6:
            printf("Regresando al menu principal...\n");
            system("cls");
            break;
        default:
            printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
            printf("Opcion no valida.\n");
            printf(ANSI_COLOR_RESET);
            pausarYLimpiar();
            break;
        }
    } while (opcion != 6);
}

/***************************************************************/
/**
 * @brief Formatea un camino de arcos como una cadena de texto.
 *
 * Esta función toma una lista enlazada de arcos (camino) y construye una cadena
 * con el formato "origen1->(costo1)->destino1->(costo2)->destino2...", mostrando
 * el costo de cada tramo entre vértices.
 *
 * @param camino Lista enlazada de arcos a formatear.
 * @return Cadena de texto con el camino formateado. El usuario debe liberar la memoria con free().
 *
 * @code
 * ListaArco camino = dijkstra(g, "A", "B");
 * char *texto = formatearCamino(camino);
 * printf("%s\n", texto);
 * free(texto);
 * @endcode
 */
/***************************************************************/
char *formatearCamino(ListaArco camino)
{
    char *resultado = (char *)malloc(1024 * sizeof(char));
    strcpy(resultado, "");

    while (camino != NULL)
    {
        strcat(resultado, camino->origen);
        char buffer[64];
        sprintf(buffer, "->(%d)->", camino->costo);
        strcat(resultado, buffer);

        if (camino->sig == NULL)
            strcat(resultado, camino->destino);

        camino = camino->sig;
    }
    return resultado;
}

/***************************************************************/
/**
 * @brief Verifica si un camino contiene arcos con costo negativo.
 *
 * Esta función recorre una lista enlazada de arcos y determina si alguno de ellos tiene un costo negativo.
 *
 * @param camino Lista enlazada de arcos a analizar.
 * @return true si existe al menos un arco con costo negativo, false en caso contrario.
 *
 * @code
 * if (tieneNegativos(camino)) {
 *     printf("El camino contiene arcos con costo negativo.\n");
 * }
 * @endcode
 */
/***************************************************************/
bool tieneNegativos(ListaArco camino)
{
    while (camino != NULL)
    {
        if (camino->costo < 0)
            return true;
        camino = camino->sig;
    }
    return false;
}

/***************************************************************/
/**
 * @brief Calcula el costo total de un camino de arcos.
 *
 * Esta función recorre una lista enlazada de arcos y suma los costos de cada uno,
 * devolviendo el costo total del camino.
 *
 * @param camino Lista enlazada de arcos que representa el camino.
 * @return Costo total del camino (suma de los costos de todos los arcos).
 *
 * @code
 * ListaArco camino = dijkstra(g, "A", "B");
 * int total = costoCamino(camino);
 * printf("Costo total: %d\n", total);
 * @endcode
 */
/***************************************************************/
int costoCamino(ListaArco camino)
{
    int costo = 0;
    while (camino != NULL)
    {
        costo += camino->costo;
        camino = camino->sig;
    }
    return costo;
}

/***************************************************************/
/**
 * @brief Menú interactivo para el Escenario 2: Caminos mínimos en un grafo de transporte.
 *
 * Permite al usuario encontrar caminos mínimos entre dos ubicaciones usando:
 * - Bellman-Ford (permite aristas con pesos negativos)
 * - Dijkstra (solo aristas con pesos positivos)
 *
 * El menú se repite hasta que el usuario elige regresar al menú principal.
 * El grafo h contiene aristas con pesos negativos y positivos, mientras que h2 es una copia solo con pesos positivos.
 *
 * @code
 * escenario2();
 * @endcode
 */
/***************************************************************/
void escenario2()

{

    Grafo h = crearGrafo();

    h = insertarVertice(h, "Central");
    h = insertarVertice(h, "Norte");
    h = insertarVertice(h, "Sur");
    h = insertarVertice(h, "Este");
    h = insertarVertice(h, "Oeste");
    h = insertarVertice(h, "Aeropuerto");
    h = insertarVertice(h, "Universidad");
    h = insertarVertice(h, "Hospital");
    h = insertarVertice(h, "Terminal");
    h = insertarVertice(h, "Industrial");

    h = insertarArco(h, "Central", "Norte", 4);
    h = insertarArco(h, "Central", "Sur", 6);
    ;
    h = insertarArco(h, "Norte", "Este", 5);
    h = insertarArco(h, "Sur", "Oeste", 3);
    h = insertarArco(h, "Este", "Universidad", 2);
    h = insertarArco(h, "Oeste", "Hospital", 2);
    h = insertarArco(h, "Universidad", "Aeropuerto", -2);
    h = insertarArco(h, "Hospital", "Terminal", 1);
    h = insertarArco(h, "Terminal", "Central", -4);
    h = insertarArco(h, "Aeropuerto", "Industrial", 3);
    h = insertarArco(h, "Industrial", "Sur", -1);

    Grafo h2 = crearGrafo();
    // El grafo h2 será una copia de h, pero con solo positivos, para usar siempre Dijkstra
    h2 = insertarVertice(h2, "Central");
    h2 = insertarVertice(h2, "Norte");
    h2 = insertarVertice(h2, "Sur");
    h2 = insertarVertice(h2, "Este");
    h2 = insertarVertice(h2, "Oeste");
    h2 = insertarVertice(h2, "Aeropuerto");
    h2 = insertarVertice(h2, "Universidad");
    h2 = insertarVertice(h2, "Hospital");
    h2 = insertarVertice(h2, "Terminal");
    h2 = insertarVertice(h2, "Industrial");

    h2 = insertarArco(h2, "Central", "Norte", 4);
    h2 = insertarArco(h2, "Central", "Sur", 6);
    h2 = insertarArco(h2, "Norte", "Este", 5);
    h2 = insertarArco(h2, "Sur", "Oeste", 3);
    h2 = insertarArco(h2, "Este", "Universidad", 2);
    h2 = insertarArco(h2, "Oeste", "Hospital", 2);
    h2 = insertarArco(h2, "Universidad", "Aeropuerto", 2);
    h2 = insertarArco(h2, "Hospital", "Terminal", 1);
    h2 = insertarArco(h2, "Terminal", "Central", 4);
    h2 = insertarArco(h2, "Aeropuerto", "Industrial", 3);
    h2 = insertarArco(h2, "Industrial", "Sur", 1);

    int opcion = 0;

    do
    {
        printf(ANSI_BOLD ANSI_COLOR_RED);
        printf("***************************************************\n");
        printf("*************** MENU ESCENARIO 2 ******************\n");
        printf("***************************************************\n\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_BOLD ANSI_COLOR_YELLOW);
        printf("\nIngresa una opcion:\n");
        printf(ANSI_COLOR_RESET);
        printf("1. Encontrar camino entre dos ubicaciones usando Bellman-Ford\n");
        printf("2. Encontrar camino entre dos ubicaciones usando Dijkstra\n");
        printf("3. Volver al menu principal\n\n");
        printf(ANSI_BOLD ANSI_COLOR_RED);
        printf("***************************************************\n");
        printf(ANSI_COLOR_RESET);
        printf("Opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n')
            ;

        switch (opcion)
        {
        case 1:
        {
            char origen[50], destino[50];
            printf("Ingrese el vertice de origen: ");
            fgets(origen, sizeof(origen), stdin);
            origen[strcspn(origen, "\n")] = 0;

            printf("Ingrese el vertice de destino: ");
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = 0;

            int existe_origen = 0, existe_destino = 0;
            ListaVertice v = h.v;
            while (v != NULL)
            {
                if (strcmp(v->dato, origen) == 0)
                    existe_origen = 1;
                if (strcmp(v->dato, destino) == 0)
                    existe_destino = 1;
                v = v->sig;
            }
            if (!existe_origen || !existe_destino)
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("Error: Uno o ambos vertices no existen en el grafo.\n");
                printf(ANSI_COLOR_RESET);
                pausarYLimpiar();
                break;
            }

            ListaArco camino = bellmanFord(h, origen, destino);
            if (camino != NULL)
            {
                char *formateado = formatearCamino(camino);
                printf("Camino encontrado:\n%s\n", formateado);
                if (tieneNegativos(camino))
                {
                    printf(ANSI_COLOR_YELLOW, ANSI_UNDERLINE);
                    printf("Advertencia: El camino contiene segmentos con ciclos negativos.\n");
                    printf(ANSI_COLOR_RESET);
                }
                printf("Costo total del camino: %d\n", costoCamino(camino));
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay camino entre %s y %s.\n", origen, destino);
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;
        }
        case 2:
            char origen[50], destino[50];
            printf("Ingrese el vertice de origen: ");
            fgets(origen, sizeof(origen), stdin);
            origen[strcspn(origen, "\n")] = 0;

            printf("Ingrese el vertice de destino: ");
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = 0;

            int existe_origen = 0, existe_destino = 0;
            ListaVertice v = h.v;
            while (v != NULL)
            {
                if (strcmp(v->dato, origen) == 0)
                    existe_origen = 1;
                if (strcmp(v->dato, destino) == 0)
                    existe_destino = 1;
                v = v->sig;
            }
            if (!existe_origen || !existe_destino)
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("Error: Uno o ambos vertices no existen en el grafo.\n");
                printf(ANSI_COLOR_RESET);
                pausarYLimpiar();
                break;
            }

            ListaArco camino = dijkstra(h2, origen, destino);
            if (camino != NULL)
            {
                char *formateado = formatearCamino(camino);
                printf("Camino encontrado:\n%s\n", formateado);
                printf("Costo total del camino: %d\n", costoCamino(camino));
                printf(ANSI_COLOR_YELLOW, ANSI_UNDERLINE);
                printf("Advertencia: No se estan tomando en cuenta los ciclos negativos, use Bellman-Ford si necesita considerar ciclos negativos.\n");
                printf(ANSI_COLOR_RESET);
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay camino entre %s y %s.\n", origen, destino);
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;

        case 3:
            printf("Regresando al menu principal...\n");
            system("cls");
            break;
        default:
            printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
            printf("Opcion no valida.\n");
            printf(ANSI_COLOR_RESET);
            pausarYLimpiar();
            break;
        }
    } while (opcion != 3);
}

/***************************************************************/
/**
 * @brief Formatea una red de arcos como una cadena de texto legible.
 *
 * Esta función toma una lista enlazada de arcos (por ejemplo, el resultado de Prim o Kruskal)
 * y construye una cadena donde cada línea representa un arco con el formato:
 * "origen -> destino (Costo: X Millones de pesos)".
 *
 * @param red Lista enlazada de arcos a formatear.
 * @return Cadena de texto con la red formateada. El usuario debe liberar la memoria con free().
 *
 * @code
 * ListaArco red = prim(g, "Bogota");
 * char *texto = formatearRed(red);
 * printf("%s", texto);
 * free(texto);
 * @endcode
 */
/***************************************************************/
char *formatearRed(ListaArco red)
{
    char *resultado = (char *)malloc(4096 * sizeof(char));
    resultado[0] = '\0';

    while (red != NULL)
    {
        char buffer[256];
        sprintf(buffer, "%s -> %s (Costo: %d Millones de pesos)\n", red->origen, red->destino, red->costo);
        strcat(resultado, buffer);
        red = red->sig;
    }
    return resultado;
}

/***************************************************************/
/**
 * @brief Menú interactivo para el Escenario 3: Árboles de expansión mínima en un grafo de ciudades.
 *
 * Permite al usuario aplicar los algoritmos de Prim y Kruskal para encontrar el árbol de expansión mínima
 * en una red de ciudades, mostrando los caminos y el costo total de la red resultante.
 *
 * Opciones del menú:
 * - Aplicar Prim a partir de "Bogota" y mostrar el árbol y su costo total.
 * - Aplicar Kruskal y mostrar el árbol y su costo total.
 * - Volver al menú principal.
 *
 * El menú se repite hasta que el usuario elige regresar al menú principal.
 *
 * @code
 * escenario3();
 * @endcode
 */
/***************************************************************/
void escenario3()
{

    Grafo i = crearGrafo();
    i = insertarVertice(i, "Bogota");
    i = insertarVertice(i, "Medellin");
    i = insertarVertice(i, "Villavicencio");
    i = insertarVertice(i, "Bucaramanga");
    i = insertarVertice(i, "Cali");
    i = insertarVertice(i, "Manizales");
    i = insertarVertice(i, "Pereira");
    i = insertarVertice(i, "Barranquilla");
    i = insertarVertice(i, "Cartagena");
    i = insertarVertice(i, "Cucuta");

    i = insertarArco(i, "Bogota", "Medellin", 8);
    i = insertarArco(i, "Bogota", "Villavicencio", 4);
    i = insertarArco(i, "Bogota", "Bucaramanga", 7);
    i = insertarArco(i, "Medellin", "Manizales", 2);
    i = insertarArco(i, "Medellin", "Pereira", 4);
    i = insertarArco(i, "Pereira", "Manizales", 1);
    i = insertarArco(i, "Bucaramanga", "Cucuta", 3);
    i = insertarArco(i, "Cali", "Manizales", 5);
    i = insertarArco(i, "Cali", "Pereira", 6);
    i = insertarArco(i, "Barranquilla", "Cartagena", 2);
    i = insertarArco(i, "Cartagena", "Medellin", 9);
    i = insertarArco(i, "Cucuta", "Villavicencio", 6);

    // Lo que debe hacer este programa es
    // 1. Aplicar Prim a partir de Bogota y mostrar el camino con costos, y su costo total
    // 2. Aplicar Kruskal a partir de cualquiera y mostrar el camino con costos, y su costo total

    int opcion = 0;

    do
    {
        printf(ANSI_BOLD ANSI_COLOR_MAGENTA);
        printf("***************************************************\n");
        printf("*************** MENU ESCENARIO 3 ******************\n");
        printf("***************************************************\n\n");
        printf(ANSI_COLOR_RESET);

        printf(ANSI_BOLD ANSI_COLOR_YELLOW);
        printf("\nIngresa una opcion:\n");
        printf(ANSI_COLOR_RESET);

        printf("1. Prim a partir de Bogota\n");
        printf("2. Kruskal\n");
        printf("3. Volver al menu principal\n\n");
        printf(ANSI_BOLD ANSI_COLOR_MAGENTA);
        printf("***************************************************\n");
        printf(ANSI_COLOR_RESET);

        printf("Opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');
        switch (opcion)
        {
        case 1:
        {
            ListaArco camino = prim(i, "Bogota");
            if (camino != NULL)
            {
                char *formateado = formatearRed(camino);

                printf("Camino encontrado:\n%s\n", formateado);
                printf("Costo total del camino: %d Millones de pesos\n", costoCamino(camino));
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay camino desde Bogota.\n");
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;
        }
        case 2:
        {
            ListaArco camino = kruskal(i);
            if (camino != NULL)
            {
                char *formateado = formatearRed(camino);
                printf("Camino encontrado:\n%s\n", formateado);
                printf("Costo total del camino: %d Millones de pesos\n", costoCamino(camino));
                free(formateado);
            }
            else
            {
                printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
                printf("No hay camino usando Kruskal.\n");
                printf(ANSI_COLOR_RESET);
            }
            pausarYLimpiar();
            break;
        }
        case 3:
            printf("Regresando al menu principal...\n");
            system("cls");
            break;
        default:
            printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
            printf("Opcion no valida.\n");
            printf(ANSI_COLOR_RESET);
            pausarYLimpiar();
            break;
        }
    } while (opcion != 3);
}

/***************************************************************/
/**
 * @brief Menú principal del programa.
 *
 * Muestra un menú interactivo que permite al usuario seleccionar uno de los escenarios disponibles:
 * - Escenario 1: Grafo de ubicaciones culturales.
 * - Escenario 2: Caminos mínimos en un grafo de transporte.
 * - Escenario 3: Árboles de expansión mínima en un grafo de ciudades.
 * - Salir del programa.
 *
 * El menú se repite hasta que el usuario elige la opción de salir.
 *
 * @code
 * menu();
 * @endcode
 */
/***************************************************************/
void menu()

{
    int opcion;
    do
    {
        printf(ANSI_BOLD ANSI_COLOR_CYAN);
        printf("***************************************************\n");
        printf("*************** MENU PRINCIPAL ********************\n");
        printf("***************************************************\n\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_BOLD ANSI_COLOR_YELLOW);
        printf("Selecciona un escenario:\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN);
        printf("1. Escenario 1\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RED);
        printf("2. Escenario 2\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_COLOR_MAGENTA);
        printf("3. Escenario 3\n");
        printf(ANSI_COLOR_RESET);
        printf("0. Salir\n\n");
        printf(ANSI_BOLD ANSI_COLOR_CYAN);
        printf("***************************************************\n");
        printf(ANSI_COLOR_RESET);
        printf("Opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n')
            ;

        switch (opcion)
        {
        case 1:
            system("cls");
            escenario1();
            break;
        case 2:
            system("cls");
            escenario2();
            break;
        case 3:
            system("cls");
            escenario3();
            break;
        case 0:
            system("cls");
            printf("Saliendo...\n");
            return;
        default:
            printf(ANSI_COLOR_BRIGHT_RED, ANSI_UNDERLINE);
            printf("Opcion no valida.\n");
            printf(ANSI_COLOR_RESET);
            pausarYLimpiar();
            break;
        }
    } while (opcion != 0);
}

/***************************************************************/
/**
 * @brief Función principal del programa.
 *
 * Punto de entrada del programa. Limpia la pantalla y muestra el menú principal para que el usuario
 * seleccione uno de los escenarios disponibles.
 *
 * @return 0 al finalizar la ejecución correctamente.
 *
 * @code
 * int main() {
 *     system("cls");
 *     menu();
 *     return 0;
 * }
 * @endcode
 */
/***************************************************************/
int main()
{
    system("cls");
    menu();
    return 0;
}