#include "DataFrame.h"

int main()
{
	DataFrame* P = new DataFrame;
	P->GenerarDatos();

	string nombreArchivo;

	while (true) {

		do {
			cout << "Ingresa el archivo que quiere abrir: "; cin >> nombreArchivo;
		} while (!P->LecturaDatos(nombreArchivo));

		P->MostrarFilas();

		P->Ordenar("nombre");
		cout << "\n\n\n";

		P->MostrarFilas();

		system("pause>0");
		system("cls");
	}
	return 0;
}