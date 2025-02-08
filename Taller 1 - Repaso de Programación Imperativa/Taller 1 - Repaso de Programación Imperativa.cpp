#include <iostream>
#include <string>

using namespace std;

/*
Ejercicio 1 
    Nombre de la función: ex1()
    Objetivo: Calcular la suma de todos los elementos de un vector.
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        sum = suma de los elementos del vector
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 2
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 2 3 4 5
        La suma de los elementos del vector es: 15

*/
void ex1()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    cout << "El vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec + i) << " ";
    }

    cout << endl;

    int sum = 0;

    for (int i = 0; i < length; i++)
    {
        sum += *(vec + i);
    }

    cout << "La suma de los elementos del vector es: " << sum << endl;

    delete[] vec;
}

/*
Ejercicio 2 
    Nombre de la función: ex2()
    Objetivo: Indicar si se encuentra un valor en el vector
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        num -> número a encontrar
        timesFound -> cantidad de veces que el num ha sido encontrado
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 4
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 4 3 4 5
        Ingrese el número a buscar: 4
        El número 4 se encontró 2 veces en el vector.

*/
void ex2()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    cout << "El vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec + i) << " ";
    }

    cout << endl;

    int num = 0;
    cout << "Ingrese el numero a buscar: ";
    cin >> num;
    int timesFound = 0;

    for (int i = 0; i < length; i++)
    {
        if (*(vec + i) == num)
        {
            timesFound++;
        }
    }
    cout << "El numero " << num << " se encontro " << timesFound << " veces en el vector." << endl;

    delete[] vec;
}

/*
Ejercicio 3
    Nombre de la función: ex3()
    Objetivo: Invertir una cadena apuntada
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        char *str = new char[100] -> puntero str, con 100 espacios de memoria reservada
        int length = 0 -> largo del str
        char *first = str -> puntero first, que señala al primer elemento de str
        char *last = str + length - 1 -> puntero last, que señala al último elemento de str
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese una cadena de texto: electroencefalografista
        La cadena invertida es: atsifargolafecnortcele

*/
void ex3()
{
    char *str = new char[100];
    cout << "Ingrese una cadena de texto: ";
    cin.ignore();
    cin.getline(str, 100);

    int length = 0;

    while (str[length] != '\0')
    {
        length++;
    }

    char *first = str;
    char *last = str + length - 1;

    while (first < last)
    {
        char temp = *first;
        *first = *last;
        *last = temp;
        first++;
        last--;
    }

    cout << "La cadena invertida es: " << str << endl;

    delete[] str;
}

/*
Ejercicio 4
    Nombre de la función: ex4()
    Objetivo: Invertir los elementos de un vector de N posiones, intercambiando el primero por el último y así
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        int *first = vec; -> puntero first, que apunta al primer elemento de vec
        int *last = vec + length - 1 -> puntero last, que apunta al último elemento de vec
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 2
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 2 3 4 5
        El vector invertido es: 5 4 3 2 1

*/
void ex4()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    int *first = vec;
    int *last = vec + length - 1;

    while (first < last)
    {
        char temp = *first;
        *first = *last;
        *last = temp;
        first++;
        last--;
    }

    cout << "El vector invertido es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec + i) << " ";
    }
    cout<<endl;

    delete[] vec;
}

/*
Ejercicio 5
    Nombre de la función: ex5()
    Objetivo: Informar la posición donde aparece por última vez un valor val en un vector
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        int val = 0 -> número a buscar
        int valLastPosition -> última posición de val
        bool elementExists = true -> booleano que revisa si el elemento existe
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 2
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 2 3 4 5
        Ingrese el valor a buscar: 3
        La última posición en la que se encontró el valor 3 es: 2

*/
void ex5()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    cout << "El vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec + i) << " ";
    }

    cout << endl;

    int val = 0;
    int valLastPosition;
    cout << "Ingrese el valor a buscar: ";
    cin >> val;

    bool elementExists = true;

    for (int i = 0; i < length; i++)
    {
        if (*(vec + i) == val)
        {
            elementExists = true;
        }
        else{
            elementExists = false;
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (*(vec + i) == val)
        {
            valLastPosition = i;
        }
    }

    if(elementExists == false){
        cout<<"El elemento "<<val<<" no esta en el vector."<<endl;
    }
    else{
        cout << "La ultima posicion en la que se encontro el valor " << val << " es: " << valLastPosition << endl;
    }



    delete[] vec;
}

