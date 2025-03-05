#include <stdlib.h>
#include <iostream>
using namespace std;

struct nodo
{
    int nro;
    struct nodo *sgte;
};

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

void mostrar_pila(ptrPila p)
{
    ptrPila aux = p;
    while (aux != NULL)
    {
        cout << "[ " << aux->nro << " ]" << endl;
        aux = aux->sgte;
    }
}

void mostrar_pila_encontrada(ptrPila p, int valor)
{
    ptrPila aux = p;
    while (aux != NULL)
    {
        if (aux->nro == valor)
            cout << "[ AQUI -> " << aux->nro << " <- AQUI ]" << endl;
        else
            cout << "[ " << aux->nro << " ]" << endl;
        aux = aux->sgte;
    }
}

void destruir_pila(ptrPila &p)
{
    ptrPila aux;
    while (p != NULL)
    {
        aux = p;
        p = aux->sgte;
        delete (aux);
    }
}

void invertir_pila(ptrPila &p)
{
    ptrPila nuevaPila = NULL;
    while (p != NULL)
    {
        int dato = pop(p);
        push(nuevaPila, dato);
    }
    p = nuevaPila;
}

int encontrar_elemento(ptrPila p, int valor)
{
    ptrPila aux = p;
    int pos = 0;
    while (aux != NULL)
    {
        if (aux->nro == valor)
            return pos;
        pos++;
        aux = aux->sgte;
    }
    return -1;
}

bool esta_ordenada(ptrPila p)
{
    if (p == NULL || p->sgte == NULL)
        return true;

    for (ptrPila aux = p; aux->sgte != NULL; aux = aux->sgte)
    {
        if (aux->nro <= aux->sgte->nro)
            return false;
    }
    return true;
}

bool son_iguales(ptrPila p, ptrPila q)
{
    ptrPila aux1 = p;
    ptrPila aux2 = q;

    int pLength = 0;
    int qLength = 0;

    while (aux1 != NULL)
    {
        pLength++;
        aux1 = aux1->sgte;
    }
    while (aux2 != NULL)
    {
        qLength++;
        aux2 = aux2->sgte;
    }

    if (pLength != qLength)
    {
        return false;
    }
    else
    {

        aux1 = p;
        aux2 = q;

        while (aux1 != NULL)
        {
            if (aux1->nro != aux2->nro)
            {
                return false;
            }

            aux1 = aux1->sgte;
            aux2 = aux2->sgte;
        }
        return true;
    }
}

void eliminar_elemento(ptrPila &p, int elemento){

    ptrPila aux = p;
    ptrPila nueva = NULL;
    
    while (aux != NULL){
        if(aux->nro != elemento){
            push(nueva, aux->nro);
        }

        aux = aux->sgte;
    }

    destruir_pila(p);

    while(nueva != NULL){
        push(p, pop(nueva));
    }
}

void añadir_elemento(ptrPila &p, int elemento, int posicion){
    ptrPila aux = p;
    ptrPila nueva = NULL;
    int posActual = 0;

    while(aux != NULL){
        if(posActual == posicion){
            push(nueva, elemento);
        }
        push(nueva, aux->nro); 

        aux = aux -> sgte;
        posActual++;

    }

    if(posActual == posicion){
        push(nueva, elemento);
    }

    destruir_pila(p);

    while(nueva != NULL){
        push(p, pop(nueva));
    }
}

void distribuir_elementos(ptrPila p, ptrPila &p1, ptrPila &p2, int valor){

    ptrPila aux = p;

    while(aux != NULL){
        if(aux->nro < valor){
            push(p1, aux->nro);
        }
        else{
            push(p2, aux->nro);
        }

        aux = aux -> sgte;
    }

    invertir_pila(p1);
    invertir_pila(p2);

}

void pasar_valores(ptrPila &original, ptrPila &nueva){

    ptrPila aux = original;
    destruir_pila(nueva);

    while(aux != NULL){
        push(nueva, aux->nro);
        aux = aux -> sgte;
    }

    invertir_pila(nueva);
}


