/*
================================================================================
Nombre del Archivo: taller_colas.cpp
Descripción:
    Implementación de operaciones sobre colas (estructura FIFO) utilizando nodos
    enlazados en C++. Se incluyen funciones para encolar, desencolar, mostrar, 
    vaciar, invertir y comprobar el orden ascendente, con la elección de cola
    (q o r) dentro de cada opción del menú.
================================================================================
*/

#include <iostream>
#include <stdlib.h>
#include "colas.h"
using namespace std;

/*
================================================================================
Nombre de la función: menu
Parámetros:
    Ninguno.
Objetivo:
    Mostrar en consola las opciones disponibles para manipular la cola.
Retorno:
    No retorna valores.
Funcionamiento:
    Se imprime un menú interactivo que permite al usuario seleccionar la operación
    a realizar sobre la cola.
================================================================================
*/

void menu() {
    cout << "\t IMPLEMENTACION DE COLAS EN C++\n\n";
    cout << "1. ENCOLAR" << endl;
    cout << "2. DESENCOLAR" << endl;
    cout << "3. MOSTRAR COLA" << endl;
    cout << "4. VACIAR COLA" << endl;
    cout << "5. INVERTIR COLA" << endl;
    cout << "6. COMPROBAR ORDEN ASCENDENTE" << endl;
    cout << "7. COMPARAR DOS COLAS" << endl;
    cout << "8. ENCONTRAR UN ELEMENTO EN UNA COLA"<<endl;
    cout << "9. INSERTAR UN ELEMENTO" <<endl;
    cout << "10. INVERTIR COLA"<<endl;
    cout << "11. DISTRIBUIR ELEMENTOS"<<endl;
    cout << "\n INGRESE OPCION: ";
}

