#include <iostream>

using namespace std;

int main(){

    int a = 10; // a es un entero, con valor 10, 
    int *puntero; // puntero es un puntero a un entero, pero no tiene valor asignado

    puntero = &a; // puntero ahora apunta a la direccion de memoria de a

    cout << "Valor de a: " << a << endl;
    cout << "Direccion de a: " << &a << endl;
    cout << "Valor de puntero: " << puntero << endl;
    cout << "Direccion de puntero: " << &puntero << endl;
    cout << "Valor de a traves del puntero: " << *puntero << endl;

    return 0;
}