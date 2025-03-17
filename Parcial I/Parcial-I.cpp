#include <stdlib.h>
#include <iostream>
using namespace std;

/*
================================================================================
Estructura: nodo
Parámetros (Miembros):
    int nro:
        Valor entero que almacena el nodo.
    struct nodo *sgte:
        Puntero que apunta al siguiente nodo en la estructura (cola o pila).
Objetivo:
    Representar un nodo para estructuras lineales (pila o cola).
Retorno:
    No retorna valores (estructura de datos).
Funcionamiento:
    Cada nodo almacena un entero y un puntero al siguiente nodo.
================================================================================
*/
struct nodo
{
    int nro;             // Valor almacenado en el nodo.
    struct nodo *sgte;   // Puntero al siguiente nodo.
};

/*
================================================================================
Tipo: ptrPila
Descripción:
    Se define ptrPila como un puntero a nodo. Se utilizará para gestionar las pilas.
================================================================================
*/
typedef nodo *ptrPila;

/*
================================================================================
Estructura: cola
Parámetros (Miembros):
    nodo *delante:
        Puntero que apunta al primer nodo (inicio) de la cola.
    nodo *atras:
        Puntero que apunta al último nodo (final) de la cola.
Objetivo:
    Representar una cola con punteros al inicio y al final.
Retorno:
    No retorna valores (estructura de datos).
Funcionamiento:
    La estructura permite acceder a ambos extremos para realizar operaciones de encolar y desencolar.
================================================================================
*/
struct cola
{
    nodo *delante; // Puntero al primer nodo de la cola.
    nodo *atras;   // Puntero al último nodo de la cola.
};

/*
================================================================================
Nombre de la función: encolar
Parámetros:
    struct cola &q:
        Referencia a la cola en la cual se va a encolar el elemento.
    int valor:
        Valor entero que se va a encolar.
Objetivo:
    Insertar un elemento al final de la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea dinámicamente un nuevo nodo y se asigna el valor.
    2. Si la cola está vacía, el nuevo nodo se convierte en el primero.
    3. En caso contrario, se enlaza al final de la cola.
    4. Se actualiza el puntero 'atras' para apuntar al nuevo nodo.
================================================================================
*/
void encolar(struct cola &q, int valor)
{
    struct nodo *aux = new (struct nodo); // Se crea un nuevo nodo.
    aux->nro = valor;                    // Se asigna el valor al nodo.
    aux->sgte = NULL;                    // Al ser el último, su siguiente es NULL.

    if (q.delante == NULL)               // Si la cola está vacía...
    {
        q.delante = aux;                 // El nuevo nodo es el primero.
    }
    else
    {
        (q.atras)->sgte = aux;           // Se enlaza el nuevo nodo al final.
    }
    q.atras = aux;                       // Se actualiza el puntero 'atras'.
}

/*
================================================================================
Nombre de la función: desencolar
Parámetros:
    struct cola &q:
        Referencia a la cola desde la cual se desencola el elemento.
Objetivo:
    Remover y retornar el primer elemento de la cola.
Retorno:
    int:
        Valor del nodo desencolado.
Funcionamiento:
    1. Se almacena en una variable el nodo del frente de la cola.
    2. Se extrae el valor y se actualiza el puntero 'delante'.
    3. Se libera la memoria del nodo removido.
================================================================================
*/
int desencolar(struct cola &q)
{
    int num;
    struct nodo *aux;

    aux = q.delante;         // Se apunta al primer nodo de la cola.
    num = aux->nro;          // Se obtiene el valor del nodo.
    q.delante = aux->sgte;   // Se actualiza el inicio de la cola.
    delete (aux);            // Se libera la memoria del nodo removido.

    return num;              // Se retorna el valor desencolado.
}

/*
================================================================================
Nombre de la función: muestraCola
Parámetros:
    struct cola q:
        Cola a mostrar (se pasa por valor para no modificar la original).
Objetivo:
    Mostrar en consola todos los elementos de la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    Se recorre la cola desde el nodo 'delante' hasta el final, imprimiendo cada valor.
================================================================================
*/
void muestraCola(struct cola q)
{
    struct nodo *aux;
    aux = q.delante;         // Se inicia en el primer nodo.
    while (aux != NULL)
    {
        cout << "[ " << aux->nro << " ] ";
        aux = aux->sgte;     // Se pasa al siguiente nodo.
    }
}

