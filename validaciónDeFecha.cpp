#include <iostream>
#include <locale.h>

using namespace std;


/*
    Estructua "fecha"
        Contiene 3 datos enteros, que equivalen al día,
        el mes y el año de la fecha.
*/

struct fecha {
	int day;
	int month;
	int year;
};

/*
    Función booleana "validarFecha"
        Recibe como tipo de dato una fecha (previamente definida)
        y devuelve un valor booleano (falso o verdadero).
        
        Hace una serie de comprobaciones para verificar si es válida.
            1. Verifica si es bisiesto con una serie de comparaciones.
            2. Haciendo uso de un switch con respecto al mes, verifica
            si el día está entre el rango posible dependiendo de su mes.
            Si lo está, devuelve verdadero, y si no, devuelve falso.
*/

bool validarFecha(fecha f) {

	bool esBisiesto;

	if((f.year%4==0 && f.year%100!=0) || f.year%400==0 ) {
		esBisiesto = true;
	}
	else {
		esBisiesto = false;
	}

	switch (f.month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if(f.day > 0 && f.day <= 31) {
			return true;
		}
		else {
			return false;
		}
	case 2:
		if((esBisiesto && (f.day > 0 && f.day <= 29)) ||(!esBisiesto && (f.day > 0 && f.day <= 28)) ) {
			return true;
		}
		else {
			return false;
		}
	case 4:
	case 6:
	case 9:
	case 11:
		if(f.day > 0 && f.day <= 30) {
			return true;
		}
		else {
			return false;
		}
	default:
		return false;
	}
}

/*
    Función principal
        Crea un dato de timpo fecha, le pide al usuario sus
        valores y realiza una comprobación para verificar si
        es o no válido, y muestra un mensaje de confirmación.
*/
    

int main() {
	setlocale(LC_ALL, "Spanish");
	
	fecha f;
	cout<<"Ingrese el dia"<<endl;
	cin>>f.day;
	cout<<"Ingrese el mes"<<endl;
	cin>>f.month;
	cout<<"Ingrese el año"<<endl;
	cin>>f.year;

	if(validarFecha (f)) cout<<"Fecha válida"<<endl;
	else cout<<"Fecha inválida"<<endl;
}
