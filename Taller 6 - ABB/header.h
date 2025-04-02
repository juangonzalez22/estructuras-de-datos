#include <iostream>

using namespace std;

struct nodo {
    int nro;
    nodo *izq;
    nodo *der;
};

typedef nodo *ABB;

/*
Nombre de la función: crearNodo()
Objetivo: Crear y retornar un nuevo nodo para el árbol binario.
Parámetros:
    - int x: Valor a asignar en el nodo.
Variables:
    - ABB nuevoNodo: Puntero al nodo creado con el valor x.
Ejemplo de uso:
    ABB nodo = crearNodo(5);
*/
ABB crearNodo(int x)
{
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

//-------------------------------------------------------------------

/*
Nombre de la función: insertar()
Objetivo: Insertar un nuevo valor en el árbol binario.
Parámetros:
    - ABB &arbol: Referencia al árbol donde se insertará el valor.
    - int x: Valor a insertar.
Variables: N/A
Ejemplo de uso:
    insertar(miArbol, 10);
*/
void insertar(ABB &arbol, int x)
{
    if(arbol == NULL)
    {
        arbol = crearNodo(x);
    }
    else if(x < arbol->nro)
        insertar(arbol->izq, x);
    else if(x > arbol->nro)
        insertar(arbol->der, x);
}

//-------------------------------------------------------------------

/*
Nombre de la función: preOrden()
Objetivo: Recorrer el árbol binario en preorden y mostrar los nodos.
Parámetros:
    - ABB arbol: Puntero al árbol que se va a recorrer.
Variables: N/A
Ejemplo de uso:
    preOrden(miArbol);
*/
void preOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        cout << arbol->nro << " ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

//-------------------------------------------------------------------

/*
Nombre de la función: enOrden()
Objetivo: Recorrer el árbol binario en orden (inorden) y mostrar los nodos.
Parámetros:
    - ABB arbol: Puntero al árbol que se va a recorrer.
Variables: N/A
Ejemplo de uso:
    enOrden(miArbol);
*/
void enOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        enOrden(arbol->izq);
        cout << arbol->nro << " ";
        enOrden(arbol->der);
    }
}

//-------------------------------------------------------------------

/*
Nombre de la función: postOrden()
Objetivo: Recorrer el árbol binario en postorden y mostrar los nodos.
Parámetros:
    - ABB arbol: Puntero al árbol que se va a recorrer.
Variables: N/A
Ejemplo de uso:
    postOrden(miArbol);
*/
void postOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->nro << " ";
    }
}

//-------------------------------------------------------------------

/*
Nombre de la función: verArbol()
Objetivo: Mostrar visualmente la estructura del árbol binario de forma ordenada.
Parámetros:
    - ABB arbol: Puntero al árbol que se va a mostrar.
    - int n: Nivel de profundidad, usado para la indentación en la visualización.
Variables: N/A
Ejemplo de uso:
    verArbol(miArbol, 0);
*/
void verArbol(ABB arbol, int n)
{
    if(arbol == NULL)
        return;
    
    verArbol(arbol->der, n + 1);

    for(int i = 0; i < n; i++)
        cout << "   ";

    cout << arbol->nro << endl;

    verArbol(arbol->izq, n + 1);
}

//-------------------------------------------------------------------

/*
Nombre de la función: buscar()
Objetivo: Buscar un valor en el árbol binario.
Parámetros:
    - ABB arbol: Puntero al árbol en el cual buscar.
    - int dato: Valor a buscar.
Variables:
    - int r: Variable auxiliar para indicar si se encontró el valor (1) o no (0).
Ejemplo de uso:
    bool encontrado = buscar(miArbol, 7);
*/
bool buscar(ABB arbol, int dato)
{
    int r = 0;   // 0 indica que no se encontró, 1 indica que se encontró

    if(arbol == NULL)
        return r;

    if(dato < arbol->nro)
        r = buscar(arbol->izq, dato);
    else if(dato > arbol->nro)
        r = buscar(arbol->der, dato);
    else
        r = 1;   // dato igual al nodo actual, se encontró

    return r;
}

//-------------------------------------------------------------------

/*
Nombre de la función: eliminar()
Objetivo: Eliminar un nodo con el valor especificado del árbol binario.
Parámetros:
    - ABB &arbol: Referencia al árbol desde el cual se eliminará el nodo.
    - int x: Valor del nodo a eliminar.
Variables:
    - ABB aux1, aux2: Punteros auxiliares para ayudar en la reestructuración del árbol.
Ejemplo de uso:
    eliminar(miArbol, 5);
*/
void eliminar(ABB &arbol, int x)
{
    ABB aux1, aux2;
    if(arbol == NULL)
        return;
    
    if(x > arbol->nro)
        eliminar(arbol->der, x);
    if(x < arbol->nro)
        eliminar(arbol->izq, x);
    
    if(x == arbol->nro)
    {
        // Caso 1: Nodo hoja
        if(arbol->der == NULL && arbol->izq == NULL)
        {
            arbol = NULL;
            return;
        }
        // Caso 2: Nodo con solo hijo derecho
        if(arbol->der != NULL && arbol->izq == NULL)
        {
            arbol = arbol->der;
            return;
        }
        // Caso 3: Nodo con hijo izquierdo (o ambos hijos)
        aux1 = arbol;
        aux2 = arbol->izq;
        while(aux2->der != NULL)
        {
            aux1 = aux2;
            aux2 = aux2->der;
        }
        arbol->nro = aux2->nro;
        if(aux1 == arbol)
            arbol->izq = aux2->izq;
        else
            aux1->der = aux2->izq;
    }
}
