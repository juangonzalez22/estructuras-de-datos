#include <iostream>
#include "header.h"

using namespace std;


int main(){
    ABB arbol = NULL;
    insertar(arbol, 5);
    insertar(arbol, 17);
    insertar(arbol, 12);
    insertar(arbol, 8);
    insertar(arbol, 3);
    insertar(arbol, 9);
    insertar(arbol, 14);
    insertar(arbol, 9);
    insertar(arbol, 11);
    insertar(arbol, 8);
    insertar(arbol, 15);
    insertar(arbol, 10);
    insertar(arbol, 2);
    insertar(arbol, 8);
    insertar(arbol, 5);
    insertar(arbol, 14);
    insertar(arbol, 5);
    insertar(arbol, 1);
    insertar(arbol, 5);
    insertar(arbol, 18);
    preOrden(arbol);
    cout << endl;
    enOrden(arbol);
    cout << endl;
    postOrden(arbol);
    eliminar(arbol, 1);
    cout << endl;
    eliminar(arbol, 12);
    cout << endl;
    eliminar(arbol, 5);
    cout << endl;
    verArbol(arbol, 0);

}
