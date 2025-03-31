#include <iostream>
#include <fstream>
#include <string.h>
#include <limits>
using namespace std;

struct Vuelo
{
    char NroDeVuelo[7];
    char Origen[20];
    char Destino[20];
    char MatriculaAvion[7];
    char NombrePiloto[20];
    char HoraVuelo[5];
    char FechaVuelo[7];
    int Estado;
    struct Vuelo *Sgte;
    struct Pasajeros *ListaPasajeros;
};

typedef struct Vuelo *DatosVuelo;

struct Pasajeros
{
    char Cedula[20];
    char NombrePersona[20];
    char Telefono[20];
    int Estado;
    struct Pasajeros *Sgte;
};

typedef struct Pasajeros *DatosPasajero;

void AbrirArchivoVuelo(DatosVuelo &Vuelos)
{
    ifstream leer("VUELOS.txt");
    if (leer.good())
    {
        cout << "El archivo VUELOS.txt fue abierto correctamente..." << endl;
    }
    else
    {
        cout << "El archivo VUELOS.txt no se pudo abrir..." << endl;
        return;
    }

    char nroVuelo[7];
    char origen[20];
    char destino[20];
    char matricula[7];
    char piloto[20];
    char hora[5];
    char fecha[7];
    int estado;

    while (leer >> nroVuelo >> origen >> destino >> matricula >> piloto >> hora >> fecha >> estado)
    {
        DatosVuelo nuevo = new Vuelo;
        nuevo->ListaPasajeros = NULL;

        strcpy(nuevo->NroDeVuelo, nroVuelo);
        strcpy(nuevo->Origen, origen);
        strcpy(nuevo->Destino, destino);
        strcpy(nuevo->MatriculaAvion, matricula);
        strcpy(nuevo->NombrePiloto, piloto);
        strcpy(nuevo->HoraVuelo, hora);
        strcpy(nuevo->FechaVuelo, fecha);
        nuevo->Estado = estado;
        nuevo->Sgte = NULL;

        if (Vuelos == NULL)
        {
            Vuelos = nuevo;
        }
        else
        {
            DatosVuelo aux = Vuelos;
            while (aux->Sgte != NULL)
            {
                aux = aux->Sgte;
            }
            aux->Sgte = nuevo;
        }
    }
    leer.close();
}

void AbrirArchivoPasajeros(DatosVuelo Vuelos)
{
    ifstream leer("PASAJEROS.txt");
    if (leer.good())
    {
        cout << "El archivo PASAJEROS.txt fue abierto correctamente..." << endl;
    }
    else
    {
        cout << "El archivo PASAJEROS.txt no se pudo abrir..." << endl;
        return;
    }
    char nroVuelo[7];
    char cedula[20];
    char nombre[20];
    char telefono[20];
    int estado;

    while (leer >> nroVuelo >> cedula >> nombre >> telefono >> estado)
    {
        DatosVuelo vuelo = Vuelos;
        while (vuelo != NULL && strcmp(vuelo->NroDeVuelo, nroVuelo) != 0)
        {
            vuelo = vuelo->Sgte;
        }
        if (vuelo != NULL)
        {
            DatosPasajero nuevo = new Pasajeros;
            strcpy(nuevo->Cedula, cedula);
            strcpy(nuevo->NombrePersona, nombre);
            strcpy(nuevo->Telefono, telefono);
            nuevo->Estado = estado;
            nuevo->Sgte = NULL;

            if (vuelo->ListaPasajeros == NULL)
            {
                vuelo->ListaPasajeros = nuevo;
            }
            else
            {
                DatosPasajero aux = vuelo->ListaPasajeros;
                while (aux->Sgte != NULL)
                {
                    aux = aux->Sgte;
                }
                aux->Sgte = nuevo;
            }
        }
    }
    leer.close();
}

string FormatearHora(const char *hora)
{
    string h(hora);
    if (h.length() == 4)
    {
        return h.substr(0, 2) + ":" + h.substr(2, 2);
    }
    return h;
}

string FormatearFecha(const char *fecha)
{
    string f(fecha);
    if (f.length() == 6)
    {
        return f.substr(0, 2) + "/" + f.substr(2, 2) + "/" + f.substr(4, 2);
    }
    return f;
}

void ActualizarArchivoVuelos(DatosVuelo Vuelos) {
    ofstream archivo("VUELOS.txt", ios::trunc);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir VUELOS.txt para actualizar." << endl;
        return;
    }
    DatosVuelo aux = Vuelos;
    while (aux != NULL) {
        archivo << aux->NroDeVuelo << " "
                << aux->Origen << " "
                << aux->Destino << " "
                << aux->MatriculaAvion << " "
                << aux->NombrePiloto << " "
                << aux->HoraVuelo << " "
                << aux->FechaVuelo << " "
                << aux->Estado << endl;
        aux = aux->Sgte;
    }
    archivo.close();
}

