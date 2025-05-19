#include <iostream>

using namespace std;

struct nodo {
    int nro;
    nodo *izq;
    nodo *der;
};

typedef nodo *ABB;

ABB crearNodo(int x)
{
    ABB nuevoNodo = new nodo();
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

void insertar(ABB &arbol, int x)
{
    if(arbol == NULL)
    {
        arbol = crearNodo(x);
    }
    else if(x < arbol->nro) {
        insertar(arbol->izq, x);
    }
    else if(x > arbol->nro) {
        insertar(arbol->der, x);
    }
}

void preOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        cout << arbol->nro << " ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void enOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        enOrden(arbol->izq);
        cout << arbol->nro << " ";
        enOrden(arbol->der);
    }
}

void postOrden(ABB arbol)
{
    if(arbol != NULL)
    {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->nro << " ";
    }
}

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

bool buscar(ABB arbol, int dato)
{
    int r = 0;
    if(arbol == NULL)
        return r;

    if(dato < arbol->nro)
        r = buscar(arbol->izq, dato);
    else if(dato > arbol->nro)
        r = buscar(arbol->der, dato);
    else
        r = 1;

    return r;
}

void eliminar(ABB &arbol, int x)
{
    ABB aux1, aux2;
    if(arbol == NULL)
        return;
    
    if(x > arbol->nro)
        eliminar(arbol->der, x);
    else if(x < arbol->nro)
        eliminar(arbol->izq, x);
    else
    {
        if (arbol->izq == NULL && arbol->der == NULL) {
            delete arbol;
            arbol = NULL;
            return;
        }
        if(arbol->der != NULL && arbol->izq == NULL)
        {
            ABB temp = arbol;
            arbol = arbol->der;
            delete temp;
            return;
        }
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
        delete aux2;
    }
}

int pesoArbol(ABB arbol, int peso)
{
    if (arbol == NULL)
        return peso;

    peso = pesoArbol(arbol->der, peso);
    peso++;
    peso = pesoArbol(arbol->izq, peso);

    return peso;
}

int nroHojas(ABB arbol, int nro)
{
    if (arbol == NULL)
        return nro;

    nro = nroHojas(arbol->der, nro);

    if (arbol->izq == NULL && arbol->der == NULL)
        nro++;

    nro = nroHojas(arbol->izq, nro);
    return nro;
}

int buscarPadre(ABB arbol, int dato)
{
    if (arbol == NULL)
        return -1;
    else if ((arbol->izq != NULL && arbol->izq->nro == dato) ||
             (arbol->der != NULL && arbol->der->nro == dato))
        return arbol->nro;
    else if (dato < arbol->nro)
        return buscarPadre(arbol->izq, dato);
    else
        return buscarPadre(arbol->der, dato);
}

ABB buscarNodoPadre(ABB arbol, int dato)
{
    if (arbol == NULL)
        return NULL;
    else if ((arbol->izq != NULL && arbol->izq->nro == dato) ||
             (arbol->der != NULL && arbol->der->nro == dato))
        return arbol;
    else if (dato < arbol->nro)
        return buscarNodoPadre(arbol->izq, dato);
    else
        return buscarNodoPadre(arbol->der, dato);
}

ABB buscarNodo(ABB arbol, int dato)
{
    if (arbol == NULL)
        return NULL;
    else if (arbol->nro == dato)
        return arbol;
    else if (dato < arbol->nro)
        return buscarNodo(arbol->izq, dato);
    else
        return buscarNodo(arbol->der, dato);
}

