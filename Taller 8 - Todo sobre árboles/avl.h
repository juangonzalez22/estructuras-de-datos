#ifndef AVL_H
#define AVL_H

#include <cstdlib>
#include <iostream>

#define TRUE 1
#define FALSE 0

using namespace std;

struct nodoAVL {
    int nro;
    int FE;
    struct nodoAVL *der;
    struct nodoAVL *izq;
    struct nodoAVL *padre;
};

typedef struct nodoAVL *AVL;

void verArbol(AVL arbol, int n) {
    if(arbol == NULL)
       return;
    verArbol(arbol->der, n + 1);

    for(int i = 0; i < n; i++)
        cout << "   ";

    cout << arbol->nro << endl;

    verArbol(arbol->izq, n + 1);
}

void RDD(AVL &r, AVL nodoAVL) {
    AVL padre = nodoAVL->padre;
    AVL A = nodoAVL;
    AVL B = A->izq;
    AVL C = B->der;
    AVL CI = C->izq;
    AVL CD = C->der;

    if (padre) {
        if (padre->der == A)
            padre->der = C;
        else
            padre->izq = C;
    } else
        r = C;

    B->der = CI;
    A->izq = CD;
    C->izq = B;
    C->der = A;
    C->padre = padre;
    A->padre = B->padre = C;

    if (CI) CI->padre = B;
    if (CD) CD->padre = A;

    switch (C->FE) {
        case -1: B->FE = 0; A->FE = 1; break;
        case 0:  B->FE = 0; A->FE = 0; break;
        case 1:  B->FE = -1; A->FE = 0; break;
    }
    C->FE = 0;
}

void RDI(AVL &r, AVL nodoAVL) {
    AVL padre = nodoAVL->padre;
    AVL A = nodoAVL;
    AVL B = A->der;
    AVL C = B->izq;
    AVL CI = C->izq;
    AVL CD = C->der;

    if (padre) {
        if (padre->der == A)
            padre->der = C;
        else
            padre->izq = C;
    } else
        r = C;

    A->der = CI;
    B->izq = CD;
    C->izq = A;
    C->der = B;
    C->padre = padre;
    A->padre = B->padre = C;

    if (CI) CI->padre = A;
    if (CD) CD->padre = B;

    A->FE = 0;
    B->FE = 0;
    C->FE = 0;
}

void RSD(AVL &r, AVL nodoAVL) {
    AVL padre = nodoAVL->padre;
    AVL A = nodoAVL;
    AVL B = A->izq;
    AVL C = B->der;

    if (padre)
        if (padre->der == A)
            padre->der = B;
        else
            padre->izq = B;
    else
        r = B;

    A->izq = C;
    B->der = A;
    A->padre = B;
    if (C) C->padre = A;

    B->padre = padre;

    A->FE = 0;
    B->FE = 0;
}

void RSI(AVL &r, AVL nodoAVL) {
    AVL padre = nodoAVL->padre;
    AVL A = nodoAVL;
    AVL B = A->der;
    AVL C = B->izq;

    if (padre) {
        if (padre->der == A)
            padre->der = B;
        else
            padre->izq = B;
    } else
        r = B;

    A->der = C;
    B->izq = A;
    A->padre = B;
    if (C) C->padre = A;
    B->padre = padre;

    A->FE = 0;
    B->FE = 0;
}

int esHoja(AVL nodoAVL) {
    return !nodoAVL->der && !nodoAVL->izq;
}

int altura(AVL arbol) {
    if (arbol == NULL) return 0;
    else {
        if (arbol->izq == NULL && arbol->der == NULL) return 1;
        int altIzq = 0;
        int altDer = 0;
        if (arbol->izq) altIzq = altura(arbol->izq);
        if (arbol->der) altDer = altura(arbol->der);

        if (altIzq > altDer)
            return altIzq + 1;
        else
            return altDer + 1;
    }
}

