/*
================================================================================
Nombre de la estructura: nodo
Parámetros:
    - nro: Valor entero almacenado en el nodo.
    - sgte: Puntero al siguiente nodo en la cola.
Objetivo:
    Representar un elemento individual de la cola.
Retorno:
    No aplica, es una definición de estructura.
Funcionamiento:
    Cada nodo almacena un número y un puntero que enlaza con el siguiente nodo,
    permitiendo formar una lista enlazada que representa la cola.
================================================================================
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct nodo {
    int nro;
    struct nodo *sgte;
};

/*
================================================================================
Nombre de la estructura: cola
Parámetros:
    - delante: Puntero al primer nodo de la cola (frente de la cola).
    - atras: Puntero al último nodo de la cola (final de la cola).
Objetivo:
    Representar la estructura de una cola, facilitando las operaciones FIFO.
Retorno:
    No aplica, es una definición de estructura.
Funcionamiento:
    La estructura cola utiliza dos punteros para gestionar el acceso a sus elementos:
    uno para el frente (para desencolar) y otro para el final (para encolar).
================================================================================
*/
struct cola {
    nodo *delante;
    nodo *atras;
};

/*
================================================================================
Nombre de la función: encolar
Parámetros:
    - q: Referencia a la cola en la que se insertará el nuevo elemento.
    - valor: Entero que se desea insertar en la cola.
Objetivo:
    Insertar un nuevo elemento al final de la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea un nuevo nodo y se asigna el valor recibido.
    2. Se establece el puntero 'sgte' del nuevo nodo a NULL, ya que será el último.
    3. Si la cola está vacía (q.delante es NULL), el nuevo nodo se convierte en el
       primer elemento de la cola.
    4. Si la cola no está vacía, se enlaza el nuevo nodo al nodo que actualmente es
       el último (apuntado por q.atras).
    5. Se actualiza q.atras para que apunte al nuevo nodo.
================================================================================
*/
void encolar(struct cola &q, int valor) {
    struct nodo *aux = new(struct nodo);
    aux->nro = valor;
    aux->sgte = NULL;

    if(q.delante == NULL) {  // Cola vacía - primer elemento
        q.delante = aux;
    } else {
        (q.atras)->sgte = aux;
    }
    q.atras = aux;
}

/*
================================================================================
Nombre de la función: desencolar
Parámetros:
    - q: Referencia a la cola de la cual se extraerá el elemento.
Objetivo:
    Remover y retornar el elemento que se encuentra en el frente de la cola.
Retorno:
    Entero que contiene el valor del nodo removido.
Funcionamiento:
    1. Se guarda el nodo que está al frente de la cola en un auxiliar.
    2. Se extrae el valor almacenado en ese nodo.
    3. Se actualiza el puntero 'delante' de la cola para apuntar al siguiente nodo.
    4. Se libera la memoria del nodo removido.
    5. Se retorna el valor extraído.
================================================================================
*/
int desencolar(struct cola &q) {
    int num;
    struct nodo *aux;

    aux = q.delante;
    num = aux->nro;
    q.delante = aux->sgte;
    delete(aux);

    return num;
}

/*
================================================================================
Nombre de la función: muestraCola
Parámetros:
    - q: Cola que se desea mostrar.
Objetivo:
    Imprimir en consola todos los elementos de la cola, desde el frente hasta el final.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la cola utilizando un puntero auxiliar que comienza en q.delante.
    2. Se imprime el valor de cada nodo hasta llegar al final de la cola (NULL).
================================================================================
*/
void muestraCola(struct cola q) {
    struct nodo *aux;
    aux = q.delante;
    while(aux != NULL) {
        cout << " " << aux->nro;
        aux = aux->sgte;
    }
}

/*
================================================================================
Nombre de la función: vaciaCola
Parámetros:
    - q: Referencia a la cola que se desea vaciar.
Objetivo:
    Eliminar todos los elementos de la cola y liberar la memoria asignada.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la cola eliminando cada nodo de forma secuencial.
    2. Se actualizan los punteros 'delante' y 'atras' para reflejar que la cola está vacía.
================================================================================
*/
void vaciaCola(struct cola &q) {
    struct nodo *aux;
    while(q.delante != NULL) {
        aux = q.delante;
        q.delante = aux->sgte;
        delete(aux);
    }
    q.delante = NULL;
    q.atras = NULL;
}

/*
================================================================================
Nombre de la función: invierteCola
Parámetros:
    - q: Referencia a la cola que se desea invertir.
Objetivo:
    Invertir el orden de los elementos de la cola utilizando recursión.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Caso base: Si la cola está vacía, se termina la recursión.
    2. Se desencola el primer elemento y se guarda en una variable temporal.
    3. Se llama recursivamente a invierteCola para invertir el resto de la cola.
    4. Se reencola el elemento temporal, ubicándolo al final de la cola invertida.
================================================================================
*/
void invierteCola(struct cola &q) {
    if(q.delante == NULL) return;
    int temp = desencolar(q);
    invierteCola(q);
    encolar(q, temp);
}