void ActualizarArchivoPasajeros(DatosVuelo Vuelos) {
    ofstream archivo("PASAJEROS.txt", ios::trunc);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir PASAJEROS.txt para actualizar." << endl;
        return;
    }
    DatosVuelo vuelo = Vuelos;
    while (vuelo != NULL) {
        DatosPasajero pasajero = vuelo->ListaPasajeros;
        while (pasajero != NULL) {
            archivo << vuelo->NroDeVuelo << " "
                    << pasajero->Cedula << " "
                    << pasajero->NombrePersona << " "
                    << pasajero->Telefono << " "
                    << pasajero->Estado << endl;
            pasajero = pasajero->Sgte;
        }
        vuelo = vuelo->Sgte;
    }
    archivo.close();
}

void AñadirVuelo(DatosVuelo &Vuelos) {
    DatosVuelo t, q = new Vuelo;

    char NroDeVuelo[20];
    char Origen[20];
    char Destino[20];
    char MatriculaAvion[20];
    char NombrePiloto[20];
    char HoraVuelo[20];
    char FechaVuelo[20];
    int Estado = 0;

    cout << "\nIngrese el numero de vuelo: ";
    cin >> NroDeVuelo;
    cout << "\nIngrese el origen del vuelo: ";
    cin >> Origen;
    cout << "\nIngrese el destino del vuelo: ";
    cin >> Destino;
    cout << "\nIngrese la matricula del avion: ";
    cin >> MatriculaAvion;
    cout << "\nIngrese el nombre del piloto: ";
    cin >> NombrePiloto;
    cout << "\nIngrese la hora del vuelo: ";
    cin >> HoraVuelo;
    cout << "\nIngrese la fecha del vuelo: ";
    cin >> FechaVuelo;

    strcpy(q->NroDeVuelo, NroDeVuelo);
    strcpy(q->Origen, Origen);
    strcpy(q->Destino, Destino);
    strcpy(q->MatriculaAvion, MatriculaAvion);
    strcpy(q->NombrePiloto, NombrePiloto);
    strcpy(q->HoraVuelo, HoraVuelo);
    strcpy(q->FechaVuelo, FechaVuelo);
    q->Estado = Estado;
    q->Sgte = NULL;
    q->ListaPasajeros = NULL;

    if (Vuelos == NULL) {
        Vuelos = q;
    } else {
        t = Vuelos;
        while (t->Sgte != NULL) {
            t = t->Sgte;
        }
        t->Sgte = q;
    }

    ofstream archivo("VUELOS.txt", ios::app);
    if (archivo.is_open()) {
        archivo << q->NroDeVuelo << " "
                << q->Origen << " "
                << q->Destino << " "
                << q->MatriculaAvion << " "
                << q->NombrePiloto << " "
                << q->HoraVuelo << " "
                << q->FechaVuelo << " "
                << q->Estado << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir VUELOS.txt para agregar el nuevo vuelo." << endl;
    }
}

void MostrarVuelos(DatosVuelo Vuelos)
{
    DatosVuelo aux = Vuelos;
    if (aux == NULL)
    {
        cout << "No hay vuelos registrados." << endl;
        return;
    }
    while (aux != NULL)
    {
        cout << "---------------------------" << endl;
        cout << "Numero de Vuelo: " << aux->NroDeVuelo << endl;
        cout << "Origen: " << aux->Origen << endl;
        cout << "Destino: " << aux->Destino << endl;
        cout << "Matricula Avion: " << aux->MatriculaAvion << endl;
        cout << "Nombre del Piloto: " << aux->NombrePiloto << endl;
        cout << "Hora de Vuelo: " << FormatearHora(aux->HoraVuelo) << endl;
        cout << "Fecha de Vuelo: " << FormatearFecha(aux->FechaVuelo) << endl;
        cout << "Estado: " << (aux->Estado == 0 ? "Programado" : "Realizado") << endl;
        aux = aux->Sgte;
    }
    cout << "---------------------------" << endl;
}