/*
Ejercicio 6
    Nombre de la función: ex6()
    Objetivo: Determinar si dos vectores de N posiciones son iguales
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec1 = new int[length] -> puntero vec1, con length espacios de memoria reservada
        int *vec2 = new int[length] -> puntero vec2, con length espacios de memoria reservada
        int val = 0 -> número a buscar
        bool equal = true -> booleano que señala si es igual o no
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0 del primer vector: 1
        Ingrese el valor de la posición 1 del primer vector: 2
        Ingrese el valor de la posición 2 del primer vector: 3
        Ingrese el valor de la posición 3 del primer vector: 4
        Ingrese el valor de la posición 4 del primer vector: 5
        El primer vector es: 1 2 3 4 5
        Ingrese el valor de la posición 0 del segundo vector: 1
        Ingrese el valor de la posición 1 del segundo vector: 2
        Ingrese el valor de la posición 2 del segundo vector: 3
        Ingrese el valor de la posición 3 del segundo vector: 4
        Ingrese el valor de la posición 4 del segundo vector: 5
        El segundo vector es: 1 2 3 4 5
        Los vectores son iguales

*/
void ex6()
{
    int length;
    cout << "Ingrese la longitud de los vectores: ";
    cin >> length;
    int *vec1 = new int[length];
    int *vec2 = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << " del primer vector : ";
        cin >> *(vec1 + i);
    }

    cout << endl;

    cout << "El primer vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec1 + i) << " ";
    }

    cout << endl;

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << " del segundo vector : ";
        cin >> *(vec2 + i);
    }

    cout << endl;

    cout << "El segundo vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec2 + i) << " ";
    }

    cout << endl;

    bool equal = true;

    for (int i = 0; i < length; i++)
    {
        if (*(vec1 + i) == *(vec2 + i))
        {
            equal = true;
        }
        else
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        cout << "Los vectores son iguales." << endl;
    }
    else
    {
        cout << "Los vectores no son iguales." << endl;
    }

    delete[] vec1;
    delete[] vec2;
}

/*
Ejercicio 7
    Nombre de la función: ex7()
    Objetivo: Eliminar de un vextor todas las apariciones de un elemento dado
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        int val = 0 -> número a buscar
        int timesFound = 0 -> veces que aparece el número
        int newLength = length-timesFound -> nuevo largo
        int *newVec = new int[newLength] -> puntero newVec, con newLength espacios de memoria reservada
        int j=0 -> indice para recorrer
        bool elementExists = true -> booleano que revisa si el elemento existe
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 2
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 2 3 4 5
        Ingrese el valor a eliminar: 3
        El vector sin el valor 3 es: 1 2 4 5

*/
void ex7()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    cout << "El vector  es: ";
    for (int i = 0; i < length; i++)
    {
        cout << *(vec + i) << " ";
    }

    cout << endl;

    int val = 0;
    cout << "Ingrese el valor a eliminar: ";
    cin >> val;

    int timesFound = 0;

    for (int i = 0; i < length; i++)
    {
        if (*(vec + i) == val)
        {
            timesFound++;
        }
    }
    int newLength = length - timesFound;
    int *newVec = new int[newLength];

    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if (*(vec + i) != val)
        {
            *(newVec + j) = *(vec + i);
            j++;
        }
    }


    cout << "El vector sin el valor " << val << " es: ";
    for (int i = 0; i < newLength; i++)
    {
        cout << *(newVec + i) << " ";
    }

    cout<<endl;

    delete[] vec;
    delete[] newVec;
}

/*
Ejercicio 8
    Nombre de las funciones: ex8() y printVector(int *vec, int length)
    Objetivo: Imprimir un vector
    Parámetros:
        int *vec -> puntero del vector a imprimir
        int length -> largo del vector a imprimir
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 1
        Ingrese el valor de la posición 1: 2
        Ingrese el valor de la posición 2: 3
        Ingrese el valor de la posición 3: 4
        Ingrese el valor de la posición 4: 5
        El vector es: 1 2 3 4 5

*/
void printVector(int *vec, int length)
{
    if (length == 0)
    {
        return;
    }
    cout << *vec << " ";
    printVector(vec + 1, length - 1);
}


void ex8()
{
    int length;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int *vec = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec + i);
    }

    cout << "El vector  es: ";
    printVector(vec, length);
    cout<<endl;
}

/*
Ejercicio 9
    Nombre de las funciones: ex9() y recursiveBubbleSort(int *vec, int length)
    Objetivo: Reordenar todos los elementos de un vector
    Parámetros:
        int *vec -> puntero del vector a imprimir
        int length -> largo del vector a imprimir
    Variables:
        int length -> largo del vector
        int *vec = new int[length] -> puntero vec, con length espacios de memoria reservada
        int temp = valor temporal para reordenar
    No retorna nada, pero le muestra al usuario en la consola el resultado de su cálculo

    Ejemplo de uso:
        Ingrese la longitud del vector: 5
        Ingrese el valor de la posición 0: 5
        Ingrese el valor de la posición 1: 3
        Ingrese el valor de la posición 2: 4
        Ingrese el valor de la posición 3: 1
        Ingrese el valor de la posición 4: 2
        El vector es: 5 3 4 1 2
        El vector reordenado es: 1 2 3 4 5

*/