/*
================================================================================
Nombre de la función: vaciaCola
Parámetros:
    struct cola &q:
        Referencia a la cola que se desea vaciar.
Objetivo:
    Eliminar todos los nodos de la cola y liberar la memoria.
Retorno:
    No retorna valores.
Funcionamiento:
    Se recorre la cola eliminando cada nodo y, al final, se resetean los punteros 'delante' y 'atras'.
================================================================================
*/
void vaciaCola(struct cola &q)
{
    struct nodo *aux;
    while (q.delante != NULL)
    {
        aux = q.delante;         // Se apunta al primer nodo.
        q.delante = aux->sgte;     // Se actualiza el inicio de la cola.
        delete (aux);            // Se elimina el nodo.
    }
    q.delante = NULL;            // Se resetea el puntero 'delante'.
    q.atras = NULL;              // Se resetea el puntero 'atras'.
}

/*
================================================================================
Nombre de la función: push
Parámetros:
    ptrPila &p:
        Referencia a la pila sobre la que se va a apilar el elemento.
    int valor:
        Valor entero a insertar en la pila.
Objetivo:
    Insertar un nuevo elemento en la parte superior de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea un nuevo nodo con el valor proporcionado.
    2. Se enlaza el nodo al inicio de la pila.
    3. Se actualiza el puntero de la pila.
================================================================================
*/
void push(ptrPila &p, int valor)
{
    ptrPila aux;
    aux = new (nodo);         // Se crea un nuevo nodo.
    aux->nro = valor;         // Se asigna el valor.
    aux->sgte = p;            // El siguiente del nuevo nodo apunta a la cima actual.
    p = aux;                  // La cima de la pila se actualiza al nuevo nodo.
}

/*
================================================================================
Nombre de la función: pop
Parámetros:
    ptrPila &p:
        Referencia a la pila de la cual se extraerá el elemento.
Objetivo:
    Remover y retornar el elemento que se encuentra en la cima de la pila.
Retorno:
    int:
        Valor del elemento removido.
Funcionamiento:
    1. Se almacena el nodo de la cima en una variable auxiliar.
    2. Se extrae el valor del nodo.
    3. Se actualiza la cima de la pila y se libera la memoria del nodo removido.
================================================================================
*/
int pop(ptrPila &p)
{
    int num;
    ptrPila aux;
    aux = p;                 // Se apunta al nodo de la cima.
    num = aux->nro;          // Se extrae el valor.
    p = aux->sgte;           // La cima se actualiza al siguiente nodo.
    delete (aux);            // Se libera la memoria.
    return num;              // Se retorna el valor extraído.
}

/*
================================================================================
Nombre de la función: mostrar_pila
Parámetros:
    ptrPila p:
        Puntero a la pila que se desea mostrar.
Objetivo:
    Mostrar en consola todos los elementos de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    Se recorre la pila desde la cima hasta el final, imprimiendo cada elemento.
================================================================================
*/
void mostrar_pila(ptrPila p)
{
    ptrPila aux = p;         // Se copia el puntero de la cima.
    while (aux != NULL)
    {
        cout << "[ " << aux->nro << " ]" << endl;
        aux = aux->sgte;     // Se avanza al siguiente nodo.
    }
}

/*
================================================================================
Nombre de la función: destruir_pila
Parámetros:
    ptrPila &p:
        Referencia a la pila que se desea eliminar.
Objetivo:
    Liberar toda la memoria ocupada por la pila, destruyéndola.
Retorno:
    No retorna valores.
Funcionamiento:
    Se recorre la pila eliminando cada nodo y liberando la memoria asignada.
================================================================================
*/
void destruir_pila(ptrPila &p)
{
    ptrPila aux;
    while (p != NULL)
    {
        aux = p;             // Se apunta al nodo actual.
        p = aux->sgte;       // Se avanza al siguiente nodo.
        delete (aux);        // Se elimina el nodo actual.
    }
}