int alturaDelArbol(ABB arbol) {
    if (arbol == NULL)
        return 0;
    int altIzq = alturaDelArbol(arbol->izq);
    int altDer = alturaDelArbol(arbol->der);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int alturaDesdeNodo(ABB arbol, int dato) {
    ABB nodo = buscarNodo(arbol, dato);
    if (nodo == NULL)
        return -1;
    return alturaDelArbol(nodo);
}

int buscarTio(ABB arbol, int dato)
{
    ABB padre = buscarNodoPadre(arbol, dato);
    if (padre == NULL)
        return -1;
    ABB abuelo = buscarNodoPadre(arbol, padre->nro);
    if (abuelo == NULL)
        return -1;
    if (abuelo->izq == padre && abuelo->der != NULL)
        return abuelo->der->nro;
    else if (abuelo->der == padre && abuelo->izq != NULL)
        return abuelo->izq->nro;
    return -1;
}

bool sonIguales(ABB arbol1, ABB arbol2)
{
    if (arbol1 == NULL && arbol2 == NULL)
        return true;
    if (arbol1 == NULL || arbol2 == NULL)
        return false;
    return (arbol1->nro == arbol2->nro) &&
           sonIguales(arbol1->izq, arbol2->izq) &&
           sonIguales(arbol1->der, arbol2->der);
}

bool sonIsomorfos(ABB arbol1, ABB arbol2)
{
    if (arbol1 == NULL && arbol2 == NULL)
        return true;
    if (arbol1 == NULL || arbol2 == NULL)
        return false;
    return (sonIsomorfos(arbol1->izq, arbol2->izq) &&
            sonIsomorfos(arbol1->der, arbol2->der)) ||
           (sonIsomorfos(arbol1->izq, arbol2->der) &&
            sonIsomorfos(arbol1->der, arbol2->izq));
}

bool mismosElementos(ABB a, ABB b, bool validarPeso = true) {
    if (validarPeso && pesoArbol(a, 0) != pesoArbol(b, 0))
        return false;
    if (a == NULL)
        return true;
    if (!buscar(b, a->nro))
        return false;
    return mismosElementos(a->izq, b, false) && mismosElementos(a->der, b, false);
}

bool estaLleno(ABB arbol) {
    if (!arbol)
        return true;
    if ((arbol->izq == NULL) != (arbol->der == NULL))
        return false;
    return estaLleno(arbol->izq) && estaLleno(arbol->der);
}

int nivelDeNodo(ABB arbol, int dato, int nivel) {
    if (arbol == NULL)
        return -1;
    if (arbol->nro == dato)
        return nivel;
    if (dato < arbol->nro)
        return nivelDeNodo(arbol->izq, dato, nivel + 1);
    else
        return nivelDeNodo(arbol->der, dato, nivel + 1);
}

bool sonPrimos(ABB arbol, int dato1, int dato2) {
    ABB padre1 = buscarNodoPadre(arbol, dato1);
    ABB padre2 = buscarNodoPadre(arbol, dato2);
    if (padre1 == NULL || padre2 == NULL)
        return false;
    return (buscarNodoPadre(arbol, padre1->nro) == buscarNodoPadre(arbol, padre2->nro));
}

bool esEstable(ABB arbol) {
    if (arbol == NULL)
        return true;
    if (arbol->izq != NULL && arbol->izq->nro >= arbol->nro)
        return false;
    if (arbol->der != NULL && arbol->der->nro <= arbol->nro)
        return false;
    return esEstable(arbol->izq) && esEstable(arbol->der);
}

int mayorElemento(ABB arbol) {
    if (arbol == NULL)
        return -1;
    while (arbol->der != NULL)
        arbol = arbol->der;
    return arbol->nro;
}

void elementosEnElNivelBuscado(ABB arbol, int nivelBuscado, int nivelActual) {
    if (arbol == NULL)
        return;
    if (nivelActual == nivelBuscado)
        cout << arbol->nro << " ";
    else {
        elementosEnElNivelBuscado(arbol->izq, nivelBuscado, nivelActual + 1);
        elementosEnElNivelBuscado(arbol->der, nivelBuscado, nivelActual + 1);
    }
}

void eliminarInorden(ABB &arbol, int x) {
    if (!arbol)
        return;
    if (x < arbol->nro)
        eliminarInorden(arbol->izq, x);
    else if (x > arbol->nro)
        eliminarInorden(arbol->der, x);
    else {
        if (arbol->izq == NULL && arbol->der == NULL) {
            delete arbol;
            arbol = NULL;
        } else if (arbol->izq == NULL) {
            ABB tmp = arbol;
            arbol = arbol->der;
            delete tmp;
        } else if (arbol->der == NULL) {
            ABB tmp = arbol;
            arbol = arbol->izq;
            delete tmp;
        } else {
            int pred = mayorElemento(arbol->izq);
            arbol->nro = pred;
            eliminarInorden(arbol->izq, pred);
        }
    }
}
