#include <iostream>
#include <stdlib.h>

using namespace std;

//-------------------------------------------
struct nodo{
    int nro;  // en este caso es un numero entero
    struct nodo *sgte;
};
typedef struct nodo *Tlista;
typedef nodo *ptrPila;

void push(ptrPila &p, int valor)
{
    ptrPila aux;
    aux = new (nodo);
    aux->nro = valor;
    aux->sgte = p;
    p = aux;
}
int pop(ptrPila &p)
{
    int num;
    ptrPila aux;
    aux = p;
    num = aux->nro;
    p = aux->sgte;
    delete (aux);
    return num;
}


//-------------------------------------------
void insertarInicio(Tlista &lista, int valor)
{
    Tlista q;
    q = new(struct nodo);
    q->nro = valor;
    q->sgte = lista;
    lista = q;
}
//-------------------------------------------
void insertarFinal(Tlista &lista, int valor)
{
    Tlista t, q = new(struct nodo);
    q->nro = valor;
    q->sgte = NULL;
    if(lista == NULL)
    {
        lista = q;
    }
    else
    {
        t = lista;
        while(t->sgte != NULL)
        {
            t = t->sgte;
        }
        t->sgte = q;
    }
}
//-------------------------------------------
//-------------------------------------------
int insertarAntesDespues()
{
    int _op, band;
    cout << endl;
    cout << "\t 1. Antes de la posicion " << endl;
    cout << "\t 2. Despues de la posicion " << endl;
    cout << "\n\t Opcion : "; cin >> _op;
    if(_op == 1)
        band = -1;
    else
        band = 0;
    return band;
}
//-------------------------------------------
void insertarElemento(Tlista &lista, int valor, int pos)
{
    Tlista q, t;
    int i;
    q = new(struct nodo);
    q->nro = valor;
    if(pos == 1)
    {
        q->sgte = lista;
        lista = q;
    }
    else
    {
        int x = insertarAntesDespues();
        t = lista;
        for(i = 1; t != NULL; i++)
        {
            if(i == pos + x)
            {
                q->sgte = t->sgte;
                t->sgte = q;
                return;
            }
            t = t->sgte;
        }
        cout << " Error...Posicion no encontrada..!" << endl;
    }
}
//-------------------------------------------
//-------------------------------------------
void buscarElemento(Tlista lista, int valor)
{
    Tlista q = lista;
    int i = 1, band = 0;
    while(q != NULL)
    {
        if(q->nro == valor)
        {
            cout << endl << " Encontrada en posicion " << i << endl;
            band = 1;
        }
        q = q->sgte;
        i++;
    }
    if(band == 0)
        cout << "\n\n Numero no encontrado..!" << endl;
}
//-------------------------------------------

void MostrarLista(Tlista lista)
{
    int i = 0;

    while(lista != NULL)
    {
        cout << " " << i+1 << ") " << lista->nro << endl;
        lista = lista->sgte;
        i++;
    }
}

//-------------------------------------------
void eliminarElemento(Tlista &lista, int valor)
{
    Tlista p, ant;
    p = lista;
    if(lista != NULL)
    {
        while(p != NULL)
        {
            if(p->nro == valor)
            {
                if(p == lista)
                    lista = lista->sgte;
                else
                    ant->sgte = p->sgte;
                delete(p);
                return;
            }
            ant = p;
            p = p->sgte;
        }
    }
    else
        cout << " Lista vacia..!";
}
void eliminaRepetidos(Tlista &lista, int valor)
{
    Tlista q, ant;
    q = lista;
    ant = lista;
    while(q != NULL)
    {
        if(q->nro == valor)
        {
            if(q == lista) // primero elemento
            {
                lista = lista->sgte;
                delete(q);
                q = lista;
            }
            else
            {
                ant->sgte = q->sgte;
                delete(q);
                q = ant->sgte;
            }
        }
        else
        {
            ant = q;
            q = q->sgte;
        }
    } // fin del while
    cout<<"\n\n Valores eliminados..!"<<endl;
}

int cantidadElemento(Tlista lista, int elemento){

    int cantidad = 0;
    while(lista != NULL)
    {
        if(lista->nro == elemento){
            cantidad++;
        }
        lista = lista->sgte;
    }

    return cantidad;
}

void invertirLista(Tlista &lista){
    ptrPila aux = NULL;

    while (lista != NULL)
    {
        push(aux, lista->nro);
        lista = lista->sgte;
    }

    while (aux != NULL){
        insertarFinal(lista, pop(aux));
    }

}

float promedioLista(Tlista lista){
    float sumaElementos = 0;
    float cantidadElementos = 0;

    while (lista != NULL){
        sumaElementos += lista->nro;
        cantidadElementos++;

        lista = lista->sgte;
    }

    if(cantidadElementos == 0){
        return -1;
    }
    else return sumaElementos/cantidadElementos;
}

int datoMayor(Tlista lista){
    int datoMayor = lista->nro;

    while (lista !=NULL)
    {
        if(lista->nro >= datoMayor) datoMayor = lista->nro;
        lista = lista->sgte;
    }

    return datoMayor;
    
}

bool estaOrdenada(Tlista lista)
{
    if (lista == NULL || lista->sgte == NULL)
        return true;

    for (Tlista aux = lista; aux->sgte != NULL; aux = aux->sgte)
    {
        if (aux->nro >= aux->sgte->nro)
            return false;
    }
    return true;
}