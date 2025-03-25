#include <iostream> // Entrada y salida de datos
#include <fstream>  // Lectura y escritura de archivos
#include <string.h> // Manejo de cadenas de caracteres
#include <limits>   // Manejo de límites numéricos
using namespace std;

struct Vuelo // Definición de la estructura "Vuelo"
{
    char NroDeVuelo[7];               // Número de vuelo
    char Origen[20];                  // Origen de vuelo
    char Destino[20];                 // Destino de vuelo
    char MatriculaAvion[7];           // Matrícula del avió
    char NombrePiloto[20];            // Nombre del piloto
    char HoraVuelo[5];                // Hora de vuelo
    char FechaVuelo[7];               // Fecha del vuelo
    int Estado;                       // Estado - 0 = programado, 1 = realizado
    struct Vuelo *Sgte;               // Puntero al siguiente vuelo de la lista
    struct Pasajeros *ListaPasajeros; // Puntero a la lista de pasajeros asignada para este vuelo
};

typedef struct Vuelo *DatosVuelo; // Creación del alias "DatosVuelo", puntero a un struct "Vuelo"

struct Pasajeros // Definición de la estructura "Pasajeros"
{
    char Cedula[20];        // Número de cédula
    char NombrePersona[20]; // Nombre de la persona
    char Telefono[20];      // Teléfono de la persona
    int Estado;             // Estado - 1 = reservado, 2 = a bordo
    struct Pasajeros *Sgte; // Puntero al siguiente pasajero de la sublista
};

typedef struct Pasajeros *DatosPasajero; // Creación del alias "DatosPasajero", puntero a un struct "Pasajeros"

char cadena[20]; // Variable temporal de cadena, que se usará para leer algunos datos

void AbrirArchivoVuelo(DatosVuelo &Vuelos) // Se crea la función "AbrirArchivo", que recibe como argumento la lista de vuelos
{
    DatosVuelo Aux;          // Declara un puntero auxiliar que se usará para crear nuevos nodos de vuelo
    ifstream leer;           // Se crea un objeto "ifstream" para manejar la lectura del archivo.
    leer.open("VUELOS.txt"); // Se intenta abrir el archivo "VUELOS.txt"

    if (leer.good()) // Si fue correcta su lectura...
    {
        cout << "El archivo fue abierto correctamente..." << endl; // Se envía un mensaje de éxito
    }
    else // De lo contrario...
    {
        cout << "El archivo no se pudo abrir..." << endl; // Se envía un mensaje de fallo y se corta la ejecución.
        return;
    }
    while (leer >> cadena)
    {
        Aux = new Vuelo;

        // Asigna el primer dato leído al campo NroDeVuelo
        strcpy(Aux->NroDeVuelo, cadena);

        // Lee y copia el origen
        leer >> Aux->Origen;

        // Lee y copia el destino
        leer >> Aux->Destino;

        // Lee y copia la matrícula del avión
        leer >> Aux->MatriculaAvion;

        // Lee y copia el nombre del piloto
        leer >> Aux->NombrePiloto;

        // Lee y copia la hora del vuelo
        leer >> Aux->HoraVuelo;

        // Lee y copia la fecha del vuelo
        leer >> Aux->FechaVuelo;

        // Lee el estado y lo asigna directamente (como int)
        leer >> Aux->Estado;

        // Enlaza el nuevo nodo al inicio de la lista
        Aux->Sgte = Vuelos;
        Vuelos = Aux;
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

void AñadirVuelo(DatosVuelo &Vuelos)
{
    DatosVuelo t, q = new (struct Vuelo);

    char NroDeVuelo[20];     // Número de vuelo
    char Origen[20];         // Origen de vuelo
    char Destino[20];        // Destino de vuelo
    char MatriculaAvion[20]; // Matrícula del avió
    char NombrePiloto[20];   // Nombre del piloto
    char HoraVuelo[20];      // Hora de vuelo
    char FechaVuelo[20];     // Fecha del vuelo
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
    q->Estado=Estado;
    

    if (Vuelos == NULL)
    {
        Vuelos = q;
    }
    else
    {
        t = Vuelos;
        while (t->Sgte != NULL)
        {
            t = t->Sgte;
        }
        t->Sgte = q;
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

bool VueloExiste(DatosVuelo Vuelos, char numero[7]){
    DatosVuelo aux = Vuelos;

    while(aux != NULL){
        if(aux->NroDeVuelo == numero) return true;
        aux=aux->Sgte;
    }

    return false;
}

void AñadirPasajeros(DatosVuelo &Vuelos){

    DatosVuelo aux = Vuelos;

    char nro[7];
    cout<<"\nIngrese el numero del vuelo";
    cin>>nro;

    if(!VueloExiste(aux, nro)){
        cout<<"El vuelo no existe. Regresando."<<endl;
    }
    else{
        //TODO: Avanzar desde acá
    }
    
}

int main()
{
    DatosVuelo Vuelos = NULL;
    DatosPasajero Personas = NULL;
    int Op;
    int Dato;
    int Pos;
    int X;
    AbrirArchivoVuelo(Vuelos);
    MostrarVuelos(Vuelos);
    AñadirVuelo(Vuelos);
    MostrarVuelos(Vuelos);
}