/*
================================================================================
Nombre de la función: invertir_pila
Parámetros:
    ptrPila &p:
        Referencia a la pila que se desea invertir.
Objetivo:
    Invertir el orden de los elementos de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea una nueva pila vacía.
    2. Se extraen todos los elementos de la pila original usando pop y se insertan en la nueva pila.
    3. La nueva pila contendrá los elementos en orden invertido.
================================================================================
*/
void invertir_pila(ptrPila &p)
{
    ptrPila nuevaPila = NULL;  // Se crea una pila auxiliar vacía.
    while (p != NULL)
    {
        int dato = pop(p);     // Se extrae el elemento de la cima de la pila original.
        push(nuevaPila, dato); // Se inserta en la nueva pila.
    }
    p = nuevaPila;             // Se asigna la nueva pila (invertida) a la original.
}

/*
================================================================================
Nombre de la función: eliminar_impares
Parámetros:
    ptrPila &p:
        Referencia a la pila de la cual se eliminarán los elementos impares.
Objetivo:
    Eliminar de la pila todos aquellos elementos que sean números impares.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila original y se transfieren los números pares a una nueva pila.
    2. Se destruye la pila original.
    3. Se reconstruye la pila original con los elementos pares en el orden correcto.
================================================================================
*/
void eliminar_impares(ptrPila &p)
{
    ptrPila aux = p;         // Puntero auxiliar para recorrer la pila.
    ptrPila nueva = NULL;    // Nueva pila para almacenar solo números pares.

    // Recorrer la pila y transferir los números pares.
    while (aux != NULL)
    {
        if (aux->nro % 2 == 0)
        {
            push(nueva, aux->nro); // Se guarda el número par en la nueva pila.
        }
        aux = aux->sgte;
    }

    destruir_pila(p);       // Se destruye la pila original.

    // Reconstruir la pila original con los números pares.
    while (nueva != NULL)
    {
        push(p, pop(nueva)); // Se apilan los elementos desde la nueva pila a la original.
    }

    invertir_pila(p);       // Se invierte la pila para restaurar el orden original.
}

/*
================================================================================
Nombre de la función: copiar_pila
Parámetros:
    ptrPila &original:
        Referencia a la pila original que se desea copiar.
    ptrPila &nueva:
        Referencia a la pila destino donde se almacenará la copia.
Objetivo:
    Realizar una copia exacta de la pila original en la pila 'nueva'.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila original apilando cada elemento en la pila 'nueva'.
    2. Se invierte la pila 'nueva' para que el orden de los elementos sea el mismo que en la original.
================================================================================
*/
void copiar_pila(ptrPila &original, ptrPila &nueva)
{
    ptrPila aux = original;  // Puntero auxiliar para recorrer la pila original.
    destruir_pila(nueva);    // Se limpia la pila destino antes de copiar.

    while (aux != NULL)
    {
        push(nueva, aux->nro); // Se copia el valor en la pila 'nueva'.
        aux = aux->sgte;
    }

    invertir_pila(nueva);    // Se invierte la pila copiada para mantener el orden original.
}

/*
================================================================================
Nombre de la función: es_palindromo
Parámetros:
    ptrPila p:
        Puntero a la pila que se desea verificar.
Objetivo:
    Determinar si la secuencia de elementos de la pila es un palíndromo.
Retorno:
    bool:
        Retorna true si la pila es palíndroma, false en caso contrario.
Funcionamiento:
    1. Se copia la pila original.
    2. Se compara la pila original con su versión invertida.
    3. Si todos los elementos coinciden en orden, la pila es palíndroma.
================================================================================
*/
bool es_palindromo(ptrPila p)
{
    ptrPila aux1 = p;
    ptrPila q = NULL;
    copiar_pila(p, q);       // Se crea una copia de la pila original.
    ptrPila aux2 = q;

    int pLength = 0;
    int qLength = 0;

    // Contar los elementos de la pila original.
    while (aux1 != NULL)
    {
        pLength++;
        aux1 = aux1->sgte;
    }
    // Contar los elementos de la copia.
    while (aux2 != NULL)
    {
        qLength++;
        aux2 = aux2->sgte;
    }

    if (pLength != qLength)  // Comprobación redundante de longitud.
    {
        return false;
    }
    else
    {
        aux1 = p;            // Se restablece el puntero a la pila original.
        copiar_pila(p, q);   // Se vuelve a copiar la pila.
        aux2 = q;
        invertir_pila(aux2); // Se invierte la copia para comparar en orden inverso.

        // Comparar elemento a elemento.
        while (aux1 != NULL)
        {
            if (aux1->nro != aux2->nro)
            {
                return false; // Si algún elemento no coincide, no es palíndromo.
            }
            aux1 = aux1->sgte;
            aux2 = aux2->sgte;
        }
        return true;         // Todos los elementos coinciden: es palíndromo.
    }
}

