/*
================================================================================
Nombre del Archivo: taller_pilas.cpp
Descripción:
    Implementación de operaciones sobre pilas (estructura LIFO) utilizando nodos
    enlazados en C++. Se incluyen funciones para apilar, desapilar, mostrar, 
    destruir, invertir, buscar, comparar, eliminar, añadir, y distribuir elementos
    en las pilas.
================================================================================
*/

#include <stdlib.h>
#include <iostream>
using namespace std;

/*
================================================================================
Nombre de la estructura: nodo
Parámetros:
    - nro: Valor entero almacenado en el nodo.
    - sgte: Puntero al siguiente nodo en la pila.
Objetivo:
    Representar un elemento de la pila.
Retorno:
    No aplica, es una definición de estructura.
Funcionamiento:
    Cada nodo almacena un número y un enlace al siguiente nodo, formando así una 
    lista enlazada.
================================================================================
*/
struct nodo
{
    int nro;
    struct nodo *sgte;
};

/*
================================================================================
Nombre del typedef: ptrPila
Parámetros:
    No aplica.
Objetivo:
    Facilitar el manejo de punteros a nodos que representan una pila.
Retorno:
    No aplica, es un alias para "nodo *".
Funcionamiento:
    Se utiliza para declarar variables que apuntan al inicio de la pila.
================================================================================
*/
typedef nodo *ptrPila;

/*
================================================================================
Nombre de la función: push
Parámetros:
    - p: Referencia a la pila (puntero a nodo) donde se apilará el nuevo valor.
    - valor: Entero que se desea apilar.
Objetivo:
    Insertar un nuevo elemento en la cima de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea un nuevo nodo (aux).
    2. Se asigna el valor recibido al campo "nro" del nodo.
    3. El campo "sgte" del nuevo nodo apunta al tope actual de la pila.
    4. Se actualiza el tope de la pila para que sea el nuevo nodo.
================================================================================
*/
void push(ptrPila &p, int valor)
{
    ptrPila aux;
    aux = new (nodo);
    aux->nro = valor;
    aux->sgte = p;
    p = aux;
}

/*
================================================================================
Nombre de la función: pop
Parámetros:
    - p: Referencia a la pila (puntero a nodo) de la cual se desea desapilar.
Objetivo:
    Remover el elemento en la cima de la pila y retornarlo.
Retorno:
    El valor entero contenido en el nodo desapilado.
Funcionamiento:
    1. Se guarda el tope actual de la pila en un nodo auxiliar.
    2. Se extrae el valor del nodo auxiliar.
    3. Se actualiza el tope de la pila al siguiente nodo.
    4. Se libera la memoria del nodo desapilado.
    5. Se retorna el valor extraído.
================================================================================
*/
int pop(ptrPila &p)
{
    int num;
    ptrPila aux;
    aux = p;
    num = aux->nro;
    p = aux->sgte;
    delete (aux);
    return num;
}

/*
================================================================================
Nombre de la función: mostrar_pila
Parámetros:
    - p: Puntero a la pila que se desea mostrar.
Objetivo:
    Imprimir todos los elementos de la pila en la consola.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se utiliza un puntero auxiliar para recorrer la pila.
    2. En cada iteración se imprime el valor del nodo en el formato "[ valor ]".
    3. Se avanza al siguiente nodo hasta alcanzar el final (NULL).
================================================================================
*/
void mostrar_pila(ptrPila p)
{
    ptrPila aux = p;
    while (aux != NULL)
    {
        cout << "[ " << aux->nro << " ]" << endl;
        aux = aux->sgte;
    }
}

/*
================================================================================
Nombre de la función: mostrar_pila_encontrada
Parámetros:
    - p: Puntero a la pila que se desea mostrar.
    - valor: Valor que se desea resaltar en la impresión.
Objetivo:
    Mostrar la pila resaltando el elemento que coincida con el valor dado.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila con un puntero auxiliar.
    2. Si el valor del nodo es igual al valor buscado, se imprime resaltado 
       con la indicación "AQUI -> valor <- AQUI".
    3. Si no coincide, se imprime normalmente.
================================================================================
*/
void mostrar_pila_encontrada(ptrPila p, int valor)
{
    ptrPila aux = p;
    while (aux != NULL)
    {
        if (aux->nro == valor)
            cout << "[ AQUI -> " << aux->nro << " <- AQUI ]" << endl;
        else
            cout << "[ " << aux->nro << " ]" << endl;
        aux = aux->sgte;
    }
}

