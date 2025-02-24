#include <iostream>
#include <locale.h>

using namespace std;

struct fecha {
	int day;
	int month;
	int year;
};

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
