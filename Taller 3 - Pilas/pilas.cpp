#include <stdlib.h>
#include <iostream>
using namespace std;

/*
 * Estructura nodo:
 * ----------------
 * Esta estructura define cada elemento (nodo) de la pila. Cada nodo contiene:
 *   - nro: Un valor entero que representa la información almacenada en el nodo.
 *   - sgte: Un puntero al siguiente nodo en la pila, permitiendo encadenar los elementos.
 */
struct nodo {
    int nro;
    struct nodo *sgte;
};

// Se define un alias "ptrPila" para apuntar a nodos, facilitando la manipulación de la pila.
typedef nodo* ptrPila;

/*
 * Nombre de la subrutina: push
 * Descripción: 
 *      La función 'push' se encarga de agregar un nuevo elemento a la pila. Para ello, reserva memoria para un nuevo nodo,
 *      asigna el valor recibido al campo 'nro' y enlaza este nodo al nodo que actualmente se encuentra en la cima de la pila.
 *      Luego, actualiza el puntero de la pila para que apunte a este nuevo nodo, convirtiéndolo en la nueva cima.
 *      Esta operación se realiza en tiempo constante (O(1)) y permite construir la pila de manera dinámica.
 * Parámetros:
 *      - p (ptrPila &): Referencia al puntero que representa la cima de la pila. Se modifica en la función, ya que
 *                        se actualiza para apuntar al nuevo nodo que se agrega.
 *      - valor (int): El número entero que se desea insertar en la pila. Este es el dato que se almacena en el nuevo nodo.
 * Retorno:
 *      - La función no devuelve ningún valor, ya que su función es modificar la estructura de la pila directamente.
 * Ejemplo de uso:
 *      ptrPila miPila = NULL;  // Se declara e inicializa una pila vacía.
 *      push(miPila, 10);       // Se agrega el número 10 a la cima de la pila.
 *
 * Notas adicionales:
 *      - Es fundamental asegurarse de liberar la memoria reservada en algún momento (por ejemplo, usando pop o destruir_pila)
 *        para evitar fugas de memoria.
 */
void push(ptrPila &p, int valor)
{
    ptrPila aux;
    aux = new(nodo);     // Reserva memoria para el nuevo nodo.
    aux->nro  = valor;   // Asigna el valor proporcionado al campo 'nro' del nuevo nodo.
    aux->sgte = p;       // Enlaza el nuevo nodo al nodo que estaba en la cima (puede ser NULL si la pila estaba vacía).
    p = aux;             // Actualiza la cima de la pila para que apunte al nuevo nodo.
}

/*
 * Nombre de la subrutina: pop
 * Descripción:
 *      La función 'pop' se encarga de eliminar el nodo que se encuentra en la cima de la pila y devolver su valor.
 *      Para ello, guarda temporalmente el puntero al nodo superior, extrae su valor, actualiza la cima de la pila
 *      para que apunte al siguiente nodo y finalmente libera la memoria del nodo eliminado. Esta operación también se
 *      realiza en tiempo constante (O(1)).
 * Parámetros:
 *      - p (ptrPila &): Referencia al puntero que representa la cima de la pila. Se modifica ya que la cima se actualiza
 *                        al nodo siguiente luego de eliminar el actual.
 * Retorno:
 *      - Devuelve un entero que representa el valor almacenado en el nodo que fue eliminado (desapilado).
 * Ejemplo de uso:
 *      int valorExtraido = pop(miPila);  // Elimina el nodo superior y almacena su valor en 'valorExtraido'.
 *
 * Consideraciones:
 *      - Es importante asegurarse de que la pila no esté vacía antes de llamar a esta función, ya que intentar
 *        desapilar de una pila vacía puede ocasionar errores o comportamientos inesperados.
 */
int pop(ptrPila &p)
{
    int num;
    ptrPila aux;

    aux = p;           // Guarda el puntero al nodo superior de la pila.
    num = aux->nro;    // Extrae el valor almacenado en el nodo superior.
    p   = aux->sgte;   // Actualiza la cima de la pila para que apunte al siguiente nodo.
    delete(aux);       // Libera la memoria asignada al nodo que fue desapilado.

    return num;        // Retorna el valor que se encontraba en el nodo eliminado.
}