void recursiveBubbleSort(int *vec, int length){
    int temp;

    if(length == 1) return;

    for(int i = 0; i<length-1;i++){
        if(*(vec+i) > *(vec+i+1)){
            temp = *(vec+i);
            *(vec+i) = *(vec+i+1);
            *(vec+i+1) = temp;
        }
    }
    length--;
    recursiveBubbleSort(vec, length);
}

void ex9(){
    
    int length = 6;
    cout << "Ingrese la longitud del vector: ";
    cin >> length;
    int* vec = new int[length];

    for(int i = 0; i < length; i++){
        cout << "Ingrese el valor de la posicion " << i << ": ";
        cin >> *(vec+i);
    }

    cout << "El vector  es: ";
    for(int i = 0; i < length; i++){
        cout << *(vec+i) << " ";
    }
    cout<<endl;
    recursiveBubbleSort(vec, length);
    
    cout << "El vector reordenado es: ";
    for(int i = 0; i < length; i++){
        cout << *(vec+i) << " ";
    }
    cout<<endl;

    delete[] vec;
}


/*
Ejercicio 10
    Nombre de las funciones: ex10() y pause()
    Objetivo: Menu que llame a cada uno de los anteriores problemas
    No recibe parámetros, el usuario va insertando los datos
    Variables:
        selection = 0 -> El usuario elige la opción que quiere hacer

    Ejemplo de uso:
        ----------------------
        TALLER #1
        Repaso de programacion imperativa
        Presentado por Juan Jose Gonzalez Rios para Estructuras De Datos
        ----------------------
        1. Calcular la suma de todos los elementos de un vector
        2. Indicar si un elemento num se encuentra en un vector
        3. Invertir una cadena apuntada
        4. Intercambiar de lugar los elementos opuestos en un vector
        5. Informar la posicion donde aparece por ultima vez un valor val en un vector
        6. Determinar si dos vectores vec1 y vec2 de N posiciones son iguales
        7. Eliminar de un vector todas las apariciones de un elemento dado
        8. Elabore una rutina recursiva que permita imprimir todos los elementos de un vector
        9. Elabore una rutina recursiva que permita ordenar un vector de forma ascendente
        Otro. Salir del programa

        Ingrese la opcion que quiere ejecutar:
        ----------------------
*/

void pause() {
    cout<<"----------------------"<<endl;
    cout << "Presiona Enter para continuar..."<<endl;
    cout<<"----------------------"<<endl;
    cin.ignore();
    cin.get();
}


void ex10(){
    int selection = 0;
    cout<<"----------------------"<<endl;
    cout<<"TALLER #1"<<endl<<"Repaso de programacion imperativa"<<endl;
    cout<<"Presentado por Juan Jose Gonzalez Rios para Estructuras De Datos"<<endl;
    cout<<"----------------------"<<endl;

    cout<<endl;

    cout<<"1. Calcular la suma de todos los elementos de un vector"<<endl;
    cout<<"2. Indicar si un elemento num se encuentra en un vector"<<endl;
    cout<<"3. Invertir una cadena apuntada"<<endl;
    cout<<"4. Intercambiar de lugar los elementos opuestos en un vector"<<endl;
    cout<<"5. Informar la posicion donde aparece por ultima vez un valor val en un vector"<<endl;
    cout<<"6. Determinar si dos vectores vec1 y vec2 de N posiciones son iguales"<<endl;
    cout<<"7. Eliminar de un vector todas las apariciones de un elemento dado"<<endl;
    cout<<"8. Elabore una rutina recursiva que permita imprimir todos los elementos de un vector"<<endl;
    cout<<"9. Elabore una rutina recursiva que permita ordenar un vector de forma ascendente"<<endl;
    cout<<"Otro. Salir del programa"<<endl;
    cout<<endl<<"Ingrese la opcion que quiere ejecutar: "<<endl;
    cout<<"----------------------"<<endl;
    cin>>selection;
    cout<<"----------------------"<<endl;

    switch (selection)
    {
    case 1:
        ex1();
        pause();
        ex10();
        break;
    case 2:
        ex2();
        pause();
        ex10();
        break;
    case 3:
        ex3();
        pause();
        ex10();
        break;
    case 4:
        ex4();
        pause();
        ex10();
        break;
    case 5:
        ex5();
        pause();
        ex10();
        break;
    case 6:
        ex6();
        pause();
        ex10();
        break;
    case 7:
        ex7();
        pause();
        ex10();
        break;
    case 8:
        ex8();
        pause();
        ex10();
        break;
    case 9:
        ex9();
        pause();
        ex10();
        break;
    default:
    cout<<"Saliendo..."<<endl;
        break;
    }

}

// Funcion principal
int main()
{
    ex10();
}