/*
================================================================================
Nombre de la función: destruir_pila
Parámetros:
    - p: Referencia a la pila que se desea destruir.
Objetivo:
    Liberar la memoria de todos los nodos de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila mientras no esté vacía.
    2. En cada iteración se guarda el nodo actual en un auxiliar.
    3. Se avanza el tope de la pila al siguiente nodo.
    4. Se libera la memoria del nodo almacenado en el auxiliar.
================================================================================
*/
void destruir_pila(ptrPila &p)
{
    ptrPila aux;
    while (p != NULL)
    {
        aux = p;
        p = aux->sgte;
        delete (aux);
    }
}

/*
================================================================================
Nombre de la función: invertir_pila
Parámetros:
    - p: Referencia a la pila que se desea invertir.
Objetivo:
    Invertir el orden de los elementos de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se crea una nueva pila auxiliar (nuevaPila) inicialmente vacía.
    2. Mientras la pila original no esté vacía, se desapila cada elemento y se 
       apila en la nueva pila.
    3. La nueva pila contendrá los elementos en orden inverso.
    4. Se asigna la nueva pila a la pila original.
================================================================================
*/
void invertir_pila(ptrPila &p)
{
    ptrPila nuevaPila = NULL;
    while (p != NULL)
    {
        int dato = pop(p);
        push(nuevaPila, dato);
    }
    p = nuevaPila;
}

/*
================================================================================
Nombre de la función: encontrar_elemento
Parámetros:
    - p: Puntero a la pila en la que se buscará el elemento.
    - valor: Valor que se desea encontrar en la pila.
Objetivo:
    Encontrar la posición (índice) del primer nodo que contenga el valor dado.
Retorno:
    Entero que representa la posición del elemento si se encuentra, o -1 si no se
    encuentra.
Funcionamiento:
    1. Se recorre la pila utilizando un puntero auxiliar y se lleva un contador 
       de posición.
    2. Si se encuentra un nodo cuyo valor coincide con el valor buscado, se retorna
       la posición actual.
    3. Si se recorre toda la pila sin encontrar el valor, se retorna -1.
================================================================================
*/
int encontrar_elemento(ptrPila p, int valor)
{
    ptrPila aux = p;
    int pos = 0;
    while (aux != NULL)
    {
        if (aux->nro == valor)
            return pos;
        pos++;
        aux = aux->sgte;
    }
    return -1;
}

/*
================================================================================
Nombre de la función: esta_ordenada
Parámetros:
    - p: Puntero a la pila que se desea verificar.
Objetivo:
    Verificar si la pila está ordenada de forma descendente, es decir, si cada 
    elemento es mayor que el siguiente.
Retorno:
    true si la pila está ordenada en forma descendente, false en caso contrario.
Funcionamiento:
    1. Si la pila está vacía o contiene un solo elemento, se considera ordenada.
    2. Se recorre la pila comparando cada nodo con su sucesor.
    3. Si se encuentra un nodo cuyo valor es menor o igual al de su siguiente, 
       la pila no está ordenada y se retorna false.
    4. Si no se encuentran inconsistencias, se retorna true.
================================================================================
*/
bool esta_ordenada(ptrPila p)
{
    if (p == NULL || p->sgte == NULL)
        return true;

    for (ptrPila aux = p; aux->sgte != NULL; aux = aux->sgte)
    {
        if (aux->nro <= aux->sgte->nro)
            return false;
    }
    return true;
}

/*
================================================================================
Nombre de la función: son_iguales
Parámetros:
    - p: Puntero a la primera pila.
    - q: Puntero a la segunda pila.
Objetivo:
    Comparar dos pilas para determinar si son iguales en longitud y en el orden de
    sus elementos.
Retorno:
    true si ambas pilas son iguales, false en caso contrario.
Funcionamiento:
    1. Se calcula la longitud de cada pila recorriéndolas con punteros auxiliares.
    2. Si las longitudes son diferentes, se retorna false.
    3. Si las longitudes son iguales, se comparan los valores de cada nodo en el
       mismo orden.
    4. Si todos los valores coinciden, se retorna true; de lo contrario, false.
================================================================================
*/
bool son_iguales(ptrPila p, ptrPila q)
{
    ptrPila aux1 = p;
    ptrPila aux2 = q;

    int pLength = 0;
    int qLength = 0;

    while (aux1 != NULL)
    {
        pLength++;
        aux1 = aux1->sgte;
    }
    while (aux2 != NULL)
    {
        qLength++;
        aux2 = aux2->sgte;
    }

    if (pLength != qLength)
    {
        return false;
    }
    else
    {
        aux1 = p;
        aux2 = q;

        while (aux1 != NULL)
        {
            if (aux1->nro != aux2->nro)
            {
                return false;
            }
            aux1 = aux1->sgte;
            aux2 = aux2->sgte;
        }
        return true;
    }
}

