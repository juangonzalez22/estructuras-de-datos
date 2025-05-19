#include "avl.h"
#include <iostream>

using namespace std;

void menu() {
    cout << "\n\t\tARBOL AVL\n\n";
    cout << " 1. INSERTAR ELEMENTO\n";
    cout << " 2. ELIMINAR ELEMENTO\n";
    cout << " 3. BUSCAR UN ELEMENTO\n";
    cout << " 4. VER EL ARBOL\n";
    cout << " 5. SALIR\n";
    cout << "\n INGRESE OPCION: ";
}

int main() {
    AVL avl = NULL;   // Raiz del AVL
    int op = 0, dato = 0;
    system("color 0b");


    do {

        // 2) Muestra el menu y lee la opcion
        menu();
        cin >> op;

        // 3) Ejecuta la opcion elegida
        switch (op) {
            case 1:
                cout << "\n NUMERO A INSERTAR: ";
                cin >> dato;
                insertar(avl, dato);
                break;

            case 2:
                cout << "\n NUMERO A ELIMINAR: ";
                cin >> dato;
                eliminarNodo(avl, dato);
                break;

            case 3:
                cout << "\n NUMERO A BUSCAR: ";
                cin >> dato;
                buscar(avl, dato);
                break;

            case 4:
                cout << "\n\n\tARBOL AVL\n\n";
                verArbol(avl, 0);
                break;

            case 5:
                cout << "\n Saliendo del programa...\n";
                break;

            default:
                cout << "\n Opcion no valida. Intenta de nuevo.\n";
        }
        cout<<endl<<endl;
        system("pause");
        system("cls");

    } while (op != 5);
    system("pause");
    return 0;
}
