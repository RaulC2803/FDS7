#include "DataFrame.h"
#include "Menu.h"

int main()
{
	int Opcion = 0;
	Menu(Opcion);
	if (Opcion == 1) {
		DataFrame* P = new DataFrame;

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
	}
	return 0;
}