void equilibrar(AVL &r, AVL &nodoAVL) {
    int salir = FALSE;

    while (nodoAVL && salir != TRUE) {
        nodoAVL->FE = altura(nodoAVL->der) - altura(nodoAVL->izq);
        if (nodoAVL->FE == 0) salir = TRUE;
        else if (nodoAVL->FE == -2) {
            if (nodoAVL->izq->FE == 1)
                RDD(r, nodoAVL);
            else
                RSD(r, nodoAVL);
            salir = TRUE;
        }
        else if (nodoAVL->FE == 2) {
            if (nodoAVL->der->FE == -1)
                RDI(r, nodoAVL);
            else
                RSI(r, nodoAVL);
            salir = TRUE;
        }
        nodoAVL = nodoAVL->padre;
    }
}

void eliminarNodo(AVL &n, int dato) {
    AVL padre = NULL;
    AVL actual;
    AVL nodoAVL;
    int aux;
    actual = n;

    while (actual != NULL) {
        if (dato == actual->nro) {
            if (esHoja(actual)) {
                if (padre == NULL) {
                    n = NULL;
                    return;
                }
                if (padre) {
                    if (padre->der == actual)
                        padre->der = NULL;
                    else if (padre->izq == actual)
                        padre->izq = NULL;
                }
                free(actual);
                actual = NULL;
                if ((padre->der == actual && padre->FE == 1) ||
                    (padre->izq == actual && padre->FE == -1)) {
                    padre->FE = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if (padre)
                    equilibrar(n, padre);
                //cout << "\n\n\tARBOL ACTUALIZADO\n";
                verArbol(n, 0);
                return;
            } else {
                padre = actual;
                if (actual->der) {
                    nodoAVL = actual->der;
                    while (nodoAVL->izq) {
                        padre = nodoAVL;
                        nodoAVL = nodoAVL->izq;
                    }
                } else {
                    nodoAVL = actual->izq;
                    while (nodoAVL->der) {
                        padre = nodoAVL;
                        nodoAVL = nodoAVL->der;
                    }
                }
                aux = actual->nro;
                actual->nro = nodoAVL->nro;
                nodoAVL->nro = aux;
                actual = nodoAVL;
            }
        } else {
            padre = actual;
            if (dato > actual->nro)
                actual = actual->der;
            else if (dato < actual->nro)
                actual = actual->izq;
        }
    }
}

void insertar(AVL &nodoAVL, int dato) {
    AVL padre = NULL;
    AVL actual = nodoAVL;
    while (actual != NULL && dato != actual->nro) {
        padre = actual;
        if (dato < actual->nro)
            actual = actual->izq;
        else if (dato > actual->nro)
            actual = actual->der;
    }
    if (actual != NULL) return;

    if (padre == NULL) {
        nodoAVL = (AVL)malloc(sizeof(struct nodoAVL));
        nodoAVL->nro = dato;
        nodoAVL->izq = nodoAVL->der = NULL;
        nodoAVL->padre = NULL;
        nodoAVL->FE = 0;
    } else if (dato < padre->nro) {
        actual = (AVL)malloc(sizeof(struct nodoAVL));
        padre->izq = actual;
        actual->nro = dato;
        actual->izq = actual->der = NULL;
        actual->padre = padre;
        actual->FE = 0;
        equilibrar(nodoAVL, padre);
    } else {
        if (dato > padre->nro) {
            actual = (AVL)malloc(sizeof(struct nodoAVL));
            padre->der = actual;
            actual->nro = dato;
            actual->izq = actual->der = NULL;
            actual->padre = padre;
            actual->FE = 0;
            equilibrar(nodoAVL, padre);
        }
    }
    //cout << "\n\n\tEl número ha sido insertado\n\n";
}

int buscar(AVL nodoAVL, int dato) {
    AVL actual = nodoAVL;
    if (nodoAVL == NULL) {
        return 0; // El árbol está vacío
    }
    while (actual != NULL) {
        if (dato == actual->nro) {
            return 1; // El número existe en el árbol
        } else if (dato < actual->nro)
            actual = actual->izq;
        else if (dato > actual->nro)
            actual = actual->der;
    }
    return 0; // El número no existe en el árbol
}

#endif
