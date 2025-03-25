#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

struct Vuelo
{
	char NroDeVuelo[7];
	char Origen[9];
	char Destino[9];
	char MatriculaAvion[7];
	char NombrePiloto[20];
	char HoraVuelo[5];
	char FechaVuelo[7];
	int Estado;
	struct Vuelo *Sgte;
	struct Pasajeros *ListaPasajeros;
};typedef struct Vuelo *DatosVuelo;

struct Pasajeros
{
	char Cedula[10];
	char NombrePersona[20];
	char Telefono[10];
	int Estado;
	struct Pasajeros *Sgte;
};typedef struct Pasajeros *DatosPasajero;

char cadena[20];

/*
Nombre del proceso: AbrirArchivo(DatosVuelo &Vuelos)
Objetivo:       Extraer de un fichero la informacion y organizarla en listas
Parametros:     DatosVuelo &Vuelos, La lista de los vuelos donde se va a guardar la informacion
Retorna:        Deja en la Lista los datos de los vuelos
Ejemplo:        (En el archivo)
                123456 MED BOG 222222 FELIPEMONTENEGRO 0900 200421 0
                (En la lista)
                Vuelos->NroDeVuelo = 123456
                Vuelos->Origen= MED
                Vuelos->Destino= BOG
                Vuelos->MatriculaAvion= 222222
                Vuelos->NombrePiloto= FELIPEMONTENEGRO
                Vuelos->HoraVuelo= 0900
                Vuelos->FechaVuelo= 200421
                Vuelos->Estado= 0
*/

void AbrirArchivo(DatosVuelo &Vuelos)
{
	DatosVuelo Aux;
    int i;
	ifstream leer;
	leer.open ("VUELOS.txt");

	if (leer.good())
	{
		cout<<"El archivo fue abierto correctamente..."<<endl;
	}
	else
	{
		cout<<"El archivo no se pudo abrir..."<<endl;
		return;
	}

	while(!leer.eof()){
		Aux = new(Vuelo);
		leer>>cadena;
		strcpy(Aux->NroDeVuelo,cadena);
    	fflush(stdin);
      	leer>>cadena;
	  	strcpy(Aux->Origen,cadena);
      	fflush(stdin);
      	leer>>cadena;
      	strcpy(Aux->Destino,cadena);
      	fflush(stdin);
      	leer>>cadena;
		strcpy(Aux->MatriculaAvion,cadena);
    	fflush(stdin);
    	leer>>cadena;
      	strcpy(Aux->NombrePiloto,cadena);
      	fflush(stdin);
      	leer>>cadena;
	  	strcpy(Aux->HoraVuelo,cadena);
      	fflush(stdin);
      	leer>>cadena;
	  	strcpy(Aux->FechaVuelo,cadena);
      	fflush(stdin);
	  	leer>>cadena;
	  	Aux->Estado = atof(cadena);
	  	Aux->Sgte = Vuelos;
	  	Vuelos = Aux;
	}
	leer.close();
}

main()
{
    DatosVuelo Vuelos = NULL;
	DatosPasajero Persona= NULL;
	int Op;
	int Dato;
	int Pos;
	int X;
	AbrirArchivo(Vuelos);
}
