#include "DataFrame.h"
#include "Menu.h"
#include <map>

void Interacción()
{
	int Opcion = 0;
	Menu(Opcion);

	DataFrame* P = new DataFrame;
	string nombreArchivo;

	while (true)
	{
		switch (Opcion)
		{
		case 1:
			while (true) {

				do {
					cout << "Ingresa el archivo que quiere abrir: "; cin >> nombreArchivo;
				} while (!P->LecturaDatos(nombreArchivo));

				cout << "DATAFRAME CREADO EXITOSAMENTE";
				break;
			}
			break;

		case 2:
			P->MostrarData(); break;

		case 3:
			if (!P->getIsEmpty()) {
				P->GuardarDatos();
				cout << "DATAFRAME GUARDADO EXITOSAMENTE";
			}
			else { cout << "No ha igresado datos al DataFrame"; }
			break;

		default:
			break;
		}
		system("pause>0");
		system("cls");
		Opcion = 0;
		Menu(Opcion);
	}
}

int main()
{  
	map<string, float> m;
	m["hola"] = 10.5;
	
	Interacción();
	return 0;
}