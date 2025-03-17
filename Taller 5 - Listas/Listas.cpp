#include <iostream>
#include <stdlib.h>
#include "listas.h"
using namespace std;

void menu1()
{
    cout<<"\n\t\tLISTA ENLAZADA SIMPLE\n\n";
    cout<<" 1. INSERTAR AL INICIO        "<<endl;
    cout<<" 2. INSERTAR AL FINAL         "<<endl;
    cout<<" 3. INSERTAR EN UNA POSICION  "<<endl;
    cout<<" 4. MOSTRAR LISTA             "<<endl;
    cout<<" 5. BUSCAR ELEMENTO           "<<endl;
    cout<<" 6. ELIMINAR ELEMENTO 'V'     "<<endl;
    cout<<" 7. ELIMINAR ELEMENTOS CON VALOR 'V'"<<endl;
    cout<<" 8. SALIR                     "<<endl;
    cout<<"\n INGRESE OPCION: ";
}
// ---------------------------------------------
//                Funcion Principal
// ---------------------------------------------
int main()
{
    Tlista lista = NULL;
    int op;       // opcion del menu
    int _dato;    // elemento a ingresar
    int pos;      // posicion a insertar
    system("color 0b");

    do
    {
        menu1();
        cin>> op;
        switch(op)
        {
            case 1: 
                cout<< "\n NUMERO A INSERTAR: ";
                cin>> _dato;
                insertarInicio(lista, _dato);
                break;

            case 2: 
                cout<< "\n NUMERO A INSERTAR: ";
                cin>> _dato;
                insertarFinal(lista, _dato);
                break;
        case 3: 
            cout<< "\n NUMERO A INSERTAR: ";
            cin>> _dato;
            cout<< " Posicion : ";
            cin>> pos;
            insertarElemento(lista, _dato, pos);
            break;

        case 4: 
            cout<< "\n\n MOSTRANDO LISTA\n\n";
            MostrarLista(lista);
            break;

        case 5: 
            cout<<"\n Valor a buscar: ";
            cin>> _dato;
            buscarElemento(lista, _dato);
            break;

        case 6: 
            cout<<"\n Valor a eliminar: ";
            cin>> _dato;
            eliminarElemento(lista, _dato);
            break;

        case 7: 
            cout<<"\n Valor repetido a eliminar: ";
            cin>> _dato;
            eliminaRepetidos(lista, _dato);
            break;}
            
        cout<<endl<<endl;
        system("pause");
        system("cls");
    }while(op!=8);
    system("pause");
    return 0;
}