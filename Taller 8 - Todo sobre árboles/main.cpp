#include <iostream>
#include "abb.h"
#include "avl.h"
#include "rojonegro.h"

using namespace std;

// Declaración de menús
// Prototipos

void abbMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2);
void avlMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2);
void rojonegroMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2);
void multiplesABB(ABB &abb1, ABB &abb2, AVL &avl, ABB &abb, RBT &rbt);
void mainMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2);

    
void mainMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2)
{
    cout << "==========================\n";
    cout << "\n\t\tMENU PRINCIPAL\n\n";
    cout << "==========================\n";
    cout << " 1. ARBOL BINARIO DE BUSQUEDA (ABB)\n";
    cout << " 2. ARBOL AVL\n";
    cout << " 3. ARBOL ROJO-NEGRO\n";
    cout << " 4. MULTIPLES ARBOLES BINARIOS DE BUSQUEDA (ABB)\n";
    cout << " 5. SALIR\n";
    cout << "==========================\n";
    cout << "\n INGRESE OPCION: \n";
    cout << "==========================\n";

    int op = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 2:
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 3:
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 4:
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);
        break;
    case 5:
        system("cls");
        cout << "\n Saliendo del programa...\n";
        break;
    default:
        cout << "\n Opcion no valida. Intenta de nuevo.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        mainMenu(avl, abb, rbt, abb1, abb2);
        break;
    }
}

void abbMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2)
{
    ABB sub = NULL;
    cout << "==========================\n";
    cout << "\n\t\tARBOL BINARIO DE BUSQUEDA (ABB)\n\n";
    cout << "==========================\n";
    cout << " 1. INSERTAR ELEMENTO\n";
    cout << " 2. ELIMINAR ELEMENTO\n";
    cout << " 3. BUSCAR UN ELEMENTO\n";
    cout << " 4. VER EL ARBOL\n";
    cout << " 5. RECORRER EL ARBOL EN-ORDEN\n";
    cout << " 6. RECORRER EL ARBOL PRE-ORDEN\n";
    cout << " 7. RECORRER EL ARBOL POST-ORDEN\n";
    cout << " 8. CALCULAR EL PESO DE UN ARBOL\n";
    cout << " 9. CALCULAR LA ALTURA DE UN ARBOL\n";
    cout << " 10. CONTAR CUANTAS HOJAS TIENE UN NODO\n";
    cout << " 11. HALLAR EL PADRE DE UN NODO\n";
    cout << " 12. HALLAR EL TIO DE UN NODO\n";
    cout << " 13. VER SI UN ARBOL ESTA LLENO\n";
    cout << " 14. VER EL NIVEL DE UN NODO\n";
    cout << " 15. VER EL TODOS LOS ELEMENTOS EN UN NIVEL\n";
    cout << " 16. COMPROBAR SI DOS ELEMENTOS SON PRIMOS\n";
    cout << " 17. COMPROBAR SI UN ARBOL ES ESTABLE\n";
    cout << " 18. ELIMINAR UN ELEMENTO EN IN-ORDEN\n";
    cout << " 19. VOLVER AL MENU PRINCIPAL\n";
    cout << "==========================\n";
    cout << "\n INGRESE OPCION:\n ";
    cout << "==========================\n";

    int op = 0, dato = 0;
    int dato2 = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        cout << "\n NUMERO A INSERTAR: ";
        cin >> dato;
        insertar(abb, dato);
        cout << "\n NUMERO INSERTADO CON EXITO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 2:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (buscar(abb, dato) == 0)
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminar(abb, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 3:
        cout << "\n NUMERO A BUSCAR: ";
        cin >> dato;
        if (buscar(abb, dato) == 0)
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
            cout << "\n NUMERO ENCONTRADO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 4:
        cout << "\n\n\tARBOL ABB\n\n";
        verArbol(abb, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 5:
        enOrden(abb);
        cout << "\n\n\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 6:
        preOrden(abb);
        cout << "\n\n\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 7:
        postOrden(abb);
        cout << "\n\n\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 8:
        cout << "\n PESO DEL ARBOL: " << pesoArbol(abb, 0) << endl;
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 9:
        cout << "\n ALTURA DEL ARBOL: " << alturaDelArbol(abb) << endl;
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 10:
        cout << "\n NODO A BUSCAR: ";
        cin >> dato;
        sub = buscarNodo(abb, dato);
        if (!sub)
            cout << "\n NODO NO ENCONTRADO\n";
        else
        cout << "\n EL NODO TIENE " << nroHojas(sub, 0) << " HOJAS\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 11:
        cout << "\n NODO A BUSCAR: ";
        cin >> dato;
        if (!buscarNodo(abb, dato))
            cout << "\n NODO NO ENCONTRADO\n";
        else if (buscarPadre(abb, dato) == -1)
            cout << "\n EL NODO ES RAIZ, NO TIENE PADRE\n";
        else
            cout << "\n EL PADRE ES: " << buscarPadre(abb, dato) << endl;
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 12:
        cout << "\n NODO A BUSCAR: ";
        cin >> dato;
        if (!buscarNodo(abb, dato))
            cout << "\n NODO NO ENCONTRADO\n";
        else
            cout << "\n EL TIO ES: " << buscarTio(abb, dato) << endl;
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 13:
        if (estaLleno(abb))
            cout << "\n EL ARBOL ESTA LLENO\n";
        else
            cout << "\n EL ARBOL NO ESTA LLENO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 14:
        cout << "\n NODO A BUSCAR: ";
        cin >> dato;
        if (!buscarNodo(abb, dato))
            cout << "\n NODO NO ENCONTRADO\n";
        else
            cout << "\n EL NIVEL DEL NODO ES: " 
                << nivelDeNodo(abb, dato, 0) << endl;
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 15:
        cout << "\n NIVEL A BUSCAR: ";
        cin >> dato;
        cout << "\n LOS ELEMENTOS EN EL NIVEL " << dato << " SON: ";
        elementosEnElNivelBuscado(abb, dato, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 16:
        cout << "\n NUMERO 1: ";
        cin >> dato;
        cout << "\n NUMERO 2: ";
        cin >> dato2;
        if (sonPrimos(abb, dato, dato2))
            cout << "\n LOS NUMEROS SON PRIMOS ENTRE SI\n";
        else
            cout << "\n LOS NUMEROS NO SON PRIMOS ENTRE SI\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 17:
        if (esEstable(abb))
            cout << "\n EL ARBOL ES ESTABLE\n";
        else
            cout << "\n EL ARBOL NO ES ESTABLE\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 18:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (!buscar(abb, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminarInorden(abb, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 19:
        system("cls");
        mainMenu(avl, abb, rbt, abb1, abb2);
        break;
    default:
        cout << "\n Opcion no valida. Intenta de nuevo.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        abbMenu(avl, abb, rbt, abb1, abb2);
        break;
    }
}

void avlMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2)
{
    cout << "==========================\n";
    cout << "\n\t\tARBOL AVL\n\n";
    cout << "==========================\n";
    cout << " 1. INSERTAR ELEMENTO\n";
    cout << " 2. ELIMINAR ELEMENTO\n";
    cout << " 3. BUSCAR UN ELEMENTO\n";
    cout << " 4. VER EL ARBOL\n";
    cout << " 5. VOLVER AL MENU PRINCIPAL\n";
    cout << "==========================\n";
    cout << "\n INGRESE OPCION:\n ";
    cout << "==========================\n";

    int op = 0, dato = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        cout << "\n NUMERO A INSERTAR: ";
        cin >> dato;
        insertar(avl, dato);
        cout << "\n NUMERO INSERTADO CON EXITO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 2:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (!buscar(avl, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminarNodo(avl, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 3:
        cout << "\n NUMERO A BUSCAR: ";
        cin >> dato;
        if (!buscar(avl, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
            cout << "\n NUMERO ENCONTRADO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 4:
        cout << "\n\n\tARBOL AVL\n\n";
        verArbol(avl, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 5:
        system("cls");
        mainMenu(avl, abb, rbt, abb1, abb2);
        break;
    default:
        cout << "\n Opcion no valida. Intenta de nuevo.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        avlMenu(avl, abb, rbt, abb1, abb2);
        break;
    }
}

void rojonegroMenu(AVL &avl, ABB &abb, RBT &rbt, ABB &abb1, ABB &abb2)
{
    cout << "==========================\n";
    cout << "\n\t ARBOL ROJO-NEGRO\n\n";
    cout << "==========================\n";
    cout << " 1. INSERTAR ELEMENTO\n";
    cout << " 2. ELIMINAR ELEMENTO\n";
    cout << " 3. BUSCAR UN ELEMENTO\n";
    cout << " 4. VER EL ARBOL\n";
    cout << " 5. VOLVER AL MENU PRINCIPAL\n";
    cout << "==========================\n";
    cout << "\n INGRESE OPCION:\n ";
    cout << "==========================\n";

    int op = 0, dato = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        cout << "\n NUMERO A INSERTAR: ";
        cin >> dato;
        insertar(rbt, dato);
        cout << "\n NUMERO INSERTADO CON EXITO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 2:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (!buscar(rbt, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminar_rbt(rbt, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 3:
        cout << "\n NUMERO A BUSCAR: ";
        cin >> dato;
        if (buscar(rbt, dato) == 0)
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
            cout << "\n NUMERO ENCONTRADO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 4:
        cout << "\n\n\tARBOL ROJO-NEGRO\n\n";
        verArbol(rbt, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    case 5:
        system("cls");
        mainMenu(avl, abb, rbt, abb1, abb2);
        break;
    default:
        cout << "\n Opcion no valida. Intenta de nuevo.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        rojonegroMenu(avl, abb, rbt, abb1, abb2);
        break;
    }
}

void multiplesABB(ABB &abb1, ABB &abb2, AVL &avl, ABB &abb, RBT &rbt){
    cout << "==========================\n";
    cout << "\n\t\tDOS ARBOLES BINARIOS DE BUSQUEDA (ABB)\n\n";
    cout << "==========================\n";
    cout << " 1. AGREGAR UN ELEMENTO AL ARBOL 1\n";
    cout << " 2. AGREGAR UN ELEMENTO AL ARBOL 2\n";
    cout << " 3. ELIMINAR UN ELEMENTO DEL ARBOL 1\n";
    cout << " 4. ELIMINAR UN ELEMENTO DEL ARBOL 2\n";
    cout << " 5. VER EL ARBOL 1\n";
    cout << " 6. VER EL ARBOL 2\n";
    cout << " 7. COMPROBAR SI SON IGUALES\n";
    cout << " 8. COMPROBAR SI SON ISOMORFOS\n";
    cout << " 9. COMPROBAR SI TIENEN LOS MISMOS ELEMENTOS\n";
    cout << " 10. VOLVER AL MENU PRINCIPAL\n";
    cout << "==========================\n";
    cout << "\n INGRESE OPCION:\n ";
    cout << "==========================\n";

    int op = 0, dato = 0;
    cin >> op;

    switch (op)
    {
    case 1:
        cout << "\n NUMERO A INSERTAR: ";
        cin >> dato;
        insertar(abb1, dato);
        cout << "\n NUMERO INSERTADO CON EXITO\n";
        cout << "\nPresione ENTER para continuar...";

        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 2:
        cout << "\n NUMERO A INSERTAR: ";
        cin >> dato;
        insertar(abb2, dato);
        cout << "\n NUMERO INSERTADO CON EXITO\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 3:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (!buscar(abb1, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminar(abb1, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 4:
        cout << "\n NUMERO A ELIMINAR: ";
        cin >> dato;
        if (!buscar(abb2, dato))
            cout << "\n NUMERO NO ENCONTRADO\n";
        else
        {
            eliminar(abb2, dato);
            cout << "\n NUMERO ELIMINADO CON EXITO\n";
        }
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 5:
        cout << "\n\n\tARBOL 1\n\n";
        verArbol(abb1, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 6:
        cout << "\n\n\tARBOL 2\n\n";
        verArbol(abb2, 0);
        cout << "\n\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 7:
        if (sonIguales(abb1, abb2))
            cout << "\n LOS ARBOLES SON IGUALES\n";
        else
            cout << "\n LOS ARBOLES NO SON IGUALES\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 8:
        if (sonIsomorfos(abb1, abb2))
            cout << "\n LOS ARBOLES SON ISOMORFOS\n";
        else
            cout << "\n LOS ARBOLES NO SON ISOMORFOS\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 9:
        if (mismosElementos(abb1, abb2))
            cout << "\n LOS ARBOLES TIENEN LOS MISMOS ELEMENTOS\n";
        else
            cout << "\n LOS ARBOLES NO TIENEN LOS MISMOS ELEMENTOS\n";
        cout << "\nPresione ENTER para continuar...";
        cin.get();
        cin.ignore();
        system("cls");
        multiplesABB(abb1, abb2, avl, abb, rbt);

        break;
    case 10:
        system("cls");
        mainMenu(avl, abb, rbt, abb1, abb2);
        break;

    default:
        break;
    }
}

int main()
{
    AVL avl = NULL;  // Raiz del AVL
    ABB abb = NULL;  // Raiz del ABB
    RBT rbt = NULL;  // Raiz del RBT
    ABB abb1 = NULL; // Raiz del ABB1 (para ejercicios de múltiples árboles)
    ABB abb2 = NULL; // Raiz del ABB2 (para ejercicios de múltiples árboles)

    mainMenu(avl, abb, rbt, abb1, abb2);
    return 0;
}