void menu()
{
    cout << "\n\tIMPLEMENTACION DE PILAS EN C++\n\n";
    cout << "1. APILAR\n";
    cout << "2. DESAPILAR\n";
    cout << "3. MOSTRAR PILA\n";
    cout << "4. DESTRUIR PILA\n";
    cout << "5. INVERTIR PILA\n";
    cout << "6. ENCONTRAR UN ELEMENTO EN LA PILA\n";
    cout << "7. VERIFICAR SI ESTA ORDENADA ASCENDENTEMENTE\n";
    cout << "8. COMPROBAR SI 1 Y 2 SON IGUALES\n";
    cout << "9. ELIMINAR UN ELEMENTO X\n";
    cout << "10. AÑADIR UN ELEMENTO X\n";
    cout << "11. DIVIDIR UNA PILA EN DOS SEGUN SUS ELEMENTOS\n";
    cout << "12. SALIR\n";
    cout << "\nINGRESE OPCION: ";
}

int main()
{
    ptrPila p = NULL;
    ptrPila q = NULL;

    ptrPila p1 = NULL;
    ptrPila p2 = NULL;
    int dato;
    int op;
    int pila;
    system("color 0b");

    do
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\nNUMERO A APILAR: ";
                cin >> dato;
                push(p, dato);
                cout << "\n\n\tNumero " << dato << " apilado...\n\n";
            }
            else if (pila == 2)
            {
                cout << "\nNUMERO A APILAR: ";
                cin >> dato;
                push(q, dato);
                cout << "\n\n\tNumero " << dato << " apilado...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;
        case 2:

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\n\n\tNumero " << pop(p) << " desapilado...\n\n";
            }
            else if (pila == 2)
            {
                cout << "\n\n\tNumero " << pop(q) << " desapilado...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        case 3:

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "\n\nMOSTRANDO PILA\n\n";
                if (p != NULL)
                    mostrar_pila(p);
                else
                    cout << "\n\tPila Vacia..!\n\n";
                break;
            }
            else if (pila == 2)
            {
                cout << "\n\nMOSTRANDO PILA\n\n";
                if (q != NULL)
                    mostrar_pila(q);
                else
                    cout << "\n\tPila Vacia..!\n\n";
                break;
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

        case 4:

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                destruir_pila(p);
                cout << "\n\n\tPila eliminada...\n\n";
            }
            else if (pila == 2)
            {
                destruir_pila(q);
                cout << "\n\n\tPila eliminada...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;
        case 5:

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                invertir_pila(p);
                cout << "\n\n\tPila invertida...\n\n";
            }
            else if (pila == 2)
            {
                invertir_pila(q);
                cout << "\n\n\tPila invertida...\n\n";
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;
        case 6:
        {

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                cout << "ELEMENTO A BUSCAR: ";
                cin >> dato;
                int encontrado = encontrar_elemento(p, dato);
                if (encontrado != -1)
                {
                    cout << "El elemento fue encontrado en la posicion " << encontrado << endl;
                    mostrar_pila_encontrada(p, dato);
                }
                else
                {
                    cout << "El elemento no fue encontrado" << endl;
                }
            }
            else if (pila == 2)
            {
                cout << "ELEMENTO A BUSCAR: ";
                cin >> dato;
                int encontrado = encontrar_elemento(q, dato);
                if (encontrado != -1)
                {
                    cout << "El elemento fue encontrado en la posicion " << encontrado << endl;
                    mostrar_pila_encontrada(q, dato);
                }
                else
                {
                    cout << "El elemento no fue encontrado" << endl;
                }
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;
        }
        case 7:
        {

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if (pila == 1)
            {
                bool estaOrdenada = esta_ordenada(q);
                if (estaOrdenada)
                    cout << "La pila esta ordenada" << endl;
                else
                    cout << "La pila no esta ordenada" << endl;
                break;
            }
            else if (pila == 2)
            {
                bool estaOrdenada = esta_ordenada(q);
                if (estaOrdenada)
                    cout << "La pila esta ordenada" << endl;
                else
                    cout << "La pila no esta ordenada" << endl;
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
            break;
        }
        case 8:
        {
            if (son_iguales(p, q) == true)
            {
                cout << "Las pilas son iguales" << endl;
            }
            else
            {
                cout << "Las pilas no son iguales" << endl;
            }
            
        }
        break;
        case 9:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if(pila == 1){
                cout<<"Ingresa el elemento a eliminar"<<endl;
                cin>>dato;
                if(encontrar_elemento(p, dato) == -1){
                    cout<<"El elemento no está en la pila"<<endl;
                }
                else{
                    eliminar_elemento(p, dato);
                    cout<<"El elemento ha sido eliminado"<<endl;
                }
            }
            else if(pila == 2){
                cout<<"Ingresa el elemento a eliminar"<<endl;
                cin>>dato;
                if(encontrar_elemento(q, dato) == -1){
                    cout<<"El elemento no está en la pila"<<endl;
                }
                else{
                    eliminar_elemento(q, dato);
                    cout<<"El elemento ha sido eliminado"<<endl;
                }

            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;
        }
        case 10:
        {
            int posicion;

            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;


            if(pila == 1){
                cout<<"Ingresa el elemento a añadir"<<endl;
                cin>>dato;
                cout<<"Ingresa la posicion a añadir"<<endl;
                cin>>posicion;
                añadir_elemento(p, dato, posicion);
                cout<<"El elemento ha sido añadido"<<endl; 
                mostrar_pila_encontrada(p, dato);
            }
            else if (pila == 2){
                cout<<"Ingresa el elemento a añadir"<<endl;
                cin>>dato;
                cout<<"Ingresa la posicion a añadir"<<endl;
                cin>>posicion;
                añadir_elemento(q, dato, posicion);
                cout<<"El elemento ha sido añadido"<<endl; 
                mostrar_pila_encontrada(q, dato);

            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }

            break;

        }
        case 11:
        {
            cout << "INGRESA LA PILA (1 o 2):" << endl;
            cin >> pila;

            if(pila == 1){
                cout<<"Ingresa el valor"<<endl;
                cin>>dato;

                distribuir_elementos(p, p1, p2, dato);
                cout<<"Los elementos menores al valor se encuentran en esta pila"<<endl;
                mostrar_pila(p1);
                cout<<"Los demas elementos se encuentran en esta pila"<<endl;
                mostrar_pila(p2);

                cout<<"Quiere guardar estas pilas como 1 y 2? 1 para sí, otro para no"<<endl;
                cin>>dato;
                if(dato == 1){
                    pasar_valores(p1, p);
                    pasar_valores(p2, q);
                    cout<<"Se han guardado las pilas"<<endl;
                }
                else{
                    cout<<"Las pilas originales permanecen iguales"<<endl;
                }

            }
            else if(pila == 2){
                cout<<"Ingresa el valor"<<endl;
                cin>>dato;

                distribuir_elementos(q, p1, p2, dato);
                cout<<"Los elementos menores al valor se encuentran en esta pila"<<endl;
                mostrar_pila(p1);
                cout<<"Los demas elementos se encuentran en esta pila"<<endl;
                mostrar_pila(p2);

                cout<<"Quiere guardar estas pilas como 1 y 2? 1 para sí, otro para no"<<endl;
                cin>>dato;
                if(dato == 1){
                    pasar_valores(p1, p);
                    pasar_valores(p2, q);
                    cout<<"Se han guardado las pilas"<<endl;
                }
                else{
                    cout<<"Las pilas originales permanecen iguales"<<endl;
                }
            }
            else{
                cout<<"Esta pila no existe. Volviendo al menu."<<endl;
            }
        }
        break;
        case 12:
        cout<<"Saliendo"<<endl;
        break;





        }
        cout << endl;
        system("pause");
        system("cls");
    } while (op != 12 || !(op > 11));

    return 0;
}
