#include <iostream>
#include "header.h"

using namespace std;
int main()
{
    ABB arbol = NULL;
    // 10, 8, 15, 18, 14, 20, 3, 4, 2, 9, 20, 25, 7, 16, 29, 28, 26
    insertar(arbol, 10);
    insertar(arbol, 8);
    insertar(arbol, 15);
    insertar(arbol, 18);
    insertar(arbol, 14);
    insertar(arbol, 20);
    insertar(arbol, 3);
    insertar(arbol, 4);
    insertar(arbol, 2);
    insertar(arbol, 9);
    insertar(arbol, 20);
    insertar(arbol, 25);    
    insertar(arbol, 7);
    insertar(arbol, 16);
    insertar(arbol, 29);
    insertar(arbol, 28);
    insertar(arbol, 26);
    // Ver el árbol
    cout << "El árbol es el siguiente: " << endl;
    verArbol(arbol, 0);

    
}