/*
 * Nombre de la subrutina: mostrar_pila
 * Descripción:
 *      Esta función recorre la pila desde la cima hasta el final (donde el puntero es NULL) y muestra
 *      en la consola el valor almacenado en cada nodo. Es útil para visualizar de forma secuencial
 *      todos los elementos que componen la pila.
 * Parámetros:
 *      - p (ptrPila): Puntero que representa la cima de la pila. La función utiliza un puntero auxiliar
 *                     para recorrer la lista sin modificar la pila original.
 * Retorno:
 *      - No devuelve ningún valor; su función es mostrar los datos en la consola.
 * Ejemplo de uso:
 *      mostrar_pila(miPila);  // Imprime todos los valores de la pila, uno por línea, en la consola.
 *
 * Notas:
 *      - Si la pila está vacía (p es NULL), el ciclo no se ejecutará y no se mostrará ningún valor.
 */
void mostrar_pila(ptrPila p)
{
    ptrPila aux = p;   // Se crea un puntero auxiliar para recorrer la pila sin modificarla.
    while (aux != NULL)
    {
        cout << "[ " << aux->nro << " ]" << endl;  // Muestra el valor almacenado en el nodo actual.
        aux = aux->sgte;                           // Avanza al siguiente nodo.
    }
}


void mostrar_pila_encontrada(ptrPila p, int valor)
{
    ptrPila aux = p;  
    while (aux != NULL)
    {
        if(aux->nro == valor){
            cout << "[ AQUI -> " << aux->nro << " <- AQUI ]" << endl;  
        }
        else{
        cout << "[ " << aux->nro << " ]" << endl;  
        }
        aux = aux->sgte;                           
    }
}

/*
 * Nombre de la subrutina: destruir_pila
 * Descripción:
 *      La función 'destruir_pila' se encarga de eliminar todos los nodos de la pila, liberando la memoria
 *      asignada a cada uno. Recorre la pila y elimina cada nodo de forma secuencial, asegurándose de que
 *      no queden fugas de memoria al finalizar la ejecución del programa o cuando se requiera limpiar la estructura.
 * Parámetros:
 *      - p (ptrPila &): Referencia al puntero que representa la cima de la pila. Se modifica durante la
 *                        operación hasta que la pila queda vacía (p pasa a ser NULL).
 * Retorno:
 *      - No devuelve ningún valor, pues su único propósito es liberar la memoria de la pila.
 * Ejemplo de uso:
 *      destruir_pila(miPila);  // Elimina todos los elementos de la pila y libera la memoria asociada.
 *
 * Consideraciones:
 *      - Es buena práctica llamar a esta función antes de terminar el programa o cuando la pila ya no se necesite,
 *        para evitar pérdidas de memoria.
 */
void destruir_pila(ptrPila &p)
{
    ptrPila aux;
    while (p != NULL)
    {
        aux = p;         // Guarda el nodo actual.
        p   = aux->sgte; // Actualiza la cima de la pila para pasar al siguiente nodo.
        delete(aux);     // Libera la memoria del nodo actual.
    }
}


/*


*/
void invertir_pila(ptrPila &p){
    ptrPila nuevaPila = NULL;
    int dato;
    while( p != NULL){
        dato = p->nro;
        push(nuevaPila, dato);
        p = p->sgte;
        pop(p);
    }
    p = nuevaPila;

}


int encontrar_elemento(ptrPila p, int valor){
    ptrPila aux = p;
    int pos = 0;
    while(aux != NULL){
        if(aux->nro == valor){
            return pos;
        }
        pos++;
        aux = aux->sgte;
    }
    return -1;
}


bool esta_ordenada(ptrPila p){
    ptrPila aux = p;
    bool orden;

    while ((aux->sgte) != NULL)
    {
        if(aux->nro < (aux->sgte)->nro){
            orden = true;
        }
        else{
            orden = false;
            break;
        }
        aux = aux->sgte;
    }
}

/*
 * Nombre de la subrutina: menu
 * Descripción:
 *      Esta función muestra en la consola un menú interactivo con diversas opciones para que el usuario
 *      pueda manipular la pila. Las opciones incluyen:
 *          1. Apilar un nuevo elemento.
 *          2. Desapilar (eliminar) el elemento superior y mostrar su valor.
 *          3. Mostrar todos los elementos de la pila.
 *          4. Destruir la pila eliminando todos los nodos.
 *          5. Salir del programa.
 *      El menú se presenta de manera clara para guiar al usuario a través de las operaciones disponibles.
 * Parámetros:
 *      - No recibe parámetros.
 * Retorno:
 *      - No devuelve ningún valor, pues su función es únicamente mostrar el menú en la consola.
 * Ejemplo de uso:
 *      menu();  // Imprime el menú de opciones en la consola.
 *
 * Notas:
 *      - La función utiliza 'cout' para imprimir en la consola y no requiere interacción directa con el usuario
 *        (esta se realiza en la función 'main').
 */