/*
================================================================================
Nombre de la función: eliminar_elemento
Parámetros:
    - p: Referencia a la pila de la cual se eliminarán las ocurrencias del elemento.
    - elemento: Valor del elemento que se desea eliminar.
Objetivo:
    Eliminar todas las ocurrencias del elemento especificado en la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila original y se construye una nueva pila (nueva) que 
       incluye solo los elementos distintos al valor especificado.
    2. Se destruye la pila original para liberar su memoria.
    3. Se reconstruye la pila original re-apilando los elementos de la nueva pila,
       preservando el orden original.
================================================================================
*/
void eliminar_elemento(ptrPila &p, int elemento){

    ptrPila aux = p;
    ptrPila nueva = NULL;
    
    while (aux != NULL){
        if(aux->nro != elemento){
            push(nueva, aux->nro);
        }
        aux = aux->sgte;
    }

    destruir_pila(p);

    while(nueva != NULL){
        push(p, pop(nueva));
    }
}

/*
================================================================================
Nombre de la función: añadir_elemento
Parámetros:
    - p: Referencia a la pila en la que se desea insertar el nuevo elemento.
    - elemento: Valor del elemento a añadir.
    - posicion: Posición en la que se desea insertar el nuevo elemento.
Objetivo:
    Insertar un nuevo elemento en una posición específica dentro de la pila.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila original y se va construyendo una nueva pila (nueva).
    2. Al alcanzar la posición indicada, se inserta el nuevo elemento.
    3. Se continúa copiando el resto de los elementos.
    4. Se destruye la pila original.
    5. Se reconstruye la pila original re-apilando los elementos de la nueva pila,
       de modo que se preserve el orden.
================================================================================
*/
void añadir_elemento(ptrPila &p, int elemento, int posicion){
    ptrPila aux = p;
    ptrPila nueva = NULL;
    int posActual = 0;

    while(aux != NULL){
        if(posActual == posicion){
            push(nueva, elemento);
        }
        push(nueva, aux->nro); 
        aux = aux -> sgte;
        posActual++;
    }

    if(posActual == posicion){
        push(nueva, elemento);
    }

    destruir_pila(p);

    while(nueva != NULL){
        push(p, pop(nueva));
    }
}

/*
================================================================================
Nombre de la función: distribuir_elementos
Parámetros:
    - p: Puntero a la pila original de donde se extraen los elementos.
    - p1: Referencia a la primera pila destino que recibirá los elementos menores 
          al valor dado.
    - p2: Referencia a la segunda pila destino que recibirá los elementos mayores o 
          iguales al valor dado.
    - valor: Valor de referencia para la distribución de los elementos.
Objetivo:
    Dividir la pila original en dos pilas, separando los elementos según si son
    menores o mayores/iguales al valor especificado.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se recorre la pila original.
    2. Si el valor del nodo es menor que el valor dado, se apila en p1; de lo 
       contrario, en p2.
    3. Se invierten ambas pilas (p1 y p2) para conservar el orden original.
================================================================================
*/
void distribuir_elementos(ptrPila p, ptrPila &p1, ptrPila &p2, int valor){

    ptrPila aux = p;

    while(aux != NULL){
        if(aux->nro < valor){
            push(p1, aux->nro);
        }
        else{
            push(p2, aux->nro);
        }
        aux = aux -> sgte;
    }

    invertir_pila(p1);
    invertir_pila(p2);
}

/*
================================================================================
Nombre de la función: pasar_valores
Parámetros:
    - original: Referencia a la pila original de la cual se copiarán los valores.
    - nueva: Referencia a la pila destino que se desea actualizar con los valores.
Objetivo:
    Copiar los valores de una pila (original) a otra (nueva), reemplazando los
    contenidos previos de la pila destino.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Se destruye la pila destino (nueva) para eliminar sus elementos previos.
    2. Se recorre la pila original y se apilan sus elementos en la pila destino.
    3. Se invierte la pila destino para preservar el orden original.
================================================================================
*/
void pasar_valores(ptrPila &original, ptrPila &nueva){

    ptrPila aux = original;
    destruir_pila(nueva);

    while(aux != NULL){
        push(nueva, aux->nro);
        aux = aux -> sgte;
    }

    invertir_pila(nueva);
}