void AñadirPasajeros(DatosVuelo &Vuelos) {
    char nro[7];
    cout << "\nIngrese el numero del vuelo: ";
    cin >> nro;

    DatosVuelo p = Vuelos;
    while (p != NULL && strcmp(p->NroDeVuelo, nro) != 0) {
        p = p->Sgte;
    }

    if (p == NULL) {
        cout << "El vuelo no existe. Regresando." << endl;
        return;
    }

    DatosPasajero nuevo = new Pasajeros;
    char cedula[20];
    char nombre[20];
    char telefono[20];
    int estado = 1;

    cout << "\nIngrese la cédula del pasajero: ";
    cin >> cedula;
    cout << "\nIngrese el nombre del pasajero: ";
    cin >> nombre;
    cout << "\nIngrese el telefono del pasajero: ";
    cin >> telefono;

    strcpy(nuevo->Cedula, cedula);
    strcpy(nuevo->NombrePersona, nombre);
    strcpy(nuevo->Telefono, telefono);
    nuevo->Estado = estado;
    nuevo->Sgte = NULL;

    if (p->ListaPasajeros == NULL) {
        p->ListaPasajeros = nuevo;
    } else {
        DatosPasajero aux = p->ListaPasajeros;
        while (aux->Sgte != NULL) {
            aux = aux->Sgte;
        }
        aux->Sgte = nuevo;
    }

    ofstream archivo("PASAJEROS.txt", ios::app);
    if (archivo.is_open()) {
        archivo << p->NroDeVuelo << " "
                << nuevo->Cedula << " "
                << nuevo->NombrePersona << " "
                << nuevo->Telefono << " "
                << nuevo->Estado << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir PASAJEROS.txt para agregar el pasajero." << endl;
    }

    cout << "Pasajero agregado exitosamente al vuelo " << p->NroDeVuelo << endl;
}

void mostrarPasajeros(DatosVuelo Vuelos)
{
    char nro[7];
    cout << "\nIngrese el numero del vuelo: ";
    cin >> nro;

    DatosVuelo vuelo = Vuelos;
    while (vuelo != NULL && strcmp(vuelo->NroDeVuelo, nro) != 0)
    {
        vuelo = vuelo->Sgte;
    }

    if (vuelo == NULL)
    {
        cout << "El vuelo no existe. Regresando." << endl;
        return;
    }

    DatosPasajero pasajero = vuelo->ListaPasajeros;
    while (pasajero != NULL)
    {
        cout << "---------------------------" << endl;
        cout << "Nombre del pasajero: " << pasajero->NombrePersona << endl;
        cout << "Cedula del pasajero: " << pasajero->Cedula << endl;
        cout << "Telefono del pasajero: " << pasajero->Telefono << endl;
        cout << "Estado: " << (pasajero->Estado == 1 ? "Reservado" : "A Bordo") << endl;
        pasajero = pasajero->Sgte;
    }
    cout << "---------------------------" << endl;
}

void abordarPasajero(DatosVuelo Vuelos) {
    char nro[7];
    char cedula[20];
    cout << "\nIngrese el numero del vuelo: ";
    cin >> nro;

    DatosVuelo vuelo = Vuelos;
    while (vuelo != NULL && strcmp(vuelo->NroDeVuelo, nro) != 0) {
        vuelo = vuelo->Sgte;
    }

    if (vuelo == NULL) {
        cout << "El vuelo no existe. Regresando." << endl;
        return;
    }

    cout << "\nIngrese la cédula del pasajero: ";
    cin >> cedula;

    DatosPasajero pasajero = vuelo->ListaPasajeros;
    while (pasajero != NULL) {
        if (strcmp(pasajero->Cedula, cedula) == 0) {
            pasajero->Estado = 2;
            cout << "Pasajero abordado exitosamente." << endl;
            ActualizarArchivoPasajeros(Vuelos);
            return;
        }
        pasajero = pasajero->Sgte;
    }
    cout << "El pasajero no se encontró en el vuelo." << endl;
}

void realizarVuelo(DatosVuelo &Vuelos) {
    char nro[7];
    cout << "\nIngrese el numero del vuelo: ";
    cin >> nro;

    DatosVuelo vuelo = Vuelos;
    while (vuelo != NULL && strcmp(vuelo->NroDeVuelo, nro) != 0) {
        vuelo = vuelo->Sgte;
    }

    if (vuelo == NULL) {
        cout << "El vuelo no existe. Regresando." << endl;
        return;
    }

    bool puedeDespegar = true;
    DatosPasajero pasajero = vuelo->ListaPasajeros;

    while (pasajero != NULL) {
        if (pasajero->Estado != 2) {
            puedeDespegar = false;
            break;
        }
        pasajero = pasajero->Sgte;
    }

    if (puedeDespegar && vuelo->Estado != 1) {
        vuelo->Estado = 1;
        cout << "Vuelo realizado exitosamente." << endl;
        ActualizarArchivoVuelos(Vuelos);
        ActualizarArchivoPasajeros(Vuelos);
    }
    else if (vuelo->Estado == 1) {
        cout << "El vuelo ya ha sido realizado." << endl;
    }
    else {
        cout << "El vuelo no puede despegar, hay pasajeros que no están abordados." << endl;
    }
}

