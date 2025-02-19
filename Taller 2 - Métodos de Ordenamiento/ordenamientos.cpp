#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>  
using namespace std;

/*
Nombre de la funcion:
    ImprimirVector
Parametros:
    *vec: Vector a ordenar
    len = Longitud del Vector
Objetivo:
    Imprimir los elementros de un vector.
Retorno:
    No retorna valores.
    dados.
Funcionamiento:
    1. Recibe un vector y su largo.
    2. Se abre el ciclo: "Mientras que el valor i (que empieza
    en el primer elemento del vector) sea menor a su largo...".
    3. Se imprime el elemento i del vector, y un espacio, para
    dar formato.
*/

int leerArchivo(int *a, int n) {
    int i = 0;
    char cadena[5];
    ifstream leer;
    leer.open("datos.txt");

    if (leer.good()) {
        cout << "El archivo fue abierto correctamente..." << endl;
    } else {
        cout << "El archivo no se pudo abrir..." << endl;
        return 0;  // Si el archivo no se pudo abrir, retorna 0
    }

    while (i < n) {
        leer >> cadena;  // Lee cada "palabra" del archivo
        *(a + i) = atof(cadena);  // Convierte la cadena a flotante y la guarda en el arreglo
        i++;
    }

    leer.close();  // Cierra el archivo
    return 1;  // Si todo fue bien, retorna 1
}


void ImprimirVector(int *vec, int len){
    for(int i = 0; i<len; i++){
        cout<<*(vec+i)<<" ";
    }
}

/*
Nombre de la funcion:
    Insercion
Parametros:
    *vec: Vector a ordenar
    len = Longitud del Vector
Objetivo:
    Ordenar los elementos de un vector haciendo
    uso del algoritmo de ordenamiento por insercion
    directa (de baraja).
Retorno:
    No retorna valores, pero modifica los parametros dados.
Funcionamiento:
    1. Recibe un vector y su largo.
    2. Se abre el ciclo: "Mientras que el valor i (que empieza
    en el segundo elemento del vector) sea menor a su largo...".
    3. Se define una variable temporal, que toma el valor del
    elemento a compararar con el vector.
    4. Se define la variable j, la cual sera igual al elemento
    anterior al que sera comparado.
    5. Se abre el ciclo "Mientras que j sea mayor o igual a 0, y
    si el elemento j (anterior a i) sea menor que el temporal...".
    6. Entonces se movera el valor de j hacia adelante, y se realizara
    la misma comparacion con el elemento anterior.
    7. Al salir del ciclo interior, se situa el temporal.
*/

void Insercion(int *vec, int len) {
    for (int i = 1; i < len; i++) {  
        int temp = *(vec+i);          
        int j = i - 1;                

        while (j >= 0 && *(vec+j) > temp) {
            *(vec+j+1) = *(vec+j);    
            j--;                  
        }
        *(vec+j+1) = temp;            
    }
}

/*
Nombre de la funcion:
    Burbuja
Parametros:
    *vec: Vector a ordenar
    len = Longitud del Vector
Objetivo:
    Ordenar los elementos de un vector haciendo
    uso del algoritmo de ordenamiento de burbuja.
Retorno:
    No retorna valores, pero modifica los parametros dados.
Funcionamiento:
    1. Abre el ciclo externo, que se encarga de pasar por
    la totalidad del vector.
    2. Abre el ciclo interno, que se ira reduciendo en cada
    iteracion.
    3. Se realiza la comparacion: "Si el elemento j del vector es
    mayor que el elemento j-1.."
    4. Se define una variable temporal, y se le da el valor del
    elemento j del vector. Haciendo uso de esta variable, se
    intercambian los valores de j y j-1.
*/

void Burbuja (int *vec, int len){
    for(int i = 1; i<len; i++){
        for (int j = 1; j<len-i+1; j++){          
            if(*(vec+j) < *(vec+j-1)){              
                int temp = *(vec+j);
                *(vec+j) = *(vec+j-1);
                *(vec+j-1) = temp;              
            }          
        }      
    }
}


/*
Nombre de la funcion:
    Partition
Parametros:
    *vec: Vector a ordenar parcialmente.
    low: indice inicial del subvector.
    high: indice final del subvector.
Objetivo:
    Reorganizar los elementos del vector en relacion con un pivote,
    ubicando los menores a su izquierda y los mayores a su derecha.
Retorno:
    Retorna la posicion final del pivote despues de la particion.
Funcionamiento:
    1. Se selecciona el ultimo elemento como pivote.
    2. Se inicializa un indice i para marcar la posicion del elemento mas pequeño.
    3. Se abre un ciclo para recorrer el subvector de low a high - 1:
    Si el elemento actual es menor o igual al pivote, se intercambia con i,
    y se incrementa i para avanzar la posicion del menor encontrado.
    4. Se intercambia el pivote con i, colocando el pivote en su posicion final.
    5. Se retorna la posicion i del pivote.
*/

int Partition(int *vec, int low, int high){
    int pivot = *(vec + high);
    int i = low;

    for(int j = low; j < high; j++){

        if(*(vec + j) <= pivot){
            int temp = *(vec + i);
            *(vec + i) = *(vec + j);
            *(vec + j) = temp;
            i++;
        }
    
    }

    int temp = *(vec + i);
    *(vec + i) = *(vec + high);
    *(vec + high) = temp;

    return i;
}