/*
================================================================================
Nombre de la función: menu
Parámetros:
    Ninguno.
Objetivo:
    Mostrar en la consola las opciones disponibles para manipular las pilas.
Retorno:
    No retorna valores.
Funcionamiento:
    1. Imprime un encabezado y la lista numerada de opciones.
    2. Solicita al usuario ingresar la opción deseada.
================================================================================
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
    cout << "8. COMPROBAR SI 1 Y 2 SON IGUALES\n";
    cout << "9. ELIMINAR UN ELEMENTO X\n";
    cout << "10. AÑADIR UN ELEMENTO X\n";
    cout << "11. DIVIDIR UNA PILA EN DOS SEGUN SUS ELEMENTOS\n";
    cout << "12. SALIR\n";
    cout << "\nINGRESE OPCION: ";
}

/*
================================================================================
Nombre de la función: main
Parámetros:
    Ninguno.
Objetivo:
    Ejecutar el programa principal que permite manipular pilas mediante un menú
    interactivo.
Retorno:
    Un entero (0) indicando la finalización exitosa del programa.
Funcionamiento:
    1. Se declaran e inicializan las pilas principales (p y q) y auxiliares (p1 y p2).
    2. Se configura el color de la consola.
    3. Se ingresa en un ciclo do-while en el que se muestra el menú y se procesa 
       la opción ingresada por el usuario.
    4. Según la opción seleccionada, se invocan funciones para:
         - Apilar o desapilar un elemento.
         - Mostrar el contenido de una pila.
         - Destruir una pila.
         - Invertir una pila.
         - Buscar un elemento en la pila y mostrar su posición.
         - Verificar si la pila está ordenada en forma descendente.
         - Comparar dos pilas.
         - Eliminar un elemento específico.
         - Añadir un elemento en una posición determinada.
         - Distribuir los elementos de una pila en dos pilas según un valor de referencia.
    5. El ciclo continúa hasta que el usuario selecciona la opción de salir (12).
================================================================================
*/
int main()
{
    ptrPila p = NULL;
    ptrPila q = NULL;

    ptrPila p1 = NULL;
    ptrPila p2 = NULL;
    int dato;
    int op;
    int pila;
    system("color 0b"); // Configura el color de la consola

    do
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\nNUMERO A APILAR: ";
                cin >> dato;
                push(p, dato);
                cout << "\n\n\tNumero " << dato << " apilado...\n\n";
            }
            else if (pila == 2)
            {
                cout << "\nNUMERO A APILAR: ";
                cin >> dato;
                push(q, dato);
                cout << "\n\n\tNumero " << dato << " apilado...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        case 2:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\n\n\tNumero " << pop(p) << " desapilado...\n\n";
            }
            else if (pila == 2)
            {
                cout << "\n\n\tNumero " << pop(q) << " desapilado...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        case 3:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\n\nMOSTRANDO PILA\n\n";
                if (p != NULL)
                    mostrar_pila(p);
                else
                    cout << "\n\tPila Vacia..!\n\n";
                break;
            }
            else if (pila == 2)
            {
                cout << "\n\nMOSTRANDO PILA\n\n";
                if (q != NULL)
                    mostrar_pila(q);
                else
                    cout << "\n\tPila Vacia..!\n\n";
                break;
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
        case 4:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                destruir_pila(p);
                cout << "\n\n\tPila eliminada...\n\n";
            }
            else if (pila == 2)
            {
                destruir_pila(q);
                cout << "\n\n\tPila eliminada...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        case 5:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                invertir_pila(p);
                cout << "\n\n\tPila invertida...\n\n";
            }
            else if (pila == 2)
            {
                invertir_pila(q);
                cout << "\n\n\tPila invertida...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        case 6:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "ELEMENTO A BUSCAR: ";
                cin >> dato;
                int encontrado = encontrar_elemento(p, dato);
                if (encontrado != -1)
                {
                    cout << "El elemento fue encontrado en la posicion " << encontrado << endl;
                    mostrar_pila_encontrada(p, dato);
                }
                else
                {
                    cout << "El elemento no fue encontrado" << endl;
                }
            }
            else if (pila == 2)
            {
                cout << "ELEMENTO A BUSCAR: ";
                cin >> dato;
                int encontrado = encontrar_elemento(q, dato);
                if (encontrado != -1)
                {
                    cout << "El elemento fue encontrado en la posicion " << encontrado << endl;
                    mostrar_pila_encontrada(q, dato);
                }
                else
                {
                    cout << "El elemento no fue encontrado" << endl;
                }
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        }
        case 7:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                bool estaOrdenada = esta_ordenada(q);
                if (estaOrdenada)
                    cout << "La pila esta ordenada" << endl;
                else
                    cout << "La pila no esta ordenada" << endl;
                break;
            }
            else if (pila == 2)
            {
                bool estaOrdenada = esta_ordenada(q);
                if (estaOrdenada)
                    cout << "La pila esta ordenada" << endl;
                else
                    cout << "La pila no esta ordenada" << endl;
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        }
        case 8:
        {
            if (son_iguales(p, q) == true)
            {
                cout << "Las pilas son iguales" << endl;
            }
            else
            {
                cout << "Las pilas no son iguales" << endl;
            }
        }
        break;
        case 9:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if(pila == 1){
                cout<<"Ingresa el elemento a eliminar"<<endl;
                cin>>dato;
                if(encontrar_elemento(p, dato) == -1){
                    cout<<"El elemento no está en la pila"<<endl;
                }
                else{
                    eliminar_elemento(p, dato);
                    cout<<"El elemento ha sido eliminado"<<endl;
                }
            }
            else if(pila == 2){
                cout<<"Ingresa el elemento a eliminar"<<endl;
                cin>>dato;
                if(encontrar_elemento(q, dato) == -1){
                    cout<<"El elemento no está en la pila"<<endl;
                }
                else{
                    eliminar_elemento(q, dato);
                    cout<<"El elemento ha sido eliminado"<<endl;
                }
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        }
        case 10:
        {
            int posicion;

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if(pila == 1){
                cout<<"Ingresa el elemento a añadir"<<endl;
                cin>>dato;
                cout<<"Ingresa la posicion a añadir"<<endl;
                cin>>posicion;
                añadir_elemento(p, dato, posicion);
                cout<<"El elemento ha sido añadido"<<endl; 
                mostrar_pila_encontrada(p, dato);
            }
            else if (pila == 2){
                cout<<"Ingresa el elemento a añadir"<<endl;
                cin>>dato;
                cout<<"Ingresa la posicion a añadir"<<endl;
                cin>>posicion;
                añadir_elemento(q, dato, posicion);
                cout<<"El elemento ha sido añadido"<<endl; 
                mostrar_pila_encontrada(q, dato);
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        }
        case 11:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if(pila == 1){
                cout<<"Ingresa el valor"<<endl;
                cin>>dato;

                distribuir_elementos(p, p1, p2, dato);
                cout<<"Los elementos menores al valor se encuentran en esta pila"<<endl;
                mostrar_pila(p1);
                cout<<"Los demas elementos se encuentran en esta pila"<<endl;
                mostrar_pila(p2);

                cout<<"Quiere guardar estas pilas como 1 y 2? 1 para sí, otro para no"<<endl;
                cin>>dato;
                if(dato == 1){
                    pasar_valores(p1, p);
                    pasar_valores(p2, q);
                    cout<<"Se han guardado las pilas"<<endl;
                }
                else{
                    cout<<"Las pilas originales permanecen iguales"<<endl;
                }
            }
            else if(pila == 2){
                cout<<"Ingresa el valor"<<endl;
                cin>>dato;

                distribuir_elementos(q, p1, p2, dato);
                cout<<"Los elementos menores al valor se encuentran en esta pila"<<endl;
                mostrar_pila(p1);
                cout<<"Los demas elementos se encuentran en esta pila"<<endl;
                mostrar_pila(p2);

                cout<<"Quiere guardar estas pilas como 1 y 2? 1 para sí, otro para no"<<endl;
                cin>>dato;
                if(dato == 1){
                    pasar_valores(p1, p);
                    pasar_valores(p2, q);
                    cout<<"Se han guardado las pilas"<<endl;
                }
                else{
                    cout<<"Las pilas originales permanecen iguales"<<endl;
                }
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
        }
        break;
        case 12:
            cout<<"Saliendo"<<endl;
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    } while (op != 12 || !(op > 11));

    return 0;
}
