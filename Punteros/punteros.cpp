#include <iostream>

using namespace std;

int main(){

    int a = 10; // a es un entero, con valor 10, 
    int *puntero; // puntero es un puntero a un entero, pero no tiene valor asignado
    int *punteroAPuntero; // punteroAPuntero es un puntero a un puntero a un entero, pero no tiene valor asignado

    //Un puntero es una variable que almacena la direccion de memoria de otra variable

    puntero = &a; // puntero ahora apunta a la direccion de memoria de a

    cout << "Valor de a: " << a << endl;
    cout << "Direccion de a: " << &a << endl;
    cout << "Valor de puntero: " << puntero << endl;
    cout << "Direccion de puntero: " << &puntero << endl;
    cout << "Valor de punteroAPuntero: " << punteroAPuntero << endl;
    cout << "Direccion de punteroAPuntero: " << &punteroAPuntero << endl;
    cout << "Valor de a traves del puntero: " << *puntero << endl;


    return 0;
}