/*
================================================================================
Nombre de la función: esAscendente
Parámetros:
    - q: Cola que se desea verificar.
Objetivo:
    Determinar si los elementos de la cola están ordenados en forma ascendente.
Retorno:
    true si la cola está ordenada ascendentemente, false en caso contrario.
Funcionamiento:
    1. Se recorre la cola utilizando un puntero auxiliar.
    2. Se comparan cada par de nodos consecutivos.
    3. Si algún nodo tiene un valor mayor que el siguiente, se retorna false.
    4. Si se recorre toda la cola sin encontrar desorden, se retorna true.
================================================================================
*/
bool esAscendente(struct cola q) {
    struct nodo *aux = q.delante;
    while(aux != NULL && aux->sgte != NULL) {
        if(aux->nro > aux->sgte->nro)
            return false;
        aux = aux->sgte;
    }
    return true;
}

/*
================================================================================
Nombre de la función: sonIguales
Parámetros:
    - q: Cola a comparar.
    - r: Otra cola a comparar.
Objetivo:
    Verificar si dos colas son iguales, es decir, contienen los mismos elementos en el mismo orden.
Retorno:
    true si las colas son iguales, false en caso contrario.
Funcionamiento:
    1. Se recorre cada cola para obtener su longitud.
    2. Se comparan las longitudes; si son distintas, se retorna false.
    3. Se recorre nuevamente cada cola comparando los elementos en el mismo orden.
    4. Si algún par de elementos es diferente, se retorna false; de lo contrario, se retorna true.
================================================================================
*/
bool sonIguales(struct cola q, struct cola r){
    struct nodo *aux1 = q.delante;
    struct nodo *aux2 = r.delante;

    int qLength = 0;
    int rLength = 0;

    while(aux1 != NULL) {
        qLength++;
        aux1 = aux1->sgte;
    }

    while(aux2 != NULL) {
        rLength++;
        aux2 = aux2->sgte;
    }

    if(qLength != rLength){
        return false;
    }

    while(aux1!=NULL && aux2!=NULL){
        if(aux1->nro!=aux2->nro){
            return false;
        }
        aux1 = aux1->sgte;
        aux2 = aux2->sgte;
    }

    return true;
}

/*
================================================================================
Nombre de la función: elementoPresente
Parámetros:
    - q: Cola en la que se buscará el elemento.
    - elemento: Valor entero que se desea buscar en la cola.
Objetivo:
    Determinar si un elemento específico está presente en la cola.
Retorno:
    true si el elemento se encuentra en la cola, false en caso contrario.
Funcionamiento:
    1. Se recorre la cola desde el frente hasta el final.
    2. Se compara el valor de cada nodo con el elemento buscado.
    3. Si se encuentra el elemento, se retorna true.
    4. Si se recorre toda la cola sin encontrarlo, se retorna false.
================================================================================
*/
bool elementoPresente(struct cola q, int elemento){
    struct nodo *aux;
    aux = q.delante;
    while(aux != NULL) {
        if(aux->nro == elemento) return true;
        aux = aux->sgte;
    }
    return false;
}

/*
================================================================================
Nombre de la función: agregarElemento
Parámetros:
    - q: Referencia a la cola en la que se agregará el elemento.
    - elemento: Valor entero que se desea agregar.
    - posicion: Posición en la que se insertará el nuevo elemento.
Objetivo:
    Insertar un nuevo elemento en una posición específica de la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea una cola auxiliar para reconstruir la cola original.
    2. Se recorre la cola original y se inserta el nuevo elemento en la posición indicada.
    3. Se vacía la cola original y se transfiere el contenido de la cola auxiliar de vuelta.
================================================================================
*/
void agregarElemento(struct cola &q, int elemento, int posicion){
    struct cola nueva;
    struct nodo *aux;
    int posActual = 0;
    

    while(aux != NULL) {
        if(posActual == posicion){
            encolar(nueva, elemento);
        }
        encolar(nueva, aux->nro);

        aux = aux->sgte;
        posActual++;
    }

    if(posActual == posicion){
        encolar(nueva, elemento);
    }


    vaciaCola(q);

    while(nueva.delante != NULL){
        encolar(q, desencolar(nueva));
    }

}

/*
================================================================================
Nombre de la función: distribuirElementos
Parámetros:
    - q: Cola de la cual se distribuirán los elementos.
    - a1: Referencia a la primera cola destino, donde se almacenarán los elementos mayores al valor.
    - a2: Referencia a la segunda cola destino, donde se almacenarán los elementos menores o iguales al valor.
    - valor: Valor de referencia para distribuir los elementos.
Objetivo:
    Distribuir los elementos de la cola original en dos colas diferentes según un valor de referencia.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se vacían las colas a1 y a2.
    2. Se recorre la cola original.
    3. Se encola en a1 los elementos mayores al valor y en a2 los elementos menores o iguales.
================================================================================
*/
void distribuirElementos(struct cola q, struct cola &a1, struct cola &a2, int valor){

    vaciaCola(a1);
    vaciaCola(a2);
    struct nodo *aux;
    a1.delante = NULL;
    a1.atras = NULL;
    a2.delante = NULL;
    a2.atras = NULL;

    aux = q.delante;

    while (aux != NULL)
    {
        if(aux->nro > valor){
            encolar(a1, aux->nro);
        }
        else{
            encolar(a2, aux->nro);
        }

        aux = aux->sgte;
    }
}
