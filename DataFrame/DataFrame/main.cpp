#include "DataFrame.h"

int main()
{
	Filas* P = new Filas;
	P->GenerarDatos();

	string nombreArchivo;

	while (true) {

		do {
			cout << "Ingresa el archivo que quiere abrir: "; cin >> nombreArchivo;
		} while (!P->LecturaDatos(nombreArchivo));

		P->Mostrar();

		system("pause>0");
		system("cls");
	}
	return 0;
}