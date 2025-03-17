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
#include "pilas.h"
using namespace std;

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