/*
================================================================================
Nombre de la función: main
Parámetros:
    Ninguno.
Objetivo:
    Ejecutar el programa principal que permite manipular la cola a través de un menú
    interactivo. En cada opción se solicita al usuario que elija la cola (1 o 2) a operar.
Retorno:
    Un entero (0) que indica la finalización exitosa del programa.
Funcionamiento:
    1. Se inicializan las colas q y r asignando NULL a sus punteros 'delante' y 'atras'.
    2. Se presenta un menú en un ciclo, permitiendo al usuario seleccionar la operación.
    3. Dentro de cada opción se solicita elegir la cola (1 para q, 2 para r) y se
       ejecuta la función correspondiente.
================================================================================
*/
int main() {
    struct cola q, r, a1, a2;
    q.delante = NULL;
    q.atras = NULL;
    r.delante = NULL;
    r.atras = NULL;
    a1.delante = NULL;
    a1.atras = NULL;
    a2.delante = NULL;
    a2.atras = NULL;

    int op;
    int dato;      
    int x;         
    int colaElegida;  

    system("color 0b");

    do {
        menu();
        cin >> op;
        switch(op) {
            case 1: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    cout << "\n NUMERO A ENCOLAR: ";
                    cin >> dato;
                    encolar(q, dato);
                    cout << "\n\tNumero " << dato << " encolado...\n\n";
                } else if (colaElegida == 2) {
                    cout << "\n NUMERO A ENCOLAR: ";
                    cin >> dato;
                    encolar(r, dato);
                    cout << "\n\tNumero " << dato << " encolado...\n\n";
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 2: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    x = desencolar(q);
                    cout << "\n\tNumero " << x << " desencolado\n\n";
                } else if (colaElegida == 2) {
                    x = desencolar(r);
                    cout << "\n\tNumero " << x << " desencolado\n\n";
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 3: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                cout << "\n\n MOSTRANDO COLA\n\n";
                if (colaElegida == 1) {
                    if (q.delante != NULL)
                        muestraCola(q);
                    else
                        cout << "\n\tCola vacia...!" << endl;
                } else if (colaElegida == 2) {
                    if (r.delante != NULL)
                        muestraCola(r);
                    else
                        cout << "\n\tCola vacia...!" << endl;
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 4: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    vaciaCola(q);
                    cout << "\n\n\tCola vaciada...\n\n";
                } else if (colaElegida == 2) {
                    vaciaCola(r);
                    cout << "\n\n\tCola vaciada...\n\n";
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 5: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    invierteCola(q);
                    cout << "\n\n\tCola q invertida...\n\n";
                } else if (colaElegida == 2) {
                    invierteCola(r);
                    cout << "\n\n\tCola r invertida...\n\n";
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 6: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    if (esAscendente(q))
                        cout << "La cola está ordenada ascendentemente" << endl;
                    else
                        cout << "La cola no está ordenada ascendentemente" << endl;
                } else if (colaElegida == 2) {
                    if (esAscendente(r))
                        cout << "La cola está ordenada ascendentemente" << endl;
                    else
                        cout << "La cola no está ordenada ascendentemente" << endl;
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 7:{
                if(sonIguales(q,r) == true) cout<<"Las colas son iguales"<<endl;
                else cout<<"Las colas no son iguales"<<endl;
            }
            case 8: {
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    //
                    cout<<"Ingresa el dato: ";
                    cin>>dato;
                    if(elementoPresente(q, dato) == true) cout <<"El elemento se encuentra presente en la cola"<<endl;
                    else cout<<"El elemento no se encuentra presente en la cola"<<endl;

                } else if (colaElegida == 2) {
                    //
                    cout<<"Ingresa el dato: ";
                    cin>>dato;
                    if(elementoPresente(r, dato) == true) cout <<"El elemento se encuentra presente en la cola"<<endl;
                    else cout<<"El elemento no se encuentra presente en la cola"<<endl;


                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;

            }
            case 9:{
                int posicion = 0;

                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    //
                    cout<<"Ingresa el elemento a insertar"<<endl;
                    cin>>dato;
                    cout<<"Ingresa la posición a insertar"<<endl;
                    cin>>posicion;
                    agregarElemento(q, dato, posicion);
                    cout<<"El dato se ha insertado en la posición indicada..."<<endl;
                    

                } else if (colaElegida == 2) {
                    //
                    cout<<"Ingresa el elemento a insertar"<<endl;
                    cin>>dato;
                    cout<<"Ingresa la posición a insertar"<<endl;
                    cin>>posicion;
                    agregarElemento(r, dato, posicion);
                    cout<<"El dato se ha insertado en la posición indicada..."<<endl;
                   


                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 10:{
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    invierteCola(q);
                    cout<<"Cola invertida...\n";

                } else if (colaElegida == 2) {
                    invierteCola(r);
                    cout<<"Cola invertida...\n";
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
            case 11:{
                cout << "INGRESA LA COLA (1 o 2):" << endl;
                cin >> colaElegida;
                if (colaElegida == 1) {
                    cout<<"Ingresa el valor a comparar:"<<endl;
                    cin>>dato;
                    distribuirElementos(q, a1, a2, dato);
                    cout<<"Los datos mayores que el valor han sido ubicados en la siguiente cola:"<<endl;
                    muestraCola(a1);
                    cout<<endl;
                    cout<<"Los demás datos han sido ubicados en la siguiente cola:"<<endl;
                    muestraCola(a2);

                } else if (colaElegida == 2) {
                    cout<<"Ingresa el valor a comparar:"<<endl;
                    cin>>dato;
                    distribuirElementos(r, a1, a2, dato);
                    cout<<"Los datos mayores que el valor han sido ubicados en la siguiente cola:"<<endl;
                    muestraCola(a1);
                    cout<<endl;
                    cout<<"Los demás datos han sido ubicados en la siguiente cola:"<<endl;
                    muestraCola(a2);
                    
                } else {
                    cout << "Esa cola no existe. Volviendo al menú." << endl;
                }
                break;
            }
        }
        cout << endl << endl;
        system("pause");
        system("cls");
    } while(op != 12);

    return 0;
}
