#include <iostream>
#include "grafo.h"

using namespace std;

int main()
{
    Grafo miGrafo = crearGrafo();
    miGrafo = insertarVertice(miGrafo, 1);
    miGrafo = insertarVertice(miGrafo, 2);
    miGrafo = insertarVertice(miGrafo, 3);
    miGrafo = insertarVertice(miGrafo, 4);
    miGrafo = insertarVertice(miGrafo, 5);
    cout << "Lista de vertices:" << endl;
    imprimirListaV(miGrafo);

    miGrafo=insertarArco(miGrafo, 1, 2, 4);
    miGrafo=insertarArco(miGrafo, 1, 3, 2);
    miGrafo=insertarArco(miGrafo, 1, 5, 6);

    miGrafo=insertarArco(miGrafo, 2, 3, 3);
    miGrafo=insertarArco(miGrafo, 2, 4, 2);

    printf("\nLista de arcos:\n");
    imprimirListaA(miGrafo);

}