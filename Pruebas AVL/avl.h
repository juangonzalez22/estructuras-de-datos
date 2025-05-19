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

// Contador de rotaciones realizadas durante una inserción
static int rotaciones = 0;

void verArbol(AVL arbol, int n) {
    if (!arbol)
        return;
    if (arbol->der) {
        verArbol(arbol->der, n + 2);
    }
    if (arbol->der) {
        for (int i = 0; i < n; i++) cout << ' ';
        cout << "/\n";
    }
    for (int i = 0; i < n; i++) cout << ' ';
    cout << arbol->nro << "\n";
    if (arbol->izq) {
        for (int i = 0; i < n; i++) cout << ' ';
        cout << "\\\n";
        verArbol(arbol->izq, n + 2);
    }
}

void RDD(AVL &r, AVL nodoAVL) {
    rotaciones++;
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
    rotaciones++;
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
    rotaciones++;
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
    rotaciones++;
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

        return (altIzq > altDer ? altIzq : altDer) + 1;
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

void insertar(AVL &nodoAVL, int dato) {
    // Reiniciar contador de rotaciones para esta inserción

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

    cout << "\n\n\tEl número ha sido insertado\n";
    cout << "\tSe han hecho " << rotaciones << " rotaciones." << endl << endl;
}

AVL buscar(AVL nodoAVL, int dato) {
    AVL actual = nodoAVL;
    if (nodoAVL == NULL) {
        cout << "\n\t¡¡ El árbol está vacío !!" << endl << endl;
        return NULL;
    }
    while (actual != NULL) {
        if (dato == actual->nro) {
            cout << "\n\tEl número " << dato << " existe en el árbol\n";
            return actual;
        } else if (dato < actual->nro)
            actual = actual->izq;
        else if (dato > actual->nro)
            actual = actual->der;
    }
    cout << "\n\tEl número " << dato << " NO existe en el árbol\n";
    return NULL;
}

#endif