void MostrarVuelosProgramados(DatosVuelo Vuelos)
{
    DatosVuelo aux = Vuelos;
    if (aux == NULL)
    {
        cout << "No hay vuelos registrados." << endl;
        return;
    }
    while (aux != NULL)
    {
        if (aux->Estado == 0)
        {
            cout << "---------------------------" << endl;
            cout << "Numero de Vuelo: " << aux->NroDeVuelo << endl;
            cout << "Origen: " << aux->Origen << endl;
            cout << "Destino: " << aux->Destino << endl;
            cout << "Matricula Avion: " << aux->MatriculaAvion << endl;
            cout << "Nombre del Piloto: " << aux->NombrePiloto << endl;
            cout << "Hora de Vuelo: " << FormatearHora(aux->HoraVuelo) << endl;
            cout << "Fecha de Vuelo: " << FormatearFecha(aux->FechaVuelo) << endl;
            cout << "Estado: " << (aux->Estado == 0 ? "Programado" : "Realizado") << endl;
        }
        aux = aux->Sgte;
    }
    cout << "---------------------------" << endl;
}

void MostrarVuelosRealizados(DatosVuelo Vuelos)
{
    DatosVuelo aux = Vuelos;
    if (aux == NULL)
    {
        cout << "No hay vuelos registrados." << endl;
        return;
    }
    while (aux != NULL)
    {
        if (aux->Estado == 1)
        {
            cout << "---------------------------" << endl;
            cout << "Numero de Vuelo: " << aux->NroDeVuelo << endl;
            cout << "Origen: " << aux->Origen << endl;
            cout << "Destino: " << aux->Destino << endl;
            cout << "Matricula Avion: " << aux->MatriculaAvion << endl;
            cout << "Nombre del Piloto: " << aux->NombrePiloto << endl;
            cout << "Hora de Vuelo: " << FormatearHora(aux->HoraVuelo) << endl;
            cout << "Fecha de Vuelo: " << FormatearFecha(aux->FechaVuelo) << endl;
            cout << "Estado: " << (aux->Estado == 0 ? "Programado" : "Realizado") << endl;
        }
        aux = aux->Sgte;
    }
    cout << "---------------------------" << endl;
}

void HistorialPasajero(DatosVuelo Vuelos)
{
    char cedula[20];
    bool tieneHistorial = false;

    DatosVuelo aux = Vuelos;
    if (aux == NULL)
    {
        cout << "No hay vuelos registrados." << endl;
        return;
    }

    cout << "\nIngrese la cédula del pasajero: ";
    cin >> cedula;

    while (aux != NULL)
    {
        DatosPasajero pasajero = aux->ListaPasajeros;
        while (pasajero != NULL)
        {
            if (strcmp(pasajero->Cedula, cedula) == 0)
            {
                if (aux->Estado == 0)
                {
                    cout << "---------------------------" << endl;
                    cout << "El pasajero esta registrado en el vuelo programado " << aux->NroDeVuelo << endl;
                    tieneHistorial = true;
                }
                else
                {
                    cout << "---------------------------" << endl;
                    cout << "El pasajero esta registrado en el vuelo realizado " << aux->NroDeVuelo << endl;
                    tieneHistorial = true;
                }
            }
            pasajero = pasajero->Sgte;
        }
        aux = aux->Sgte;
    }

    if (!tieneHistorial)
    {
        cout << "El pasajero no tiene historial" << endl;
    }

    cout << "---------------------------" << endl;
}

void menu()
{
    cout << "\n---------------------------" << endl;
    cout << "        MENU PRINCIPAL     " << endl;
    cout << "---------------------------" << endl;
    cout << "1. Mostrar Vuelos" << endl;
    cout << "2. Agregar Vuelo" << endl;
    cout << "3. Agregar Pasajero a un Vuelo" << endl;
    cout << "4. Mostrar Pasajeros de un Vuelo" << endl;
    cout << "5. Abordar Pasajero" << endl;
    cout << "6. Realizar Vuelo" << endl;
    cout << "7. Mostrar Vuelos Programados" << endl;
    cout << "8. Mostrar Vuelos Realizados" << endl;
    cout << "9. Ver historial de Pasajero" << endl;
    cout << "10. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main()
{
    DatosVuelo Vuelos = NULL;
    int opcion;

    AbrirArchivoVuelo(Vuelos);
    AbrirArchivoPasajeros(Vuelos);

    do
    {
        menu();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            MostrarVuelos(Vuelos);
            break;
        case 2:
            AñadirVuelo(Vuelos);
            break;
        case 3:
            AñadirPasajeros(Vuelos);
            break;
        case 4:
            mostrarPasajeros(Vuelos);
            break;
        case 5:
            abordarPasajero(Vuelos);
            break;
        case 6:
            realizarVuelo(Vuelos);
            break;
        case 7:
            MostrarVuelosProgramados(Vuelos);
            break;
        case 8:
            MostrarVuelosRealizados(Vuelos);
            break;
        case 9:
            HistorialPasajero(Vuelos);
            break;
        case 10:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

        system("pause");
        system("cls");
    } while (opcion != 10);

    return 0;
}
