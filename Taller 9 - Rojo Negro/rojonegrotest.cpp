#include <iostream>
#include "rojonegro.h"

using namespace std;

int main(){
    RBT arbol = NULL;
    // 20, 10, 30, 40, 27, 35, 40, 50, 60, 67, 80, 62, 70, 83, 84, 85
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
    verArbol(arbol, 0);
    
}