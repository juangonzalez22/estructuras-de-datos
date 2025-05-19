/**
 * @file main.cpp
 * @brief Programa principal que muestra un menu para interactuar con el arbol Rojo-Negro.
 *
 * Opciones disponibles:
 *  - Insertar un valor en el arbol.
 *  - Eliminar un valor del arbol.
 *  - Buscar un valor en el arbol.
 *  - Ver la representacion en consola del arbol.
 */

 #include <iostream>
 #include "rojonegro.h"  /**< @brief Incluye la implementacion del arbol Rojo-Negro. */
 
 using namespace std;
 
 /**
  * @brief Funcion principal con menu de operaciones para el arbol Rojo-Negro.
  *
  * Muestra un menu interactivo donde el usuario puede elegir:
  * 1. Insertar un numero
  * 2. Eliminar un numero
  * 3. Buscar un numero
  * 4. Ver el arbol
  * 5. Salir del programa
  *
  * @return int Codigo de salida (0 si todo va bien).
  */
 int main() {
     RBT arbol = NULL;  /**< @brief Puntero a la raiz del arbol. */
     int opcion = 0;    /**< @brief Seleccion del usuario en el menu. */
     int valor = 0;     /**< @brief Valor para operaciones de insercion, eliminacion o busqueda. */
 
     do {
         cout << "\n=== Menu arbol Rojo-Negro ===\n";
         cout << "1. Insertar un valor\n";
         cout << "2. Eliminar un valor\n";
         cout << "3. Buscar un valor\n";
         cout << "4. Ver arbol\n";
         cout << "5. Salir\n";
         cout << "Seleccione una opcion: ";
         cin >> opcion;
 
         switch (opcion) {
             case 1:
                 cout << "Ingrese el valor a insertar: ";
                 cin >> valor;
                 insertar(arbol, valor);
                 break;
             case 2:
                 cout << "Ingrese el valor a eliminar: ";
                 cin >> valor;
                 eliminar_rbt(arbol, valor);
                 break;
             case 3:
                 cout << "Ingrese el valor a buscar: ";
                 cin >> valor;
                 buscar(arbol, valor);
                 break;
             case 4:
                 cout << "\n--- Estado Actual del arbol ---\n";
                 verArbol(arbol, 0);
                 break;
             case 5:
                 cout << "Saliendo del programa...\n";
                 break;
             default:
                 cout << "Opcion invalida. Intente de nuevo.\n";
         }
 
     } while (opcion != 5);
 
     return 0;
 }
 