/*
Nombre de la funcion:
    Quicksort
Parametros:
    *vec: Vector a ordenar.
    low: indice inicial del subvector.
    high: indice final del subvector.
Objetivo:
    Ordenar los elementos del vector haciendo uso del algoritmo QuickSort.
Retorno:
    No retorna valores, pero modifica el vector en su lugar.
Funcionamiento:
    1. Se verifica que low sea menor que high para continuar con la recursion.
    2. Se llama a la funcion Partition para dividir el vector en dos partes:
    Elementos menores al pivote y elementos mayores al pivote.
    3. Se realiza la llamada recursiva de QuickSort en la parte izquierda del pivote.
    4. Se realiza la llamada recursiva de QuickSort en la parte derecha del pivote.
*/

void Quicksort(int *vec, int low, int high){
    if(low<high){
        int pi = Partition(vec, low, high);

        Quicksort(vec, low, pi - 1);
        Quicksort(vec, pi + 1, high);
    }
}

/*
Nombre de la funcion:
    Shellsort
Parametros:
    *vec: Vector a ordenar.
    len: Longitud del vector.
Objetivo:
    Ordenar los elementos del vector haciendo uso del algoritmo ShellSort.
Retorno:
    No retorna valores, pero modifica los parametros dados.
Funcionamiento:
    1. Se define la variable gap, que sera el tamaño del salto entre los elementos a comparar.
    2. Se abre un ciclo que se repetira mientras gap sea mayor a 0.
    3. Se abre un ciclo que recorrera el vector desde gap hasta el final.
    4. Se define una variable temporal que tomara el valor del elemento a comparar.
    5. Se define una variable j que tomara el valor de i.
    6. Se abre un ciclo que se repetira mientras j sea mayor o igual a gap y el elemento j-gap sea mayor que el temporal.

*/


void Shellsort(int *vec, int len) {
    for (int gap = len / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; i++) {
            int temp = *(vec + i);
            int j;
            for (j = i; j >= gap && *(vec+j-gap) > temp; j -= gap) {
                *(vec+j) = *(vec+j-gap);
            }
            *(vec+j) = temp;
        }
    }
}

/*
¿Como puedo medir el tiempo que tarda cada funcion en ejecutarse?
Para medir el tiempo que tarda cada funcion en ejecutarse, se puede hacer uso de la libreria <chrono> de C++.
Esta libreria permite medir el tiempo transcurrido entre dos puntos de un programa, y se puede utilizar para medir el tiempo que tarda en ejecutarse una funcion.

*/

void MainMenu(int *vec, int len){
    cout<<"¿Que algoritmo de ordenamiento usara?"<<endl;
    cout<<"1. Insercion directa "<<endl;
    cout<<"2. Burbuja "<<endl;
    cout<<"3. Quicksort "<<endl;
    cout<<"4. Shellsort "<<endl;
    cout<<"Ingrese el numero de la opcion que desea: ";

    int alg;
    cin>>alg;

    switch (alg)
    {
    case 1:
    {
        auto start = chrono::high_resolution_clock::now();
        Insercion(vec, len);
        auto end = chrono::high_resolution_clock::now();
        cout<<"El vector ordenado es:"<<endl;
        ImprimirVector(vec, len);
        cout<<endl;
        cout<<"El tiempo de ejecucion fue: "<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<<" milisegundos"<<endl;
        break;
    }
    case 2:
    {
        auto start2 = chrono::high_resolution_clock::now();
        Burbuja(vec, len);
        auto end2 = chrono::high_resolution_clock::now();
        cout<<"El vector ordenado es:"<<endl;
        //ImprimirVector(vec, len);
        cout<<endl;
        cout<<"El tiempo de ejecucion fue: "<<chrono::duration_cast<chrono::milliseconds>(end2-start2).count()<<" milisegundos"<<endl;
        break;
    }
    case 3:
    {
        auto start3 = chrono::high_resolution_clock::now();
        Quicksort(vec, 0, len-1);
        auto end3 = chrono::high_resolution_clock::now();
        cout<<"El vector ordenado es:"<<endl;
        ImprimirVector(vec, len);
        cout<<endl;
        cout<<"El tiempo de ejecucion fue: "<<chrono::duration_cast<chrono::milliseconds>(end3-start3).count()<<" milisegundos"<<endl;
        break;
    }
    case 4:
    {
        auto start4 = chrono::high_resolution_clock::now();
        Shellsort(vec, len);
        auto end4 = chrono::high_resolution_clock::now();
        cout<<"El vector ordenado es:"<<endl;
        ImprimirVector(vec, len);
        cout<<endl;
        cout<<"El tiempo de ejecucion fue: "<<chrono::duration_cast<chrono::milliseconds>(end4-start4).count()<<" "<<endl;
        break;
    }
    
    default:
        break;
    }


}


void PickLength(){
    cout<<"¿Cuantos elementos quiere que tenga el vector?"<<endl;
    cout<<"1. 100 "<<endl;
    cout<<"2. 1000 "<<endl;
    cout<<"3. 10000 "<<endl;
    cout<<"4. 100000 "<<endl;
    cout<<"5. 1000000 "<<endl;
    cout<<"Ingrese el numero de la opcion que desea: ";

    int lengthChoice;
    cin>>lengthChoice;
    int cant = 0;

    switch (lengthChoice)
    {
    case 1:
        cant = 100;
        break;
    case 2:
        cant = 1000;
        break;
    case 3:
        cant = 10000;
        break;
    case 4:
        cant = 100000;
        break;
    case 5:
        cant = 1000000;
        break;
    default:
        cout << "Opcion no valida. Saliendo..." << endl;
        return;
    }

    int *vec = new int[cant];

    if (leerArchivo(vec, cant)) { 
        cout<<"El vector original es:"<<endl;
        //ImprimirVector(vec, cant);
        cout<<endl;
        MainMenu(vec, cant);
    } else {
        cout << "Error al leer el archivo. Saliendo..." << endl;
    }

    delete[] vec; 
}


int main() {
    PickLength();
    return 0;  // Finaliza el programa
}