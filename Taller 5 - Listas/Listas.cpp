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
    cout<<" 8. BUSCAR CUANTAS VECES APARECE UN ELEMENTO V   "<<endl;
    cout<<" 9. INVERTIR LISTA"<<endl;
    cout<<" 10. PROMEDIO DE LOS ELEMENTOS DE LA LISTA"<<endl;
    cout<<" 11. BUSCAR EL MAYOR ELEMENTO DE LA LISTA"<<endl;
    cout<<" 12. VERIFICAR SI LA LISTA ESTA ORDENADA"<<endl;

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
            break;
        case 8:
            cout<<"\n Valor a buscar: ";
            cin>> _dato;
            cout<<"El valor aparece "<<cantidadElemento(lista, _dato)<<" veces en la lista."<<endl;
            break;
        case 9:
            invertirLista(lista);
            cout<<"\nLista invertida... ";
            break;
        case 10:
            _dato = promedioLista(lista);
            if(_dato == -1){
                cout<<"No hay elementos en la lista!"<<endl;
            }
            else{
                cout<<"El promedio de los elementos en la lista es de "<<_dato<<endl;
            }
            break;
        case 11:
            cout<<"El dato mayor en la lista es "<<datoMayor(lista)<<endl;
            break;
        case 12:
            if(estaOrdenada(lista)){
                cout<<"La lista esta ordenada."<<endl;
            }
            else{
                cout<<"La lista no esta ordenada."<<endl;
            }
            break;
        }
        
        
            
        cout<<endl<<endl;
        system("pause");
        system("cls");
    }while(op!=13);
    system("pause");
    return 0;
}