/*
================================================================================
Nombre de la función: agregar_elemento
Parámetros:
    struct cola &q:
        Referencia a la cola en la cual se agregará el nuevo elemento.
    int elemento:
        Valor del elemento a agregar.
    int posicion:
        Posición en la cola donde se insertará el elemento.
Objetivo:
    Insertar un elemento en una posición determinada de la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea una cola auxiliar vacía.
    2. Se recorre la cola original, encolando en la auxiliar los elementos y, cuando se alcanza la posición deseada, se inserta el nuevo elemento.
    3. Si la posición es al final, se inserta al concluir el recorrido.
    4. Se vacía la cola original y se transfiere el contenido de la auxiliar a la original.
================================================================================
*/
void agregar_elemento(struct cola &q, int elemento, int posicion)
{
    struct cola nueva;
    nueva.delante = nueva.atras = NULL; // Inicialización de la cola auxiliar.
    struct nodo *aux = q.delante;
    int posActual = 0;

    // Recorrer la cola original.
    while (aux != NULL)
    {
        if (posActual == posicion)
        {
            encolar(nueva, elemento); // Se inserta el nuevo elemento en la posición indicada.
        }
        encolar(nueva, aux->nro);     // Se transfiere el elemento actual.
        aux = aux->sgte;
        posActual++;
    }

    // Si la posición es al final de la cola.
    if (posActual == posicion)
    {
        encolar(nueva, elemento);
    }

    vaciaCola(q); // Se vacía la cola original.

    // Se transfiere todo el contenido de la cola auxiliar a la original.
    while (nueva.delante != NULL)
    {
        encolar(q, desencolar(nueva));
    }
}

/*
================================================================================
Nombre de la función: sumar_elementos
Parámetros:
    ptrPila p:
        Puntero a la pila cuyos elementos se desean sumar.
Objetivo:
    Calcular la suma de todos los elementos almacenados en la pila.
Retorno:
    int:
        Valor resultante de la suma de los elementos.
Funcionamiento:
    Se recorre la pila acumulando el valor de cada nodo y se retorna la suma total.
================================================================================
*/
int sumar_elementos(ptrPila p)
{
    ptrPila aux = p;  // Puntero auxiliar para recorrer la pila.
    int suma = 0;
    while (aux != NULL)
    {
        suma += aux->nro; // Se acumula el valor de cada nodo.
        aux = aux->sgte;
    }
    return suma;
}

/*
================================================================================
Nombre de la función: menu
Parámetros:
    Ninguno.
Objetivo:
    Mostrar en consola las opciones disponibles para manipular la pila y la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    Se imprime un menú interactivo que permite al usuario seleccionar la operación
    a realizar sobre la pila o la cola.
================================================================================
*/
void menu()
{
    cout << "\t PRIMER PARCIAL\n\n";
    cout << "1. APILAR" << endl;
    cout << "2. DESAPILAR" << endl;
    cout << "3. MOSTRAR PILA" << endl;
    cout << "4. VACIAR PILA" << endl;
    cout << "5. ENCOLAR" << endl;
    cout << "6. DESENCOLAR" << endl;
    cout << "7. MOSTRAR COLA" << endl;
    cout << "8. DESTRUIR COLA" << endl;
    cout << "9. ELIMINAR TODOS LOS ELEMENTOS IMPARES DE UNA PILA" << endl;
    cout << "10. VERIFICAR SI UNA PILA ES UN PALINDROMO" << endl;
    cout << "11. AGREGAR UN ELEMENTO A UNA COLA EN UNA POSICIoN DETERMINADA" << endl;
    cout << "12. SUMAR TODOS LOS ELEMENTOS DE UNA PILA" << endl;
    cout << "13. SALIR" << endl;

    cout << "\n INGRESE OPCION: ";
}