void menu()
{
    cout << "\n\tIMPLEMENTACION DE PILAS EN C++\n\n";
    cout << "1. APILAR\n";
    cout << "2. DESAPILAR\n";
    cout << "3. MOSTRAR PILA\n";
    cout << "4. DESTRUIR PILA\n";
    cout << "5. INVERTIR PILA\n";
    cout << "6. ENCONTRAR UN ELEMENTO EN LA PILA\n";
    cout << "7. VERIFICAR SI ESTA ORDENADA ASCENDENTEMENTE\n";
    cout << "\nINGRESE OPCION: ";
}

/*
 * Nombre de la subrutina: main
 * Descripción:
 *      Función principal del programa que permite al usuario interactuar con una pila implementada con nodos enlazados.
 *      A través de un menú de opciones, el usuario puede:
 *          - Apilar (insertar) un nuevo elemento.
 *          - Desapilar (eliminar) el elemento en la cima y obtener su valor.
 *          - Mostrar el contenido completo de la pila.
 *          - Destruir la pila liberando la memoria de todos los nodos.
 *          - Salir del programa.
 *      El ciclo do-while permite que el usuario realice múltiples operaciones hasta que decida salir (opción 5).
 * Parámetros:
 *      - La función main no recibe parámetros desde la línea de comandos.
 * Retorno:
 *      - Devuelve 0 al finalizar la ejecución, indicando que el programa se ejecutó correctamente.
 * Ejemplo de uso:
 *      // Al compilar y ejecutar el programa, se desplegará el menú en la consola.
 *      // El usuario debe ingresar el número de la opción deseada y seguir las instrucciones.
 *      // Por ejemplo, ingresar 1 para apilar un número, 2 para desapilar, etc.
 *
 * Consideraciones:
 *      - La función utiliza 'system("color 0b")' para cambiar el color de la consola, lo cual es opcional y puede
 *        no funcionar en todos los entornos.
 *      - Se utilizan 'system("pause")' y 'system("cls")' para pausar y limpiar la pantalla respectivamente, 
 *        lo que es específico de algunos sistemas operativos (por ejemplo, Windows).
 */
int main()
{
    ptrPila p = NULL;  // Inicializa la pila como vacía (no hay nodos en la pila).
    int dato;          // Variable para almacenar el valor ingresado por el usuario para apilar.
    int op;            // Variable para almacenar la opción del menú seleccionada por el usuario.

    system("color 0b");  // Cambia el color de la consola (esto es opcional y específico de Windows).

    do {
        menu();         // Muestra el menú de opciones al usuario.
        cin >> op;      // Captura la opción seleccionada por el usuario.

        switch(op)
        {
            case 1:
                cout << "\nNUMERO A APILAR: ";
                cin >> dato;
                push(p, dato);   // Llama a la función 'push' para insertar el número en la pila.
                cout << "\n\n\tNumero " << dato << " apilado...\n\n";
                break;

            case 2:
                // Antes de llamar a 'pop', en una implementación robusta se debería verificar que la pila no esté vacía.
                cout << "\n\n\tNumero " << pop(p) << " desapilado...\n\n";
                break;

            case 3:
                cout << "\n\nMOSTRANDO PILA\n\n";
                if (p != NULL)
                    mostrar_pila(p);   // Llama a 'mostrar_pila' para imprimir todos los elementos.
                else
                    cout << "\n\tPila Vacia..!\n\n"; // Informa al usuario que la pila no contiene elementos.
                break;

            case 4:
                destruir_pila(p);      // Elimina todos los nodos de la pila y libera la memoria.
                cout << "\n\n\tPila eliminada...\n\n";
                break;
            case 5:
                invertir_pila(p);
                cout << "\n\n\tPila invertida...\n\n";
                break;
            case 6: {
                cout << "ELEMENTO A BUSCAR: ";
                cin >> dato;
                int encontrado = encontrar_elemento(p, dato);
                if(encontrado != -1) {
                    cout << "El elemento fue encontrado en la posicion " << encontrado << endl;
                    mostrar_pila_encontrada(p, dato);
                } else {
                    cout << "El elemento no fue encontrado" << endl;
                }
                break;
            }
            case 7: {
                bool estaOrdenada = esta_ordenada(p);
                if(estaOrdenada)
                    cout << "La pila esta ordenada" << endl;
                else
                    cout << "La pila no esta ordenada" << endl;
                break;
            }
                
        }

        cout << endl;
        system("pause");  // Pausa la ejecución para que el usuario pueda ver los resultados de la operación.
        system("cls");    // Limpia la pantalla de la consola para mostrar nuevamente el menú.
    } while (op != 8);    // El ciclo continúa hasta que el usuario ingrese la opción 6 para salir.

    return 0;  // Finaliza el programa indicando que todo se ejecutó correctamente.
}