/*
================================================================================
Nombre de la función: main
Parámetros:
    Ninguno.
Objetivo:
    Función principal que ejecuta el menú interactivo para manipular la pila y la cola.
Retorno:
    int:
        Retorna 0 al finalizar la ejecución.
Funcionamiento:
    1. Inicializa la cola y la pila.
    2. Muestra el menú y lee la opción del usuario.
    3. Ejecuta la operación correspondiente (apilar, desapilar, encolar, desencolar, etc.).
    4. Repite hasta que se ingrese la opción de salida (en este caso, opción 13).
================================================================================
*/
int main()
{
    struct cola q;
    q.delante = NULL; // Inicializa el inicio de la cola.
    q.atras = NULL;   // Inicializa el final de la cola.

    int op = 0;       // Variable para almacenar la opción del menú.
    int dato = 0;     // Variable para almacenar los datos a procesar.
    int posicion = 0; // Variable para la posición al agregar en la cola.

    ptrPila p = NULL; // Inicializa la pila vacía.

    system("color 0b"); // Cambia el color de la consola.

    do
    {
        menu();        // Muestra el menú de opciones.
        cin >> op;     // Lee la opción ingresada por el usuario.

        switch (op)
        {
        case 1:
            cout << "\nNUMERO A APILAR: ";
            cin >> dato;
            push(p, dato);   // Se apila el número en la pila.
            cout << "\n\n\tNumero " << dato << " apilado...\n\n";
            break;

        case 2:
            cout << "\n\n\tNumero " << pop(p) << " desapilado...\n\n";
            break;

        case 3:
            cout << "\n\nMOSTRANDO PILA\n\n";
            if (p != NULL)
                mostrar_pila(p);  // Se muestra la pila si no está vacía.
            else
                cout << "\n\tPila Vacia..!\n\n";
            break;

        case 4:
            destruir_pila(p);      // Se destruye la pila.
            cout << "\n\n\tPila eliminada...\n\n";
            break;
        case 5:
            cout << "\nNUMERO A ENCOLAR: ";
            cin >> dato;
            encolar(q, dato);      // Se encola el número en la cola.
            cout << "\n\n\tNumero " << dato << " encolado...\n\n";
            break;

        case 6:
            cout << "\n\n\tNumero " << desencolar(q) << " desencolado...\n\n";
            break;

        case 7:
            cout << "\n\nMOSTRANDO COLA\n\n";
            if (q.delante != NULL)
                muestraCola(q);     // Se muestra la cola si no está vacía.
            else
                cout << "\n\tCola Vacia..!\n\n";
            break;

        case 8:
            vaciaCola(q);           // Se elimina la cola.
            cout << "\n\n\tCola eliminada...\n\n";
            break;
        case 9:
            eliminar_impares(p);    // Se eliminan los números impares de la pila.
            cout << "\n\n\tNumeros impares eliminados de la pila...\n\n";
            break;
        case 10:
            if (es_palindromo(p))
                cout << "\n\n\tLa pila es un palIndromo\n\n";
            else
                cout << "\n\n\tLa pila no es un palIndromo\n\n";
            break;
        case 11:
            cout << "\nNUMERO A ENCOLAR: ";
            cin >> dato;
            cout << "\nPOSICIÓN A ENCOLAR: ";
            cin >> posicion;
            agregar_elemento(q, dato, posicion); // Se inserta el elemento en la posición indicada.
            cout << "\n\n\tEl elemento ha sido agregado a la cola...\n\n";
            break;
        case 12:
            dato = sumar_elementos(p);           // Se suman los elementos de la pila.
            cout << "\n\n\tLa suma de todos los elementos de la cola es: " << dato << endl;
            break;
        default:
            cout << "\n\n\tOpcion no encontrada!\n" << endl;
        }

        cout << endl;
        system("pause");
        system("cls");
    } while (op != 13); // Se finaliza cuando se ingresa la opción 13.
}
